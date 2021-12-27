#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "Constant.h"
#include "ResourcesImages.h"
#include "ResourcesSounds.h"
#include "Constant.h"

//Forward declaration
class Player;
class Enemy;
class Present;
class AddTimePresent;
class AddEnemyPresent;
class AddLifePresent;
class AddScorePresent;
class Coin;
class Ladder;
class Rod;
class Wall;

using namespace sf;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	 
	virtual void handleCollision(GameObject& gameObject) = 0;
	virtual void handleCollision(Wall& gameObject) = 0;
	virtual void handleCollision(Rod& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) = 0;
	virtual void handleCollision(Ladder& gameObject) = 0;
	virtual void handleCollision(Enemy& gameObject) = 0;
	virtual void handleCollision(Coin& gameObject) = 0;
	virtual void handleCollision(AddTimePresent& gameObject) = 0;
	virtual void handleCollision(AddEnemyPresent& gameObject) = 0;
	virtual void handleCollision(AddLifePresent& gameObject) = 0;
	virtual void handleCollision(AddScorePresent& gameObject) = 0;

	void setLocation(float height, float width);
	void setDisposed();
	void draw(sf::RenderWindow& window);

	bool checkCollision(const sf::FloatRect& floatRect) const;
	bool isDisposed() const;

	sf::Sprite getSprite();

protected:
	bool m_isDisposed = false;
	sf::Sprite m_sprite;
private:


};