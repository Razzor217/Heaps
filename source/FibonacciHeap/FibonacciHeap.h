#pragma once

#include <interface/IHeap.h>

template<class V, class K> class FibonacciHeap;

/**
 * @brief Template for nodes of a fibonacci heap.
 *
 * Fibonacci heap nodes maintain pointers to their parent node, left and right 
 * sibling as well as one child node. 
 * 
 * They are associated with a key of type `K` and store some value of type `V`.
 * Furthermore, they mantain a rank and may be marked.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> 
struct FNode : public INode<V, K> 
{
public:
    friend class FibonacciHeap<V, K>;

    /**
     * @brief Get the parent node.
     * 
     * @return A pointer to the parent node
     */
    FNode<V, K>* getParent() 
    { 
        return parent; 
    }

    /**
     * @brief Gets the left sibling node.
     * 
     * @return A pointer to the left sibling node
     */
    FNode<V, K>* getLeft() 
    { 
        return left; 
    }

    /**
     * @brief Gets the right sibling node.
     * 
     * @return A pointer to the right sibling node
     */
    FNode<V, K>* getRight() 
    { 
        return right; 
    }

    /**
     * @brief Gets one child node.
     * 
     * @return A pointer to one child node
     */
    FNode<V, K>* getChild() 
    { 
        return child; 
    }

    /**
     * @brief Gets the value of the heap node.
     * 
     * @return The value stored in the heap node
     */
    V getValue() 
    { 
        return value; 
    }

    /**
     * @brief Gets the key associated with the heap node.
     * 
     * @return The key associated with the heap node
     */
    K getKey()
    {
        return key;
    }

    /**
     * @brief Get the rank associated with the heap node.
     * 
     * @return The rank of the heap node.
     */
    int getRank() 
    { 
        return rank; 
    }

    /**
     * @brief Checks whether the heap node is marked.
     * 
     * @return true if the node is marked, false otherwise
     */
    bool isMarked() 
    { 
        return marked; 
    }

    bool hasChildren() override 
    { 
        return child; 
    }

    bool hasParents() override 
    { 
        return parent; 
    }

private:
    FNode* parent;
    FNode* left;
    FNode* right;
    FNode* child;

    V value;
    K key;

    int rank;
    bool marked;
};

/**
 * @brief Template for fibonacci heap data structures.
 *
 * Fibonacci heaps specialize pairing heaps by refining operations in order to 
 * maintain balanced trees within the forest.
 * 
 * This results in amortized logarithmic time for deletions and amortized 
 * constant time for every other operation.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> 
class FibonacciHeap : public IHeap<V, K>
{
private:
    FNode<V, K>* forest;
    FNode<V, K>* minPtr;
    int count;

public:
    /**
     * @brief Constructs a new fibonacci heap.
     * 
     */
    FibonacciHeap()
    {
        _init();
    }

    /**
     * @brief Destroys the fibonacci heap.
     *
     * Recursively deletes all nodes of all trees maintained by the heap.
     * 
     */
    virtual ~FibonacciHeap()
    {
        if (forest)
        {
            _deleteAll(forest);
        }
    }

    /**
     * @brief Builds a fibonacci heap from a set of values with associated keys.
     *
     * Both sets must have the same length. This implementation assumes that 
     * the following property holds for all indices `i`:
     *
     * `key[i]` is the key associated with `elements[i]`.
     *
     * This implementation inserts every key-value-pair separately. 
     * 
     * Runtime: \f$ O(\log n)\f$
     * 
     * @param elements 
     * @param keys 
     */
    void build(std::vector<V>& elements, std::vector<K>& keys) override
    {
        assert(elements.size() == keys.size());

        for (int i = 0; i < elements.size(); ++i)
        {
            insert(elements[i], keys[i]);
        }

        ++count;
    }

    /**
     * @brief Determines the current size of the fibonacci heap.
     * 
     * Runtime: \f$ O(1) \f$
     * 
     * @return The current size of the heap
     */
    int size() override
    {
        return count;
    }

    /**
     * @brief Inserts a key-value-pair into the fibonacci heap.
     *
     * This implementation inserts a key-value-pair by inserting a new node 
     * as a new tree into the forest.
     * 
     * Runtime: \f$ O(1) \f$
     * 
     * @param element Value to insert
     * @param key Key associated with `value`
     * @return A pointer to the resulting pairing heap node
     */
    INode<V, K>* insert(V element, K key) override
    {
        FNode<V, K>* handle = _singleton(element);
        _newTree(handle);

        ++count;

        return handle;
    }

    /**
     * @brief Determines the value of the node with the smallest key.
     * 
     * Runtime: \f$ O(1) \f$
     * 
     * @return Value of the smallest element
     */
    V min() override
    {
        return minPtr->getValue();
    }

    /**
     * @brief Deletes the heap node with smallest key and returns its value.
     * 
     * Runtime: \f$ O(\log n) \f$ amortized
     *
     * @return The value of the smallest element
     */
    V deleteMin() override
    {
        V value = minPtr->getValue();

        _deleteMin();

        count = (count > 0) ? count-- : 0;

        return value;
    }

    /**
     * @brief Removes a given node from the fibonacci heap.
     *
     * The key associated with the node is first decreased such that the new key
     * is smaller than any other key. Afterwards, the element with smallest key,
     * i.e. the given node, is deleted.
     * 
     * Runtime: \f$ O(\log n) \f$ amortized
     * 
     * @param handle Pointer to the node to remove
     * @return Value of the deleted node
     */
    V remove(INode<V, K>* handle) override
    {
        decreaseKey(handle, minPtr->getKey() - 1);

        deleteMin();
    }

    /**
     * @brief Decreases the key of a given heap node.
     * 
     * Runtime: \f$ O(1) \f$ amortized
     *
     * @param handle Pointer to the heap node 
     * @param key New key value of the heap node
     */
    void decreaseKey(INode<V, K>* handle, V key) override
    {
        if (key < handle->getKey())
        {
            _decreaseKey(handle, key);
        }
    }

    /**
     * @brief Merges two instances of fibonacci heaps.
     * 
     * The new forest becomes the union of both forests.
     *
     * Runtime: \f$ O(1) \f$
     *
     * @param other Pointer to the fibonacci heap to merge with
     */
    void merge(IHeap<V, K>* other) override
    {
        if (other->getMinPtr()->getKey() < minPtr->getKey())
        {
            minPtr = other->getMinPtr();
        }

        _insertForest(other->getForest());
        other->getForest() = NULL;
    }

    /**
     * @brief Gets the forest of trees.
     * 
     * @return A pointer to the first tree in the forest.
     */
    FNode<V, K>* getForest()
    {
        return forest;
    }

    /**
     * @brief Gets the node with the smallest key.
     * 
     * @return A pointer to the smallest element
     */
    FNode<V, K>* getMinPtr()
    {
        return minPtr;
    }

private:
    void _init();

    void _deleteAll(FNode<V, K>* handle);

    FNode<V, K>* _singleton(V element, K key);

    void _newTree(FNode<V, K>* handle);

    void _cut(FNode<V, K>* handle);

    void _link(FNode<V, K>* a, FNode<V, K>* b);

    void _cascadingCut(FNode<V, K>* handle);

    void _unionByRank();

    void _insertByRank(std::vector<FNode<V, K>*>& ranks, FNode<V, K>* handle);

    void _deleteMin();

    void _decreaseKey(FNode<V, K>* handle, K key);

    void _insertForest(FNode<V, K>* other);
};

#include <FibonacciHeap/FibonacciHeap.hpp>