#pragma once
#include "SFML\Graphics\Transform.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

// returns the magnitude of the vector
float magnitude(sf::Vector2f vector);

// returns the normalized vector
sf::Vector2f normalize(sf::Vector2f& input);

// returns the angle in degrees between two vectors
float angleBetweenVectors(sf::Vector2f leftHandVector, sf::Vector2f rightHandVector);