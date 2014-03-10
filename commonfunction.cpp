#include <time.h>
#include <sstream>
#include <stdlib.h>
#include "commonfunction.h"

using std::stringstream;

int CommonFunction::StringToInt(const string &str)
{
    return atoi(str.c_str());
}

string CommonFunction::IntToString(int n)
{
    stringstream stream;
    stream << n;
    return stream.str();
}

string CommonFunction::GetCurrentTime()
{
    time_t current_time;
    time(&current_time);
    stringstream stream;
    stream << asctime(gmtime(&current_time));
    return stream.str();
}
