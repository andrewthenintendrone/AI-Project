#include "VectorMaths.h"

// returns the magnitude of the vector
float magnitude(sf::Vector2f vector)
{
    if (vector == sf::Vector2f(0, 0))
    {
        return 0;
    }
    return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

// returns the squared magnitude of a vector
float sqrMagnitude(sf::Vector2f vector)
{
    if (vector == sf::Vector2f(0, 0))
    {
        return 0;
    }
    return (vector.x * vector.x) + (vector.y * vector.y);
}

// returns the normalized vector
sf::Vector2f normalize(sf::Vector2f& input)
{
    if (input != sf::Vector2f(0, 0))
    {
        input = (input / magnitude(input));
    }
    return input;
}

// returns the normalized vector multiplied by the scalar
sf::Vector2f normalize(sf::Vector2f& input, float scalar)
{
    if (input != sf::Vector2f(0, 0))
    {
        input = (input / magnitude(input) * scalar);
    }
    return input;
}

// linearly interpolates between two vectors
sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
    return (start + percent * (end - start));
}

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f leftHandVector, sf::Vector2f rightHandVector)
{
    sf::Vector2f angleVector = leftHandVector - rightHandVector;
    return std::atan2f(angleVector.y, angleVector.x) * 180 / M_PI;
}