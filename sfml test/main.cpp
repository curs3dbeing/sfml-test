#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include <random>
#include "Character.h"
#include "Room.h"

using namespace sf;

void Movement(Sprite& rect, RectangleShape& vision_box);
RenderWindow window(VideoMode(1920, 1080), "My Game", sf::Style::Default);
Vector2f window_size = static_cast<sf::Vector2f>(window.getSize()); // window size

int main()
{
	//room
	Room mainroom(9,16);
	sf::Texture blocktexture;
	std::string floorpath = "imagez/block_floor.png";
	blocktexture.loadFromFile(floorpath);
	mainroom.setBlocks(blocktexture);

	

	// player
	Character player; 
	std::string path = "imagez/hero.png";	
	player.setTexture(path);
	player.setSprite();
	player.getSprite().move(window_size.x / 2 - player.getTexture().getSize().x/2, window_size.y / 2 - player.getTexture().getSize().y/2);



	RectangleShape vision_box(Vector2f(700.f, 400.f)); // vision box - box for camera movement 
	// vision box atributes for modeling the camera movement and etc.
	vision_box.setOutlineThickness(3.f);
	vision_box.setOutlineColor(Color::White);
	vision_box.setFillColor(Color::Black);
	vision_box.setFillColor(Color::Transparent);

	window.setFramerateLimit(120); //FPS border(just in case)

	vision_box.move(window_size.x / 2 - vision_box.getSize().x/2, window_size.y / 2 - vision_box.getSize().y / 2);
	Event ev;
	while (window.isOpen()) {
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
			window.clear();
			mainroom.roomDraw(window);
			window.draw(vision_box);
			window.draw(player.getSprite());

			Movement(player.getSprite(), vision_box);

			window.display();

	}
}


//vision_box is not used for now
void Movement(Sprite& rect, RectangleShape& vision_box) {
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
		rect.move(5.f, -5.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
		rect.move(-5.f, -5.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) {
		rect.move(-5.f, 5.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
		rect.move(5.f, 5.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		rect.move(0.f, -7.07f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		rect.move(-7.07f, 0.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		rect.move(0.f, 7.07f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		rect.move(7.07f, 0.f);
		return;
	}
}