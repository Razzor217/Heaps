#include <PairingHeap/PairingHeap.h>

#include <algorithm>
#include <random>

#define BOOST_TEST_MODULE pairing_heap test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(constructorTest)
{
    PairingHeap<int, int> heap;

    // assert heap is empty

    BOOST_CHECK(!heap.getForest());
    BOOST_CHECK(!heap.getMinPtr());
    BOOST_CHECK_EQUAL(heap.size(), 0);
}

BOOST_AUTO_TEST_CASE(insertTest1)
{
    PairingHeap<int, int> heap;

    // insert one item

    auto node = heap.insert(5, 5);

    // check key / value

    BOOST_CHECK_EQUAL(node->getValue(), 5);
    BOOST_CHECK_EQUAL(node->getKey(), 5);

    // check size

    BOOST_CHECK_EQUAL(heap.size(), 1);

    // check whether min pointers are updated

    BOOST_CHECK(heap.getForest());
    BOOST_CHECK(heap.getMinPtr());

    BOOST_CHECK_EQUAL(heap.getMinPtr()->getValue(), 5);
    BOOST_CHECK_EQUAL(heap.getMinPtr()->getKey(), 5);

    BOOST_CHECK_EQUAL(heap.min(), 5);
}

BOOST_AUTO_TEST_CASE(insertTest2)
{
    PairingHeap<int, int> heap;

    /*
     * insert multiple items 
     * check size and min pointers
     */

    std::vector<int> elements = { 7, 2, 13, 24, 5, 87, 1, 23, -3, 19 };

    for (size_t i = 0; i < elements.size(); i++)
    {
        heap.insert(elements[i], elements[i]);

        BOOST_CHECK_EQUAL(heap.size(), i + 1);
    }

    BOOST_CHECK_EQUAL(heap.min(), -3);
}

BOOST_AUTO_TEST_CASE(buildTest1)
{
    PairingHeap<int, int> heap;

    /*
     * build heap from multiple items 
     * check size and min pointers
     */

    std::vector<int> elements = { 7, 2, 13, 24, 5, 87, 1, 23, -3, 19 };

    heap.build(elements, elements);

    BOOST_CHECK_EQUAL(heap.size(), elements.size());

    BOOST_CHECK_EQUAL(heap.min(), -3);
}

BOOST_AUTO_TEST_CASE(deleteMinTest1)
{
    PairingHeap<int, int> heap;

    // insert element

    heap.insert(5, 5);

    // deleteMin

    auto result = heap.deleteMin();

    // check result and size

    BOOST_CHECK_EQUAL(result, 5);
    BOOST_CHECK_EQUAL(heap.size(), 0);
}

BOOST_AUTO_TEST_CASE(deleteMinTest2)
{
    PairingHeap<int, int> heap;

    // insert two elements

    heap.insert(5, 5);
    heap.insert(3, 3);

    // deleteMin

    auto result = heap.deleteMin();

    // check result, size, min pointer

    BOOST_CHECK_EQUAL(result, 3);
    BOOST_CHECK_EQUAL(heap.size(), 1);
    BOOST_CHECK_EQUAL(heap.min(), 5);
}

BOOST_AUTO_TEST_CASE(deleteMinTest3)
{
    PairingHeap<int, int> heap;

    // insert two elements

    heap.insert(3, 3);
    heap.insert(5, 5);

    // deleteMin

    auto result = heap.deleteMin();

    // check result, size, min pointer

    BOOST_CHECK_EQUAL(result, 3);
    BOOST_CHECK_EQUAL(heap.size(), 1);
    BOOST_CHECK_EQUAL(heap.min(), 5);
}

BOOST_AUTO_TEST_CASE(sortTest1)
{
    PairingHeap<int, int> heap;

    int n = 100;

    std::vector<int> elements(n);
    for (int i = 0; i < n; ++i)
    {
        elements[i] = n - i;
    }

    // build heap from elements

    heap.build(elements, elements);

    // check size and min

    BOOST_CHECK_EQUAL(heap.size(), elements.size());
    BOOST_CHECK_EQUAL(heap.min(), 1);

    // delete min to obtain sorted vector

    // std::vector<int> result;
    // for (int i = 0; i < n; ++i)
    // {
    //     result.push_back(heap.deleteMin());
    // }

    // // check size, check whether result is sorted

    // BOOST_CHECK_EQUAL(heap.size(), 0);
    // BOOST_CHECK(std::is_sorted(result.begin(), result.end()));
}

BOOST_AUTO_TEST_CASE(sortTest2)
{
    PairingHeap<int, int> heap;

    int n = 100;

    std::vector<int> elements(n);
    
    // pseudo random number generator
    std::random_device seed;
    std::mt19937 rng(seed());
    std::uniform_int_distribution<> dist(-n, n);

    for (int i = 0; i < n; ++i)
    {
        elements[i] = dist(rng);
    }

    // build heap from random elements

    heap.build(elements, elements);

    // delete min to obtain sorted vector

    // std::vector<int> result;
    // for (int i = 0; i < n; ++i)
    // {
    //     result.push_back(heap.deleteMin());
    // }

    // // check size, check whether result is sorted

    // BOOST_CHECK_EQUAL(heap.size(), 0);
    // BOOST_CHECK(std::is_sorted(result.begin(), result.end()));
}
