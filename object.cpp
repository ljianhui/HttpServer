#include "object.h"
#include <algorithm>

Object::Object(Object *parent)
    :this_parent(parent)
{
    /***
    函数功能：创建一个Object对象，若其parent不为空，
        则把当前对象插入到其子对象列表中
    ***/
    if(this_parent != NULL)
        this_parent->childern.push_back(this);
}



Object::Object(const Object& obj)
{
    /***
    函数功能：根据对象obj，复制一个对象
    ***/
    //复制时，只是把当前对象和obj的父对象设置为同一个父对象
    //并不复制obj的子对象列表
    _appendObjectList(obj.this_parent);
}

Object& Object::operator= (const Object &obj)
{
    /***
    函数功能：若当前对象无父对象，则把obj的父对象设置成当前对象的父对象
    返回：当前对象的引用
    ***/
    if(this_parent == NULL)
    {
        _appendObjectList(obj.this_parent);
    }
    return *this;
}

Object::~Object()
{
    /***
    函数功能：释放由该对象new出来的子对象
    ***/
    //若当前对象有父对象，则将当前对象从共父对象的子对象列表中删除
    if(this_parent != NULL)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
//        this_parent->childern.remove(this);
    }
    //释放其new出来的子对象
    while(!childern.empty())
    {
        ObjectList::iterator it(childern.begin());
        delete *it;
    }
}

void Object::setParent(Object *parent)
{
    /***
    函数功能：重新设置对象的父对象
    返回：无
    ***/
    //若当前对象有父对象，则把当前对象从其父对象的子对象列表中删除
    if(this_parent != NULL)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
//        this_parent->childern.remove(this);
    }
    //插入当前对象到parent对象的子对象列表中
    _appendObjectList(parent);
}
