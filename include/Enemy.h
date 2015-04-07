//
//  Enemy.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_Enemy_h
#define yobatronika_Enemy_h

#include "SDLGameObject.h"

namespace Yoba {
    
    class Enemy : public SDLGameObject {
    public:
        Enemy(const LoaderParams &params);
        virtual ~Enemy();
        
        virtual void draw() override;
        virtual void update() override;
        virtual void clean() override;

    };
    
}


#endif
