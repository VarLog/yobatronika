//
//  MenuState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_MenuState_h
#define yobatronika_MenuState_h

#include <vector>
#include <memory>

#include "GameState.h"
#include "GameObject.h"

namespace Yoba {
    
    class MenuState : public GameState {
    public:
        virtual void update() override;
        virtual void render() override;
        
        virtual bool onEnter() override;
        virtual bool onExit() override;
        
        virtual std::string getStateID() const { return s_menuID; }
        
        ~MenuState();
    private:
        static const std::string s_menuID;
        
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    };
    
}

#endif
