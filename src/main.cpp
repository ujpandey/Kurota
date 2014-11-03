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


int main()
{
    Game::get_instance() -> init();
    
    while(Game::get_instance() -> running())
    {
        Game::get_instance() -> handle_event();
        Game::get_instance() -> update();
        Game::get_instance() -> draw();
    }
    Game::get_instance() -> clean();

    return 0;
}
