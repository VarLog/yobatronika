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

using namespace Yoba;

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
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
                                         "play_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/exit_button.png",
                                         "exit_button", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    auto button1 = std::make_shared<MenuButton>(LoaderParams(100, 100, 145, 35, "play_button"));
    auto button2 = std::make_shared<MenuButton>(LoaderParams(100, 300, 145, 35, "exit_button"));
    
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    return true;
}

bool MenuState::onExit() {
    std::cout << "exiting MenuState" << std::endl;
    
    m_gameObjects.clear();
    
    TextureManager::Instance()->clearFromTextureMap("play_button");
    TextureManager::Instance()->clearFromTextureMap("exit_button");
    
    return true;
}
