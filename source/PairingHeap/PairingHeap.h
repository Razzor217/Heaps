#pragma once

#include "../interface/IHeap.h"

template<class V, class K> class PairingHeap;

template<class V, class K> 
struct Node : public INode<V, K> 
{
public:
    friend class PairingHeap<V, K>;

    Node<V, K>* getParent() 
    { 
        return parent; 
    }

    Node<V, K>* getLeft() 
    { 
        return left; 
    }

    Node<V, K>* getRight() 
    { 
        return right; 
    }

    Node<V, K>* getChild() 
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
    Node<V, K>* parent;
    Node<V, K>* left;
    Node<V, K>* right;
    Node<V, K>* child;

    V value;
    K key;
};

template<class V, class K> 
class PairingHeap : public IHeap<V, K>
{
private:
    Node<V, K>* forest;
    Node<V, K>* minPtr;
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
        Node<V, K>* node = _singleton(element, key);
        _newTree(node);

        ++count;

        return node;
    }

    V min() override
    {
        return minPtr->getValue();
    }

    V deleteMin() override
    {
        V value = minPtr->getValue();

        _deleteMin();

        count = (count > 0) ? count-- : 0;

        return value;
    }

    V remove(INode<V, K>* handle) override
    {
        decreaseKey(handle, minPtr->getKey() - 1);

        deleteMin();
    }

    void decreaseKey(INode<V, K>* handle, K key) override
    {
        if (key < handle->getKey())
        {
            _decreaseKey(handle, key);
        }
    }

    void merge(PairingHeap<V, K>* other) override
    {
        if (other->getMinPtr()->getKey() < minPtr->getKey())
        {
            minPtr = other->getMinPtr();
        }

        _insertForest(other->getForest());
        other->getForest() = NULL;
    }

    Node<V, K>* getForest()
    {
        return forest;
    }

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

    void _union(Node<V, K>* a, Node<V, K>* b);

    void _deleteMin();

    void _decreaseKey(Node<V, K>* handle, K key);

    void _insertForest(Node<V, K>* other);
};

#include "PairingHeap.hpp"