#include "AddScorePresent.h"
//#include "Controller.cpp"

AddScorePresent::AddScorePresent(float height, float width)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_present));
	m_sprite.setPosition(width, height);
}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Player& gameObject)
{
	ResourcesSounds::getInstance().playSound(s_present);
	m_isDisposed = true;
}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Wall& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Rod& gameObject) {}
//-----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Ladder& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Enemy& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(Coin& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(AddTimePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(AddEnemyPresent& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(AddLifePresent& gameObject) {}
//----------------------------------------------------------------------------
void AddScorePresent::handleCollision(AddScorePresent& gameObject) {}
