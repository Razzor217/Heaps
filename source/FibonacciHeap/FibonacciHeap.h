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
    FibonacciHeap()
    {

    }

    virtual ~FibonacciHeap()
    {
        if (forest)
        {

        }
    }

    void build(std::vector<V, K> elements) override;

    int size() override;

    INode<V, K>* insert(V element) override;

    V min() override;

    V deleteMin() override;

    V remove(INode<V, K>* handle) override;

    void decreaseKey(INode<V, K>* handle, V key) override;

    void merge(IHeap<V, K>* other) override;

private:
    FNode<V, K>* forest;
    FNode<V, K>* minPtr;
    int count;
};