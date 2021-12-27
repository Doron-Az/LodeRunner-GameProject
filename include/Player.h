#pragma once
#include "GameObject.h"
#include "MovingObject.h"
#include "Board.h"
#include <cmath>

//Forward declaration
class Enemy;
class Board;

class Player : public MovingObject
{
public:
	Player(int height, int width, int coin, Board* board);
	void move(sf::Time deltaTime, float heigth, float width) override;
	void  setTexture(sf::Texture);

	void digger(char, float)override;

	virtual void handleCollision(GameObject& gameObject)  override;
	virtual void handleCollision(Wall& gameObject)  override;
	virtual void handleCollision(Rod& gameObject)  override;
	virtual void handleCollision(Player& gameObject)  override;
	virtual void handleCollision(Ladder& gameObject)  override;
	virtual void handleCollision(Enemy& gameObject)  override;
	virtual void handleCollision(Coin& gameObject)  override;
	virtual void handleCollision(AddTimePresent& gameObject)  override;
	virtual void handleCollision(AddEnemyPresent& gameObject) override;
	virtual void handleCollision(AddLifePresent& gameObject) override;
	virtual void handleCollision(AddScorePresent& gameObject) override;
	virtual int getScore()const override;
	virtual int getLive()const override;
	virtual	void setScore(int score)override;
	virtual void setLive(int live)override;
	virtual void fallDown(sf::Time deltaTime, float height, 
		float width, char currBoardChar)override;
	void setAnimationIcon(char icon)override;

private:
	int m_coin, m_live;
	bool m_isFirst = true;
	float m_totalTime;
	Board* m_board;
};

namespace
{
	sf::Vector2f dirFromKey()
	{
		static const
			std::initializer_list<std::pair<sf::Keyboard::Key, sf::Vector2f>>
			keyToVectorMapping =
		{
			{ sf::Keyboard::Right, { 1, 0 } },
			{ sf::Keyboard::Left , { -1, 0 } },
			{ sf::Keyboard::Up   , { 0, -1 } },
			{ sf::Keyboard::Down , { 0, 1 } },
		};
		for (const auto& pair : keyToVectorMapping)
		{
			if (sf::Keyboard::isKeyPressed(pair.first))
			{
				return pair.second;
			}
		}
		return { 0, 0 };
	}
}