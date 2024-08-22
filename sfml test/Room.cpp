#include "Room.h"
#include "Block.h"
#include "SFML/Graphics.hpp"



Room::Room(int n /*y size*/, int k /*x_size*/, sf::Vector2f room_pos  /*roompos*/ ) {
	this->x_size = k;
	this->y_size = n;
	this->room_pos = room_pos;
	this->room_size = new Block * [n];
	for (int i = 0; i < n; i++) {
		this->room_size[i] = new Block[k];
	}
}

// ??????????????????????
Room::~Room() {
	for (int i = 0; i < this->y_size; i++) {
		delete[] this->room_size[i];
	}
	delete[] this->room_size;
}


void Room::roomDraw(sf::RenderWindow& window) {
	/*for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			window.draw(room_size[i][j].getSprite());
		}
	}*/
	int walls = allWalls.size();
	for (int i = 0; i < walls; i++) {
		allWalls[i].setScale(walls_scale);
		window.draw(allWalls[i]);
	}
}

void Room::setWalls(sf::Texture& texture) {
	int x = texture.getSize().x;
	int y = texture.getSize().y;
	walls_scale = { wall_size.x / x,wall_size.y/y };
	x = x * walls_scale.x;
	y = y * walls_scale.y;
	int x_size = 1920 / x;
	int y_size = 1080 / y;
	allWalls.resize((x_size + y_size)*2);
	for (int wall = 0,k=0; wall < 4; wall++) {
		switch (wall) {
		case 0:
			for (int i = 0; i < x_size; i++, k++) {
				allWalls[k].setTexture(texture);
				allWalls[k].setPosition(room_pos.x+x*i,room_pos.y);
			}
			break;
		case 1:
			for (int i = 0; i < y_size-1; i++, k++) {
				allWalls[k].setTexture(texture);
				allWalls[k].setPosition(room_pos.x + x * x_size, room_pos.y + y * i);
				allWalls[k].rotate(90.f);
			}
			break;
		case 2:
			for (int i = x_size; i > 0; i--, k++) {
				allWalls[k].setTexture(texture);
				allWalls[k].setPosition(room_pos.x +x*i,room_pos.y+y*y_size);
				allWalls[k].rotate(180.f);
			}
			break;
		case 3:
			for (int i = y_size; i > 1; i--, k++) {
				allWalls[k].setTexture(texture);
				allWalls[k].setPosition(room_pos.x, room_pos.y + y * i);
				allWalls[k].rotate(270.f);
			}
			break;
		}
	}
}

void Room::setFloor(sf::Texture& texture) {
	for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			this->room_size[i][j].setTexture(texture);
			this->room_size[i][j].setPosition(sf::Vector2f(this->room_size[i][j].getTexture().getSize().x * j, this->room_size[i][j].getTexture().getSize().y * i));
		}
	}
}

sf::Vector2f Room::getPos() const{
	return this->room_pos;
}
