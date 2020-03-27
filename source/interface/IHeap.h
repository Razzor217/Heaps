#pragma once

#include <interface/INode.h>

#include <vector>

/**
 * @mainpage Heap Data Structures
 *
 * The API documentation of this implentation of heap data structures includes 
 * explanations and asymptotic behaviour of runtime (and or space requirements).
 */

/**
 * @brief Template interface for heap data structures.
 *
 * Any extension of this interface is required to provide implementations of 
 * all of the following methods.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> class IHeap
{
public:
    /**
     * @brief Builds a heap data structure from a set of values with associated keys.
     *
     * Usually implemented as a series of insertions.
     * 
     * @param elements Vector of values to insert
     * @param keys Vector of keys
     */
    virtual void build(std::vector<V>& elements, std::vector<K>& keys) = 0;

    /**
     * @brief Determines the current size of the heap data structure.
     * 
     * @return The current size of the heap
     */
    virtual int size() = 0;

    /**
     * @brief Inserts a key-value-pair into the heap data structure.
     * 
     * @param element Value to insert
     * @param key Key associated with `element`
     * @return A pointer to the resulting heap node
     */
    virtual INode<V, K>* insert(V element, K key) = 0;

    /**
     * @brief Determines the value of the heap node with smallest key.
     * 
     * @return The value of the smallest element
     */
    virtual V min() = 0;

    /**
     * @brief Deletes the heap node with smallest key and returns its value.
     * 
     * @return The value of the smallest element
     */
    virtual V deleteMin() = 0;

    /**
     * @brief Removes a given heap node from the data structure.
     * 
     * @param handle Pointer to the heap node to remove
     * @return Value of the deleted element
     */
    virtual V remove(INode<V, K>* handle) = 0;

    /**
     * @brief Decreases the key of a given heap node.
     * 
     * @param handle Pointer to the heap node 
     * @param key New key value of the heap node
     */
    virtual void decreaseKey(INode<V, K>* handle, K key) = 0;

    /**
     * @brief Merges two instances of heap data structures.
     * 
     * @param other Pointer to the heap to merge with
     */
    virtual void merge(IHeap<V, K>* other) = 0;
};