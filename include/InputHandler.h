//
//  InputHandler.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#ifndef yobatronika_InputHandler_h
#define yobatronika_InputHandler_h

#include <memory>
#include <vector>

#include "SDL.h"

#include "Vector2D.h"

namespace Yoba {
    
    class InputHandler {
    public:
        static std::shared_ptr<InputHandler> Instance();
        static void DeleteInstance();
        
        void update();
        void clean();
        
        /**
         * Joysticks
         */
        ///@{
        void initialiseJoysticks();
        bool joysticksInitialised() {
            return m_bJoysticksInitialised;
        }
        const Vector2D joystickValue(int joy, int stick);
        ///@}
        
        ~InputHandler();

    private:
        InputHandler();
        
        static std::shared_ptr<InputHandler> m_spInstance;
        
        /**
         * Joysticks
         */
        ///@{
        std::vector<SDL_Joystick*> m_vJoysticks;
        std::vector<std::pair<Vector2D, Vector2D>> m_vJoystickValues;
        bool m_bJoysticksInitialised = false;
        const int m_joystickDeadZone = 10000;
        ///@}
    };
    
}

#endif
