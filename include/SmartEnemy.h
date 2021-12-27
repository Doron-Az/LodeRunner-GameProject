#pragma once
#include "Enemy.h"
#include "Board.h"

//Forward declaration
class Player;

class SmartEnemy : public Enemy
{
public:
	SmartEnemy(MovingObject* target, const Board &board, float height, float width);
	void move(sf::Time deltaTime, float heigth, float width) override;
	void chooseDirectionToPlayer();

private:
	bool m_first = true;
	sf::Clock m_clock;
	Direction m_LeftOrRight;
	MovingObject* m_target;
	Board m_board;
};