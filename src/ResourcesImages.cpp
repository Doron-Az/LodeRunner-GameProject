#include "ResourcesImages.h"

//Singlton
ResourcesImages::ResourcesImages()
{
	sf::Texture texture;
	texture.loadFromFile("guard.png");
	v_texture.push_back(texture);
	texture.loadFromFile("coin.png");
	v_texture.push_back(texture);
	texture.loadFromFile("ladder.png");
	v_texture.push_back(texture);
	texture.loadFromFile("runner.png");
	v_texture.push_back(texture);
	texture.loadFromFile("rod.png");
	v_texture.push_back(texture);
	texture.loadFromFile("wall.png");
	v_texture.push_back(texture);
	texture.loadFromFile("present.png");
	v_texture.push_back(texture);
	texture.loadFromFile("over.png");
	v_texture.push_back(texture);
	texture.loadFromFile("explanation.jpeg");
	v_texture.push_back(texture);
	texture.loadFromFile("opening.png");
	v_texture.push_back(texture);
	texture.loadFromFile("play.png");
	v_texture.push_back(texture);
	texture.loadFromFile("exit.png");
	v_texture.push_back(texture);
}
//-----------------------------------------------------------------------------
ResourcesImages& ResourcesImages::getInstance()
{
	static ResourcesImages img;
	return img;
}
//-----------------------------------------------------------------------------
sf::Texture& ResourcesImages::getTexture(int index)
{
	return v_texture[index];
}
