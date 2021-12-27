#pragma once
#include "MovingObject.h"

class Enemy : public MovingObject
{
public:

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

	virtual int getScore()const override { return 0; };
	virtual int getLive() const override { return 0; };
	virtual void setScore(int) override {};
	virtual void setLive(int) override {};
	virtual void digger(char, float) {};

	void setAnimationIcon(char icon);
	void fallDown(sf::Time deltaTime, float height, float width, char currBoardChar);

protected:
private:

};

