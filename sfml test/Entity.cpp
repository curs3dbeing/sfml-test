#include "Entity.h"
#include "Weapon.h"

Entity::Entity() {
	this->HP = 0;
}

Entity::Entity(float _HP, std::string img_path) : HP(_HP), img_path(img_path) {

	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(this->texture);
}

float& Entity::getHP() {
	return this->HP;
}

void Entity::zeroVelocity() {
	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Entity::addVelocity(sf::Vector2f velocity) {
	this->velocity += velocity;
}

void Entity::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}

sf::Vector2f& Entity::getVelocity() {
	return this->velocity;
}

void Entity::setWeapon(Weapon _weapon) {
	this->weapon=_weapon;
}
Weapon Entity::getWeapon() {
	return this->weapon;
}		

sf::Sprite& Entity::getSprite() {
	return this->sprite;
}