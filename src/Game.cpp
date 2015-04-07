//
//  Game.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include <iostream>

#include "Game.h"
#include "LoaderParams.h"

using namespace Yoba;

std::shared_ptr<Game> Game::m_spInstance = nullptr;

std::shared_ptr<Game> Game::Instance()
{
    if(m_spInstance == nullptr)
    {
        m_spInstance = std::shared_ptr<Game>(new Game());
    }
    return m_spInstance;
}

void Game::DeleteInstance() {
    m_spInstance.reset();
}


Game::Game() {
}

Game::~Game() {
    clean();
}

bool Game::init(int xpos, int ypos, int width, int height) {
    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init success" << std::endl;
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, sdl_init_flags);
        
        if(m_pWindow != nullptr) {
            std::cout << "window creation success" << std::endl;
            
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, sdl_render_flags);
            if(m_pRenderer != nullptr) {
                std::cout << "renderer creation success" << std::endl;
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
            } else {
                std::cout << "renderer init fail" << std::endl;
                return false;   /// \todo exception

            }
            
            //Initialize PNG loading
            if( !( IMG_Init( sdl_init_flags ) & sdl_init_flags ) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                return false; /// \todo exception
            }
            
            
        } else {
            std::cout << "window init fail" << std::endl;
            return false;   /// \todo exception
        }
    } else {
        std::cout << "SDL init fail" << std::endl;
        return false;   /// \todo exception
    }
    
    TextureManager::Instance()->load("assets/tiger.png", "player", m_pRenderer);
    m_spPlayer = std::make_shared<Player>("yoba", LoaderParams(10, 100, 75, 48, "player"));
    m_vGameObjects.push_back(m_spPlayer);
    
    TextureManager::Instance()->load("assets/rider.png", "enemy", m_pRenderer);
    for (int i = 0; i < 3; i++) {
        auto sp_enemy = std::make_shared<Enemy>(LoaderParams(10+48+50, 10+(123*(i)), 123, 86, "enemy"));
        m_vEnemies.push_back(sp_enemy);
        m_vGameObjects.push_back(sp_enemy);
    }
    
    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

void Game::render() {
    // clear the renderer to the draw color
    SDL_RenderClear(m_pRenderer);
    
    for (auto obj : m_vGameObjects) {
        obj->draw();
    }
    
    // draw to the screen
    SDL_RenderPresent(m_pRenderer);
}

void Game::update() {
    for (auto obj : m_vGameObjects) {
        obj->draw();
    }
    
    /*
    const int delta = 200;
    static int lastTicks = 0;
    static int idx = 0;
    
    if ( (SDL_GetTicks() - lastTicks) > delta ) {
        idx++;
        lastTicks = SDL_GetTicks();
    }
    
    if (idx == 6) {
        idx = 0;
        m_destinationRectangle.x += m_destinationRectangle.w/6;
    }
    
    m_sourceRectangle.x = m_sourceRectangle.w * idx;
    
    m_destinationRectangle.x += m_destinationRectangle.w/36;
    
    if (m_destinationRectangle.x > 600) {
        m_destinationRectangle.x = 0;
    }
     */
}

void Game::handleEvents() {
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                m_bRunning = false;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        m_bRunning = false;
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
}

void Game::clean() {
    std::cout << "cleaning game\n";
    
    /// \todo use destructor only for it
    for (auto obj : m_vGameObjects) {
        obj->clean();
    }
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}

SDL_Renderer* Game::getRenderer() const {
    return m_pRenderer;
}
