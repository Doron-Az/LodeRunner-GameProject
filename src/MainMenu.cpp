#include "MainMenu.h"

#include <iostream> // мозеч

MainMenu::MainMenu() :m_height(OPEN_WINDOWS_HEIGHT), m_width(OPEN_WINDOWS_WIDTH)
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_explanation));
	m_play.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_play));
	m_play.setPosition(PLAY_POSITION_Y, PLAY_POSITION_X);
	m_exit.setTexture(ResourcesImages::getInstance().getTexture(vectorIconType::i_exit));
	m_exit.setPosition(EXIT_POSITION_Y, EXIT_POSITION_X);
	m_window.create(sf::VideoMode(m_width, m_height), "Explanation");
	runExplanation();
}
//-----------------------------------------------------------------------------
void MainMenu::run()
{
	m_sprite.setTexture(ResourcesImages::getInstance().getTexture(i_open));
	m_window.create(sf::VideoMode(m_width, m_height), "Opening");

	while (m_window.isOpen())
	{
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			m_locationMouse = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
				auto clickLocation = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					switch (clickOnMenu(clickLocation))
					{
					case e_play:
						m_window.close();
						break;
					case e_exit:
						exit(EXIT_SUCCESS);
						break;
					}
					break;
				}
				break;
			}
		}
		draw();
	}
}
//-----------------------------------------------------------------------------
void MainMenu::draw()
{
	makeFrame(m_locationMouse);

	m_window.clear();
	m_window.draw(m_sprite);
	m_window.draw(m_exit);
	m_window.draw(m_play);

	if (m_isFrame)
		m_window.draw(m_frame);

	m_window.display();
}
//-----------------------------------------------------------------------------
void MainMenu::runExplanation()
{
	while (m_window.isOpen())
	{
		for (auto event = sf::Event(); m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_window.close();
					run();
					break;
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					m_window.close();
					run();
					break;
				}
			}
		}
		m_window.clear();
		m_window.draw(m_sprite);
		m_window.display();
	}
}
//-----------------------------------------------------------------------------
int MainMenu::clickOnMenu(sf::Vector2f clickLocation)
{
	if (clickLocation.x > m_exit.getPosition().x &&
		clickLocation.x < m_exit.getPosition().x + OPEN_BUTTON_WIDTH)
		if (clickLocation.y > m_exit.getPosition().y &&
			clickLocation.y < m_exit.getPosition().y + OPEN_BUTTON_HEIGHT)
			return e_exit;

	if (clickLocation.x > m_play.getPosition().x &&
		clickLocation.x < m_play.getPosition().x + OPEN_BUTTON_WIDTH)
		if (clickLocation.y > m_play.getPosition().y &&
			clickLocation.y < m_play.getPosition().y + OPEN_BUTTON_HEIGHT)
			return e_play;

	return e_nothing;
}
//-----------------------------------------------------------------------------
void MainMenu::makeFrame(sf::Vector2f buttonLocation)
{
	int click = clickOnMenu(buttonLocation);

	if (click == e_exit)
	{
		m_frame.setPosition(m_exit.getPosition());
		m_isFrame = true;
	}
	else if (click == e_play)
	{
		m_frame.setPosition(m_play.getPosition());
		m_isFrame = true;
	}
	else m_isFrame = false;

	sf::Vector2f size(OPEN_BUTTON_WIDTH, OPEN_BUTTON_HEIGHT);
	m_frame.setSize(size);

	m_frame.setOutlineThickness(4);
	m_frame.setFillColor(sf::Color::Transparent);
	m_frame.setOutlineColor(sf::Color::White);
}