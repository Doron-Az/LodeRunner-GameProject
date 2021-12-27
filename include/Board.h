#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <experimental/vector>

#include "StaticObject.h"
#include "Constant.h"

using std::vector;
using std::ifstream;
using std::cerr;
using namespace std;

//Forward declaration
class GameObject;
class Rod;
class Ladder;
class Wall;
class Coin;
class AddEnemyPresent;
class AddLifePresent;
class AddTimePresent;
class AddScorePresent;

//save delete wall data
struct EraseWalls {
	Vector2f location;
	float deleteTime = 0;
};

class Board
{
public:
	Board();
	Board(const Board& board); //copy constractor
	~Board() = default;

	enum PresentType { AddEnemy, AddLife, AddScore, AddTime };

	void scanMap();
	void resetSeek();
	void checkWhichObejectDelete();
	void resetObjectVector();
	float getHeight()const;
	float getWidth()const;
	unsigned int getTime()const;
	unsigned int getCoins()const;
	char getCharObject(int height, int width)const;
	bool onGraund(GameObject& gameObject);
	void handleCollisionsStaticObjects(GameObject& gameObject);
	void drawStaticObjects(sf::RenderWindow& window);
	void scanObjectsIconToMap();
	void createObject(char type, float height, float width);
	void setAddEnemy();
	void setAddTime();
	void setAddScore();
	bool getIfAddEnemy()const;
	bool getIfAddTime()const;
	bool getIfAddScore()const;
	void digger(sf::Vector2f playerLocation, char side, float currTime);
	void deleteWall(int x, int y, float currTime);
	void checkReturnWalls(float currTime);
	bool checkIfPresentOrCoin(int x, int y);
	bool isWall(sf::Vector2f location);

	sf::Vector2i getEmptyLocation();

	std::unique_ptr<StaticObject> 
		createStaticObject(char type, float height, float width);

	std::unique_ptr<StaticObject>
		createRandPresentObject(float height, float width);

private:
	float m_width, m_height;
	unsigned int m_coins, m_time;
	ifstream m_boardFile;
	vector<vector<char>> m_map;
	vector<EraseWalls> v_eraseWalls;
	std::vector<std::unique_ptr<StaticObject>> m_unmovables;

	bool m_addEnemy;
	bool m_addTime;
	bool m_addScore;
};