#include "Coin.h"
#include "Player.h"
//static
int Coin::m_coinCounter = 0;
//-----------------------------------------------------------------------------
Coin::Coin()
{
	++m_coinCounter;
}
//-----------------------------------------------------------------------------
Coin::~Coin()
{
	--m_coinCounter;
}
//-----------------------------------------------------------------------------
Coin::Coin(float height, float width)
{
	++m_coinCounter;
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_coin));
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
int Coin::getCoinNum()
{
	return m_coinCounter;
}
//-----------------------------------------------------------------------------
void Coin::setSpriteLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}

//----------------------------------------------------------------------------
void Coin::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void Coin::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
	m_isDisposed = true;
}
//----------------------------------------------------------------------------
void Coin::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void Coin::handleCollision(Ladder& gameObject) {}
//-----------------------------------------------------------------------------
void Coin::handleCollision(Enemy& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void Coin::handleCollision(AddScorePresent& gameObject) {}
//----------------------------------------------------------------------------
