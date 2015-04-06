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
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, sdl_init_flags);
        
        if(m_pWindow != nullptr) {
            std::cout << "window creation success\n";
            
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, sdl_render_flags);
            if(m_pRenderer != nullptr) {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 128, 128, 128, 255);
            } else {
                std::cout << "renderer init fail\n";
                return false;   /// \todo exception

            }
        } else {
            std::cout << "window init fail\n";
            return false;   /// \todo exception
        }
    } else {
        std::cout << "SDL init fail\n";
        return false;   /// \todo exception
    }
    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update() {
    
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
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

bool Game::running() {
    return m_bRunning;
}
