#include <PairingHeap/PairingHeap.h>

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

    BOOST_CHECK_EQUAL(heap.getMinPtr()->getValue(), -3);
    BOOST_CHECK_EQUAL(heap.getMinPtr()->getKey(), -3);
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

    BOOST_CHECK_EQUAL(heap.getMinPtr()->getValue(), -3);
    BOOST_CHECK_EQUAL(heap.getMinPtr()->getKey(), -3);
}