#include "Command.h"
#include "GameState.h"
#include "Network.h"

Command::Command()
{}

Command::~Command()
{}

LoginCommand::LoginCommand(TextArea * notice_board,
                           TextBox * uname,
                           TextBox * passwd,
                           const std::string & response)
    : _notice_board(notice_board), _uname(uname), _passwd(passwd),
      _response(response)
{
}

LoginCommand::~LoginCommand()
{
}

void LoginCommand::execute()
{
    std::cout << "erm" << std::endl;
    NetworkManager * nm = NetworkManager::get_instance();
    std::string id = _uname -> get_text();
    std::string password = _passwd -> get_text();
    nm -> say("L" + id + " " + password);
    _response = nm -> listen();
    _notice_board -> set_text(_response);
    if (_response == "success")
        GameStateManager::get_instance() -> change(new PlayState);
}

RegistrationCommand::RegistrationCommand(TextArea * notice_board,
                           TextBox * uname,
                           TextBox * passwd,
                           const std::string & response)
    : _notice_board(notice_board), _uname(uname), _passwd(passwd),
      _response(response)
{
}

RegistrationCommand::~RegistrationCommand()
{
}

void RegistrationCommand::execute()
{
    NetworkManager * nm = NetworkManager::get_instance();
    std::string id = _uname -> get_text();
    std::string password = _passwd -> get_text();
    nm -> say("R" + id + " " + password);
    _response = nm -> listen();
    _notice_board -> set_text(_response);
}
