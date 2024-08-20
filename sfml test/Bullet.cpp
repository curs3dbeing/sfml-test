#include "Bullet.h"
#include <chrono>

Bullet::Bullet(float damage, float velocity, sf::Texture text, sf::Vector2f pos) : damage(damage), velocity(velocity), pos(pos) {
	sprite.setTexture(text);
	sprite.setPosition(pos);

	startTime = std::chrono::system_clock::now().time_since_epoch().count();
	livedTime = startTime;
}

bool Bullet::isExpired() {
	return (livedTime - startTime) > lifeTime;
}

void Bullet::update(float dt) {
	livedTime = std::chrono::system_clock::now().time_since_epoch().count();
	sprite.move(sf::Vector2f(dt * velocity, 0));
}

sf::Sprite Bullet::getSprite() {
	return sprite;
}