#include "Block.h"
#include "SFML/Graphics.hpp"
#include <string>

Block::Block() {

}

Block::Block(std::string img_path, bool visible, bool passable) : img_path(img_path), visible(visible), passable(passable) {
	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(this->texture);
}

bool Block::isPassable() {
	return this->passable;
}

bool Block::isVisible() {
	return this->visible;
}

sf::Sprite& Block::getSprite() {
	return this->sprite;
}

void Block::setPassable(bool passable) {
	this->passable = passable;
}

void Block::setVisible(bool visible) {
	this->visible = visible;
}

void Block::setTexture(sf::Texture& texture) {
	this->texture = texture;
	this->sprite.setTexture(this->texture);
}

void Block::setPosition(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

sf::Texture& Block::getTexture() {
	return this->texture;
}