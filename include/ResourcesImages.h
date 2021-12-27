
#pragma once
#include <SFML/Graphics.hpp>
#include "Constant.h"

//Singleton 
class ResourcesImages
{
public:
	~ResourcesImages() = default;
	static ResourcesImages& getInstance();
	sf::Texture& getTexture(int index);

private:
	ResourcesImages();
	ResourcesImages(const ResourcesImages&) = default;
	ResourcesImages& operator=(const ResourcesImages&) = default;
	std::vector< sf::Texture > v_texture;
};
