#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include "Character.h"
#include "Room.h"
#include <vector>
#include <map>
#include <set>
#include <list>
#include <map>
#include <cmath>
#include <random>
#include "Block.h"
#include "utils.h"
#include "Randomizer.h"
#include <stdlib.h>

using namespace sf;
#define PI 3.1415926535

RenderWindow window(VideoMode(1920, 1080), "My Game", sf::Style::Fullscreen& (sf::Style::Titlebar | sf::Style::Close));


const float CAMERA_HEIGHT = 907.2f;
const float CAMERA_WIDTH = 1612.8f;

Vector2f window_size = static_cast<sf::Vector2f>(window.getSize()); // window size
sf::View Camera(sf::FloatRect((window_size.x-CAMERA_WIDTH)/2, (window_size.y - CAMERA_HEIGHT) / 2, CAMERA_WIDTH, CAMERA_HEIGHT)); // camera view

std::map<block_types, Block> Block::allBlocks; // hash-table of all blocks

sf::RectangleShape fog_of_war(window_size); // fog_of_war
sf::RectangleShape levelFloor(sf::Vector2f(-5000.f, -5000.f)); // floor

void addBlock(std::vector<Block>&, Block); 
void fileWrite(std::list<Block>);
void fileRead(std::list<Block>&);

void Shoot(Character& player, float& dt, sf::Texture& bullet_txt);
//Bullet stuff
bool canShoot = true;
const float shootCd = 0.2f;
float lastShoot = 0.f;
const float bullet_vel = 800;
//delete later
sf::Vector2i mousePos;
Text mouseText;
Font mainFont;

void Movement(Character& player, RectangleShape& vision_box, float& dt);
void WallCollision(Character& player, Room& mainroom);

int main()
{
	std::list<Block> blocks;
	std::map<std::string, sf::Texture> res = loadTextureFolder("imagez/bullets");
	fog_of_war.setFillColor(sf::Color::Black);
	levelFloor.move(sf::Vector2f(2500.f,2500.f));
	Randomizer generate;
	int n = 15;
	int fh = 2954;
	std::cout << generate.random_value_generator(n, fh);

	//init font
	if (!mainFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		throw std::runtime_error("error with font loading");
	}
	mouseText.setFont(mainFont);

	/*************************
	
			blocks.push_back(Block(static_cast<block_types>(0), "imagez/floor1.png", true, true));
			blocks.push_back(Block(static_cast<block_types>(1), "imagez/wall1.png", true, false));
			fileWrite(blocks);

	*************************/

	fileRead(blocks);

	for (auto block : blocks) {
		Block::allBlocks.insert(std::make_pair(block.getBlockName(),block));
	}

	Block::allBlocks[block_types::floor1].setTextureReapeted(true);
	Block::allBlocks[block_types::floor1].setTextureSmooth(true);
	levelFloor.setTexture(&Block::allBlocks[block_types::floor1].getTexture());
	levelFloor.setTextureRect(sf::IntRect(levelFloor.getPosition().x,levelFloor.getPosition().y, levelFloor.getSize().x,levelFloor.getSize().y));

	//room
	int y_size = 1080 / 64;
	int x_size = 1920 / 64;

	Room mainroom(y_size,x_size-1,sf::Vector2f(0.f,0.f));

	mainroom.setFloor(Block::allBlocks[block_types::floor1].getTexture());
	mainroom.setWalls(Block::allBlocks[block_types::wall1].getTexture());

	// player
	float dt;
	sf::Clock dt_clock;

	Character player;
	player.setSpeed(STARTING_SPEED);

	std::string path = "imagez/hero.png";
	std::string bullet_img = "imagez/bullets/bullet1.png";

	sf::Texture bullet;
	bullet.loadFromFile(bullet_img);
	bullet.setSmooth(true);

	player.setTexture(path);
	player.setSprite();
	player.getSprite().move(window_size.x / 2 - player.getTexture().getSize().x/2, window_size.y / 2 - player.getTexture().getSize().y/2); //move player to center

	RectangleShape vision_box(Vector2f(700.f, 400.f));
	vision_box.setFillColor(Color::Transparent);
	vision_box.move(window_size.x / 2 - vision_box.getSize().x/2, window_size.y / 2 - vision_box.getSize().y / 2);

	window.setFramerateLimit(300);
	Event ev;
	while (window.isOpen()) {

		dt = dt_clock.restart().asSeconds();

		while (window.pollEvent(ev)) {

			switch (ev.type) {
				case Event::KeyPressed:
				{
					if (ev.key.code==Keyboard::Escape) {
						window.close();
					}
					break;
				}
				case Event::Closed:
					window.close();
					break;
			}
		}

		window.setView(Camera);
		window.clear();
		window.draw(levelFloor);
		mainroom.roomDraw(window);
		window.draw(vision_box);
		//window.draw(fog_of_war);
		window.draw(player.getVisionCircle());

		Movement(player, vision_box, dt);
		WallCollision(player,mainroom);
		player.getSprite().move(player.getVelocity());
		window.draw(player.getSprite());
		mousePos = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition()));
		Shoot(player, dt, bullet);

		mouseText.setString(std::to_string(mousePos.x) + " : " + std::to_string(mousePos.y));
		mouseText.setCharacterSize(24);
		mouseText.setPosition(Camera.getCenter().x - Camera.getSize().x / 2 + 5, Camera.getCenter().y - Camera.getSize().y / 2 + 5);

		window.draw(mouseText);

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

		window.display();

	}
}



