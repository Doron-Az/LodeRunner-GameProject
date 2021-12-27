#pragma once
#include "Enemy.h"

class RegularEnemy : public Enemy
{
public:
	RegularEnemy(float height, float width);
	void move(sf::Time deltaTime, float heigth, float width) override;
private:
	sf::Clock m_clock;
	bool m_bool = true;
};