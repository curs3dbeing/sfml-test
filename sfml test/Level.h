#pragma once
#include <vector>
#include <random>

#include "Room.h"

class Level {
private:
	int _levelN;
	//std::vector<Room> rooms;

	std::mt19937 gen;

public:
	void generateLevel(float seed, int level);
	
	Level();
	~Level();
};
