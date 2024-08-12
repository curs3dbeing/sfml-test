#include "Character.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>

extern sf::Vector2f window_size;

Character::Character() {
	this->hitbox = sf::RectangleShape(sf::Vector2f(100.f, 100.f));
	this->hitbox.move(window_size.x / 2 - 50.f, window_size.y / 2 - 50.f);
	this->hitbox.setFillColor(sf::Color::Red);
}

Character::Character(float _HP, std::string _Name, std::string img_path, float speed) : Entity(_HP, _Name, img_path) {
	this->speed = speed;
}

void Character::setSpeed(float speed) {
	this->speed = speed;
}

float Character::getSpeed() {
	return this->speed;
}

sf::RectangleShape& Character::getHitbox() {
	return this->hitbox;
}

void Character::setTexture(std::string path) {
	this->img_path = path;
	this->texture.loadFromFile(path);
}
void Character::setSprite() {
	this->sprite.setTexture(this->getTexture());
}

sf::Texture Character::getTexture() {
	return this->texture;
}