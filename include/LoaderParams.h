//
//  LoaderParams.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#ifndef yobatronika_LoaderParams_h
#define yobatronika_LoaderParams_h

#include <string>

namespace Yoba {
    
    class LoaderParams {
    public:
        LoaderParams(int x, int y, int width, int height, int numFrames, std::string textureID)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_numFrames(numFrames), m_textureID(textureID)
        { }
        
        int getX() const { return m_x; }
        int getY() const { return m_y; }
        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }
        int getNumFaces() const { return m_numFrames; }
        std::string getTextureID() const { return m_textureID; }
        
    private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_numFrames;
        std::string m_textureID;
    };
    
}

#endif
