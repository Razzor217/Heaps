#pragma once

#include "../interface/IHeap.h"

template<class V> class FibonacciHeap;

template<class V> 
struct FNode : public INode<V> 
{
public:
    friend class FibonacciHeap<V>;

    FNode<V>* getParent() 
    { 
        return parent; 
    }

    FNode<V>* getLeft() 
    { 
        return left; 
    }

    FNode<V>* getRight() 
    { 
        return right; 
    }
    FNode<V>* getChild() 
    { 
        return child; 
    }
    V getValue() 
    { 
        return value; 
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
    int rank;
    bool marked;
};

template<class V> 
class FibonacciHeap : public IHeap<V>
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

    void build(std::vector<V> elements) override;

    int size() override;

    INode<V>* insert(V element) override;

    V min() override;

    V deleteMin() override;

    V remove(INode<V>* handle) override;

    void decreaseKey(INode<V>* handle, V key) override;

    void merge(IHeap<V>* other) override;

private:
    FNode<V>* forest;
    FNode<V>* minPtr;
    int count;
};