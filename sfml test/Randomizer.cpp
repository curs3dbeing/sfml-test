#include "Randomizer.h"
#include <random>

template<typename T>
T& Randomizer::random_value_generator(T low_num, T high_num) {
	std::uniform_real_distribution<T> distribution(low_num, high_num);
	return distribution(this->generator);
}

Randomizer::Randomizer() {
}