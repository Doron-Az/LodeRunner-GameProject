#include "Ladder.h"
#include "Player.h"
#include "Enemy.h"

Ladder::Ladder(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_ladder));
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
void Ladder::setSpriteLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}
//----------------------------------------------------------------------------
void Ladder::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void Ladder::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void Ladder::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Ladder::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void Ladder::handleCollision(AddScorePresent& gameObject) {}
//----------------------------------------------------------------------------
