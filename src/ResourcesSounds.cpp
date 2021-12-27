#include "ResourcesSounds.h"
#include <iostream>
//Singlton
ResourcesSounds::ResourcesSounds()
{
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;

	soundBuffer.loadFromFile("born.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("dead.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("dig.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("down.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("fall.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("getGold.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("pass.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("present.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("nextLevel.ogg");
	v_soundBuffer.push_back(soundBuffer);
	soundBuffer.loadFromFile("createEnemy.ogg");
	v_soundBuffer.push_back(soundBuffer);


	for (int i = 0; i < NUM_OF_SOUNDS; i++)
	{
		sound.setBuffer(v_soundBuffer[i]);
		v_sound.push_back(sound);
	}
}
//-----------------------------------------------------------------------------
ResourcesSounds& ResourcesSounds::getInstance()
{
	static ResourcesSounds sound;
	return sound;
}
//-----------------------------------------------------------------------------
void ResourcesSounds::playSound(int index)
{
	v_sound[index].play();
}
//-----------------------------------------------------------------------------
void ResourcesSounds::pauseSound(int index)
{
	v_sound[index].pause();
}