#pragma once
#include "StaticObject.h"

//Forward declaration
class Player;

class Coin : public StaticObject
{
public:
	Coin();
	~Coin()override;
	Coin(float height, float width);
	void setSpriteLocation(sf::Vector2f location) override;

	virtual void handleCollision(GameObject& gameObject)  override;
	virtual void handleCollision(Player& gameObject)  override;
	virtual void handleCollision(Wall& gameObject)  override;
	virtual void handleCollision(Rod& gameObject)  override;
	virtual void handleCollision(Ladder& gameObject)  override;
	virtual void handleCollision(Enemy& gameObject)  override;
	virtual void handleCollision(Coin& gameObject)  override;
	virtual void handleCollision(AddTimePresent& gameObject)  override;
	virtual void handleCollision(AddEnemyPresent& gameObject) override;
	virtual void handleCollision(AddLifePresent& gameObject) override;
	virtual void handleCollision(AddScorePresent& gameObject) override;
	static int getCoinNum();
private:
	static int m_coinCounter;
};