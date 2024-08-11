#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <iostream>

using namespace sf;

void Update(RenderWindow&);

int main()
{
	RenderWindow window(VideoMode(1000, 900), "My Game");
	/*Vector2f windowsize = static_cast<sf::Vector2f>(window.getSize());*/
	RectangleShape rect(Vector2f(100.f,100.f));
	rect.setFillColor(Color::Red);

	Event ev;

	while (window.isOpen()) {

		while (window.pollEvent(ev)) {

			switch (ev.type) {
			case Event::KeyPressed:
				if (ev.type == Keyboard::Escape) {
					window.close();
					break;
				}
				if (ev.key.code == Keyboard::W) {
					rect.move(0.f, -3.f);
					break;
				}
				if (ev.key.code == Keyboard::A) {
					rect.move(-3.f, 0.f);
					break;
				}
				if (ev.key.code == Keyboard::S) {
					rect.move(0.f, 3.f);
					break;
				}
				if (ev.key.code == Keyboard::D) {
					rect.move(3.f, 0.f);
					break;
				}
			case Event::Closed:
				window.close();
				break;

			case Event::MouseButtonPressed:
				if (ev.key.code == Mouse::Left) {
					rect.setFillColor(Color::Green);
					break;
				}
				if (ev.key.code == Mouse::Right) {
					rect.setFillColor(Color::Red);
					break;
				}
			}
		}
		window.clear();
		// Draw
		window.draw(rect);
		// Render
		window.display();

	}

}