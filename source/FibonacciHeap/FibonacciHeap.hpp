template<class V, class K>
void FibonacciHeap<V, K>::_init()
{
    forest = NULL;
    minPtr = NULL;
    count = 0;
}

template<class V, class K>
void FibonacciHeap<V, K>::_deleteAll(FNode<V, K>* handle)
{
    if (handle)
    {
        FNode<V, K>* current = handle;
        do 
        {
            FNode<V, K>* node = current;
            current = current->right;
            _deleteAll(node->child);
            delete node;
        }
        while (current != handle);
    }
}

template<class V, class K>
FNode<V, K>* FibonacciHeap<V, K>::_singleton(V element, K key)
{
    FNode<V, K>* node = new FNode<V, K>;

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->child = NULL;

    node->value = element;
    node->key = key;

    node->rank = 0;
    node->marked = false;

    return node;
}

template<class V, class K>
void FibonacciHeap<V, K>::_newTree(FNode<V, K>* handle)
{
    if (!forest)
    {
        forest = handle;
    }
    else
    {
        FNode<V, K>* end = forest->left;
        forest->left = handle;
        handle->left = end;
        handle->right = forest;
        end->right = handle;
    }
    
    if (!minPtr || handle->key < minPtr->key)
    {
        minPtr = handle;
    }
}

template<class V, class K>
void FibonacciHeap<V, K>::_cut(FNode<V, K>* handle)
{
    // advance child pointer of parent
    if (handle->parent->child == handle)
    {
        handle->parent->child == handle->right;
    }

    // remove subtree rooted at handle
    handle->right->left = handle->left;
    handle->left->right = handle->right;
    handle->left = handle;
    handle->right = handle;

    handle->parent = NULL;

    // insert handle as new tree
    _newTree(handle);
}

template<class V, class K>
void FibonacciHeap<V, K>::_link(FNode<V, K>* a, FNode<V, K>* b)
{
    b->left->right = b->right;
    b->right->left = b->left;

    if (forest == b)
    {
        forest = a;
    }

    if (a->child)
    {
        // insert b as child at end of children
        auto end = a->child->left;
        b->left = end;
        a->child->left = b;
        b->right = a->child;
        end->right = b;
    }
    else
    {
        a->child = b;
        b->left = b;
        b->right = b;
    }

    b->parent = a;

    // increment rank of surviving root
    (a->rank)++;
}

template<class V, class K>
void FibonacciHeap<V, K>::_cascadingCut(FNode<V, K>* handle)
{
    // cut if handle is not a root
    if (handle->parent)
    {
        FNode<V, K>* parent = handle-> parent;
        handle->marked = false;

        _cut(handle);

        // cascading cuts
        if (parent->marked)
        {
            _cascadingCut(parent);
        }
        else
        {
            parent->marked = true;
        }
    }
    else 
    {
        // update min pointer
        if (handle->key < minPtr->key)
        {
            minPtr = handle;
        }
    }
}

template<class V, class K>
void FibonacciHeap<V, K>::_unionByRank()
{
    if (forest)
    {
        std::vector<FNode<V, K>*> ranks(count, NULL);

        FNode<V, K>* it = forest;
        do
        {
            _insertByRank(ranks, it);
        }
        while (it != forest);
    }
}

template<class V, class K>
void FibonacciHeap<V, K>::_insertByRank(
    std::vector<FNode<V, K>*>& ranks, FNode<V, K>* handle)
{
    /*
     * if there is a collision, 
     *  1. link nodes with same rank
     *  2. insert surviving root recursively
     */
    FNode<V, K>* collision = ranks[handle->rank];
    if (collision)
    {
        if (handle->key < collision->key)
        {
            _link(handle, collision);
            _insertByRank(ranks, handle);
        }
        else
        {
            _link(collision, handle);
            _insertByRank(ranks, collision);
        }
    }
    else
    {
         ranks[handle->rank] = handle;
    }
}

template<class V, class K>
void FibonacciHeap<V, K>::_updateMinPtr()
{
    if (forest)
    {
        // update min pointer
        auto current = forest->right;
        minPtr = forest;
        while (current != forest)
        {
            if (current->key < minPtr->key)
            {
                minPtr = current;
            }

            current = current->right;
        }
    }
    
}

template<class V, class K>
void FibonacciHeap<V, K>::_deleteMin()
{
    auto handle = minPtr;

    // connect siblings
    if (handle->left == handle || handle->right == handle)
    {
        handle->left = NULL;
        handle->right = NULL;
    }
    else
    {
        handle->left->right = handle->right;
        handle->right->left = handle->left;
    }

    // connect parent to next child
    if (handle->parent)
    {
        handle->parent->child = handle->right;
        handle->parent = NULL;
    }

    // add children as new trees
    if (handle->child)
    {
        auto current = handle->child;
        do
        {
            auto node = current;
            current = current->right;

            _newTree(node);
        }
        while (current != handle->child);
    }

    if (handle == forest)
    {
        forest = handle->right;
    }

    delete handle;

    _unionByRank();

    _updateMinPtr();
}

template<class V, class K>
void FibonacciHeap<V, K>::_decreaseKey(FNode<V, K>* handle, K key)
{
    handle->key = key;

    _cascadingCut(handle);
}

template<class V, class K>
void FibonacciHeap<V, K>::_insertForest(FNode<V, K>* other)
{
    // insert other forest into heap
    FNode<V, K>* end = forest->left;
    forest->left = other->left;
    other->left->right = forest;
    other->left = end;
    end->right = other;
}