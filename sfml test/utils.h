#pragma once 
#include <SFML/Graphics.hpp>

float dot(sf::Vector2f left, sf::Vector2f right) {
	return left.x * right.x + left.y * right.y;
}