#include "Rod.h"
#include "Player.h"
#include "Enemy.h"
Rod::Rod(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_rod));
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
void Rod::setSpriteLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}
//----------------------------------------------------------------------------
void Rod::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Rod::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void Rod::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void Rod::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Rod::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void Rod::handleCollision(AddScorePresent& gameObject) {}
