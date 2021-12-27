#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	~Animation() = default;
	Animation() = default;
	Animation(sf::Vector2i imageCount, float m_switchTime, int index);

	void setAnimation(sf::Vector2i imageCount, float m_switchTime, int index);
	void update(float deltaTime, bool faceRight, bool moving);
	void setPrintOrder(int row, int start, int end);

	sf::IntRect m_uvRect;
private:
	sf::Vector2i imageCount;
	sf::Vector2i currentImage;

	float m_totalTime = 0;
	float m_switchTime = 0;

	int m_row = 0;
	int m_startAnimation = 0;
	int m_endAnimation = 0;
};