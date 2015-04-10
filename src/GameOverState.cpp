//
//  GameOverState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 11.04.15.
//
//

#include <iostream>

#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

using namespace Yoba;

const std::string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::~GameOverState() {
    
}

void GameOverState::update() {
    for (auto obj : m_gameObjects) {
        obj->update();
    }
}

void GameOverState::render() {
    for (auto obj : m_gameObjects) {
        obj->draw();
    }
}

bool GameOverState::onEnter() {
    std::cout << "entering GameOverState" << std::endl;
    
    if(!TextureManager::Instance()->load("assets/gameover.png",
                                            "gameovertext", Game::Instance()->renderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/mainmenu_button.png",
                                            "mainbutton", Game::Instance()->renderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/restart_button.png",
                                            "restartbutton", Game::Instance()->renderer()))
    {
        return false;
    }
    

    auto gameOverText = std::make_shared<AnimatedGraphic>(LoaderParams(200, 100, 192, 26, 2, "gameovertext"), 2);
    
    auto f_mainmenu = [] {
        Game::Instance()->stateMachine()->changeState(std::make_shared<MenuState>());
    };
    auto button_mainmenu = std::make_shared<MenuButton>(LoaderParams(200, 200, 132, 51, 3, "mainbutton"), f_mainmenu);
    
    auto f_restart = [] {
        Game::Instance()->stateMachine()->changeState(std::make_shared<PlayState>());
    };
    auto button_restart = std::make_shared<MenuButton>(LoaderParams(200, 300, 141, 55, 3, "restartbutton"), f_restart);
    
    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button_mainmenu);
    m_gameObjects.push_back(button_restart);
    
    return true;
}

bool GameOverState::onExit() {
    std::cout << "exiting PauseState" << std::endl;
    
    m_gameObjects.clear();
    TextureManager::Instance()->clearFromTextureMap("gameovertext");
    TextureManager::Instance()->clearFromTextureMap("restartbutton");
    TextureManager::Instance()->clearFromTextureMap("mainbutton");
    
    InputHandler::Instance()->resetMouseButtonStates();
    
    return true;
}
