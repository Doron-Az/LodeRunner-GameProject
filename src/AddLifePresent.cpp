#include "AddLifePresent.h"
#include "Player.h"

AddLifePresent::AddLifePresent(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_present));
	m_sprite.setPosition(width, height);
}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Player& gameObject)
{
	ResourcesSounds::getInstance().playSound(s_present);
	gameObject.handleCollision(*this);
	m_isDisposed = true;
}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Rod& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Enemy& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddLifePresent::handleCollision(AddScorePresent& gameObject) {}