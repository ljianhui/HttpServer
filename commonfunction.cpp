#include <time.h>
#include <sstream>
#include <stdlib.h>
#include "commonfunction.h"

using std::stringstream;
using std::ifstream;
using std::string;
using std::streampos;
using std::ios;

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

string CommonFunction::CurrentTime()
{
    time_t current_time;
    time(&current_time);
    stringstream stream;
    stream << asctime(gmtime(&current_time));
    return stream.str();
}

size_t CommonFunction::FileLength(ifstream &file)
{
    streampos current_pos = file.tellg();
    file.seekg(0, ios::end);
    size_t len = file.tellg();
    file.seekg(current_pos);
    return len;
}
