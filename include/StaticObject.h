#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	virtual void setSpriteLocation(sf::Vector2f location) = 0;
private:

};