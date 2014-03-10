#ifndef LOGFILE_H_INCLUDED
#define LOGFILE_H_INCLUDED

#include <fstream>
#include <string>
#include "object.h"

using std::string;

class LogFile : public Object
{
    public:
        LogFile(Object *parent = NULL);
        LogFile(const string &filename, Object *parent = NULL);
        ~LogFile();

        void open(const string &filename);
        void addLog(const string &data);
        void addLog(const char *data, size_t data_len);
    private:
        LogFile(const LogFile &log){}
        LogFile& operator=(const LogFile &log){return *this;}

        std::ofstream log_file;
};

#endif // LOGFILE_H_INCLUDED
