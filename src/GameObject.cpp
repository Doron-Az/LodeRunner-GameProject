#include "GameObject.h"

//-----------------------------------------------------------------------------
void GameObject::setLocation(float height, float width)
{
	m_sprite.setPosition(width, height);
}
//-----------------------------------------------------------------------------
bool GameObject::checkCollision(const sf::FloatRect& floatRect) const
{
	return m_sprite.getGlobalBounds().intersects(floatRect);
}
//-----------------------------------------------------------------------------
bool GameObject::isDisposed() const
{
	return m_isDisposed;
}
sf::Sprite GameObject::getSprite()
{
	return m_sprite;
}
//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
void GameObject::setDisposed()
{
	m_isDisposed = true;
}
