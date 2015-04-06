
#include <SDL.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

int main(int argc, char* args[])
{
    // initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        g_pWindow = SDL_CreateWindow("Setting up SDL",
                                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                     640, 480,
                                     SDL_WINDOW_SHOWN);
        
        if(g_pWindow != 0) {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }
        
    } else {
        return 1;
    }
    
    SDL_SetRenderDrawColor(g_pRenderer, 128, 128, 128, 255);

    SDL_RenderClear(g_pRenderer);
    
    SDL_RenderPresent(g_pRenderer);
    
    bool done = false;
    while (!done) {
    
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            switch(event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                    
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            done = true;
                            break;
                    }
                    break;
            }
        }
        
    }
    
    SDL_DestroyWindow(g_pWindow);
    SDL_Quit();
    
    return 0;
    
}

