#ifndef COMMAND_H
#define COMMAND_H

#include "Includes.h"
#include "Text.h"

class Text;

class Command
{
public:
    virtual ~Command();
    virtual void execute() = 0;
protected:
    Command();
};

class LoginCommand : public Command
{
public:
    LoginCommand(TextArea * notice_board,
                 TextBox * uname,
                 TextBox * passwd,
                 const std::string & response="");
    virtual ~LoginCommand();

    virtual void execute();
private:
    TextArea * _notice_board;
    TextBox * _uname;
    TextBox * _passwd;
    std::string _response;
};

class RegistrationCommand : public Command
{
public:
    RegistrationCommand(TextArea * notice_board,
                 TextBox * uname,
                 TextBox * passwd,
                 const std::string & response="");
    virtual ~RegistrationCommand();

    virtual void execute();
private:
    TextArea * _notice_board;
    TextBox * _uname;
    TextBox * _passwd;
    std::string _response;
};

#endif
