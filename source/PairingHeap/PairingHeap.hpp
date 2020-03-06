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
void PairingHeap<V>::_newTree(PNode<V>* node)
{
    PNode<V>* end = forest->left;
    forest->left = node;
    node->left = end;
    node->right = forest;
    end->right = node;

    if (node->value < minPtr->value)
    {
        minPtr = node;
    }
}