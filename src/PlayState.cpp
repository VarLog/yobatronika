//
//  PlayState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>
#include <algorithm>

#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"

using namespace Yoba;

const std::string PlayState::s_playID = "PLAY";

PlayState::~PlayState() {

}

void PlayState::update() {
    
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        Game::Instance()->stateMachine()->pushState(std::make_shared<PauseState>());
    }
    
    for (auto obj : m_gameObjects) {
        obj->update();
    }
    
    std::find_if(m_enemies.cbegin(), m_enemies.cend(), [this](const std::shared_ptr<Enemy> enemy) {
        if(this->checkCollision(m_spPlayer, enemy)) {
            Game::Instance()->stateMachine()->pushState(std::make_shared<GameOverState>());
            return true;
        }
        return false;
    });
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
    
    m_spPlayer = std::make_shared<Player>(LoaderParams(10, 100, 75, 48, 1, "tiger"), "yoba");
    m_gameObjects.push_back(m_spPlayer);
    
    for (int i = 0; i < 3; i++) {
        auto sp_enemy = std::make_shared<Enemy>(LoaderParams(10+48+50, 10+(123*(i)), 123, 86, 1, "rider"));
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

bool PlayState::checkCollision(std::shared_ptr<SDLGameObject> obj1, std::shared_ptr<SDLGameObject> obj2) {
    
    /// \todo implement geometry for purposes like these.
    
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    leftA   = obj1->getPosition().getX();
    rightA  = obj1->getPosition().getX() + obj1->getWidth();
    topA    = obj1->getPosition().getY();
    bottomA = obj1->getPosition().getY() + obj1->getHeight();
    
    leftB   = obj2->getPosition().getX();
    rightB  = obj2->getPosition().getX() + obj2->getWidth();
    topB    = obj2->getPosition().getY();
    bottomB = obj2->getPosition().getY() + obj2->getHeight();
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB ){ return false; }
    if( topA >= bottomB ){ return false; }
    if( rightA <= leftB ){ return false; }
    if( leftA >= rightB ){ return false; }
    
    return true;
}
