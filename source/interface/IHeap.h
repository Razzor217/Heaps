#pragma once

#include "INode.h"

#include <vector>

template<class V, class K> class IHeap
{
public:
    virtual void build(std::vector<V>& elements, std::vector<K>& keys) = 0;

    virtual int size() = 0;

    virtual INode<V, K>* insert(V element, K key) = 0;

    virtual V min() = 0;

    virtual V deleteMin() = 0;

    virtual V remove(INode<V, K>* handle) = 0;

    virtual void decreaseKey(INode<V, K>* handle, K key) = 0;

    virtual void merge(IHeap<V, K>* other) = 0;
};