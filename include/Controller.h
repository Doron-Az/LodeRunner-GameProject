#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <experimental/vector>

#include <chrono>
#include <thread>
#include <string>

#include "MainMenu.h"
#include "Animation.h"
#include "Information.h"

#include "Board.h"
#include "Player.h"
#include "Coin.h"
#include "LeftRightEnemy.h"
#include "RegularEnemy.h"
#include "SmartEnemy.h"
#include "ResourcesSounds.h"

class Controller
{
public:

	Controller();
	void run();
	void scanObjectsIconToMap();
	void createMovingObject(char type, float height, float width);
	void setWindow();
	void drawObjects();
	void handleCollisions(GameObject& gameObject);
	void resetLevel();
	void gameOver();
	void disqualification();
	void nextLevel();
	bool checkGravity(GameObject& gameObject);
	bool CheckIfTimeOut()const;
	void updateDataLevel();
	void draw();
	void handleEvents();
	void updateGameObjects();
	void updateScoreAndInformation();
	void addTimeToLevel();
	void addEnemyToLevel();
	void resetData();
	void fullScanObject();
	int setTimeToPrint();

	std::unique_ptr<MovingObject>
		createRandEnemygObject(float height, float width);

private:
	int m_level;
	int m_score;
	int m_currCoinPlayer;
	int m_currLive;
	int m_playerIndex;
	int m_extraTime;
	bool m_fullScan = true;

	sf::Clock m_deltaClock, m_levelClock;
	sf::Time m_time;
	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<MovingObject>> m_movables;

	Board m_board;
	Information m_information;
	MainMenu m_mainMenu;
};



