//
//  PlayState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>

#include "PlayState.h"

using namespace Yoba;

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() {
    // nothing for now
}

void PlayState::render() {
    // nothing for now
}

bool PlayState::onEnter() {
    std::cout << "entering PlayState" << std::endl;
    return true;
}

bool PlayState::onExit() {
    std::cout << "exiting PlayState" << std::endl;
    return true;
}
