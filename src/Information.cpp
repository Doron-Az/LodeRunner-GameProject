#include "Information.h"

//-----------------------------------------------------------------------------
Information::Information(int score, int live, int time, int level, float height, float width) :
	m_score(score), m_live(live), m_time(time), m_level(level), m_height(height), m_width(width)
{
	if (!m_font.loadFromFile("FontFile.ttf"))
	{
		std::cout << "Error font" << std::endl;
		exit(EXIT_FAILURE);
	}

	setText(text[0], sf::Color::Yellow, "Score ", height, 0);
	setText(text[1], sf::Color::Red, std::to_string(score), height, 125);
	setText(text[2], sf::Color::Yellow, "Live ", height, 225);
	setText(text[3], sf::Color::Red, std::to_string(live), height, 325);
	setText(text[4], sf::Color::Yellow, "Level ", height, 425);
	setText(text[5], sf::Color::Red, std::to_string(level), height, 550);
	setText(text[6], sf::Color::Yellow, "Time ", height, 650);
	setText(text[7], sf::Color::Red, std::to_string(time), height, 775);
}

//-----------------------------------------------------------------------------
void Information::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUM_TEXT; i++)
		window.draw(text[i]);
}
//-----------------------------------------------------------------------------
void Information::setPosition(float height)
{
	for (int i = 0; i < MAX_NUM_TEXT; i++) {
		text[i].setPosition(text[i].getPosition().x, height);
	}
}

//-----------------------------------------------------------------------------
void Information::setInformation(int score, int live, int time, int level)
{
	text[1].setString(std::to_string(score));
	text[3].setString(std::to_string(live));
	text[5].setString(std::to_string(level));
	if(time == NO_TIME)
		text[7].setString("###");
	else
	text[7].setString(std::to_string(time));
}
//-----------------------------------------------------------------------------
void Information::setText(sf::Text& text,const sf::Color& color, std::string str,
	float height, float width)
{
	text.setString(str);
	text.setPosition(width, height);
	text.setFont(m_font);
	text.setColor(color);
}
//-----------------------------------------------------------------------------
