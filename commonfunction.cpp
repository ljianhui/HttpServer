#include <time.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
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
    char *time;
    time = asctime(gmtime(&current_time));
    int len = strlen(time);
    time[len-1] = ' ';
    string fin_time(time);
    fin_time += "GMT";
    return fin_time;
}

size_t CommonFunction::FileLength(ifstream &file)
{
    streampos current_pos = file.tellg();
    file.seekg(0, ios::end);
    size_t len = file.tellg();
    file.seekg(current_pos);
    return len;
}

string CommonFunction::FileName(const string &path)
{
    size_t pos = path.find_last_of("/");
    if(pos == string::npos)
        return string("");

    return path.substr(pos+1);
}

string CommonFunction::FileType(const string &filename)
{
    size_t pos = filename.find_last_of(".");
    if(pos == string::npos)
        return string("");
    return filename.substr(pos+1);
}
