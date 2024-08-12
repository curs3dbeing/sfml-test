#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <string>

enum Rarity {
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};

class Weapon {
protected:
	std::string name;
	float attack_range;
	float attack_speed;
	float damage;
	Rarity rarity_type;
public:
	virtual void setName(std::string _name);
	virtual void setAttack_range(float _attack_range);
	virtual void setAttack_speed(float _attack_speed);
	virtual void setDamage(float _damage);
	virtual void setRarity(Rarity _rarity_type);
};

#endif

