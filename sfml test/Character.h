#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>

class Character : public Entity
{
public:
	Character(float _HP, std::string _Name, std::string img_path, sf::RectangleShape _hitbox);
	void setSpeed(float _speed);
	float getSpeed();
private:
	float speed;
};

#endif
