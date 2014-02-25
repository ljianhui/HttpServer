#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <list>

using std::list;
class Object;
typedef list<Object*> ObjectList;

class Object
{
    public:
        virtual ~Object();

        void setParent(Object *parent);
        inline const ObjectList& getChildern()const;
        inline const Object* getParent()const;

    protected:
        explicit Object(Object *parent = NULL);
        Object(const Object &obj);
        Object& operator=(const Object &obj);

    private:
        inline void _appendObjectList(Object *parent);

        ObjectList childern;
        Object *this_parent;
};

void Object::_appendObjectList(Object *parent)
{
    this_parent = parent;
    if(this_parent != NULL)
        this_parent->childern.push_back(this);
}

const ObjectList& Object::getChildern()const
{
    return childern;
}

const Object* Object::getParent()const
{
    return this_parent;
}


#endif // OBJECT_H_INCLUDED
