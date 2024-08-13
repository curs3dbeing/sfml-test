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
