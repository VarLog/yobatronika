//
//  MainApplication.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 09.04.15.
//
//

#include <stdlib.h>
#include <iostream>

#include "MainApplication.h"
#include "Game.h"

using namespace Yoba;

int MainApplication::run(int argc, const char **argv) {
    
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
    
    Game::DeleteInstance();
    InputHandler::DeleteInstance();
    TextureManager::DeleteInstance();
    
    return EXIT_SUCCESS;
}
