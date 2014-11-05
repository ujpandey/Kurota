#include "MockDB.h"

MockDB::MockDB(const std::string & file_name)
    : _file_name(file_name)
{
    std::fstream fs;
    fs.open(_file_name.c_str(), std::fstream::in);
    if (fs.is_open())
    {
        std::string input;
        while (std::getline(fs, input))
        {
            std::cout << input << std::endl;
        }
        fs.close();
    }
}

MockDB::~MockDB()
{
}

void MockDB::add_user(const User * user)
{
    if (get_user(user -> get_id()) == "")
        _users.push_back(user.serialize());
}

void MockDB::del_user(const User * user)
{
    std::vector< std::string >::iterator it =
        std::find(_users.begin(), _users.end(), id);
    if (it != _users.end())
        _users.erase(it);
}

std::string MockDB::get_user(const std::string & id) const
{
    std::vector< std::string >::iterator it =
        std::find(_users.begin(), _users.end(), id);
    if (it == _users.end())
        return "";
    return *it;
}

bool MockDB::authenticate(const std::string & id, const std::string & pw)
{
    std::string user_info = get_user(id);
    if (user_info = "")
        return false;
    if (
}

bool MockDB::commit()
{
    std::fstream fs;
    fs.open(_file_name.c_str(), std::fstream::out);
    if (fs.is_open())
    {
        for (std::vector< std::string >::iterator it = _users.begin();
             it != _users.end(); ++it)
        {
            fs << *it << '\n';
        }

        fs.close();
    }
}
