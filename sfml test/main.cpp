#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include "Character.h"
#include "Room.h"
#include <vector>
#include <set>
#include <list>
#include <map>
#include <cmath>
#include "Block.h"
#include <stdlib.h>

using namespace sf;

RenderWindow window(VideoMode(1920, 1080), "My Game", sf::Style::Fullscreen& (sf::Style::Titlebar | sf::Style::Close));



Vector2f window_size = static_cast<sf::Vector2f>(window.getSize()); // window size
sf::View Camera(sf::FloatRect((window_size.x-1612.8f)/2, (window_size.y - 907.2f) / 2, 1612.8f, 907.2f)); // camera view

std::map<block_types, Block> Block::allBlocks; // hash-table of all blocks

sf::RectangleShape fog_of_war(window_size); // fog_of_war
sf::RectangleShape levelFloor(sf::Vector2f(-5000.f, -5000.f)); // floor

void addBlock(std::vector<Block>&, Block); 

void Movement(Character& player, RectangleShape& vision_box, float& dt);


int main()
{
	std::list<Block> blocks;
	fog_of_war.setFillColor(sf::Color::Black);
	levelFloor.move(sf::Vector2f(2500.f,2500.f));
	window.setVerticalSyncEnabled(true);
	/*blocks.push_back(Block(static_cast<block_types>(0), "imagez/floor1.png", true, true));
	blocks.push_back(Block(static_cast<block_types>(1), "imagez/wall1.png", true, false));

	for (auto block : blocks) {
		Block::allBlocks.insert(std::make_pair(block.getBlockName(), block));
	}
	
	std::ofstream blockFile("data//data.bin", std::ios::binary & std::ios::app);
	try {
		if (blockFile.is_open()) {
			for (auto block : blocks) {
				block.serialize(blockFile);
			}
		}
	}
	catch (std::ios_base::failure) {
		std::cerr << "error occured while serializing a blocks file";
		exit(-1);
	}*/

	//blocks.clear();
	// BLOCK FILE READ ( I HONESTLY DONT LIKE THIS PART (REWORK REQUIRED) ) 

	std::ifstream blocksFile("data//data.bin", std::ios::binary); 
	try {
		blocks.push_back(Block());
		std::list<Block>::iterator it = blocks.begin();
		
		blocksFile.seekg(0, std::ios::end);
		std::streampos end_of_file = blocksFile.tellg();
		blocksFile.seekg(0, std::ios::beg);

		if (blocksFile.is_open()) {
			while (blocksFile.tellg() != end_of_file) {
				it->deserialize(blocksFile);
				blocks.push_back(Block());
				it++;
			}
			blocks.pop_back();
		}

	}
	catch (std::ios_base::failure) {
		std::cerr << "error occured while deserializing a blocks file";
		exit(-1);
	}

	for (auto block : blocks) {
		Block::allBlocks.insert(std::make_pair(block.getBlockName(),block));
	}

	Block::allBlocks[block_types::floor1].setTextureReapeted(true);
	levelFloor.setTexture(&Block::allBlocks[block_types::floor1].getTexture());
	levelFloor.setTextureRect(sf::IntRect(levelFloor.getPosition().x,levelFloor.getPosition().y, levelFloor.getSize().x,levelFloor.getSize().y));

	//room
	int y_size = 1080 / 64;
	int x_size = 1920 / 64;
	Room mainroom(y_size,x_size-1);
	mainroom.setFloor(Block::allBlocks[block_types::floor1].getTexture());
	mainroom.setWalls(Block::allBlocks[block_types::wall1].getTexture());

	// player
	float dt;
	sf::Clock dt_clock;

	Character player;
	player.setSpeed(400.f);

	std::string path = "imagez/hero.png";

	player.setTexture(path);
	player.setSprite();
	player.getSprite().move(window_size.x / 2 - player.getTexture().getSize().x/2, window_size.y / 2 - player.getTexture().getSize().y/2);

	RectangleShape vision_box(Vector2f(700.f, 400.f)); // vision box - box for camera movement 
	// vision box atributes for modeling the camera movement and etc.
	vision_box.setFillColor(Color::Transparent);
	/*vision_box.setOutlineThickness(10.f);
	vision_box.setOutlineColor(sf::Color::White);*/

	window.setFramerateLimit(300); //FPS border(just in case)

	vision_box.move(window_size.x / 2 - vision_box.getSize().x/2, window_size.y / 2 - vision_box.getSize().y / 2);
	Event ev;
	while (window.isOpen()) {

		dt = dt_clock.restart().asSeconds();

		while (window.pollEvent(ev)) {

			switch (ev.type) {
			case Keyboard::Escape:
			{
				window.close();
				break;
			}
			case Event::Closed:
				window.close();
				break;
			}
		}

		player.zeroVelocity();

		window.setView(Camera);
		window.clear();
		//mainroom.roomDraw(window);
		window.draw(levelFloor);
		window.draw(vision_box);
		//window.draw(fog_of_war);
		window.draw(player.getVisionCircle());
		window.draw(player.getSprite());

		Movement(player, vision_box, dt);

		if (player.getPosition().x <= vision_box.getGlobalBounds().getPosition().x) { //left wall
			if (player.getPosition().y > vision_box.getGlobalBounds().getPosition().y || player.getPosition().y + player.getSprite().getGlobalBounds().height < vision_box.getGlobalBounds().height + vision_box.getPosition().y) {
				vision_box.move(player.getVelocity().x,0.f);
				Camera.move(player.getVelocity().x, 0.f);
			}
		}
		if (player.getPosition().y <= vision_box.getGlobalBounds().getPosition().y) { //top wall
			if (player.getPosition().x > vision_box.getGlobalBounds().getPosition().x || player.getPosition().x + player.getSprite().getGlobalBounds().width < vision_box.getGlobalBounds().width + vision_box.getPosition().x) {
				vision_box.move(0.f,player.getVelocity().y);
				Camera.move(0.f,player.getVelocity().y);
			}
		}
		if (player.getPosition().x+player.getSprite().getGlobalBounds().width >= vision_box.getGlobalBounds().width+vision_box.getPosition().x) { //right wall
			if (player.getPosition().y > vision_box.getGlobalBounds().getPosition().y || player.getPosition().y + player.getSprite().getGlobalBounds().height < vision_box.getGlobalBounds().height + vision_box.getPosition().y) {
				vision_box.move(player.getVelocity().x,0.f);
				Camera.move(player.getVelocity().x,0.f);
			}
		}
		if (player.getPosition().y+player.getSprite().getGlobalBounds().height >= vision_box.getGlobalBounds().height + vision_box.getPosition().y) { //bottom wall
			if (player.getPosition().x > vision_box.getGlobalBounds().getPosition().x || player.getPosition().x + player.getSprite().getGlobalBounds().width < vision_box.getGlobalBounds().width + vision_box.getPosition().x) {
				vision_box.move(0.f, player.getVelocity().y);
				Camera.move(0.f, player.getVelocity().y);
			}
		}
		
		//if (player.getPosition().x <= levelFloor.getPosition().x) { //left wall collision
		//	player.setPosition(sf::Vector2f(levelFloor.getPosition().x, player.getPosition().y));
		//}

		//if (player.getPosition().y <= 0.f) { //top wall collision
		//	player.setPosition(sf::Vector2f(player.getPosition().x, 0.f));
		//}

		//if (player.getPosition().x + player.getSprite().getGlobalBounds().width >= window_size.x) { //right wall collision
		//	player.setPosition(sf::Vector2f(window_size.x - player.getSprite().getGlobalBounds().width, player.getPosition().y));
		//}

		//if (player.getPosition().y + player.getSprite().getGlobalBounds().height >= window_size.y) { //bottom wall collision
		//	player.setPosition(sf::Vector2f(player.getPosition().x, window_size.y-player.getSprite().getGlobalBounds().height));
		//}

		window.display();

	}
}


