#pragma once

#include "../interface/IHeap.h"

template<class V> class PairingHeap;

template<class V> 
struct PNode : public INode<V> 
{
public:
    friend class PairingHeap<V>;

    PNode<V>* getParent() 
    { 
        return parent; 
    }

    PNode<V>* getLeft() 
    { 
        return left; 
    }

    PNode<V>* getRight() 
    { 
        return right; 
    }

    PNode<V>* getChild() 
    { 
        return child; 
    }

    V getValue() 
    { 
        return value; 
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
    PNode<V>* parent;
    PNode<V>* left;
    PNode<V>* right;
    PNode<V>* child;

    V value;
};

template<class V> 
class PairingHeap : public IHeap<V>
{
private:
    PNode<V>* forest;
    PNode<V>* minPtr;
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

    void build(std::vector<V>& elements) override
    {
        for (auto e : elements)
        {
            insert(e);
        }
    }

    int size() override
    {
        return count;
    }

    INode<V>* insert(V element) override
    {
        PNode<V>* node = _singleton(element);
        _newTree(node);
    }

    V min() override
    {
        return minPtr->getValue();
    }

    V deleteMin() override;

    V remove(INode<V>* handle) override;

    void decreaseKey(INode<V>* handle, V key) override;

    void merge(IHeap<V>* other) override;

private:
    void _init();

    void _deleteAll(PNode<V>* handle);

    PNode<V>* _singleton(V element);

    void _newTree(PNode<V>* handle);
};

#include "PairingHeap.hpp"