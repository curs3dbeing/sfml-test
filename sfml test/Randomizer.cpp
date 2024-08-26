#include "Randomizer.h"
#include "SFML/Graphics.hpp"
#include <random>

template<typename T>
T Randomizer::random_value_generator(T low_num, T high_num) {
	std::uniform_real_distribution<T> distribution(low_num, high_num);
	return distribution(this->generator);
}

template<>
sf::Vector2f Randomizer::random_value_generator(sf::Vector2f low_num, sf::Vector2f high_num) {
	std::uniform_real_distribution<float> distribution_x(low_num.x, high_num.x);
	std::uniform_real_distribution<float> distribution_y(low_num.y, high_num.y);
	return(sf::Vector2f(distribution_x(generator),distribution_y(generator)));
}

Randomizer::Randomizer() {}