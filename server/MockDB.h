#ifndef MOCKDB_H
#define MOCKDB_H

#include "Includes.h"
#include "Game.h"
#include "GameObject.h"

class MockDB
{
public:
    MockDB(const std::string & file_name=".Players.mdb");
    ~MockDB();
    void add_user(const Player * player);
    void del_user(const Player * player);
    void get_user(const std::string & id);
    void authenticate(const std::string & id, const std::string & pw);
    bool commit();
    
private:
    std::string _file_name;
    std::vector< std::string > players;
};
    
#endif
