#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>


class Randomizer
{
private:
	std::random_device	device;
	std::mt19937		generator;
public:
	explicit			Randomizer();
	template<typename T>
	T					random_value_generator(T low_num, T high_num);
};


#endif RANDOMIZER_H