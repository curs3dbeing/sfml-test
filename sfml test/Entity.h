#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
#include "Weapon.h"

class Entity
{
protected:
	float HP;
	std::string Name;
	Weapon weapon;
public:
	Entity(float _HP, std::string _Name) : HP(_HP), Name(_Name) {}

	virtual float getHP();
	virtual std::string getName();
	virtual void setWeapon(Weapon _weapon);
	virtual Weapon getWeapon();

};

#endif