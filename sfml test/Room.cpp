#include "Room.h"
#include "Block.h"
#include "SFML/Graphics.hpp"



Room::Room(int n /*y size*/, int k /*x_size*/) {
	this->x_size = k;
	this->y_size = n;
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
	for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			window.draw(room_size[i][j].getSprite());
		}
	}
}

void Room::setWalls(sf::Texture& texture) {
	int x = texture.getSize().x;
	int y = texture.getSize().y;
	int x_size = 1920 / x;
	int y_size = 1080 / y;
	for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			//this->room_size[i][j].setTexture(texture);
			//this->room_size[i][j].setPosition(sf::Vector2f(x * j, y * i));
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
