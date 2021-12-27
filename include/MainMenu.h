#pragma once
#include <SFML/Graphics.hpp>
#include "ResourcesImages.h"
#include "Constant.h"

class MainMenu
{
public:
	enum buttonType
	{
		e_play,
		e_exit,
		e_nothing
	};

	MainMenu();
	void run();
	void draw();
	void runExplanation();
	int clickOnMenu(sf::Vector2f clickLocation);
	void makeFrame(sf::Vector2f buttonLocation);

private:
	int m_width;
	int m_height;
	bool m_isFrame = false;

	sf::Vector2f m_locationMouse;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Sprite m_exit;
	sf::Sprite m_play;
	sf::RenderWindow m_window;
	sf::RectangleShape m_frame;
};