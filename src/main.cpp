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
#include "TextureManager.h"


int main()
{
    Game * TheGame = Game::get_instance();
    TheGame -> init();
    Player * p1 = new Player("P1", "../assets/male_walkcycle.png",
                             TheGame -> get_renderer(),
                             0, 0, 64, 64);
    TheGame -> register_game_object(p1);
    while(TheGame -> get_status() != INACTIVE)
    {
        TheGame -> handle_events();
        TheGame -> update();
        TheGame -> render();
    }
    TheGame -> clean();

    return 0;
}
