#include "AddTimePresent.h"
#include "Controller.h"

AddTimePresent::AddTimePresent(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_present));
	m_sprite.setPosition(width, height);
}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Player& gameObject)
{
	ResourcesSounds::getInstance().playSound(s_present);
	m_isDisposed = true;
}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Enemy& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddTimePresent::handleCollision(AddScorePresent& gameObject) {}
//----------------------------------------------------------------------------
