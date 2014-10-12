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
    
    while(TheGame -> get_status() != INACTIVE)
    {
        TheGame -> handle_events();
        TheGame -> update();
        TheGame -> render();
    }
    TheGame -> clean();

    return 0;
}
