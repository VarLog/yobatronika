//
//  MainApplication.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 09.04.15.
//
//

#ifndef yobatronika_MainApplication_h
#define yobatronika_MainApplication_h

namespace Yoba {
    
    class MainApplication {

    private:
        
        MainApplication() = delete;
        ~MainApplication() = delete;

        static const int FPS = 60;
        static const int DELAY_TIME = 1000.0f / FPS;

    public:
        
        static int run(int argc, const char **argv);
        
    };
    
}

#endif
