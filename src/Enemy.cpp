#include "Enemy.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rod.h"

//----------------------------------------------------------------------------
void Enemy::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Wall& gameObject)
{

	if (m_dir == Direction::d_up)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y + OBJECT_SIZE);
	if (m_dir == Direction::d_down)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y - OBJECT_SIZE);
	if (m_dir == Direction::d_right)
	{

		if ((abs(m_sprite.getPosition().y - gameObject.getSprite().getPosition().y) < OBJECT_SIZE * 0.6) &&
			m_sprite.getPosition().y != gameObject.getSprite().getPosition().y)
			m_sprite.setPosition(gameObject.getSprite().getPosition().x, gameObject.getSprite().getPosition().y - OBJECT_SIZE);


		else {
			m_sprite.setPosition(gameObject.getSprite().getPosition().x - OBJECT_SIZE, m_sprite.getPosition().y);
		}
	}
	if (m_dir == Direction::d_left)
	{
		if ((abs(m_sprite.getPosition().y - gameObject.getSprite().getPosition().y) < OBJECT_SIZE * 0.6) &&
			m_sprite.getPosition().y != gameObject.getSprite().getPosition().y)
			m_sprite.setPosition(gameObject.getSprite().getPosition().x + OBJECT_SIZE / 2,
				gameObject.getSprite().getPosition().y - OBJECT_SIZE);

		else
			m_sprite.setPosition(gameObject.getSprite().getPosition().x + OBJECT_SIZE, m_sprite.getPosition().y);

	}
	if ((m_dir == Direction::d_left || m_dir == Direction::d_right) && abs(m_sprite.getPosition().y - OBJECT_SIZE
		- gameObject.getSprite().getPosition().y) < 1)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y + OBJECT_SIZE);

	(m_dir == Direction::d_right) ? m_dir = Direction::d_left : m_dir = Direction::d_right;

	setAnimationIcon(ObjectType::EnemyChar);

}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Rod& gameObject)
{
	if (m_dir != Direction::d_down && (abs((m_sprite.getPosition().y - 50) -
		(gameObject.getSprite().getPosition().y)) < 20))
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y);

	if ((abs((m_sprite.getPosition().x) - (gameObject.getSprite().getPosition().x)) < 49))
		setAnimationIcon(ObjectType::RodChar);

	else setAnimationIcon(ObjectType::EnemyChar);
}

//-----------------------------------------------------------------------------
void Enemy::handleCollision(Ladder& gameObject)
{
	if (m_dir == Direction::d_down || m_dir == Direction::d_up)
	{
		if (abs((m_sprite.getPosition().x) - (gameObject.getSprite().getPosition().x)) < OBJECT_SIZE)
		{
			m_sprite.setPosition(gameObject.getSprite().getPosition().x, m_sprite.getPosition().y);
			setAnimationIcon(ObjectType::LadderChar);
		}
		else
			setAnimationIcon(ObjectType::EnemyChar);
	}

	else if (m_dir == Direction::d_left || m_dir == Direction::d_right) {
		if ((abs((m_sprite.getPosition().y) - (gameObject.getSprite().getPosition().y - OBJECT_SIZE))) < OBJECT_SIZE * 0.3) {
			m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y - OBJECT_SIZE);
		}
		setAnimationIcon(ObjectType::EnemyChar);
	}
}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Player& gameObject) {}
//-----------------------------------------------------------------------------
void Enemy::handleCollision(Enemy& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::handleCollision(AddScorePresent& gameObject) {}
//----------------------------------------------------------------------------
void Enemy::setAnimationIcon(char icon)
{
	if (icon == ObjectType::LadderChar)
	{
		m_animation.setPrintOrder(0, 6, 8);
	}
	if (icon == ObjectType::RodChar) {
		m_animation.setPrintOrder(1, 0, 3);
	}
	if (icon == ObjectType::EnemyChar) {
		m_animation.setPrintOrder(0, 0, 3);
	}
}
//----------------------------------------------------------------------------
void Enemy::fallDown(sf::Time deltaTime, float height, float width, char currBoardChar)
{
	if (currBoardChar == ObjectType::WallChar)
		return;
	Vector2f down(0, 1);

	if (m_dir == Direction::d_right || m_dir == Direction::d_left)
		m_sprite.setPosition(floor(m_sprite.getPosition().x / OBJECT_SIZE) * OBJECT_SIZE, m_sprite.getPosition().y);


	sf::Vector2 nextPos(m_sprite.getPosition().x + down.x, m_sprite.getPosition().y + down.y);

	if (checkNextMoveLimit(nextPos, height, width)) {
		m_sprite.move(down * FALL_SPEED * deltaTime.asSeconds());
		m_dir = Direction::d_down;
	}
	m_sprite.setTextureRect(sf::IntRect((int)(OBJECT_SIZE * FALL_ICON_COL),
		(int)(OBJECT_SIZE * FALL_LEFT_ICON_ROW), (int)OBJECT_SIZE, (int)OBJECT_SIZE));

}