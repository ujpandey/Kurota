#include "Command.h"
#include "GameState.h"

Command::Command()
{}

Command::~Command()
{}

LoginCommand::LoginCommand(TextArea * notice_board,
                           const std::string & response)
    : _notice_board(notice_board), _response(response)
{
    _notice_board -> set_text(_response);
}

LoginCommand::~LoginCommand()
{
}

void LoginCommand::execute()
{
    std::cout << "Hi" << std::endl;
    GameStateManager::get_instance() -> change(new PlayState);
}

void LoginCommand::authenticate()
{
}
