#include "Level.h"

void Level::generateLevel(float seed, int level) {

	gen.seed(seed);

	std::uniform_int_distribution<> dis(4, 5);

	int room_num = level * 3 + dis(gen);

	//rooms.resize(room_num);

}