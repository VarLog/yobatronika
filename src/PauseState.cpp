//
//  PauseState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>

#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "MenuButton.h"

using namespace Yoba;

const std::string PauseState::s_pauseID = "PAUSE";

PauseState::~PauseState() {
    
}

void PauseState::update() {
    for (auto obj : m_gameObjects) {
        obj->update();
    }
}

void PauseState::render() {
    for (auto obj : m_gameObjects) {
        obj->draw();
    }
}

bool PauseState::onEnter()
{
    std::cout << "entering PauseState" << std::endl;
    
    if(!TextureManager::Instance()->load("assets/resume_button.png", "resumebutton", Game::Instance()->renderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/mainmenu_button.png", "mainbutton", Game::Instance()->renderer()))
    {
        return false;
    }
    
    auto f_mainmenu = [] {
        Game::Instance()->stateMachine()->changeState(std::make_shared<MenuState>());
    };
    auto button_mainmenu = std::make_shared<MenuButton>(LoaderParams(200, 100, 132, 51, "mainbutton"), f_mainmenu);
    
    auto f_resume = [] {
        Game::Instance()->stateMachine()->popState();
    };
    auto button_resume = std::make_shared<MenuButton>(LoaderParams(200, 300, 132, 51, "resumebutton"), f_resume);
    
    m_gameObjects.push_back(button_mainmenu);
    m_gameObjects.push_back(button_resume);
    
    return true;
}
bool PauseState::onExit()
{
    std::cout << "exiting PauseState" << std::endl;

    m_gameObjects.clear();
    TextureManager::Instance()->clearFromTextureMap("resumebutton");
    TextureManager::Instance()->clearFromTextureMap("mainbutton");
    
    InputHandler::Instance()->resetMouseButtonStates();
    
    return true;
}
