#include "Room.h"
#include "Block.h"
#include "SFML/Graphics.hpp"



Room::Room(int n, int k) {
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
			//room_size[i][j].getSprite().move(sf::Vector2f(100.f*j,100.f*i));
			window.draw(room_size[i][j].getSprite());
		}
	}
}

void Room::setBlocks(sf::Texture& texture) {
	for (int i = 0; i < y_size; i++) {
		for (int j = 0; j < x_size; j++) {
			this->room_size[i][j].setTexture(texture);
			this->room_size[i][j].setPosition(sf::Vector2f(100.f * j, 100.f * i));
		}
	}
}
