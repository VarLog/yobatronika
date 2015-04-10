//
//  Game.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef __yobatronika__Game__
#define __yobatronika__Game__

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "InputHandler.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"

namespace Yoba {
    
    class Game {
    public:
        static constexpr char const *title = "YOBAtronika";
        
        bool init(int xpos, int ypos, int width, int height);

        ~Game();
        
        void render();
        void update();
        void handleEvents();
        
        void quit();
        
        bool running();
        
        SDL_Renderer* renderer() const;
        const std::shared_ptr<GameStateMachine> stateMachine() const;
        
        static std::shared_ptr<Game> Instance();
        static void DeleteInstance();
        
    private:
        
        Game();
        
        static std::shared_ptr<Game> m_spInstance;

        void clean();

        static constexpr int sdl_init_flags = SDL_WINDOW_SHOWN;
        static constexpr int sdl_render_flags = SDL_RENDERER_PRESENTVSYNC;
        static constexpr int sdl_img_flags = IMG_INIT_PNG;

        bool m_bRunning = false;
        
        SDL_Window *m_pWindow = nullptr;
        SDL_Renderer *m_pRenderer = nullptr;
        
        std::shared_ptr<GameStateMachine> m_spGameStateMachine = nullptr;
    };
}

#endif /* defined(__yobatronika__Game__) */
