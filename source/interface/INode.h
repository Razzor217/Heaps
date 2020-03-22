#pragma once

/**
 * @brief Template interface for elements (nodes) of heap data structures.
 * 
 * @tparam V Template parameter for value types
 * @tparam K Template parameter for key types
 */
template<class V, class K> struct INode
{
public: 
    /**
     * @brief Checks whether a heap node has any child nodes.
     * 
     * @return true if the node has any children, false otherwise
     */
    virtual bool hasChildren() = 0;
    
    /**
     * @brief Checks whether a heap node has a parent node.
     * 
     * @return true if the node has a parent node, false otherwise
     */
    virtual bool hasParent() = 0;
};