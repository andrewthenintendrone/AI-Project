#include "VectorMaths.h"

// returns the magnitude of the vector
float magnitude(sf::Vector2f vector)
{
    if (vector == sf::Vector2f(0, 0))
    {
        return 1;
    }
    return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

// returns the normalized vector
sf::Vector2f normalize(sf::Vector2f& input)
{
    input = (input / magnitude(input));
    return input;
}

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f leftHandVector, sf::Vector2f rightHandVector)
{
    sf::Vector2f angleVector = leftHandVector - rightHandVector;
    return std::atan2f(angleVector.y, angleVector.x) * 180 / (float)M_PI;
}