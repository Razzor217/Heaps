#pragma once

#include "INode.h"

#include <vector>

template<class V> class IHeap
{
public:
    virtual void build(std::vector<V>& elements) = 0;

    virtual int size() = 0;

    virtual INode<V>* insert(V element) = 0;

    virtual V min() = 0;

    virtual V deleteMin() = 0;

    virtual V remove(INode<V>* handle) = 0;

    virtual void decreaseKey(INode<V>* handle, V key) = 0;

    virtual void merge(IHeap<V>* other) = 0;
};