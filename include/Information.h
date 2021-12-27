#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "Animation.h"
#include "Constant.h"

class Information
{
public:
	Information() = default;
	Information(int score, int live, int time, int level, float height, float width);

	void setInformation(int score, int live, int time, int level);
	void setText(sf::Text&,const sf::Color&, std::string, float, float);
	void setPosition(float height);
	void draw(sf::RenderWindow& window);

private:
	unsigned int m_score;
	unsigned int m_live;
	unsigned int m_level;
	unsigned int m_time;
	float m_width;
	float m_height;

	sf::Font m_font;
	sf::Text text[MAX_NUM_TEXT];
};