void Shoot(Character& player, float& dt, sf::Texture& bullet_txt) {
	if (Keyboard::isKeyPressed(Keyboard::Space) && canShoot) {

		lastShoot = 0.f;
		canShoot = false;

		sf::FloatRect bounds = player.getSprite().getGlobalBounds();
		sf::Vector2f pos(bounds.left + bounds.width / 2 - bounds.width / 6, bounds.top + bounds.height / 2 - bounds.height / 6);

		sf::Vector2f direction = sf::Vector2f(mousePos) - player.getCenteredPosition();
		bool fix_angle = direction.y > 0;
		sf::Vector2f baseLine = sf::Vector2f(-1, 0);
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length != 0.f) {
			direction /= length;
		}
		float cos = dot(direction, baseLine);
		float angle = std::acos(cos) * 180 / PI;
		if (fix_angle) {
			angle = 360 - angle;
		}
		player.bullets.push_back(std::make_unique<Bullet>(10.f, direction * bullet_vel, bullet_txt, pos));
		player.bullets[player.bullets.size() - 1].get()->rotate(angle);
	}

	lastShoot += dt;

	if (lastShoot > shootCd) {
		canShoot = true;
	}

	for (auto it = player.bullets.begin(); it != player.bullets.end(); ) {
		it->get()->update(dt);
		if (it->get()->isExpired()) {
			it = player.bullets.erase(it);
		}
		else {
			window.draw(it->get()->getSprite());
			++it;
		}
	}
}

//vision_box is not used for now
void Movement(Character& player, RectangleShape& vision_box, float& dt) {
	player.zeroVelocity();

	sf::Vector2f velocity(0.f, 0.f);

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		velocity.y -= dt * player.getSpeed();
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		velocity.x -= dt * player.getSpeed();
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		velocity.y += dt * player.getSpeed();
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		velocity.x += dt * player.getSpeed();
	}

	float l = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (l != 0) {
		velocity /= l;
	}

	velocity *= player.getSpeed() * dt;
	player.addVelocity(velocity);
	//player.getSprite().move(player.getVelocity()); //-> came into main() after collision check function
}

void fileWrite(std::list<Block> blocks) {

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
	}
}
void fileRead(std::list<Block>& blocks) {

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
}
void WallCollision(Character& player, Room& mainroom) {
	for (auto& wall : mainroom.getAllWalls()) {

		FloatRect wallBounds = wall.getGlobalBounds();
		FloatRect playerBounds = player.getSprite().getGlobalBounds();
		
		FloatRect nextPos = playerBounds;
		nextPos.left += player.getVelocity().x;
		nextPos.top += player.getVelocity().y;

		if (wallBounds.intersects(nextPos)) {
			//Top Collision
			if (playerBounds.top > wallBounds.top
				&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left) 
			{
				player.setVelocity({ player.getVelocity().x, 0.f });
				player.setPosition({ playerBounds.left,wallBounds.top + wallBounds.height });
			}
			//Bottom Collision
			else if (playerBounds.top < wallBounds.top
				&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
				&& playerBounds.left < wallBounds.left + wallBounds.width
				&& playerBounds.left + playerBounds.width > wallBounds.left)
			{
				player.setVelocity({ player.getVelocity().x, 0.f });
				player.setPosition({ playerBounds.left,wallBounds.top - playerBounds.height });
			}
			//Right Collision
			if (playerBounds.left < wallBounds.left
				&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top) 
			{
				player.setVelocity({0.f,player.getVelocity().y});
				player.setPosition(sf::Vector2f(wallBounds.left-playerBounds.width, playerBounds.top));
			}
			//Left Collision
			else if (playerBounds.left > wallBounds.left
				&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
				&& playerBounds.top < wallBounds.top + wallBounds.height
				&& playerBounds.top + playerBounds.height > wallBounds.top)
			{
				player.setVelocity({ 0.f,player.getVelocity().y });
				player.setPosition(sf::Vector2f(wallBounds.left + wallBounds.width, playerBounds.top));
			}
		}

	}
}

void addBlock(std::vector<Block>& allBlocks, Block block) {
	sf::Texture texture = block.getTexture();
	bool visible = block.isVisible();
	bool passable = block.isPassable();
	block_types blockName = block.getBlockName();
}