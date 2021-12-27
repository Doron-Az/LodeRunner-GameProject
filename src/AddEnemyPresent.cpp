#include "AddEnemyPresent.h"
#include "Controller.h"

AddEnemyPresent::AddEnemyPresent( float height, float width)
{
    m_sprite.setTexture(ResourcesImages::getInstance() .getTexture(vectorIconType::i_present));
    m_sprite.setPosition(width, height);  
}
//----------------------------------------------------------------------------
void AddEnemyPresent::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    //double dispatch
    gameObject.handleCollision(*this);
}
//----------------------------------------------------------------------------
void AddEnemyPresent::handleCollision(Player& gameObject)
{
    ResourcesSounds::getInstance().playSound(s_createEnemy);
    m_isDisposed = true;   
}
//----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(Wall& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(Rod& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(Ladder& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(Enemy& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(Coin& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(AddTimePresent& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(AddEnemyPresent& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(AddLifePresent& gameObject) {}
 //----------------------------------------------------------------------------
 void AddEnemyPresent::handleCollision(AddScorePresent& gameObject) {}
