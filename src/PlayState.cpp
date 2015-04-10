//
//  PlayState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>

#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"

using namespace Yoba;

const std::string PlayState::s_playID = "PLAY";

PlayState::~PlayState() {

}

void PlayState::update() {
    for (auto obj : m_gameObjects) {
        obj->update();
    }
}

void PlayState::render() {
    for (auto obj : m_gameObjects) {
        obj->draw();
    }
}

bool PlayState::onEnter() {
    std::cout << "entering PlayState" << std::endl;
    
    if(!TextureManager::Instance()->load("assets/tiger.png", "tiger", Game::Instance()->renderer()))
    {
        return false;
    }
    
    if(!TextureManager::Instance()->load("assets/rider.png", "rider", Game::Instance()->renderer()))
    {
        return false;
    }
    
    m_spPlayer = std::make_shared<Player>("yoba", LoaderParams(10, 100, 75, 48, "tiger"));
    m_gameObjects.push_back(m_spPlayer);
    
    for (int i = 0; i < 3; i++) {
        auto sp_enemy = std::make_shared<Enemy>(LoaderParams(10+48+50, 10+(123*(i)), 123, 86, "rider"));
        m_enemies.push_back(sp_enemy);
        m_gameObjects.push_back(sp_enemy);
    }
    
    return true;
}

bool PlayState::onExit() {
    std::cout << "exiting PlayState" << std::endl;
    
    m_spPlayer.reset();
    m_enemies.clear();
    m_gameObjects.clear();
    
    TextureManager::Instance()->clearFromTextureMap("tiger");
    TextureManager::Instance()->clearFromTextureMap("rider");
    
    return true;
}
