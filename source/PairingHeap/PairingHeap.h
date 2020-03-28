#pragma once

#include <cassert>
#include <vector>

template<class V, class K> class PairingHeap;

/**
 * @brief Template for nodes of a pairing heap.
 *
 * Pairing heap nodes maintain pointers to their parent node, left and right 
 * sibling as well as one child node. 
 * 
 * They are associated with a key of type `K` and store some value of type `V`.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> 
struct Node
{
public:
    friend class PairingHeap<V, K>;

    /**
     * @brief Get the parent node.
     * 
     * @return A pointer to the parent node
     */
    Node<V, K>* getParent() 
    { 
        return parent; 
    }

    /**
     * @brief Gets the left sibling node.
     * 
     * @return A pointer to the left sibling node
     */
    Node<V, K>* getLeft() 
    { 
        return left; 
    }

    /**
     * @brief Gets the right sibling node.
     * 
     * @return A pointer to the right sibling node
     */
    Node<V, K>* getRight() 
    { 
        return right; 
    }

    /**
     * @brief Gets one child node.
     * 
     * @return A pointer to one child node
     */
    Node<V, K>* getChild() 
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

    bool hasChildren() 
    { 
        return child; 
    }

    bool hasParent() 
    { 
        return parent; 
    }

private:
    Node<V, K>* parent;
    Node<V, K>* left;
    Node<V, K>* right;
    Node<V, K>* child;

    V value;
    K key;
};

/**
 * @brief Template for pairing heap data structures.
 *
 * Pairing heaps generalize standard heap implementations such as binary heaps 
 * by extending a single tree to a forest of trees. 
 * 
 * This allows for insertions and merging in constant time as well as 
 * deletions in logarithmic time.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> 
class PairingHeap
{
private:
    Node<V, K>* forest;
    Node<V, K>* minPtr;
    int count;

public:
    /**
     * @brief Constructs a new pairing heap.
     * 
     */
    PairingHeap()
    {
        _init();
    }

    /**
     * @brief Destroys the pairing heap.
     *
     * Recursively deletes all nodes of all trees maintained by the heap.
     * 
     */
    virtual ~PairingHeap()
    {
        if (forest)
        {
            _deleteAll(forest);
        }
    }

    /**
     * @brief Builds a pairing heap from a set of values with associated keys.
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
    void build(std::vector<V>& elements, std::vector<K>& keys)
    {
        assert(elements.size() == keys.size());

        for (int i = 0; i < elements.size(); ++i)
        {
            insert(elements[i], keys[i]);
        }
    }

    /**
     * @brief Determines the current size of the pairing heap.
     * 
     * Runtime: \f$ O(1) \f$
     * 
     * @return The current size of the heap
     */
    int size()
    {
        return count;
    }

    /**
     * @brief Inserts a key-value-pair into the pairing heap.
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
    Node<V, K>* insert(V element, K key)
    {
        Node<V, K>* node = _singleton(element, key);
        _newTree(node);

        ++count;

        return node;
    }

    /**
     * @brief Determines the value of the node with the smallest key.
     * 
     * Runtime: \f$ O(1) \f$
     * 
     * @return Value of the smallest element
     */
    V min()
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
    V deleteMin()
    {
        assert(size());

        V value = minPtr->getValue();

        _deleteMin();

        count--;
        
        return value;
        
    }

    /**
     * @brief Removes a given node from the pairing heap.
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
    V remove(Node<V, K>* handle)
    {
        decreaseKey(handle, minPtr->getKey() - 1);

        deleteMin();
    }

    /**
     * @brief Decreases the key of a given heap node.
     * 
     * Runtime: \f$ O(\log \log n) \leq T \leq O(\log n) \f$
     *
     * @param handle Pointer to the heap node 
     * @param key New key value of the heap node
     */
    void decreaseKey(Node<V, K>* handle, K key)
    {
        if (key < handle->getKey())
        {
            _decreaseKey(handle, key);
        }
    }

    /**
     * @brief Merges two instances of pairing heaps.
     * 
     * The new forest becomes the union of both forests.
     *
     * Runtime: \f$ O(1) \f$
     *
     * @param other Pointer to the pairing heap to merge with
     */
    void merge(PairingHeap<V, K>* other)
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
    Node<V, K>* getForest()
    {
        return forest;
    }

    /**
     * @brief Gets the node with the smallest key.
     * 
     * @return A pointer to the smallest element
     */
    Node<V, K>* getMinPtr()
    {
        return minPtr;
    }

private:
    void _init();

    void _deleteAll(Node<V, K>* handle);

    Node<V, K>* _singleton(V element, K key);

    void _newTree(Node<V, K>* handle);

    void _cut(Node<V, K>* handle);

    void _link(Node<V, K>* a, Node<V, K>* b);

    Node<V, K>* _union(Node<V, K>* a, Node<V, K>* b);

    void _pairWiseUnion();

    void _updateMinPtr();

    void _deleteMin();

    void _decreaseKey(Node<V, K>* handle, K key);

    void _insertForest(Node<V, K>* other);
};

#include <PairingHeap/PairingHeap.hpp>