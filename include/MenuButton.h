//
//  MenuButton.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 10.04.15.
//
//

#ifndef yobatronika_MenuButton_h
#define yobatronika_MenuButton_h

#include "SDLGameObject.h"

namespace Yoba {
    
    class MenuButton : public SDLGameObject {
        
    public:
        
        enum BUTTON_STATES
        {
            BUTTON_STATE_MOUSE_OUT  = 1,
            BUTTON_STATE_MOUSE_OVER = 2,
            BUTTON_STATE_CLICKED    = 3
        };
        
        MenuButton(const LoaderParams &params);
        virtual ~MenuButton();
        
        virtual void draw() override;
        virtual void update() override;
        virtual void clean() override;
    };
    
}


#endif
