#ifndef OBJECT_H
#define OBJECT_H

#include <list>

using std::list;
class Object;
typedef list<Object*> ObjectList;

class Object
{
    public:
        virtual ~Object();

        //重新设置对象的父对象
        void setParent(Object *parent);

        //获得当前对象的子对象列表
        inline const ObjectList& getChildern() const;

        //获得当前对象的父对象
        inline const Object* getParent() const;

    protected:
        explicit Object(Object *parent = NULL);
        Object(const Object& obj);
        Object& operator= (const Object &obj);

    private:
        //把当前对象插入到parent指向的父对象的子对象列表中
        inline void _appendObjectList(Object *parent);

        ObjectList childern;//子对象列表
        Object *this_parent;//指向对象的父对象
};

void Object::_appendObjectList(Object *parent)
{
    /***
    函数功能：把当前对象插入到parent指向的父对象的子对象列表中
    返回：无
    ***/
    this_parent = parent;//设置当前对象的父对象
    //若其父对象不为空，则加入到父对象的子对象列表中
    if(this_parent != NULL)
        this_parent->childern.push_back(this);
}

const ObjectList& Object::getChildern() const
{
    return childern;
}

const Object* Object::getParent() const
{
    return this_parent;
}

#endif // OBJECT_H
