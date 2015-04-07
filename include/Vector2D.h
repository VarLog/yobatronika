//
//  Vector2D.h
//  yobatronika
//
//  Created by Maxim Fedorenko on 08.04.15.
//
//

#ifndef yobatronika_Vector2D_h
#define yobatronika_Vector2D_h

#include <math.h>

namespace Yoba {
    
    class Vector2D {
    public:
        Vector2D(float x, float y);
        
        float getX() const;
        float getY() const;
        
        void setX(float x);
        void setY(float y);
    
        float length() const;
        
        Vector2D operator+(const Vector2D& v2) const;
        friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
        {
            v1.m_x += v2.m_x;
            v1.m_y += v2.m_y;
            return v1;
        }
        
        Vector2D operator*(float scalar);
        Vector2D& operator*=(float scalar);
        
        Vector2D operator-(const Vector2D& v2) const;
        friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
        {
            v1.m_x -= v2.m_x;
            v1.m_y -= v2.m_y;
            return v1;
        }
        
        Vector2D operator/(float scalar);
        Vector2D& operator/=(float scalar);
        
        void normalize();
        
    private:
        float m_x;
        float m_y;
    };
    
}

#endif
