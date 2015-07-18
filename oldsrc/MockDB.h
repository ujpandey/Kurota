#ifndef MOCKDB_H
#define MOCKDB_H

#include "Includes.h"
#include "Game.h"
#include "GameObject.h"

struct User
{
    std::string _id;
    std::string _password;
    vec2d _position;

    std::string serialize()
    {
        std::ostringstream ret_stream;
        ret_stream << _id << ' ' << _password << ' '
                   << _position.get_x() << ' ' << _position.get_y();
        return ret_stream.str();
    }

    void deserialize(const std::string & serialized)
    {
        std::istringstream in_stream(serialized);
        double px, py;
        in_stream >> _id >> _password >> px >> py;
        _position.set_x(px);
        _position.set_y(py);
    }
};

class MockDB
{
public:
    MockDB(const std::string & file_name=".Users.mdb");
    ~MockDB();
    
    void add_user(const User * user);
    void del_user(const User * user);
    void get_user(const std::string & id);

    bool authenticate(const std::string & id, const std::string & pw);

    bool commit();
    
private:
    std::string _file_name;
    std::vector< std::string > _users;
};
    
#endif
