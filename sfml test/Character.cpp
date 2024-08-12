#include "Character.h"
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>

Character::Character(float _HP, std::string _Name, std::string img_path, sf::RectangleShape _hitbox, float speed) : Entity(_HP, _Name, _hitbox, img_path) {
	this->speed = speed;
}
