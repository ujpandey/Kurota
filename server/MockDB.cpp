#include "MockDB.h"

MockDB::MockDB(const std::string & file_name)
    : _file_name(file_name)
{
    std::fstream fs;
    fs.open(_file_name.c_str(), std::fstream::in);
    if (fs.is_open)
    {
        std::string input;
        while (std::getline(fs, input))
        {
        }
    }
}
