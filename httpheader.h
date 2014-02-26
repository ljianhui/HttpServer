#ifndef HTTPHEADER_H_INCLUDED
#define HTTPHEADER_H_INCLUDED

#include "object.h"
#include <string>
#include <list>

using std::string;
using std::list;

typedef list<string> StringList;

class HttpHeader : public Object
{
    public:
        HttpHeader(Object *parent = NULL);
        HttpHeader(const HttpHeader &header);
        HttpHeader(const string &head);
        HttpHeader(const char *head);
        HttpHeader& operator=(const HttpHeader &header);
        virtual ~HttpHeader();

        void setVersion(const string &ver);
        void addValue(const string &key, const string &value);
        void setValue(const string &key, const string &new_value);
        void setContentLength(int len);
        void setContentType(const string &type);

        string getVersion() const;
        int getMajorVersion() const;
        int getMinorVersion() const;
        string getValue(const string &key) const;
        const StringList& getAllValues() const;
        const StringList& getKeys() const;
        int getContentLength() const;
        string getContentType() const;

        bool isVaild() const;
        bool hasContentLength() const;
        bool hasContentType() const;
        bool hasKey(const string &key) const;

        void removeValue(const string &key);
        virtual string toString()const;

    protected:
        const char* getContent();

    private:
        string version;
        char *content;
        int content_len;
        string content_type;
        list<string> keys;
        list<string> values;
};

#endif // HTTPHEAD_H_INCLUDED
