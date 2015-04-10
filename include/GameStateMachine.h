//
//  GameStateMachine.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_GameStateMachine_h
#define yobatronika_GameStateMachine_h

#include <memory>
#include <vector>

#include "GameState.h"

namespace Yoba {
    
    class GameStateMachine {
    public:
        void pushState(std::shared_ptr<GameState> pState);
        void changeState(std::shared_ptr<GameState> pState);
        void popState();
        
        void update();
        void render();
        
    private:
        std::vector<std::shared_ptr<GameState>> m_gameStates;
        
        std::shared_ptr<GameState> m_stateToChange = nullptr;
        bool m_bRemoveCurrentState = false;
    };
    
}

#endif
