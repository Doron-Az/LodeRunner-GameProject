#include "Player.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rod.h"
#include "Enemy.h"
#include <iostream> 

//-----------------------------------------------------------------------------
Player::Player(int height, int width, int coin, Board* board)	
	:m_coin(coin), m_live(BEGIN_LIFE), m_totalTime(RESET)
{
	m_board = board;
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_player));
	m_sprite.setTextureRect(sf::IntRect(OBJECT_SIZE * 1, OBJECT_SIZE * 0, OBJECT_SIZE, OBJECT_SIZE));

	m_animation.setAnimation(sf::Vector2i(9, 2), 0.08f, vectorIconType::i_player);
	m_animation.setPrintOrder(0, 0, 3);
	m_faceRight = true;
	m_moving = false;

	ResourcesSounds::getInstance().playSound(s_born);
}
//-----------------------------------------------------------------------------
void  Player::setTexture(sf::Texture icon)
{
	m_sprite.setTexture(icon);
}
//-----------------------------------------------------------------------------
void Player::digger(char side, float currTime)
{
	m_board->digger(m_sprite.getPosition(), side, currTime);
}
//-----------------------------------------------------------------------------
void Player::move(sf::Time deltaTime, float heigth, float width)
{
	sf::Vector2f movement = dirFromKey();

	if (movement == sf::Vector2f(0, -1))
		m_dir = Direction::d_up;
	else if (movement == sf::Vector2f(0, 1))
		m_dir = Direction::d_down;
	else if (movement == sf::Vector2f(-1, 0))
		m_dir = Direction::d_left;
	else if (movement == sf::Vector2f(1, 0))
		m_dir = Direction::d_right;
	else m_dir = Direction::d_stay;

	sf::Vector2 nextPos(m_sprite.getPosition().x
		+ movement.x, m_sprite.getPosition().y + movement.y);

	if (checkNextMoveLimit(nextPos, heigth, width))
		m_sprite.move(movement * PLAYER_SPEED * deltaTime.asSeconds());

	if (m_dir == Direction::d_stay)
		m_moving = false;

	else
	{
		m_moving = true;

		if (movement.x > 0.0f)
			m_faceRight = true;
		else
			m_faceRight = false;
	}
	m_animation.update(deltaTime.asSeconds(), m_faceRight, m_moving);
	m_sprite.setTextureRect(m_animation.m_uvRect);
}
//----------------------------------------------------------------------------
int Player::getScore()const 
{
	return m_coin;
}
//----------------------------------------------------------------------------
int Player::getLive()const
{
	return m_live;
}
//----------------------------------------------------------------------------
void Player::setScore(int score)
{
	m_coin = score;
}
//----------------------------------------------------------------------------
void Player::setLive(int live)
{
	m_live = live;
}
//----------------------------------------------------------------------------
void Player::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Player::handleCollision(Wall& gameObject)
{
	setAnimationIcon(ObjectType::PlayerChar);

	if (m_dir == Direction::d_up)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y + OBJECT_SIZE);
	if (m_dir == Direction::d_down)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y - OBJECT_SIZE);
	if (m_dir == Direction::d_right)
	{
		if ((abs(m_sprite.getPosition().y - gameObject.getSprite().getPosition().y) < OBJECT_SIZE * 0.6) &&
			m_sprite.getPosition().y != gameObject.getSprite().getPosition().y)
			m_sprite.setPosition(gameObject.getSprite().getPosition().x, gameObject.getSprite().getPosition().y -
				OBJECT_SIZE);

		else   m_sprite.setPosition(gameObject.getSprite().getPosition().x - OBJECT_SIZE, m_sprite.getPosition().y);

	}
	if (m_dir == Direction::d_left)
	{
		if ((abs(m_sprite.getPosition().y - gameObject.getSprite().getPosition().y) < OBJECT_SIZE * 0.6) &&
			m_sprite.getPosition().y != gameObject.getSprite().getPosition().y)
			m_sprite.setPosition(gameObject.getSprite().getPosition().x + OBJECT_SIZE / 2,
				gameObject.getSprite().getPosition().y - OBJECT_SIZE);

		else   m_sprite.setPosition(gameObject.getSprite().getPosition().x +
			OBJECT_SIZE, m_sprite.getPosition().y);
	}
	if ((m_dir == Direction::d_left || m_dir == Direction::d_right) && abs(m_sprite.getPosition().y - OBJECT_SIZE
		- gameObject.getSprite().getPosition().y) < 1)
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y + OBJECT_SIZE);
}
//----------------------------------------------------------------------------
void Player::handleCollision(Rod& gameObject)
{
	if (m_dir != Direction::d_down && (abs((m_sprite.getPosition().y - 50) -
		(gameObject.getSprite().getPosition().y)) < 20))
		m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y);

	if ((abs((m_sprite.getPosition().x) - (gameObject.getSprite().getPosition().x)) < 49))
		setAnimationIcon(ObjectType::RodChar);

	else setAnimationIcon(ObjectType::PlayerChar);

}
//-----------------------------------------------------------------------------
void Player::handleCollision(Player& gameObject) {}
//-----------------------------------------------------------------------------
void Player::handleCollision(Ladder& gameObject)
{
	if (m_dir == Direction::d_down || m_dir == Direction::d_up)
	{
		if (abs((m_sprite.getPosition().x) - (gameObject.getSprite().getPosition().x)) < OBJECT_SIZE) {
			m_sprite.setPosition(gameObject.getSprite().getPosition().x, m_sprite.getPosition().y);
			setAnimationIcon(ObjectType::LadderChar);
		}
		else
			setAnimationIcon(ObjectType::PlayerChar);
	}
	else if (m_dir == Direction::d_left || m_dir == Direction::d_right) {
		if ((abs((m_sprite.getPosition().y) - (gameObject.getSprite().getPosition().y -
			OBJECT_SIZE))) < OBJECT_SIZE * 0.3) {
			m_sprite.setPosition(m_sprite.getPosition().x, gameObject.getSprite().getPosition().y -
				OBJECT_SIZE);
		}
		setAnimationIcon(ObjectType::PlayerChar);
	}
}
//----------------------------------------------------------------------------
void Player::handleCollision(Enemy& gameObject)
{
	if ((abs(m_sprite.getPosition().x - gameObject.getSprite().getPosition().x) < OBJECT_SIZE * 0.7) &&
		(abs(m_sprite.getPosition().y - gameObject.getSprite().getPosition().y) < OBJECT_SIZE * 0.7))
	{
		m_live--;
		if (m_live == END_LIVE)
			m_isDisposed = true;

		ResourcesSounds::getInstance().playSound(s_dead);
		setAnimationIcon(ObjectType::PlayerChar);
	}
}
//----------------------------------------------------------------------------
void Player::handleCollision(Coin& gameObject)
{
	m_coin++;
	ResourcesSounds::getInstance().playSound(s_getGold);
}
//----------------------------------------------------------------------------
void Player::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Player::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Player::handleCollision(AddLifePresent& gameObject)
{
	m_live++;
}
//----------------------------------------------------------------------------
void Player::handleCollision(AddScorePresent& gameObject) {}
//----------------------------------------------------------------------------
void Player::fallDown(sf::Time deltaTime, float height, float width, char currBoardChar)
{
	m_sprite.setPosition(floor((m_sprite.getPosition().x + OBJECT_SIZE / 2) / OBJECT_SIZE) *
		OBJECT_SIZE, m_sprite.getPosition().y);

	m_sprite.setTextureRect(sf::IntRect((int)(OBJECT_SIZE * FALL_ICON_COL),
		(int)(OBJECT_SIZE * FALL_LEFT_ICON_ROW), (int)OBJECT_SIZE, (int)OBJECT_SIZE));

	Vector2f down(0, 1);
	sf::Vector2 nextPos(m_sprite.getPosition().x + down.x, m_sprite.getPosition().y + down.y);

	if (checkNextMoveLimit(nextPos, height, width)) {
		m_sprite.move(down * FALL_SPEED * deltaTime.asSeconds());
		m_dir = Direction::d_down;
	}
}
//----------------------------------------------------------------------------
void Player::setAnimationIcon(char icon)
{
	if (icon == ObjectType::LadderChar)
	{
		m_animation.setPrintOrder(0, 6, 8);
	}
	if (icon == ObjectType::RodChar) {
		m_animation.setPrintOrder(1, 0, 3);
	}
	if (icon == ObjectType::PlayerChar) {
		m_animation.setPrintOrder(0, 0, 3);
	}
}