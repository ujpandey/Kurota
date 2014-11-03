#include "GameState.h"
#include "Widget.h"
#include "Text.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Command.h"


//-----------------------------------------------------------------------------
// GameState
//-----------------------------------------------------------------------------
GameState::GameState(const std::string & id)
    : EventHandler(id)
{
    set_successor(Game::get_instance());
}

GameState::~GameState()
{}

// void GameState::handle_event()
// {
// }

void GameState::update()
{
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> update();
    }
    SDL_Delay(30);
}

void GameState::draw(SDL_Renderer * renderer)
{
    std::cout << "Drawing for: ";
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
    std::cout << _id << std::endl;
}

const std::string & GameState::get_id()
{
    return _id;
}

void GameState::on_entry()
{
    // Make resources persistent and switch.
}

void GameState::on_exit()
{
    std::cout << "Exiting ... " << _id << std::endl;
    // Temporary solution to clear things out like this. Want Persistence.
    TextureManager::get_instance() -> clear();
    EventManager::get_instance() -> clear();
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        delete (*it);
    }
    game_objects.clear();
}

void GameState::register_game_object(GameObject * g_o)
{
    game_objects.push_back(g_o);
    g_o -> set_successor(this);
    EventManager::get_instance() -> lease(g_o);
}

void GameState::release_game_object(GameObject * g_o)
{
    std::vector< GameObject * >::iterator it =
        std::find(game_objects.begin(), game_objects.end(), g_o);
    if (it != game_objects.end())
        game_objects.erase(it);
    EventManager::get_instance() -> release(g_o);
}


//-----------------------------------------------------------------------------
// SplashScreen
//-----------------------------------------------------------------------------
SplashScreen::SplashScreen(const std::string & id)
    : GameState(id)
{}

void SplashScreen::on_entry()
{
    // Logo
    Button * Logo = new Button("Logo", "../assets/logo.png",
                               Game::get_instance() -> get_renderer(),
                               375, 150);
    register_game_object(Logo);

    // Login Box
    Border * Splash_dbox_brdr = new Border("Splash_dbox_brdr",
                                           10, 0, 64, 71, 255);
    register_game_object(Splash_dbox_brdr);

    DialogBox * Splash_dbox = new DialogBox("Splash_dbox",
                                            "../assets/Splash_dbox.png",
                                            Game::get_instance() -> get_renderer(),
                                            325, 250, 400, 250);
    Splash_dbox_brdr -> add_child(Splash_dbox);

    TextArea * Feedback = new TextArea("Feedback", "", 10, 10, 300, 30);
    TextArea * User_query = new TextArea("User_query", "Username: ", 40, 60, 150, 30);
    TextArea * Password_query = new TextArea("Password_query", "Password: ", 40, 110, 150, 30);
    TextBox * Username = new TextBox("Username", "", 160, 60, 200, 30);
    TextBox * Password = new TextBox("Password", "", 160, 110, 200, 30, true);
    Button * Login = new Button("Login", "../assets/login.png",
                                Game::get_instance() -> get_renderer(),
                                80, 180, 100, 40, new LoginCommand(Feedback));
    Button * Register = new Button("Register", "../assets/register.png",
                                   Game::get_instance() -> get_renderer(),
                                   220, 180, 100, 40);

    Splash_dbox -> add_child(User_query);
    Splash_dbox -> add_child(Password_query);
    Splash_dbox -> add_child(Username);
    Splash_dbox -> add_child(Password);
    Splash_dbox -> add_child(Login);
    Splash_dbox -> add_child(Register);
}


//-----------------------------------------------------------------------------
// PlayState
//-----------------------------------------------------------------------------
PlayState::PlayState(const std::string & id)
    : GameState(id)
{}

void PlayState::on_entry()
{
    std::cout << "Beginning play" << std::endl;
    TextBox * Chat_box = new TextBox("Chat_box", "", 0, 0, 200, 30);
    register_game_object(Chat_box);
}


//-----------------------------------------------------------------------------
// GameStateManager
//-----------------------------------------------------------------------------
GameStateManager * GameStateManager::_instance = NULL;

GameStateManager * GameStateManager::get_instance()
{
    if (_instance)
        return _instance;
    _instance = new GameStateManager;
    return _instance;
}

GameStateManager::GameStateManager()
{}

GameStateManager::~GameStateManager()
{}

void GameStateManager::update()
{
    (*(_game_states.end() - 1)) -> update();
}

void GameStateManager::draw(SDL_Renderer * renderer)
{
    (*(_game_states.end() - 1)) -> draw(renderer);
}

const std::string & GameStateManager::get_current_state_id()
{
    return (*(_game_states.end() - 1)) -> get_id();
}

void GameStateManager::register_game_object(GameObject * g_o)
{
    (*(_game_states.end() - 1)) -> register_game_object(g_o);
}

void GameStateManager::release_game_object(GameObject * g_o)
{
    (*(_game_states.end() - 1)) -> release_game_object(g_o);
}

void GameStateManager::change(GameState * state)
{
    pop();
    push(state);
}

void GameStateManager::push(GameState * state)
{
    state -> on_entry();
    _game_states.push_back(state);
}

void GameStateManager::pop()
{
    (*(_game_states.end() - 1)) -> on_exit();
    _game_states.pop_back(); 
}
