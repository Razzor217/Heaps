#pragma once

#include "../interface/IHeap.h"

template<class V, class K> class FibonacciHeap;

template<class V, class K> 
struct FNode : public INode<V, K> 
{
public:
    friend class FibonacciHeap<V, K>;

    FNode<V, K>* getParent() 
    { 
        return parent; 
    }

    FNode<V, K>* getLeft() 
    { 
        return left; 
    }

    FNode<V, K>* getRight() 
    { 
        return right; 
    }
    FNode<V, K>* getChild() 
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

    int getRank() 
    { 
        return rank; 
    }

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

template<class V, class K> 
class FibonacciHeap : public IHeap<V, K>
{
private:
    FNode<V, K>* forest;
    FNode<V, K>* minPtr;
    int count;

public:
    FibonacciHeap()
    {
        _init();
    }

    virtual ~FibonacciHeap()
    {
        if (forest)
        {
            _deleteAll(forest);
        }
    }

    void build(std::vector<V>& elements, std::vector<K>& keys) override
    {
        assert(elements.size() == keys.size());

        for (int i = 0; i < elements.size(); ++i)
        {
            insert(elements[i], keys[i]);
        }

        ++count;
    }

    int size() override
    {
        return count;
    }

    INode<V, K>* insert(V element, K key) override
    {
        FNode<V, K>* handle = _singleton(element);
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

    void decreaseKey(INode<V, K>* handle, V key) override
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

    FNode<V, K>* getForest()
    {
        return forest;
    }

    FNode<V, K>* getMinPtr()
    {
        return minPtr;
    }

private:
    void _init();

    void _deleteAll();

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