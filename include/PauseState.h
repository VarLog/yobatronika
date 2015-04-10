//
//  PauseState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_PauseState_h
#define yobatronika_PauseState_h

#include <vector>
#include <memory>

#include "GameState.h"
#include "GameObject.h"

namespace Yoba {
    
    class PauseState : public GameState {
    public:
        virtual void update() override;
        virtual void render() override;
        
        virtual bool onEnter() override;
        virtual bool onExit() override;
        
        virtual std::string getStateID() const { return s_pauseID; }
        
        ~PauseState();
    private:
        static const std::string s_pauseID;
        
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
    
}

#endif
