#include "RegularEnemy.h"

class Controller;
RegularEnemy::RegularEnemy(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_enemy));
	m_sprite.setPosition(width, height);
	m_startLocation.x = width;
	m_startLocation.y = height;

	m_animation.setAnimation(sf::Vector2i(11, 2), 0.08f, i_enemy);
	m_animation.setPrintOrder(0, 0, 3);
	m_faceRight = true;
	m_moving = true;
}
//-----------------------------------------------------------------------------
void RegularEnemy::move(sf::Time deltaTime, float heigth, float width)
{
	int direction;
	int time = (int)m_clock.getElapsedTime().asSeconds();

	if ((time % SWITCH_TIME) == 0 && m_bool)
	{
		direction = rand() % NUM_OF_DIRECTIONS;
		switch (direction)
		{
		case e_up:
			m_dir = Direction::d_up;
			break;
		case e_down:
			m_dir = Direction::d_down;
			break;
		case e_left:
			m_dir = Direction::d_left;
			break;
		case e_right:
			m_dir = Direction::d_right;
			break;
		}
		m_bool = false;
	}

	if ((time % SWITCH_TIME) != 0 && !m_bool)
		m_bool = true;

	sf::Vector2 nextPos(m_sprite.getPosition().x + dirToVector(m_dir).x, m_sprite.getPosition().y + dirToVector(m_dir).y);

	if (checkNextMoveLimit(nextPos, heigth, width))
		m_sprite.move(dirToVector(m_dir) * ENEMY_SPEED * deltaTime.asSeconds());
	else   (m_dir == Direction::d_left) ? m_dir = Direction::d_right : m_dir = Direction::d_left;

	(m_dir == Direction::d_left) ? m_faceRight = false : m_faceRight = true;
	m_animation.update(deltaTime.asSeconds(), m_faceRight, m_moving);
	m_sprite.setTextureRect(m_animation.m_uvRect);
}

