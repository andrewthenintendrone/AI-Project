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

sf::Vector2f truncate(sf::Vector2f& vector, float max);

sf::Vector2f scaleBy(sf::Vector2f& vector, float scalar);

// linearly interpolates between two vectors
sf::Vector2f Lerp(sf::Vector2f start, sf::Vector2f end, float percent);

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f leftHandVector, sf::Vector2f rightHandVector);