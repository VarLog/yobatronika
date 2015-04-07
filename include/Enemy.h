//
//  Enemy.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_Enemy_h
#define yobatronika_Enemy_h

#include "GameObject.h"

namespace Yoba {
    
    class Enemy : public GameObject {
    public:
        Enemy(int x, int y, int width, int height, std::string textureID);
        ~Enemy();
        
    };
    
}


#endif
