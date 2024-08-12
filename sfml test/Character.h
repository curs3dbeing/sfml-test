#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>

class Character : public Entity
{
public:
	Character();
	Character(float _HP, std::string _Name, std::string img_path, float speed);
	void setSpeed(float _speed);
	float getSpeed();
	sf::RectangleShape& getHitbox();
	void setTexture(std::string path);
	void setSprite();
	sf::Texture getTexture();
private:
	float speed;
	sf::RectangleShape hitbox;
};

#endif
