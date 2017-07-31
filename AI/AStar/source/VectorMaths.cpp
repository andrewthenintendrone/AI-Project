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

// reduces the magitude of the vector to max only if the magnitude is already bigger
sf::Vector2f truncate(sf::Vector2f& vector, float max)
{
    float i = std::min(magnitude(vector), max);
    return normalize(vector, i);
}

// linearly interpolates between two vectors
sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
    return (start + percent * (end - start));
}

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f lhs, sf::Vector2f rhs)
{
    sf::Vector2f angleVector = lhs - rhs;
    float angle = std::atan2f(angleVector.y, angleVector.x) * 180 / (float)M_PI;
    return angle < 0.0f ? angle + 360.0f : angle;
}

float vectorAngle(sf::Vector2f& vector)
{
    float angle = std::atan2f(vector.y, vector.x) / (float)M_PI * 180.0f;
    return angle < 0.0f ? angle + 360.0f : angle;
}

sf::Vector2f getRandomVector(float length)
{
    float randomAngle = ((float)rand() / RAND_MAX) * (float)M_PI * 2.0f;
    return sf::Vector2f(cosf(randomAngle), sinf(randomAngle) * length);
}
