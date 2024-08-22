#pragma once 
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <exception>

float dot(sf::Vector2f left, sf::Vector2f right) {
	return left.x * right.x + left.y * right.y;
}

std::map<std::string,sf::Texture> loadTextureFolder(std::string path) {
	std::map<std::string, sf::Texture> texts;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		sf::Texture newText;
		if (newText.loadFromFile(entry.path().generic_string())) {
			texts[entry.path().stem().string()] = newText;
		}
		else {
			throw std::runtime_error("failed to load file from " + path);
		}

	}
	return texts;
}