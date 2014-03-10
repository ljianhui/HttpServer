#include "logfile.h"

using std::ofstream;
using std::ios;

LogFile::LogFile(Object *parent):
    Object(parent),
    log_file("logfile", ofstream::app)
{
}

LogFile::LogFile(const string &filename, Object *parent):
    Object(parent),
    log_file(filename.c_str(), ofstream::app)
{
}

LogFile::~LogFile()
{
    if(log_file.is_open())
    {
        log_file.close();
        log_file.clear();
    }
}

void LogFile::open(const string &filename)
{
    if(log_file.is_open())
    {
        log_file.close();
        log_file.clear();
    }
    log_file.open(filename.c_str(), ios::app);
}

void LogFile::addLog(const string &data)
{
    if(!log_file)
        return;

    log_file.write(data.c_str(), data.length());
}

void LogFile::addLog(const char *data, size_t data_len)
{
    if(!log_file)
        return;
    log_file.write(data, data_len);
}
