#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Constant.h"

//Singleton  
class ResourcesSounds
{
public:
	~ResourcesSounds() = default;
	static ResourcesSounds& getInstance();
	void playSound(int index);
	void pauseSound(int index);

private:
	ResourcesSounds();
	ResourcesSounds(const ResourcesSounds&) = default;
	ResourcesSounds& operator=(const ResourcesSounds&) = default;

	std::vector< sf::Sound > v_sound;
	std::vector< sf::SoundBuffer > v_soundBuffer;
};
