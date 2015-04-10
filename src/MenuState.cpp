//
//  MenuState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>

#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

using namespace Yoba;

const std::string MenuState::s_menuID = "MENU";

MenuState::~MenuState() {
    
}

void MenuState::update() {
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance()->quit();
    }
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::Instance()->stateMachine()->changeState(std::make_shared<PlayState>());
    }
    
    for (auto obj : m_gameObjects) {
        obj->update();
    }
}

void MenuState::render() {
    for (auto obj : m_gameObjects) {
        obj->draw();
    }
}

bool MenuState::onEnter() {
    std::cout << "entering MenuState" << std::endl;
    
    if(!TextureManager::Instance()->load("assets/play_button.png",
                                         "play_button", Game::Instance()->renderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/exit_button.png",
                                         "exit_button", Game::Instance()->renderer()))
    {
        return false;
    }
    

    auto f_play = [] {
        Game::Instance()->stateMachine()->changeState(std::make_shared<PlayState>());
    };

    auto button_play = std::make_shared<MenuButton>(LoaderParams(100, 100, 145, 35, 3, "play_button"), f_play);
    
    auto f_exit = [] {
        Game::Instance()->quit();
    };

    auto button_exit = std::make_shared<MenuButton>(LoaderParams(100, 300, 145, 35, 3, "exit_button"), f_exit);
    
    m_gameObjects.push_back(button_play);
    m_gameObjects.push_back(button_exit);
    
    return true;
}

bool MenuState::onExit() {
    std::cout << "exiting MenuState" << std::endl;
    
    m_gameObjects.clear();
    
    TextureManager::Instance()->clearFromTextureMap("play_button");
    TextureManager::Instance()->clearFromTextureMap("exit_button");
    
    InputHandler::Instance()->resetMouseButtonStates();
    
    return true;
}
