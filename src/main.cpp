/******************************************************************************
 * main.cpp: Kurota main entry point.
 *
 * Latest Change on 09/12/2014 by Ujjwal
 * - Introduce the main game framework in the form of Game & GameObject classes.
 *
 * Latest Change on 09/11/2014 by Ujjwal
 * - Initiate project. Create a SDL window and do some basic tests.
 * 
 * Current status:
 * - Only a basic SDL demo for now.
 *
 * TODO:
 * - Add an animation class.
 *****************************************************************************/


#include "Includes.h"
#include "Game.h"
#include "Text.h"


int main()
{
    Game * TheGame = Game::get_instance();
    TheGame -> init();

    TextBox * Chat_box = new TextBox("Chat_box", "", 0, 0, 200, 30);
    TheGame -> register_game_object(Chat_box);

    // Login Box
    Border * Splash_dbox_brdr = new Border("Splash_dbox_brdr",
                                           10, 0, 64, 71, 255);
    TheGame -> register_game_object(Splash_dbox_brdr);

    DialogBox * Splash_dbox = new DialogBox("Splash_dbox",
                                            "../assets/Splash_dbox.png",
                                            TheGame -> get_renderer(),
                                            250, 250, 350, 350);
    Splash_dbox_brdr -> add_child(Splash_dbox);
    
    TextBox * Username = new TextBox("Username", "", 10, 10, 200, 30);
    TextBox * Password = new TextBox("Password", "", 10, 40, 200, 30);
    Button * Login = new Button("Login", "../assets/login.png",
                                  TheGame -> get_renderer(),
                                  10, 50);
    Button * Register = new Button("Register", "../assets/register.png",
                                 TheGame -> get_renderer(),
                                 120, 50);
    
    Splash_dbox -> add_child(Username);
    Splash_dbox -> add_child(Password);
    Splash_dbox -> add_child(Login);
    Splash_dbox -> add_child(Register);
    
    while(TheGame -> running())
    {
        TheGame -> handle_event();
        TheGame -> update();
        TheGame -> draw();
    }
    TheGame -> clean();

    return 0;
}
