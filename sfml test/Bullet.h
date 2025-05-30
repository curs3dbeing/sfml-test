#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:

	Bullet(float damage, sf::Vector2f velocity, sf::Texture& text, sf::Vector2f pos);

	bool				isExpired();
	void				update(float dt);
	void				rotate(float angle);
	sf::Sprite&			getSprite();

private:

	sf::Vector2f		pos;
	sf::Sprite			sprite;
	float				damage;
	const float			lifeTime = 4.f;
	float				livedTime = 0.f;
	const float			baseSpeed = 400.f;
	sf::Vector2f		velocity;
};