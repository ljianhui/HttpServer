#ifndef HTTPHEADER_H_INCLUDED
#define HTTPHEADER_H_INCLUDED

#include "object.h"
#include <string>
#include <list>

using std::string;

class HttpHeader : public Object
{
    public:
        HttpHeader(Object *parent = NULL);
        HttpHeader(const HttpHeader &header);
        HttpHeader(const string &header, Object *parent = NULL);
        HttpHeader(const char *header, Object *parent = NULL);
        HttpHeader& operator=(const HttpHeader &header);
        virtual ~HttpHeader();

        void addValue(const string &key, const string &value);
        void setValue(const string &key, const string &new_value);
        void setContentLength(int len);
        void setContentType(const string &type);

        virtual string getVersion() const = 0;
        virtual int getMajorVersion() const = 0;
        virtual int getMinorVersion() const = 0;
        string getValue(const string &key) const;
        inline const std::list<string>& getAllValues() const;
        inline const std::list<string>& getAllKeys() const;
        int getContentLength() const;
        string getContentType() const;

        inline bool isVaild() const;
        bool hasContentLength() const;
        bool hasContentType() const;
        bool hasKey(const string &key) const;

        void removeValue(const string &key);
        virtual string toString() const;

    protected:
        void _cstringToHttpheader(const char *header);
        inline void _setVaild(bool vaild);

    private:
        void _assign(const HttpHeader &header);
        std::list<string>::iterator _findValue(const string &key);
        std::list<string>::const_iterator _findValueConst(const string &key) const;

        bool is_vaild;
        std::list<string> keys;
        std::list<string> values;
};

const std::list<string>& HttpHeader::getAllValues()const
{
    return values;
}

const std::list<string>& HttpHeader::getAllKeys()const
{
    return keys;
}

bool HttpHeader::isVaild()const
{
    return is_vaild;
}

void HttpHeader::_setVaild(bool vaild)
{
    is_vaild = vaild;
}

#endif // HTTPHEAD_H_INCLUDED
