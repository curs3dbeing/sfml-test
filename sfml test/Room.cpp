#include "Room.h"
#include "Block.h"
#include "SFML/Graphics.hpp"

Room::Room(int n, int k) {
	this->x_size = n;
	this->y_size = k;
	this->room_size = new Block * [n];
	for (int i = 0; i < n; i++) {
		this->room_size[i] = new Block[k];
	}
}

Room::~Room() {
	for (int i = 0; i < this->y_size; i++) {
		delete[] this->room_size[i];
	}
	delete[] this->room_size;
}
