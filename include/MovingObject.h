#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"

//Forward declaration
class Wall;

class MovingObject : public GameObject
{
public:
	enum class Direction
	{
		d_stay,
		d_up,
		d_down,
		d_left,
		d_right,
	};

	virtual void move(sf::Time, float, float) = 0;
	virtual int getScore()const = 0;
	virtual int getLive()const = 0;
	virtual	void setScore(int score) = 0;
	virtual void setLive(int live) = 0;
	virtual void setStartLocation(sf::Vector2f location);
	virtual void setAnimationIcon(char icon) = 0;
	virtual void digger(char, float) = 0;
	virtual void fallDown(sf::Time, float height, float width, char curr) = 0;
	sf::Vector2f getStartLocation();
	sf::Vector2f getCurrLocation();
	bool checkNextMoveLimit(Vector2f, float, float);

protected:
	sf::Vector2f m_startLocation;

	Direction m_dir = Direction::d_stay;

	Animation m_animation;
	bool m_faceRight = true;
	bool m_moving = true;

private:
};
//-----------------------------------------------------------------------------
namespace
{
	sf::Vector2f dirToVector(MovingObject::Direction dir)
	{
		switch (dir)
		{
		case MovingObject::Direction::d_right: return { 1, 0 };
		case MovingObject::Direction::d_left: return { -1, 0 };
		case MovingObject::Direction::d_up: return { 0, -1 };
		case MovingObject::Direction::d_down: return { 0, 1 };
		case MovingObject::Direction::d_stay: return { 0, 0 };
		}
		return { 0, 0 };
	}
}
//-----------------------------------------------------------------------------
