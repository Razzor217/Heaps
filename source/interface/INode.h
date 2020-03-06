#pragma once

template<class V> struct INode
{
public: 
    virtual bool hasChildren() = 0;
    
    virtual bool hasParent() = 0;
};