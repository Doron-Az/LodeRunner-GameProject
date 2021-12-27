#include "Board.h"
#include "GameObject.h"
#include "Rod.h"
#include "Ladder.h"
#include "Wall.h"
#include "Coin.h"
#include "AddLifePresent.h"
#include "AddTimePresent.h"
#include "AddEnemyPresent.h"
#include "AddScorePresent.h"

#include <iostream>
#include <chrono>
#include <thread>

Board::Board() 
	:m_height(0), m_width(0), m_time(0), m_coins(0),
	m_map(NULL),m_addEnemy(false), m_addScore(false), m_addTime(false)
{
	m_boardFile.open("Board.txt");

	if (!m_boardFile) {
		cerr << "Cannot open file " << "Board.txt" << endl;
		exit(EXIT_FAILURE);
	}
	scanMap();
	scanObjectsIconToMap();
}
//-----------------------------------------------------------------------------
Board::Board(const Board& board)
{
	if (board.getHeight() == 0 || board.getWidth() == 0)
		this->~Board();
	{
		this->m_coins = board.getCoins();
		this->m_height = board.getHeight();
		this->m_width = board.getWidth();
		this->m_time = board.getTime();

		this->m_map.resize((int)board.getHeight());
		this->m_boardFile.close();

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width + 1; j++)
			{
				this->m_map[i].push_back(board.getCharObject(i, j));
			}
		}
	}
}
//-----------------------------------------------------------------------------
void Board::scanMap()
{
	char c;

	m_boardFile >> m_height;
	m_boardFile >> std::noskipws >> c;

	m_boardFile >> m_width;
	m_boardFile >> std::noskipws >> c;

	m_boardFile >> m_time;
	m_boardFile >> std::noskipws >> c;


	m_map.clear();
	m_map.resize((int)m_height);

	for (int row = 0; row < m_height; row++) {
		for (int col = 0; col < m_width + 1; col++) { //+1 for the '\n'
			m_boardFile >> std::noskipws >> c;
			m_map[row].push_back(c);
			if (c == '*')
				m_coins++;
		}
	}
}
//-----------------------------------------------------------------------------
float Board::getHeight()const { return m_height; }
//-----------------------------------------------------------------------------
float Board::getWidth()const { return m_width; }
//-----------------------------------------------------------------------------
unsigned int Board::getTime()const { return m_time; }
//-----------------------------------------------------------------------------
char Board::getCharObject(int height, int width)const
{
	if (height >= m_height || width >= m_width || width < 0 || height < 0)
		return 'x';

	return m_map[height][width];
}
//-----------------------------------------------------------------------------
sf::Vector2i Board::getEmptyLocation()
{
	sf::Vector2i empty;

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width + 1; j++)
		{
			int down = i + 1;
			if (m_map[i][j] == ObjectType::SpaceChar && i * j != 0 &&
				m_map[down][j] == ObjectType::WallChar)
			{
				empty.x = j; empty.y = i;
				return empty;
			}
		}
	}
	return Vector2i(0, 0);
}

