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
    
    
    SDL_Surface* pTempSurface = loadSurface("assets/tiger.png");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer,
                                              pTempSurface);
    SDL_FreeSurface(pTempSurface);
    
    int tex_width, tex_height;
    SDL_QueryTexture(m_pTexture, NULL, NULL,
                     &tex_width, &tex_height);
    
    
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;
    m_sourceRectangle.w = tex_width/6;
    m_sourceRectangle.h = tex_height;
    
    m_destinationRectangle.x = 100;
    m_destinationRectangle.y = 100;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    
    TextureManager::Instance()->load("assets/tiger.png",
                          "tiger", m_pRenderer);
    
    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

SDL_Surface* Game::loadSurface( std::string path )
{
    SDL_Surface *loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        /// \todo exception
        std::cout << "Unable to load image " << path.c_str()
                    << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }

    return loadedSurface;
}

void Game::render() {
    SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
    
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle,
                   &m_destinationRectangle);
    
    auto rect = m_destinationRectangle;
    rect.x = 0;
    rect.y += rect.w;
    SDL_RenderCopyEx(m_pRenderer, m_pTexture,
                     &m_sourceRectangle, &rect,
                     0, 0, SDL_FLIP_HORIZONTAL); // pass in the horizontal flip
    
    TextureManager::Instance()->drawFrame("tiger", 100,100, 128, 82,
                               1, 1, m_pRenderer);
    
    SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update() {
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
