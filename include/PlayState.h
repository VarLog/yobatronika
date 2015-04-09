//
//  PlayState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_PlayState_h
#define yobatronika_PlayState_h

#include "GameState.h"

namespace Yoba {
    
    class PlayState : public GameState {
    public:
        virtual void update() override;
        virtual void render() override;
        
        virtual bool onEnter() override;
        virtual bool onExit() override;
        
        virtual std::string getStateID() const { return s_playID; }
    private:
        static const std::string s_playID;
    };
}

#endif
