//
//  GameObject.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_GameObject_h
#define yobatronika_GameObject_h

#include <SDL.h>

#include "LoaderParams.h"


namespace Yoba {
    
    class GameObject {
    public:
        
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void clean() = 0;
        
    protected:
        GameObject(const LoaderParams &params) {}
        virtual ~GameObject() {}
        
    };
   
}
#endif