//
//  AnimatedGraphic.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 11.04.15.
//
//

#ifndef yobatronika_AnimatedGraphic_h
#define yobatronika_AnimatedGraphic_h

#include "SDLGameObject.h"

namespace Yoba {
    
    class AnimatedGraphic : public SDLGameObject {
    public:
        AnimatedGraphic(const LoaderParams &params, const int animSpeed);
        virtual ~AnimatedGraphic();
        
        virtual void draw() override;
        virtual void update() override;
        virtual void clean() override;
        
    private:
        void handleInput();
        
        int m_animSpeed;
    };
    
}


#endif
