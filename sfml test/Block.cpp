#include "Block.h"
#include "SFML/Graphics.hpp"
#include <string>

Block::Block(sf::RectangleShape shape, std::string img_path, bool visible, bool passable) : shape(shape), img_path(img_path), visible(visible), passable(passable) {
	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(this->texture);
}

bool Block::isPassable() {
	return this->passable;
}

bool Block::isVisible() {
	return this->visible;
}