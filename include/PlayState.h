//
//  PlayState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_PlayState_h
#define yobatronika_PlayState_h

#include <vector>
#include <memory>

#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

namespace Yoba {
    
    class PlayState : public GameState {
    public:
        virtual void update() override;
        virtual void render() override;
        
        virtual bool onEnter() override;
        virtual bool onExit() override;
        
        virtual std::string getStateID() const { return s_playID; }
        
        ~PlayState();
    private:
        static const std::string s_playID;
        
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
        std::shared_ptr<Player> m_spPlayer = nullptr;
        std::vector<std::shared_ptr<Enemy>> m_enemies;
    };
}

#endif
