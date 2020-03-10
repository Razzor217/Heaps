#pragma once

#include "../interface/IHeap.h"

template<class V, class K> class PairingHeap;

template<class V, class K> 
struct PNode : public INode<V, K> 
{
public:
    friend class PairingHeap<V, K>;

    PNode<V, K>* getParent() 
    { 
        return parent; 
    }

    PNode<V, K>* getLeft() 
    { 
        return left; 
    }

    PNode<V, K>* getRight() 
    { 
        return right; 
    }

    PNode<V, K>* getChild() 
    { 
        return child; 
    }

    V getValue() 
    { 
        return value; 
    }

    K getKey()
    {
        return key;
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
    PNode<V, K>* parent;
    PNode<V, K>* left;
    PNode<V, K>* right;
    PNode<V, K>* child;

    V value;
    K key;
};

template<class V, class K> 
class PairingHeap : public IHeap<V, K>
{
private:
    PNode<V, K>* forest;
    PNode<V, K>* minPtr;
    int count;

public:
    PairingHeap()
    {
        _init();
    }

    virtual ~PairingHeap()
    {
        if (forest)
        {
            _deleteAll(forest);
        }
    }

    void build(std::vector<V, K>& elements, std::vector<K>& keys) override
    {
        for (int i = 0; i < elements.size(); ++i)
        {
            insert(elements[i], keys[i]);
        }
    }

    int size() override
    {
        return count;
    }

    INode<V, K>* insert(V element, K key) override
    {
        PNode<V, K>* node = _singleton(element, key);
        _newTree(node);

        return node;
    }

    V min() override
    {
        return minPtr->getValue();
    }

    V deleteMin() override
    {
        V value = minPtr->getValue();
        
    }

    V remove(INode<V, K>* handle) override;

    void decreaseKey(INode<V, K>* handle, K key) override
    {
        if (key < handle->getKey())
        {
            _decreaseKey(handle, key);
        }
    }

    void merge(IHeap<V, K>* other) override
    {
        if (other->getMinPtr()->getKey() < minPtr->getKey())
        {
            minPtr = other->getMinPtr();
        }
        _insertForest(other->getForest());
        other->getForest() = NULL;
    }

    PNode<V, K>* getForest()
    {
        return forest;
    }

    PNode<V, K>* getMinPtr()
    {
        return minPtr;
    }

private:
    void _init();

    void _deleteAll(PNode<V, K>* handle);

    PNode<V, K>* _singleton(V element, K key);

    void _newTree(PNode<V, K>* handle);

    void _cut(PNode<V, K>* handle);

    void _link(PNode<V, K>* a, PNode<V, K>* b);

    void _union(PNode<V, K>* a, PNode<V, K>* b);

    void _decreaseKey(PNode<V, K>* handle, K key);

    void _insertForest(PNode<V, K>* other);
};

#include "PairingHeap.hpp"