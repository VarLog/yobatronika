
#include <iostream>
#include <memory>

#include "Game.h"
using namespace Yoba;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
    Uint32 frameStart, frameTime;
    
    auto game = Game::Instance();
    
    if (!game->init(100, 100, 640, 480)) {
        std::cerr << "game init failure - " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    
    while(game->running())
    {
        frameStart = SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }        
    }
    
    // Destroy the Game before exit is important because a destructor of
    // the Game class uses some other singletons which can be destroyed early.
    Game::DeleteInstance();
    
    return EXIT_SUCCESS;
}
