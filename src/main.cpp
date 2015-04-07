
#include <iostream>
#include <memory>

#include "Game.h"
using namespace Yoba;


int main(int argc, char* args[])
{
    auto game = Game::Instance();
    
    if (!game->init(100, 100, 640, 480)) {
        std::cerr << "game init failure - " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    
    while(game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
        
        SDL_Delay(10);
    }
    
    return EXIT_SUCCESS;
}
