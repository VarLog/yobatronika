//
//  GameState.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_GameState_h
#define yobatronika_GameState_h

#include <string>

namespace Yoba {
    
    class GameState {
    public:
        virtual void update() = 0;
        virtual void render() = 0;
        virtual bool onEnter() = 0;
        virtual bool onExit() = 0;
        virtual std::string getStateID() const = 0;
    };
    
}


#endif
