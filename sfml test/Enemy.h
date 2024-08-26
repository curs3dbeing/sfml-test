#pragma once
#include "Entity.h"
#include "Serializable.h"

enum EnemyNames {
	CUBE,
	RECTANGLE,
	CIRCLE
};

class Enemy: public Entity//, public Serializable
{

private:

	float				speed;
	sf::Vector2f		spawn_position;
	EnemyNames			name;

public:

	Enemy(float HP, float speed, EnemyNames name, std::string img_path, sf::Vector2f spawn_position) : Entity(HP, img_path), name(name), speed(speed), spawn_position(spawn_position) {}





};

