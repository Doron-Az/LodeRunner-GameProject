#include "Wall.h"
#include "Enemy.h"
#include "Player.h"

class Player;

Wall::Wall(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_wall));
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
void Wall::setSpriteLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}
//-----------------------------------------------------------------------------

void Wall::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Wall::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void Wall::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void Wall::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(Enemy& gameObject)
{
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void Wall::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void Wall::handleCollision(AddScorePresent& gameObject) {}



