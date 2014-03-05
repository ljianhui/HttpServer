#ifndef HTTPKEYVALUE_H_INCLUDED
#define HTTPKEYVALUE_H_INCLUDED

#include <map>
#include <string>
#include "object.h"
#include "mutex.h"

using std::string;

class HttpKeyValue
{
    public:
        static HttpKeyValue* create();
        ~HttpKeyValue();

        string getReasonPhrase(int code);
        string getContentType(const string &file_type);

    private:
        HttpKeyValue();

        void _insertType();
        void _insertError();

        static HttpKeyValue *obj_ptr;
        static int count;
        static Mutex mutex;
        std::map<string,string> type;
        std::map<int, string> error;
};

#endif // HTTPKEYVALUE_H_INCLUDED
