//
//  MenuState.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include <iostream>

#include "MenuState.h"

using namespace Yoba;

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
    // nothing for now
}

void MenuState::render() {
    // nothing for now
}

bool MenuState::onEnter() {
    std::cout << "entering MenuState" << std::endl;
    return true;
}

bool MenuState::onExit() {
    std::cout << "exiting MenuState" << std::endl;
    return true;
}
