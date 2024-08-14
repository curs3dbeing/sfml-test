#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "SFML\Graphics.hpp"
#include "string"

enum block_types {
	floor1,
	floor2,
	floor3,
	wall1,
	wall2,
	wall3
};

class Block
{
protected:
	block_types blockName;
	std::string img_path;
	sf::Sprite sprite;
	sf::RectangleShape shape;
	sf::Texture texture;
	bool visible;
	bool passable;
public:
	Block();
	Block(std::string,bool,bool);
	sf::Sprite& getSprite();
	void setTexture(sf::Texture&);
	sf::Texture& getTexture();
	void setVisible(bool);
	void setPassable(bool);
	void setPosition(sf::Vector2f pos);
	virtual bool isVisible();
	virtual bool isPassable();
};

#endif
