//
//  GameStateMachine.cpp
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#include "GameStateMachine.h"

using namespace Yoba;

void GameStateMachine::pushState(std::shared_ptr<GameState> spState) {
    m_gameStates.push_back(spState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    /// \todo use queue for it
    m_bRemoveCurrentState = true;
}

void GameStateMachine::changeState(std::shared_ptr<GameState> spState) {
    if(!m_gameStates.empty()) {
        if(m_gameStates.back()->getStateID() == spState->getStateID()) {
            return;
        }
    }
    
    /// \todo use queue for it
    m_stateToChange = spState;
}

void GameStateMachine::update() {
    /// \todo extract to separatel method
    if (m_bRemoveCurrentState) {
        if(!m_gameStates.empty()) {
            if(m_gameStates.back()->onExit()) {
                m_gameStates.pop_back();
            }
        }
        m_bRemoveCurrentState = false;
    }

    /// \todo extract to separatel method
    if (m_stateToChange) {
        if(!m_gameStates.empty()) {
            if(m_gameStates.back()->onExit()) {
                m_gameStates.pop_back();
            } else {
                /// \todo error handle
            }
        }
        
        m_gameStates.push_back(m_stateToChange);
        m_gameStates.back()->onEnter();
        
        m_stateToChange.reset();
    }
    
    if(!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() {
    if(!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}
