#include "Object.h"
#include <algorithm>

Object::Object(Object *parent)
    :this_parent(parent)
{
    /***
    �������ܣ�����һ��Object��������parent��Ϊ�գ�
        ��ѵ�ǰ������뵽���Ӷ����б���
    ***/
    if(this_parent != NULL)
        this_parent->childern.push_back(this);
}



Object::Object(const Object& obj)
{
    /***
    �������ܣ����ݶ���obj������һ������
    ***/
    //����ʱ��ֻ�ǰѵ�ǰ�����obj�ĸ���������Ϊͬһ��������
    //��������obj���Ӷ����б�
    _appendObjectList(obj.this_parent);
}

Object& Object::operator= (const Object &obj)
{
    /***
    �������ܣ�����ǰ�����޸��������obj�ĸ��������óɵ�ǰ����ĸ�����
    ���أ���ǰ���������
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
    �������ܣ��ͷ��ɸö���new�������Ӷ���
    ***/
    //����ǰ�����и������򽫵�ǰ����ӹ���������Ӷ����б���ɾ��
    if(this_parent != NULL)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
//        this_parent->childern.remove(this);
    }
    //�ͷ���new�������Ӷ���
    while(!childern.empty())
    {
        ObjectList::iterator it(childern.begin());
        delete *it;
    }
}

void Object::setParent(Object *parent)
{
    /***
    �������ܣ��������ö���ĸ�����
    ���أ���
    ***/
    //����ǰ�����и�������ѵ�ǰ������丸������Ӷ����б���ɾ��
    if(this_parent != NULL)
    {
        ObjectList::iterator it =
            find(this_parent->childern.begin(),
                 this_parent->childern.end(),
                 this);
        this_parent->childern.erase(it);
//        this_parent->childern.remove(this);
    }
    //���뵱ǰ����parent������Ӷ����б���
    _appendObjectList(parent);
}

