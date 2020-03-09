template<class V>
void PairingHeap<V>::_init()
{
    forest = NULL;
    minPtr = NULL;
    count = 0;
}

template<class V>
void PairingHeap<V>::_deleteAll(PNode<V>* handle)
{
    if (handle)
    {
        PNode<V>* current = handle;
        do 
        {
            PNode<V>* node = current;
            current = current->right;
            _deleteAll(node->child);
            delete node;
        }
        while (current != handle);
    }
}

template<class V>
PNode<V>* PairingHeap<V>::_singleton(V element)
{
    PNode<V>* node = new PNode<V>;

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->child = NULL;

    node->value = element;

    return node;
}

template<class V>
void PairingHeap<V>::_newTree(PNode<V>* handle)
{
    PNode<V>* end = forest->left;
    forest->left = handle;
    handle->left = end;
    handle->right = forest;
    end->right = handle;

    if (handle->value < minPtr->value)
    {
        minPtr = handle;
    }
}

template<class V>
void PairingHeap<V>::_cut(PNode<V>* handle)
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

template<class V>
void PairingHeap<V>::_link(PNode<V>* a, PNode<V>* b)
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

template<class V>
void PairingHeap<V>::_union(PNode<V>* a, PNode<V>* b)
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