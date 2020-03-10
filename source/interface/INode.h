#pragma once

template<class V, class K> struct INode
{
public: 
    virtual bool hasChildren() = 0;
    
    virtual bool hasParent() = 0;
};