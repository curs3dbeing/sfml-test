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

std::string Block::getImgPath() {
	return this->img_path;
}

void Block::setTextureReapeted(bool repeat) {
	this->texture.setRepeated(repeat);
}

block_types& Block::getBlockName() {
	return this->blockName;
}

Block::Block(block_types blockName, std::string img_path, bool visible, bool passable) : blockName(blockName), img_path(img_path), visible(visible), passable(passable) {
	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(texture);
}

void Block::serialize(std::ostream& os) const {

	int blockName = static_cast<int>(this->blockName); // enum to int value
	os.write(reinterpret_cast<const char*>(&blockName), sizeof(int)); // block name write

	int img_pathLength = static_cast<int>(this->img_path.length()); // image length
	os.write(reinterpret_cast<const char*>(&img_pathLength),sizeof(int)); // img length write
	os.write(this->img_path.c_str(), img_pathLength); //img_path write

	bool isPassable = this->passable;
	bool isVisible = this->visible;
	os.write(reinterpret_cast<const char*>(&isPassable),sizeof(bool));
	os.write(reinterpret_cast<const char*>(&isVisible), sizeof(bool));
}

void Block::deserialize(std::istream& is) {
	is.read(reinterpret_cast<char*>(&blockName), sizeof(int));

	int img_pathLength;
	is.read(reinterpret_cast<char*>(&img_pathLength), sizeof(int));
	img_path.resize(img_pathLength);
	is.read(&img_path[0], img_pathLength);

	this->texture.loadFromFile(img_path);
	this->sprite.setTexture(texture);

	is.read(reinterpret_cast<char*>(&passable), sizeof(bool));
	is.read(reinterpret_cast<char*>(&visible), sizeof(bool));
}