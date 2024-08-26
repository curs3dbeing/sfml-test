#ifndef ROOM_HPP
#define ROOM_HPP
#include "SFML/Graphics.hpp"
#include "Block.h"
#include "vector"
#include "string"

class Room
{
private:

	Block**					room_size;
	int						x_size;
	int						y_size;
	const sf::Vector2f		wall_size = {100.f,56.25f};
	std::vector<sf::Sprite> allWalls;
	sf::Vector2f			room_pos;
	sf::Vector2f			walls_scale;
	
public:

	Room(int n, int k, sf::Vector2f room_pos /*room position*/);
	~Room();

	void						roomDraw(sf::RenderWindow& window);

	void						setFloor(sf::Texture&);
	void						setWalls(sf::Texture&);

	std::vector<sf::Sprite>&	getAllWalls();

	sf::Vector2f				getPos() const;
};

#endif

