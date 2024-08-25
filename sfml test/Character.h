#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include <string>
#include "Bullet.h"
#include <memory>

class Character : public Entity
{
public:

	Character();
	Character(float _HP, std::string _Name, std::string img_path, float speed);

	void				setSpeed(float _speed);
	float				getSpeed();

	sf::CircleShape&	getVisionCircle();
	void				setVisionCircle(sf::CircleShape&);
	void				changeVisionCircle(float radius);

	void				setTexture(std::string path);
	sf::Texture&		getTexture();

	void				setPosition(sf::Vector2f newpos);
	sf::Vector2f		getPosition();

	sf::Vector2f		getCenteredPosition();
	void				setSprite();



	//TODO refactor this code
	std::vector<std::unique_ptr<Bullet>> bullets;


private:
	float speed;
	sf::CircleShape visionCircle;
};

#endif
