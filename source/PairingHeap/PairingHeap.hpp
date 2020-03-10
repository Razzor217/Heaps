template<class V, class K>
void PairingHeap<V, K>::_init()
{
    forest = NULL;
    minPtr = NULL;
    count = 0;
}

template<class V, class K>
void PairingHeap<V, K>::_deleteAll(Node<V, K>* handle)
{
    if (handle)
    {
        Node<V, K>* current = handle;
        do 
        {
            Node<V, K>* node = current;
            current = current->right;
            _deleteAll(node->child);
            delete node;
        }
        while (current != handle);
    }
}

template<class V, class K>
Node<V, K>* PairingHeap<V, K>::_singleton(V element, K key)
{
    Node<V, K>* node = new Node<V, K>;

    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->child = NULL;

    node->value = element;
    node->key = key;

    return node;
}

template<class V, class K>
void PairingHeap<V, K>::_newTree(Node<V, K>* handle)
{
    Node<V, K>* end = forest->left;
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
void PairingHeap<V, K>::_cut(Node<V, K>* handle)
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
void PairingHeap<V, K>::_link(Node<V, K>* a, Node<V, K>* b)
{

    b->left->right = b->right;
    b->right->left = b->left;

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
        b->left = b;
        b->right = b;

        b->parent = a;
    }
}

template<class V, class K>
void PairingHeap<V, K>::_union(Node<V, K>* a, Node<V, K>* b)
{
    assert(!a->parent);
    assert(!b->parent);

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
void PairingHeap<V, K>::_deleteMin()
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

    delete handle;

    // perform pair-wise union operations on roots
    auto current = forest->right;
    do
    {
        auto node = current;
        current = current->right->right;

        _union(node, node->right);
    }
    while (current != forest && current != forest->right);

}

template<class V, class K>
void PairingHeap<V, K>::_decreaseKey(Node<V, K>* handle, K key)
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
void PairingHeap<V, K>::_insertForest(Node<V, K>* other)
{
    // insert other forest into heap
    Node<V, K>* end = forest->left;
    forest->left = other->left;
    other->left->right = forest;
    other->left = end;
    end->right = other;
}