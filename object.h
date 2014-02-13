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

        //�������ö���ĸ�����
        void setParent(Object *parent);

        //��õ�ǰ������Ӷ����б�
        inline const ObjectList& getChildern() const;

        //��õ�ǰ����ĸ�����
        inline const Object* getParent() const;

    protected:
        explicit Object(Object *parent = NULL);
        Object(const Object& obj);
        Object& operator= (const Object &obj);

    private:
        //�ѵ�ǰ������뵽parentָ��ĸ�������Ӷ����б���
        inline void _appendObjectList(Object *parent);

        ObjectList childern;//�Ӷ����б�
        Object *this_parent;//ָ�����ĸ�����
};

void Object::_appendObjectList(Object *parent)
{
    /***
    �������ܣ��ѵ�ǰ������뵽parentָ��ĸ�������Ӷ����б���
    ���أ���
    ***/
    this_parent = parent;//���õ�ǰ����ĸ�����
    //���丸����Ϊ�գ�����뵽��������Ӷ����б���
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
