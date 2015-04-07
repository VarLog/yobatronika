//
//  GameObject.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 07.04.15.
//
//

#ifndef yobatronika_GameObject_h
#define yobatronika_GameObject_h

#include <SDL.h>

#include <string>

namespace Yoba {
    
    class GameObject {
    private:
        void load(int x, int y, int width, int height, std::string textureID);

    public:
        GameObject(int x, int y, int width, int height, std::string textureID);
        virtual ~GameObject();
        
        virtual void draw(SDL_Renderer* pRenderer);
        
        virtual void update();
        virtual void clean();
    
        
    protected:
        
        std::string m_textureID;
        
        int m_currentFrame;
        int m_currentRow;
        
        int m_x;
        int m_y;
        
        int m_width;
        int m_height;
    };
   
}
#endif
