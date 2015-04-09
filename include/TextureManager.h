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
    private:
        std::map<std::string, SDL_Texture*> m_textureMap;
    
        static std::shared_ptr<TextureManager> m_spInstance;
        
        /// \todo other constructors
        TextureManager(){};
    public:
        
        ~TextureManager();
        
        bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);
        
        void draw(std::string id, int x, int y, int width, int height,
                  SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                       SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        void clearFromTextureMap(std::string id);
        void clean();
        
        static std::shared_ptr<TextureManager> Instance();
        static void DeleteInstance();
    };
    
}

#endif
