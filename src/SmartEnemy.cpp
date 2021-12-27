#include "SmartEnemy.h"
#include "Player.h"
#include <iomanip>
#include <cmath>

SmartEnemy::SmartEnemy(MovingObject* target, const Board& board, float height, float width):m_board(board)
{
	m_target = target;
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_enemy));
	m_sprite.setPosition(width, height);
	m_startLocation.x = width;
	m_startLocation.y = height;
	chooseDirectionToPlayer();

	m_animation.setAnimation(sf::Vector2i(11, 2), 0.08f, i_enemy);
	m_animation.setPrintOrder(0, 0, 3);
	m_faceRight = true;

	m_moving = true;
}
//-----------------------------------------------------------------------------
void SmartEnemy::move(sf::Time deltaTime, float heigth, float width)
{
	Vector2f target(m_target->getCurrLocation());
	Vector2f enemyLocation = m_sprite.getPosition();

	int x = (int)floor((enemyLocation.x + 25) / OBJECT_SIZE);
	int y = (int)floor((enemyLocation.y + 25) / OBJECT_SIZE);

	char current = m_board.getCharObject(y, x);
	char up = m_board.getCharObject(y - 1, x);
	char down = m_board.getCharObject(y + 1, x);

	int time = (int)m_clock.getElapsedTime().asSeconds();


	if ((int)(time % SWITCH_TIME && m_first) == 0) {
		chooseDirectionToPlayer();
		m_first = false;
	}
	if ((time % SWITCH_TIME) != 0 && !m_first)
		m_first = true;

	if ((target.y > enemyLocation.y) &&
		(down == ObjectType::LadderChar ||
			current == ObjectType::RodChar))
		m_dir = Direction::d_down;

	else if ((up == ObjectType::LadderChar ||
		current == ObjectType::LadderChar) &&
		(target.y < enemyLocation.y))
		m_dir = Direction::d_up;

	sf::Vector2f temp = dirToVector(m_dir);
	sf::Vector2 nextPos(m_sprite.getPosition().x + temp.x, m_sprite.getPosition().y + temp.y);

	if (checkNextMoveLimit(nextPos, heigth, width))
		m_sprite.move(dirToVector(m_dir) * ENEMY_SPEED * deltaTime.asSeconds());

	(m_dir == Direction::d_left) ? m_faceRight = false : m_faceRight = true;

	m_animation.update(deltaTime.asSeconds(), m_faceRight, m_moving);
	m_sprite.setTextureRect(m_animation.m_uvRect);

}
//-----------------------------------------------------------------------------
void SmartEnemy::chooseDirectionToPlayer()
{
	Vector2f target(m_target->getCurrLocation());
	Vector2f enemyLocation = m_sprite.getPosition();

	if (target.x > enemyLocation.x)
		m_dir = Direction::d_right;
	else
		m_dir = Direction::d_left;

}