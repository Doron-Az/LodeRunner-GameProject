#pragma once
#include "StaticObject.h"

//Forward declaration
class Controller;

class Present : public StaticObject
{
public:
	void setSpriteLocation(sf::Vector2f location) override;

protected:
	Controller* m_controller = NULL;
private:
};