#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "SFML\Graphics.hpp"
#include "string"

class Block
{
protected:
	std::string img_path;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	sf::Texture texture;
	bool visible;
	bool passable;
public:
	Block(sf::RectangleShape,std::string,bool,bool);
	virtual bool isVisible();
	virtual bool isPassable();
};

#endif
