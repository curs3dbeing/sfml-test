#include "Entity.h"
#include "Weapon.h"


float Entity::getHP() {
	return this->HP;
}

std::string Entity::getName() {
	return this->Name;
}

void Entity::setWeapon(Weapon _weapon) {
	this->weapon=_weapon;
}
Weapon Entity::getWeapon() {
	return this->weapon;
}		
