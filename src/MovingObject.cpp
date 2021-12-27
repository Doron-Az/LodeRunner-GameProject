#include "MovingObject.h"
//-----------------------------------------------------------------------------
bool MovingObject::checkNextMoveLimit(Vector2f nextPos, float heigth, float width)
{
	if (nextPos.x < START_WINDOW || nextPos.y < START_WINDOW ||
		nextPos.x + OBJECT_SIZE> width * OBJECT_SIZE ||
		nextPos.y + OBJECT_SIZE> heigth * OBJECT_SIZE)
		return false;
	return true;
}
//-----------------------------------------------------------------------------
sf::Vector2f MovingObject::getStartLocation()
{
	return m_startLocation;
}
//-----------------------------------------------------------------------------
sf::Vector2f MovingObject::getCurrLocation()
{
	return m_sprite.getPosition();
}
//-----------------------------------------------------------------------------
void MovingObject::setStartLocation(sf::Vector2f location)
{
	m_sprite.setPosition(location);
}