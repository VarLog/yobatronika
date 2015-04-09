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
        enum MOUSE_BUTTONS
        {
            MOUSE_BUTTON_LEFT   = 0,
            MOUSE_BUTTON_MIDDLE = 1,
            MOUSE_BUTTON_RIGHT  = 2
        };
        
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
        const Vector2D joystickValue(int joy, int stick) const;
        bool joystickButtonState(int joy, int buttonNumber) const;
        ///@}
        
        /**
         * Mouse
         */
        ///@{
        bool mouseButtonState(MOUSE_BUTTONS button) const;
        const Vector2D mousePosition() const;
        ///@}
        
        /**
         * Keyboard
         */
        ///@{
        bool isKeyDown(SDL_Scancode key) const;
        ///@}

        ~InputHandler();

    private:
        InputHandler();
        
        static std::shared_ptr<InputHandler> m_spInstance;
        
        /**
         * Joysticks
         */
        ///@{
        void onJoystickAxisMove(SDL_Event& event);
        void onJoystickButtonDown(SDL_Event& event);
        void onJoystickButtonUp(SDL_Event& event);
        
        std::vector<SDL_Joystick*> m_vJoysticks;
        std::vector<std::pair<Vector2D, Vector2D>> m_vJoystickValues;
        std::vector<std::vector<bool>> m_vJoystickButtonStates;
        bool m_bJoysticksInitialised = false;
        const int m_joystickDeadZone = 10000;
        ///@}
        
        /**
         * Mouse
         */
        ///@{
        void onMouseMove(SDL_Event& event);
        void onMouseButtonDown(SDL_Event& event);
        void onMouseButtonUp(SDL_Event& event);
        
        std::vector<bool> m_vMouseButtonStates;
        Vector2D m_mousePosition;
        ///@}
        
        /**
         * Keyboard
         */
        ///@{
        void onKeyDown(SDL_Event& event);
        void onKeyUp(SDL_Event& event);
        
        const Uint8* m_keystates;
        ///@}
    };
    
}

#endif
