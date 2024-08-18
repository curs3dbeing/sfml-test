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

	sf::CircleShape& getVisionCircle();
	void setVisionCircle(sf::CircleShape&);
	void changeVisionCircle(float radius);

	void setTexture(std::string path);
	sf::Texture& getTexture();

	void setSprite();

private:
	float speed;
	sf::CircleShape visionCircle;
};

#endif
