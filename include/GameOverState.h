//
//  GameOverState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 11.04.15.
//
//

#ifndef yobatronika_GameOverState_h
#define yobatronika_GameOverState_h

#include <vector>
#include <memory>

#include "GameState.h"
#include "GameObject.h"

namespace Yoba {
    
    class GameOverState : public GameState {
    public:
        virtual void update() override;
        virtual void render() override;
        
        virtual bool onEnter() override;
        virtual bool onExit() override;
        
        virtual std::string getStateID() const { return s_gameOverID; }
        
        ~GameOverState();
    private:
        static const std::string s_gameOverID;
        
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
    
}


#endif
