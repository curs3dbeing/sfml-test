#include "Bullet.h"
#include <chrono>

Bullet::Bullet(float damage, sf::Vector2f velocity, sf::Texture& text, sf::Vector2f pos) : damage(damage), velocity(velocity), pos(pos) {
	sprite.setTexture(text);
	sprite.setPosition(pos);

	//startTime = std::chrono::system_clock::now().time_since_epoch().count();
	//livedTime = startTime;
}

bool Bullet::isExpired() {
	return livedTime > lifeTime;
}

void Bullet::update(float dt) {
	livedTime += dt;
	sprite.move(dt * velocity);
}

sf::Sprite& Bullet::getSprite() {
	return sprite;
}

void Bullet::rotate(float angle) {
	sprite.rotate(angle);
}