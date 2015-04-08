//
//  Player.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_Player_h
#define yobatronika_Player_h

#include "SDLGameObject.h"

namespace Yoba {
    
    class Player : public SDLGameObject {
    public:
        Player(std::string name, const LoaderParams &params);
        virtual ~Player();
        
        virtual void draw() override;
        virtual void update() override;
        virtual void clean() override;

    private:
        void handleInput();
        
        std::string m_sName;
    };
    
}

#endif
