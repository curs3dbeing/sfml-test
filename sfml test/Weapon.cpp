#include "Weapon.h"
#include <string>

void Weapon::setName(std::string _name) {
	this->name = _name;
}
void Weapon::setAttack_range(float _attack_range) {
	this->attack_range = _attack_range;
}
void Weapon::setAttack_speed(float _attack_speed) {
	this->attack_speed = _attack_speed;
}
void Weapon::setDamage(float _damage) {
	this->damage = _damage;
}
void Weapon::setRarity(Rarity _rarity_type) {
	this->rarity_type = _rarity_type;
}