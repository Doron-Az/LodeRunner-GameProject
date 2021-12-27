#pragma once
#include "Enemy.h"
#include "Board.h"


class LeftRightEnemy : public Enemy
{
public:
	LeftRightEnemy(const Board& board, float height, float width);
	void move(sf::Time deltaTime, float heigth, float width) override;
	void chooseDirection();
private:
	Board m_board;
};