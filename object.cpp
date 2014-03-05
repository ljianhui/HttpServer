#include "object.h"
#include <algorithm>

Object::Object(Object *parent):
    this_parent(parent)
{
    if(this_parent != NULL)
        this_parent->childern.push_back(this);
}

Object::Object(const Object &obj)
{
    _appendObjectList(obj.this_parent);
}

Object& Object::operator=(const Object &obj)
{
    if(this != &obj)
    {
        if(this_parent == NULL)
            _appendObjectList(obj.this_parent);
    }
    return *this;
}

Object::~Object()
{
    if(this_parent != NULL && this_parent != this)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
    }

    while(!childern.empty())
    {
        ObjectList::iterator it(childern.begin());
        delete *it;
    }
}

void Object::setParent(Object *parent)
{
    if(this_parent != NULL)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
    }
    _appendObjectList(parent);
}
