#ifndef BLOCK_HPP
#define BLOCK_HPP
#include "SFML\Graphics.hpp"
#include <string>
#include <map>
#include "Serializable.h"

enum class block_types {
	floor1,
	wall1
};



class Block : public Serializable
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
	static std::map<block_types,Block> allBlocks;

	Block();
	Block(std::string,bool,bool);
	Block(block_types, std::string, bool, bool);
	void setTextureReapeted(bool repeat);
	sf::Sprite& getSprite();
	std::string getImgPath();
	void setTexture(sf::Texture&);
	sf::Texture& getTexture();
	void setVisible(bool);
	void setPassable(bool);
	void setTextureSmooth(bool);
	void setPosition(sf::Vector2f pos);
	virtual bool isVisible();
	virtual bool isPassable();
	block_types& getBlockName();
	void serialize(std::ostream& os) const;
	void deserialize(std::istream& is);
};

#endif
