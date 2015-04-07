//
//  TextureManager.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_TextureManager_h
#define yobatronika_TextureManager_h

#include <map>
#include <string>
#include <memory>

#include <SDL.h>

namespace Yoba {
    class TextureManager {
        
        std::map<std::string, SDL_Texture*> m_textureMap;
    
        static std::shared_ptr<TextureManager> m_spInstance;
        
        TextureManager(){};
    public:
        
        bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);
        
        void draw(std::string id, int x, int y, int width, int height,
                  SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                       SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        static std::shared_ptr<TextureManager> Instance()
        {
            if(m_spInstance == nullptr)
            {
                m_spInstance = std::shared_ptr<TextureManager>(new TextureManager());
            }
            return m_spInstance;
        }
        
        static void DeleteInstance() {
            m_spInstance.reset();
        }
    };
}

#endif
