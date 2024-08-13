#ifndef ROOM_HPP
#define ROOM_HPP
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "vector"
#include "string"

class Room
{
private:
	Block** room_size;
	int x_size;
	int y_size;
	
public:
	Room(int n, int k);
	~Room();
	void roomDraw(sf::RenderWindow& window);
	void setBlocks(sf::Texture&);
};

#endif

