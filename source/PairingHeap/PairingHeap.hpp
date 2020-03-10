template<class V, class K>
void PairingHeap<V, K>::_init()
{
    forest = NULL;
    minPtr = NULL;
    count = 0;
}

template<class V, class K>
void PairingHeap<V, K>::_deleteAll(PNode<V, K>* handle)
{
    if (handle)
    {
        PNode<V, K>* current = handle;
        do 
        {
            PNode<V, K>* node = current;
            current = current->right;
            _deleteAll(node->child);
            delete node;
        }
        while (current != handle);
    }
}

template<class V, class K>
PNode<V, K>* PairingHeap<V, K>::_singleton(V element, K key)
{
    PNode<V, K>* node = new PNode<V, K>;

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->child = NULL;

    node->value = element;
    node->key = key;

    return node;
}

template<class V, class K>
void PairingHeap<V, K>::_newTree(PNode<V, K>* handle)
{
    PNode<V, K>* end = forest->left;
    forest->left = handle;
    handle->left = end;
    handle->right = forest;
    end->right = handle;

    if (handle->value < minPtr->value)
    {
        minPtr = handle;
    }
}

template<class V, class K>
void PairingHeap<V, K>::_cut(PNode<V, K>* handle)
{
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
void PairingHeap<V, K>::_link(PNode<V, K>* a, PNode<V, K>* b)
{
    if (a->hasChildren())
    {
        // insert b as child at end of children
        auto end = a->child->left;
        b->left = end;
        a->child->left = b;
        b->right = a->child;
        end->right = b;

        b->parent = a;
    }
    else
    {
        a->child = b;
        b->parent = a;
    }
}

template<class V, class K>
void PairingHeap<V, K>::_union(PNode<V, K>* a, PNode<V, K>* b)
{
    if (a->value < b->value)
    {
        _link(a, b);
    }
    else
    {
        _link(b, a);
    }
}

template<class V, class K>
void PairingHeap<V, K>::_decreaseKey(PNode<V, K>* handle, K key)
{
    handle->key = key;

    /*
     * cut subtree rooted at handle if handle is not a root
     * otherwise update minPtr
     */
    if (handle->parent)
    {
        _cut(handle);
    }
    else
    {
        if (key < minPtr->key)
        {
            minPtr = handle;
        }
    }
}

template<class V, class K>
void PairingHeap<V, K>::_insertForest(PNode<V, K>* other)
{
    // insert other forest into heap
    PNode<V, K>* end = forest->left;
    forest->left = other->left;
    other->left->right = forest;
    other->left = end;
    end->right = other;
}