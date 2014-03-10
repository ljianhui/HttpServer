#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include <string>

using std::string;

namespace CommonFunction
{
    int StringToInt(const string &str);
    string IntToString(int n);
    string GetCurrentTime();
}

#endif // COMMONFUNCTION_H_INCLUDED
