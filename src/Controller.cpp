#include "Controller.h"

//=============================================================================
Controller::Controller() :m_level(FIRST_LEVEL), m_currLive(BEGIN_LIFE),
m_playerIndex(PLAYER_INDEX),m_currCoinPlayer(RESET), m_extraTime(RESET),
m_score(RESET), m_information(RESET, RESET, RESET, RESET, RESET, RESET)
{
	srand((unsigned int)time(NULL));
	scanObjectsIconToMap();
	setWindow();
	m_deltaClock.restart();
	m_information.setPosition(m_board.getHeight() * OBJECT_SIZE);
}
//=============================================================================
void Controller::run()
{
	while (m_window.isOpen())
	{
		handleEvents();
		updateGameObjects();
		updateDataLevel();
		m_board.checkWhichObejectDelete();
		updateScoreAndInformation();
		draw();
	}
}
//-----------------------------------------------------------------------------
void Controller::scanObjectsIconToMap()
{
	if (m_fullScan)
		m_movables.push_back(std::make_unique<Player>(RESET, RESET, m_currCoinPlayer,&m_board));

	for (int height = 0; height < m_board.getHeight(); height++) {
		for (int width = 0; width < m_board.getWidth(); width++) {
			createMovingObject((ObjectType)m_board.getCharObject(height, width),
				(float)(height * OBJECT_SIZE), (float)(width * OBJECT_SIZE));
		}
	}
	m_fullScan = false;
}
//=============================================================================
void Controller::createMovingObject(char type,float height,float width)
{
	if (type == ObjectType::PlayerChar) {
		m_movables[m_playerIndex]->setLocation(height, width);
		return;
	}
	if (type == ObjectType::EnemyChar && m_fullScan == true) {
		std::unique_ptr<MovingObject> movable = createRandEnemygObject(height, width);
		m_movables.push_back(std::move(movable));
		return;
	}
}
//-----------------------------------------------------------------------------
std::unique_ptr<MovingObject> Controller::createRandEnemygObject(float height, float width)
{
	int enemyType = rand() % NUM_ENEMY_TYPE;
	switch (enemyType) {
	case EnemyType::Regular:
		return std::make_unique<RegularEnemy>(height, width);
	case EnemyType::LeftRight:
		return std::make_unique<LeftRightEnemy>(m_board, height, width);
	case EnemyType::Smart:
		return std::make_unique<SmartEnemy>(m_movables[m_playerIndex].get(), m_board, height, width);
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
void Controller::setWindow()
{
	unsigned int width = MIN_WIDTH_WINDOW;
	if ((m_board.getWidth() * OBJECT_SIZE) > MIN_WIDTH_WINDOW)
		width = (unsigned int)(m_board.getWidth() * OBJECT_SIZE);

	m_window.create(sf::VideoMode(width, (unsigned int)(m_board.getHeight()
		* OBJECT_SIZE + OBJECT_SIZE)), "Loud Runner");

	m_information.setPosition(m_board.getHeight() * OBJECT_SIZE);
}
//-----------------------------------------------------------------------------
void Controller::drawObjects()
{
	m_board.drawStaticObjects(m_window);

	for (auto& movable : m_movables) {
		movable->draw(m_window);
	}
}
//-----------------------------------------------------------------------------
void Controller::handleCollisions(GameObject& gameObject)
{
	m_board.handleCollisionsStaticObjects(gameObject);

	for (auto& movable : m_movables)
		if (gameObject.checkCollision(movable->getSprite().getGlobalBounds()))
			gameObject.handleCollision(*movable);
}
//-----------------------------------------------------------------------------
bool Controller::checkGravity(GameObject& gameObject)
{
	return m_board.onGraund(gameObject);
}
//-----------------------------------------------------------------------------
void Controller::resetLevel()
{
	m_extraTime = RESET;
	m_levelClock.restart();
	m_time = m_levelClock.getElapsedTime();

	if (m_fullScan == false)
		for (auto& movable : m_movables)
			movable->setStartLocation(movable->getStartLocation());
	else
		m_movables.clear();

	m_board.resetObjectVector();
	m_board.scanObjectsIconToMap();
	scanObjectsIconToMap();
}
//-----------------------------------------------------------------------------
void Controller::gameOver()
{
	sf::Sprite over;
	over.setTexture(ResourcesImages::getInstance().getTexture(NUM_OF_TEXTURE));
	over.setPosition(m_window.getView().getCenter().x - WIDTH_GAME_OVER,
		m_window.getView().getCenter().y - HEIGHT_GAME_OVER);
	over.setScale(2, 2);

	m_window.clear();
	drawObjects();
	m_window.draw(over);
	m_window.display();
	this_thread::sleep_for(chrono::milliseconds(5000));
	m_window.close();
	m_mainMenu.run();

	resetData();
	fullScanObject();
	setWindow();
}
//-----------------------------------------------------------------------------
void Controller::disqualification()
{
	if (m_movables[m_playerIndex]->isDisposed() == true)
		gameOver();
	else
		resetLevel();
}
//-----------------------------------------------------------------------------
void Controller::nextLevel()
{
	m_score += BONUS_LEVEL * m_level;
	m_board.scanMap();
	m_levelClock.restart();
	setWindow();
	fullScanObject();
	m_level++;

	ResourcesSounds::getInstance().playSound(s_nextLevel);
}
//-----------------------------------------------------------------------------
bool Controller::CheckIfTimeOut()const
{
	return((m_levelClock.getElapsedTime().asSeconds() - m_time.asSeconds()) >=
		m_board.getTime() + m_extraTime);
}
//-----------------------------------------------------------------------------
void Controller::updateDataLevel()
{
	if (m_currLive > m_movables[m_playerIndex]->getLive()) {
		m_currLive--;
		disqualification();
	}

	else if (m_currLive < m_movables[m_playerIndex]->getLive())
		m_currLive = m_movables[m_playerIndex]->getLive();

	if (Coin::getCoinNum() == 0) {
		nextLevel();
	}

	if (m_board.getIfAddEnemy())
		addEnemyToLevel();

	if (m_board.getIfAddTime())
		addTimeToLevel();

	if (CheckIfTimeOut() && m_board.getTime() != NO_TIME) {
		disqualification();
		m_currLive--;
		m_movables[m_playerIndex]->setLive(m_currLive);
	}
	m_board.checkReturnWalls(m_levelClock.getElapsedTime().asSeconds());
}
//-----------------------------------------------------------------------------
void Controller::draw()
{
	m_window.clear();
	m_information.draw(m_window);
	drawObjects();
	m_window.display();
}
//-----------------------------------------------------------------------------
//keyboard events 
void Controller::handleEvents()
{
	for (auto event = sf::Event(); m_window.pollEvent(event);)
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::Z)
			{
				m_movables[m_playerIndex]->digger(d_digLeft,
					(float)m_levelClock.getElapsedTime().asSeconds());
				break;
			}
			if (event.key.code == sf::Keyboard::X)
			{
				m_movables[m_playerIndex]->digger(d_digRight,
					(float)m_levelClock.getElapsedTime().asSeconds());
				break;
			}
		}
}
//-----------------------------------------------------------------------------
//moving function && check if return wall && check isFall
void Controller::updateGameObjects()
{
	const auto deltaTime = m_deltaClock.restart();

	for (auto& movable : m_movables)
	{
		char currBoardChar = m_board.getCharObject((int)(floor(movable->getSprite().getPosition().y)
			/ OBJECT_SIZE), (int)(floor(movable->getSprite().getPosition().x + OBJECT_SIZE / 2) / OBJECT_SIZE));
		if (!checkGravity(*movable))
			movable->fallDown(deltaTime, m_board.getHeight(), m_board.getWidth(), currBoardChar);

		else movable->move(deltaTime, m_board.getHeight(), m_board.getWidth());

		handleCollisions(*movable);
		//check if there is deleted walls to stuck the movable 
		if (m_board.isWall(movable->getSprite().getPosition()) == true)
		{
			movable->setLocation(movable->getSprite().getPosition().y - OBJECT_SIZE
				, movable->getSprite().getPosition().x);
		}
	}
}
//-----------------------------------------------------------------------------
void Controller::updateScoreAndInformation()
{
	if (m_currCoinPlayer < m_movables[m_playerIndex]->getScore())
	{
		m_score += SCORE_PER_COIN * m_level;
		m_currCoinPlayer = m_movables[m_playerIndex]->getScore();
	}
	if (m_board.getIfAddScore() == true) //move to updateDataLevel
	{
		m_score += PRESENT_BONUS;
		m_board.setAddScore();
	}

	m_information.setInformation(m_score, m_movables[m_playerIndex]->getLive(),
		setTimeToPrint(), m_level);
}
//-----------------------------------------------------------------------------
void Controller::addTimeToLevel()
{
	m_extraTime += TIME_BONUS;
	m_board.setAddTime();
}
//-----------------------------------------------------------------------------
void Controller::addEnemyToLevel()
{
	sf::Vector2i empty = m_board.getEmptyLocation();

	std::unique_ptr<MovingObject> movable = createRandEnemygObject((float)
		(empty.y * OBJECT_SIZE), (float)(empty.x * OBJECT_SIZE));

	m_movables.push_back(std::move(movable));
	m_board.setAddEnemy();
}
//-----------------------------------------------------------------------------
void Controller::resetData()
{
	m_score = RESET;
	m_currCoinPlayer = RESET;
	m_extraTime = RESET;
	m_level = FIRST_LEVEL;
	m_board.resetSeek();
	m_board.scanMap();
	m_deltaClock.restart();
	m_information.setPosition(m_board.getHeight() * OBJECT_SIZE);
}
//-----------------------------------------------------------------------------
void Controller::fullScanObject()
{
	m_fullScan = true;
	resetLevel();
}
//-----------------------------------------------------------------------------
int Controller::setTimeToPrint()
{
	if (m_board.getTime() == NO_TIME)
		return NO_TIME;

	return (m_extraTime + m_board.getTime() - (int)m_levelClock.getElapsedTime().asSeconds()-
		(int)m_time.asSeconds());
}