//vision_box is not used for now
void Movement(Character& player, RectangleShape& vision_box, float& dt) {

	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
		player.setVelocity(sf::Vector2f(player.getSpeed()*dt/sqrt(2), -player.getSpeed() * dt / sqrt(2)));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
		player.setVelocity(sf::Vector2f(-player.getSpeed() * dt / sqrt(2), -player.getSpeed() * dt / sqrt(2)));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
		player.setVelocity(sf::Vector2f(-player.getSpeed() * dt / sqrt(2), player.getSpeed() * dt / sqrt(2)));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
		player.setVelocity(sf::Vector2f(player.getSpeed() * dt / sqrt(2), player.getSpeed() * dt / sqrt(2)));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.setVelocity(sf::Vector2f(0, -player.getSpeed() * dt));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.setVelocity(sf::Vector2f(-player.getSpeed() * dt, 0));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		player.setVelocity(sf::Vector2f(0, player.getSpeed() * dt));
		player.getSprite().move(player.getVelocity());
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.setVelocity(sf::Vector2f(player.getSpeed() * dt, 0));
		player.getSprite().move(player.getVelocity());
		return;
	}
}

void addBlock(std::vector<Block>& allBlocks, Block block) {
	sf::Texture texture = block.getTexture();
	bool visible = block.isVisible();
	bool passable = block.isPassable();
	block_types blockName = block.getBlockName();

}