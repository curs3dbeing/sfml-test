#include "Character.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>


extern sf::Vector2f window_size;

Character::Character() {
	visionCircle.setFillColor(sf::Color::Transparent);
	visionCircle.setRadius(300.f);
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

sf::CircleShape& Character::getVisionCircle() {
	return this->visionCircle;
}

void Character::setVisionCircle(sf::CircleShape& visioncircle) {
	visionCircle = visioncircle;
}
void Character::changeVisionCircle(float radius) {
	this->visionCircle.setRadius(radius);
}

void Character::setTexture(std::string path) {
	this->img_path = path;
	this->texture.loadFromFile(path);
}
void Character::setSprite() {
	this->sprite.setTexture(this->getTexture());
}

void Character::setPosition(sf::Vector2f newpos) {
	this->sprite.setPosition(newpos);
}

sf::Vector2f Character::getPosition() {
	return this->getSprite().getGlobalBounds().getPosition();
}


sf::Texture& Character::getTexture() {
	return this->texture;
}