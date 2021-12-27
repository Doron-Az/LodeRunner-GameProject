#include "LeftRightEnemy.h"
//-----------------------------------------------------------------------------
LeftRightEnemy::LeftRightEnemy(const Board& board, float height, float width): m_board (board)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_enemy));
	m_sprite.setPosition(width, height);
	m_startLocation.x = width;
	m_startLocation.y = height;

	m_dir = Direction::d_left;
	m_animation.setAnimation(sf::Vector2i(11, 2), 0.08f, i_enemy);
	m_animation.setPrintOrder(0, 0, 3);
	m_faceRight = true;
	m_moving = true;
}
//-----------------------------------------------------------------------------
void LeftRightEnemy::move(sf::Time deltaTime, float heigth, float width)
{
	chooseDirection();

	sf::Vector2 nextPos(m_sprite.getPosition().x + dirToVector(m_dir).x,
		m_sprite.getPosition().y + dirToVector(m_dir).y);

	if (checkNextMoveLimit(nextPos, heigth, width))
		m_sprite.move(dirToVector(m_dir) * ENEMY_SPEED * deltaTime.asSeconds());

	else (m_dir == Direction::d_left) ? m_dir = Direction::d_right : m_dir = Direction::d_left;

	(m_dir == Direction::d_left) ? m_faceRight = false : m_faceRight = true;
	m_animation.update(deltaTime.asSeconds(), m_faceRight, m_moving);
	m_sprite.setTextureRect(m_animation.m_uvRect);

}
//-----------------------------------------------------------------------------
void LeftRightEnemy::chooseDirection()
{
	int x = (int)round((m_sprite.getGlobalBounds().left) / OBJECT_SIZE);
	int y = (int)round((m_sprite.getGlobalBounds().top) / OBJECT_SIZE);


	char leftDown = m_board.getCharObject(y + 1, x - 1);
	char rightDown = m_board.getCharObject(y + 1, x + 1);

	if (leftDown == ' ' && m_dir == Direction::d_left)
		m_dir = Direction::d_right;

	if (rightDown == ' ' && m_dir == Direction::d_right)
		m_dir = Direction::d_left;
}