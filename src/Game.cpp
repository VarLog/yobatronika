//
//  Game.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#include <iostream>

#include "Game.h"

using namespace Yoba;

Game::Game(int xpos, int ypos, int width, int height) {
    init(xpos, ypos, width, height);
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
    
    TextureManager::Instance()->load("assets/tiger.png", "tiger", m_pRenderer);
    m_gameObject.load(10, 10, 75, 48, "tiger");
    
    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
    
    m_gameObject.draw(m_pRenderer);
    
    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update() {
    m_gameObject.update();
    
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
    m_gameObject.clean();
    
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}
