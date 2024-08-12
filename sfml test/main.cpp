#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>
#include "Character.h"

using namespace sf;

void Movement(RectangleShape& rect, RectangleShape& vision_box);
RenderWindow window(VideoMode(1000, 1000), "My Game");
Vector2f window_size = static_cast<sf::Vector2f>(window.getSize()); // window size


int main()
{
	Character player; // player
	std::string path = "C://Users//USER//Desktop//TPPO//sfml test//imagez//block.jpg";
	player.setTexture(path);
	player.setSprite();
	RectangleShape vision_box(Vector2f(400.f, 200.f)); // vision box - box for camera movement 

	// vision box atributes for modeling the camera movement and etc.
	vision_box.setOutlineThickness(3.f);
	vision_box.setOutlineColor(Color::White);
	vision_box.setFillColor(Color::Black);

	window.setFramerateLimit(120); //FPS border(just in case)

	vision_box.move(window_size.x / 2 - 200.f, window_size.y / 2 - 100.f);

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
			Movement(player.getHitbox(),vision_box);
			window.draw(vision_box);
			window.draw(player.getHitbox());
			// Render
			window.display();

	}
}


//vision_box is not used for now
void Movement(RectangleShape& rect, RectangleShape& vision_box) {
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
		rect.move(0.f, -8.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		rect.move(-8.f, 0.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		rect.move(0.f, 8.f);
		return;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		rect.move(8.f, 0.f);
		return;
	}
}