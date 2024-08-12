#include "Entity.h"
#include "Weapon.h"


Entity::Entity(float _HP, std::string _Name, sf::RectangleShape _hitbox, std::string img_path) : HP(_HP), Name(_Name), hitbox(_hitbox), img_path(img_path) {
	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(this->texture);

}

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
