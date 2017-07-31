#pragma once
#include "SFML\Graphics\Transform.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

// returns the magnitude of the vector
float magnitude(sf::Vector2f vector);

// returns the squared magnitude of a vector
float sqrMagnitude(sf::Vector2f vector);

// returns the normalized vector
sf::Vector2f normalize(sf::Vector2f& input);

// returns the normalized vector multiplied by the scalar
sf::Vector2f normalize(sf::Vector2f& vector, float scalar);

// reduces the magitude of the vector to max only if the magnitude is already bigger
sf::Vector2f truncate(sf::Vector2f& vector, float max);

// linearly interpolates between two vectors
sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent);

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f lhs, sf::Vector2f rhs);

// returns the angle of the vector
float vectorAngle(sf::Vector2f& vector);

// returns a random vector of a specified length
sf::Vector2f getRandomVector(float length);