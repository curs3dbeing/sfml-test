#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include "SFML/Graphics.hpp"
#include "Weapon.h"

class Entity
{
protected:
	float HP;
	sf::Vector2f velocity = sf::Vector2f(0.f,0.f);
	std::string Name;
	Weapon weapon;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string img_path;
public:
	Entity();
	Entity(float _HP, std::string _Name, std::string img_path);

	virtual void zeroVelocity();
	virtual sf::Vector2f& getVelocity();
	virtual void setVelocity(sf::Vector2f);
	virtual float& getHP();
	virtual std::string getName();
	virtual void setWeapon(Weapon _weapon);
	virtual Weapon getWeapon();
	virtual sf::Sprite& getSprite();

};

#endif