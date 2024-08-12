#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include "SFML/Graphics.hpp"
#include "Weapon.h"

class Entity
{
protected:
	float HP;
	sf::RectangleShape hitbox;
	std::string Name;
	Weapon weapon;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string img_path;
public:
	Entity(float _HP, std::string _Name, sf::RectangleShape _hitbox, std::string img_path);

	virtual float getHP();
	virtual std::string getName();
	virtual void setWeapon(Weapon _weapon);
	virtual Weapon getWeapon();

};

#endif