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

#include "MenuState.h"
#include "PlayState.h"

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
                SDL_SetRenderDrawColor(m_pRenderer, 128, 128, 128, 255);
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
    
    InputHandler::Instance()->initialiseJoysticks();
    
    TextureManager::Instance()->load("assets/tiger.png", "player", m_pRenderer);
    m_spPlayer = std::make_shared<Player>("yoba", LoaderParams(10, 100, 75, 48, "player"));
    m_vGameObjects.push_back(m_spPlayer);
    
    TextureManager::Instance()->load("assets/rider.png", "enemy", m_pRenderer);
    for (int i = 0; i < 3; i++) {
        auto sp_enemy = std::make_shared<Enemy>(LoaderParams(10+48+50, 10+(123*(i)), 123, 86, "enemy"));
        m_vEnemies.push_back(sp_enemy);
        m_vGameObjects.push_back(sp_enemy);
    }
    
    m_spGameStateMachine = std::make_shared<GameStateMachine>();
    m_spGameStateMachine->changeState(std::make_shared<MenuState>());
    
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
        obj->update();
    }
}

void Game::quit() {
    m_bRunning = false;
    clean();
}

void Game::handleEvents() {
    InputHandler::Instance()->update();

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_spGameStateMachine->changeState(std::make_shared<PlayState>());
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

SDL_Renderer* Game::getRenderer() const {
    return m_pRenderer;
}
