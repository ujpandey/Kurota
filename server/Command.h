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
                 const std::string & response="Enter your information.");
    virtual ~LoginCommand();

    virtual void execute();
    virtual void authenticate();
private:
    TextArea * _notice_board;
    std::string _response;
};

#endif
