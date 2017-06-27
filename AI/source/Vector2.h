#pragma once
#include <math.h>
#include <iostream>
#include "SFML\System\Vector2.hpp"

namespace AFMaths
{   
    class Vector2
    {
    public:
        // variables
        union
        {
            struct
            {
                float v[2];
            };
            struct
            {
                float x;
                float y;
            };
        };

        // constructors and destructor
        Vector2();
        Vector2(const float& value);
        Vector2(float newX, float newY);
        Vector2(const Vector2& newVector);
        ~Vector2();

        // functions
        float dot(Vector2& rhs);
        Vector2 cross(Vector2& rhs);
        float magnitude();
        float squaremagnitude();
        void normalise();
        Vector2 normalized();
        sf::Vector2f toSFMLFloatVector();
        sf::Vector2i toSFMLIntVector();

        // shortcuts
        static Vector2 Up();
        static Vector2 Down();
        static Vector2 Left();
        static Vector2 Right();
        static Vector2 Zero();

        // overloads
        friend std::ostream& operator << (std::ostream& stream, const Vector2& vector);
        operator float *();
        float& operator [] (const int& index);
        bool operator == (const Vector2& rhs);
        void operator = (const Vector2& newVector);
        Vector2 operator + (const Vector2& rhs);
        void operator += (const Vector2& rhs);
        Vector2 operator - (const Vector2& rhs);
        void operator -= (const Vector2& rhs);
        Vector2 operator * (const Vector2& rhs);
        void operator *= (const Vector2& rhs);
        Vector2 operator * (const float& scalar);
        void operator *= (const float& scalar);
        friend Vector2 operator * (const float& scalar, Vector2& vector);
        Vector2 operator / (const float& scalar);
        void operator /= (const float& scalar);

        // swizzling
        Vector2 GetXX();
        Vector2 GetYX();
        Vector2 GetYY();
    };
}
