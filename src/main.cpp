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



#include <iostream>
#include <string>


#include "SDL.h"
#include "SDL_image.h"


#include "Game.h"
#include "Text.h"


int main()
{
    Game * TheGame = Game::get_instance();
    TheGame -> init();
    Player * p1 = new Player("P1", "../assets/warrior.png",
                             TheGame -> get_renderer(),
                             0, 0, 64, 64);
    Button * Login = new Button("Login", "../assets/login.png",
                                  TheGame -> get_renderer(),
                                  10, 20);
    Button * Register = new Button("Register", "../assets/register.png",
                                 TheGame -> get_renderer(),
                                 120, 20);
    DialogBox * Splash_dbox = new DialogBox("Splash_dbox",
                                            "../assets/Splash_dbox.png",
                                            TheGame -> get_renderer(),
                                            400, 400);
    Border * Splash_dbox_brdr = new Border("Splash_dbox_brdr",
                                           10, 0, 64, 71, 255);
    TextBox * Chat_box = new TextBox("Chat_box", "", 0, 0, 200, 200);
    Splash_dbox -> add_child(Login);
    Splash_dbox -> add_child(Register);
    Splash_dbox_brdr -> add_child(Splash_dbox);
    TheGame -> register_game_object(p1);
    TheGame -> register_game_object(Splash_dbox_brdr);
    TheGame -> register_game_object(Chat_box);
    
    while(TheGame -> get_status() != INACTIVE)
    {
        TheGame -> handle_events();
        TheGame -> update();
        TheGame -> render();
    }
    TheGame -> clean();

    return 0;
}