//-----------------------------------------------------------------------------
void Board::resetSeek()
{
	m_boardFile.seekg(0, m_boardFile.beg);
	m_unmovables.clear();
}
//-----------------------------------------------------------------------------
unsigned int Board::getCoins()const
{
	return m_coins;
}
//-----------------------------------------------------------------------------
void Board::scanObjectsIconToMap()
{
	for (int height = 0; height < m_height; height++) {
		for (int width = 0; width < m_width; width++) {
			createObject(m_map[height][width],
				(float)(height * OBJECT_SIZE), (float)(width * OBJECT_SIZE));
		}
	}
}
//-----------------------------------------------------------------------------
void Board::createObject(char type, float height, float width)
{
	std::unique_ptr<StaticObject> unmovable = createStaticObject(type, height, width);

	if (unmovable) {
		m_unmovables.push_back(std::move(unmovable));
		return;
	}
	if (type == ObjectType::SpaceChar || type == ObjectType::EndLineChar)
		return;
}
//-----------------------------------------------------------------------------
std::unique_ptr<StaticObject> Board::createStaticObject(char type,
	float height, float width)
{
	switch (type)
	{
	case ObjectType::RodChar:
		return std::make_unique<Rod>(height, width);
	case ObjectType::LadderChar:
		return std::make_unique<Ladder>(height, width);
	case ObjectType::WallChar:
		return std::make_unique<Wall>(height, width);
	case ObjectType::CoinChar:
		return std::make_unique<Coin>(height, width);
	case ObjectType::PresentChar:
		return createRandPresentObject(height, width);
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
std::unique_ptr<StaticObject> Board::createRandPresentObject(float height,
	float width)
{
	int presentType = rand() % NUM_PRESENT_TYPE;

	switch (presentType) {

	case PresentType::AddEnemy:
		return std::make_unique<AddEnemyPresent>(height, width);
	case PresentType::AddLife:
		return std::make_unique<AddLifePresent>(height, width);
	case PresentType::AddScore:
		return std::make_unique<AddScorePresent>(height, width);
	case PresentType::AddTime:
		return std::make_unique<AddTimePresent>(height, width);
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
void Board::resetObjectVector()
{
	m_unmovables.clear();
	v_eraseWalls.clear();
}
//-----------------------------------------------------------------------------
void Board::handleCollisionsStaticObjects(GameObject& gameObject)
{
	for (auto& unmovable : m_unmovables)
		if (gameObject.checkCollision(unmovable->getSprite().getGlobalBounds()))
			gameObject.handleCollision(*unmovable);
}
//-----------------------------------------------------------------------------
bool Board::onGraund(GameObject& gameObject)
{
	FloatRect temp = gameObject.getSprite().getGlobalBounds();
	temp.top += 0.01f;
	temp.width -= 20;

	for (auto& unmovable : m_unmovables) {
		if (unmovable->getSprite().getGlobalBounds().intersects(temp)) {
			if (typeid(*unmovable) == typeid(Wall) ||
				typeid(*unmovable) == typeid(Ladder))
				return true;

			else if (typeid(*unmovable) == typeid(Rod) &&
				(abs(unmovable->getSprite().getGlobalBounds().top -
					gameObject.getSprite().getGlobalBounds().top) < MIN_COLLISION))
				return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
void Board::checkWhichObejectDelete()
{
	for (auto& unmovable : m_unmovables) {
		if (typeid(*unmovable) == typeid(AddEnemyPresent) &&
			unmovable->isDisposed() == true)
			m_addEnemy = true;
		if (typeid(*unmovable) == typeid(AddTimePresent) &&
			unmovable->isDisposed() == true)
			m_addTime = true;
		if (typeid(*unmovable) == typeid(AddScorePresent) &&
			unmovable->isDisposed() == true)
			m_addScore = true;

	}
	std::experimental::erase_if(m_unmovables, [](auto& unmovable)
		{
			return unmovable->isDisposed();
		});

}
//-----------------------------------------------------------------------------
void Board::drawStaticObjects(sf::RenderWindow& window)
{
	
	for (auto& unmovable : m_unmovables)
		unmovable->draw(window);
}
//-----------------------------------------------------------------------------
bool Board::getIfAddEnemy()const
{
	return m_addEnemy;
}
//-----------------------------------------------------------------------------
void Board::setAddEnemy()
{
	m_addEnemy = false;
}
//-----------------------------------------------------------------------------
bool Board::getIfAddTime()const
{
	return m_addTime;
}
//-----------------------------------------------------------------------------
void Board::setAddTime()
{
	m_addTime = false;
}
//-----------------------------------------------------------------------------
bool Board::getIfAddScore()const
{
	return m_addScore;
}
//-----------------------------------------------------------------------------
void Board::setAddScore()
{
	m_addScore = false;
}
//-----------------------------------------------------------------------------
void Board::digger(sf::Vector2f playerLocation, char side, float currTime)
{
	int x = (int)round((playerLocation.x) / OBJECT_SIZE);
	int y = (int)round((playerLocation.y) / OBJECT_SIZE);
	int down = y + 1;
	int left = x - 1;
	int right = x + 1;

	if (x > 0 && y >= 0 && x < m_width && y < m_height) {
		if (side == digDierction::d_digLeft)
		{
			if (m_map[down][left] == ObjectType::WallChar)
			{
				if (m_map[y][left] == ObjectType::SpaceChar)
					deleteWall(left, down, currTime);
				else if (!checkIfPresentOrCoin(left, y))
					deleteWall(left, down, currTime);
			}
		}
		if (side == digDierction::d_digRight)
		{
			if (m_map[down][right] == ObjectType::WallChar)
			{
				if (m_map[y][right] == ObjectType::SpaceChar)
					deleteWall(right, down, currTime);
				else if (!checkIfPresentOrCoin(right, y))
					deleteWall(right, down, currTime);
			}
		}
	}
}
//-----------------------------------------------------------------------------
void Board::deleteWall(int x, int y, float currTime)
{
	struct EraseWalls currWall;

	ResourcesSounds::getInstance().playSound(soundType::s_dig);

	for (auto& unmovable : m_unmovables)
	{
		cout << unmovable->getSprite().getPosition().x <<" " << unmovable->getSprite().getPosition().y << endl;
		cout << m_unmovables.size()<<  endl;
		if (unmovable->getSprite().getPosition().x == x * OBJECT_SIZE &&
			unmovable->getSprite().getPosition().y == y * OBJECT_SIZE) 
		{
			unmovable->setDisposed();
			currWall.location = unmovable->getSprite().getPosition();
			currWall.deleteTime = currTime;
			v_eraseWalls.push_back(currWall);
		}
	}
}
//-----------------------------------------------------------------------------
void Board::checkReturnWalls(float currTime)
{
	if (v_eraseWalls.size() > EMPTY) {
		for (int i = 0; i < v_eraseWalls.size(); i++) {
			if (currTime - v_eraseWalls[i].deleteTime > SWITCH_TIME) {
				std::unique_ptr<StaticObject> unmovable =
					createStaticObject(WallChar, v_eraseWalls[i].location.y,
						v_eraseWalls[i].location.x);
				m_unmovables.push_back(std::move(unmovable));
				v_eraseWalls.erase(v_eraseWalls.begin() + i);
			}
		}
	}
}
//-----------------------------------------------------------------------------
bool Board::checkIfPresentOrCoin(int x, int y)
{
	for (auto& unmovable : m_unmovables) {
		if (((unmovable->getSprite().getPosition().x / OBJECT_SIZE) == x) &&
			((unmovable->getSprite().getPosition().y / OBJECT_SIZE) == y))
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
bool Board::isWall(sf::Vector2f location)
{
	for (auto& unmovable : m_unmovables)
	{
		if (typeid(*unmovable) == typeid(Wall))
		{
			if ((unmovable->getSprite().getPosition().x / OBJECT_SIZE) ==
				floor(location.x / OBJECT_SIZE) &&
				((unmovable->getSprite().getPosition().y / OBJECT_SIZE) ==
					floor((location.y + (OBJECT_SIZE / 2)) / OBJECT_SIZE)))

				return true;

		}
	}
	return false;
}