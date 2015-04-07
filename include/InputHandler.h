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

namespace Yoba {
    
    class InputHandler {
    public:
        static std::shared_ptr<InputHandler> Instance();
        static void DeleteInstance();
        
        void update();
        void clean();
        
    private:
        InputHandler();
        
        static std::shared_ptr<InputHandler> m_spInstance;
    };
    
}

#endif
