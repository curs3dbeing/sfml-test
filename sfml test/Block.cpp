#include "Block.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "Serializable.h"

block_types last_in_enum = block_types::wall1;

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

block_types& Block::getBlockName() {
	return this->blockName;
}

Block::Block(block_types blockName, std::string img_path, bool visible, bool passable) : blockName(blockName), img_path(img_path), visible(visible), passable(passable) {
	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(texture);
}

auto Block::serialize(std::ostream& os) const -> std::size_t {
	os.write(reinterpret_cast<char*>(this),sizeof(this));
}

auto Block::deserialize(std::istream is) -> std::size_t {
	std::size_t size = 25;
	return size;
}

auto Block::serialized_size() const -> std::size_t {
	std::size_t size = 25;
	return size;
}