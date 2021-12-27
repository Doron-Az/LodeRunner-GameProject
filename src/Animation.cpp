#include "Animation.h"
#include <iostream>
#include "ResourcesImages.h"

//-----------------------------------------------------------------------------
Animation::Animation(sf::Vector2i imageCount, float m_switchTime,int index)
{
	this->imageCount = imageCount;
	this->m_switchTime = m_switchTime;
	m_totalTime = 0.0f;
	currentImage.x = 0;

	m_uvRect.width = ResourcesImages::getInstance().getTexture(index).getSize().x / (imageCount.x);
	m_uvRect.height = ResourcesImages::getInstance().getTexture(index).getSize().y / (imageCount.y);
}
//----------------------------------------------------------------------------- 
void Animation::setAnimation(sf::Vector2i imageCount, float m_switchTime,int index)
{
	this->imageCount = imageCount;
	this->m_switchTime = m_switchTime;
	m_totalTime = 0.0f;
	currentImage.x = 0;

	m_uvRect.width = ResourcesImages::getInstance()
		.getTexture(index).getSize().x / (imageCount.x);
	m_uvRect.height = ResourcesImages::getInstance()
		.getTexture(index).getSize().y / (imageCount.y);

}
//----------------------------------------------------------------------------- 
void Animation::update(float deltaTime, bool faceRight, bool moving)
{
	currentImage.y = m_row;
	m_totalTime += deltaTime;

	if (m_totalTime >= m_switchTime && moving)
	{
		m_totalTime -= m_switchTime;
		currentImage.x++;

		if (currentImage.x >= m_endAnimation)
			currentImage.x = m_startAnimation;	
	}

	m_uvRect.top = currentImage.y * m_uvRect.height;


	//to rotate image
	if (faceRight)
	{
		m_uvRect.left = currentImage.x * m_uvRect.width;
		m_uvRect.width = abs(m_uvRect.width);
	}
	else
	{
		m_uvRect.left = (currentImage.x + 1) * abs(m_uvRect.width);
		m_uvRect.width = -abs(m_uvRect.width);
	}
}
//-----------------------------------------------------------------------------
void Animation::setPrintOrder(int row, int start, int end)
{
	m_row = row;
	m_startAnimation = start;
	m_endAnimation = end;
}


