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