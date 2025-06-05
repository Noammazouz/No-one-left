//-----include section-----
#include "GameController.h"

//-----functions section------
//-----------------------------------------------------------------------------
GameController::GameController()
	: m_timer(sf::seconds(0))
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(desktop.width * WINDOW_RATIO, desktop.height * WINDOW_RATIO), "No One Left");
	m_screen.push(screen)
}

//-----------------------------------------------------------------------------
void GameController::newGame()
{
	handleMusicTransition(false);
	m_screen.top().activate();
	runLevel();
}

//-----------------------------------------------------------------------------
void GameController::runLevel()
{
	
	handleMusicTransition(true);
	m_scoreboard.updateScore(0);

	sf::Clock clock;
	handleLoadingLevel(clock);

	while (m_window.isOpen())
	{
		m_window.clear();

		drawWindow();
		m_window.display();

		m_player.setDirection(sf::Vector2f());

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
			{
				handleKeyPressed(event.key);
				break;
			}
			}
		}

		move(clock);
		handleCollision();
		explosion();
		handleErasing();
		handleSocreboard();
		if (m_player.getWin())
		{
			calculateScore();
			handleLoadingLevel(clock);
			if (m_win)
			{
				winWindow();
				break;
			}
		}
		if (m_player.getLife() == END_GAME)
		{
			lostWindow();
			break;
		}
		else if (m_timer.asSeconds() <= 0.f)
		{
			m_player.decLife();
			handleLoadingLevel(clock);
		}
	}
}

//-----------------------------------------------------------------------------
void  GameController::drawWindow()
{
	ResourcesManager& resources = ResourcesManager::getInstance();
	sf::Sprite backround;

	backround.setTexture(resources.getTexture("backround"));
	m_window.draw(backround);

	for (const auto& staticObj : m_staticObj)
	{
		staticObj->draw(m_window);
	}

	// Draw moving objects
	for (const auto& movingObj : m_movingObj)
	{
		movingObj->draw(m_window);
	}

	m_player.draw(m_window);
	m_window.draw(m_scoreboard.getLevel());
	m_window.draw(m_scoreboard.getScore());
	m_window.draw(m_scoreboard.getTime());
	m_window.draw(m_scoreboard.getLives());
}

//-----------------------------------------------------------------------------
void GameController::move(sf::Clock& clock)
{
	const auto deltaTime = clock.restart();

	int index = 0;
	m_player.update(deltaTime);
	for (const auto& movingObj : m_movingObj)
	{
		if (index < Guard::getNumOfGuardsAlive())
		{
			movingObj->setDirection(m_player.getPosition());
		}
		movingObj->update(deltaTime);
		index++;
	}
	m_timer -= deltaTime;
}

//-----------------------------------------------------------------------------
void GameController::handleCollision()
{
	for (const auto& staticObj : m_staticObj)
	{
		if (m_player.checkCollision(*staticObj))
		{
			m_player.collide(*staticObj);
		}
	}

	handlePresents();

	for (const auto& movingObj : m_movingObj)
	{
		for (const auto& staticObj : m_staticObj)
		{
			if (movingObj->checkCollision(*staticObj))
			{
				movingObj->collide(*staticObj);
			}
		}
	}

	for (int guard = 0; guard < Guard::getNumOfGuardsAlive(); ++guard)
	{
		if (m_player.checkCollision(*m_movingObj[guard]))
		{
			m_sound.setBuffer(ResourcesManager::getInstance().getSound("hit"));
			m_sound.setVolume(100.f);
			m_sound.play();
			m_player.collide(*m_movingObj[guard]);
			resetLevel();
			break;
		}
	}

	for (int moveObj = 0; moveObj < (Guard::getNumOfGuardsAlive() - 1); ++moveObj)
	{
		for (int nextMoveObj = moveObj + 1; nextMoveObj < Guard::getNumOfGuardsAlive(); ++nextMoveObj)
		{
			if (m_movingObj[moveObj]->checkCollision(*m_movingObj[nextMoveObj]))
			{
				m_movingObj[moveObj]->collide(*m_movingObj[nextMoveObj]);
			}
		}
	}
}

//-----------------------------------------------------------------------------
void GameController::setbomb()
{
	m_movingObj.push_back(std::make_unique<Bombs>(sf::Vector2f(m_player.getPosition()), ResourcesManager::getInstance().getTexture("bomb")));
}

//-----------------------------------------------------------------------------
void GameController::handleErasing()
{
	std::erase_if(m_movingObj, [](const auto& item)
		{return item->isDead(); });

	std::erase_if(m_staticObj, [](const auto& item)
		{return item->isDead(); });
}

//-----------------------------------------------------------------------------
void GameController::explosion()
{
	auto bomb = Guard::getNumOfGuardsAlive();

	for (; bomb < m_movingObj.size(); bomb++)
	{
		if (m_movingObj[bomb]->getExpo())
		{
			m_sound.setBuffer(ResourcesManager::getInstance().getSound("explosion"));
			m_sound.setVolume(100.f);
			m_sound.play();
			setExpoDirection(bomb);
			checkVaildDraw();
			drawWindow();
			checkExpo();
		}
	}
}

//-----------------------------------------------------------------------------
void GameController::calculateScore()
{
	int points = 0;
	points += ENDING_LEVEL;
	points += (Guard::getNumOfStartingGuards() * POINT_FOR_GUARD);
	points += (std::abs(Guard::getNumOfGuardsAlive() - Guard::getNumOfStartingGuards()) * KILL_GUARD);
	m_player.setScore(points);
}

//-----------------------------------------------------------------------------
void GameController::resetLevel()
{
	for (int index = 0; index < Guard::getNumOfGuardsAlive(); ++index)
	{
		m_movingObj[index]->setPosition(m_movingObj[index]->getStartingPosition());
	}
	for (int index = Guard::getNumOfGuardsAlive(); index < m_movingObj.size(); ++index)
	{
		m_movingObj[index]->setLife(true);
	}
}

//-----------------------------------------------------------------------------
void GameController::setExpoDirection(int index)
{
	for (int direction = 0; direction < NUM_OF_DIRECTION; direction++)
	{
		switch (direction)
		{
		case UP:
			m_movingObj.push_back(std::make_unique<Explosion>(sf::Vector2f(m_movingObj[index]->getPosition()), ResourcesManager::getInstance().getTexture("explosion")));
			m_movingObj[m_movingObj.size() - 1]->setDirection(sf::Vector2f(0, -DEFUALT_WIDTH));
			break;
		case DOWN:
			m_movingObj.push_back(std::make_unique<Explosion>(sf::Vector2f(m_movingObj[index]->getPosition()), ResourcesManager::getInstance().getTexture("explosion")));
			m_movingObj[m_movingObj.size() - 1]->setDirection(sf::Vector2f(0, DEFUALT_WIDTH));
			break;
		case LEFT:
			m_movingObj.push_back(std::make_unique<Explosion>(sf::Vector2f(m_movingObj[index]->getPosition()), ResourcesManager::getInstance().getTexture("explosion")));
			m_movingObj[m_movingObj.size() - 1]->setDirection(sf::Vector2f(-DEFUALT_WIDTH, 0));
			break;
		case RIGHT:
			m_movingObj.push_back(std::make_unique<Explosion>(sf::Vector2f(m_movingObj[index]->getPosition()), ResourcesManager::getInstance().getTexture("explosion")));
			m_movingObj[m_movingObj.size() - 1]->setDirection(sf::Vector2f(DEFUALT_WIDTH, 0));
			break;
		}
	}
	m_movingObj.push_back(std::make_unique<Explosion>(sf::Vector2f(m_movingObj[index]->getPosition()), ResourcesManager::getInstance().getTexture("explosion")));
}

//-----------------------------------------------------------------------------
void GameController::checkExpo()
{
	auto explosion = m_movingObj.size() - NUM_OF_EXPLOSION;
	for (; explosion < m_movingObj.size(); explosion++)
	{
		for (int guard = 0; guard < Guard::getNumOfGuardsAlive(); guard++)
		{
			if (m_movingObj[explosion]->checkCollision(*m_movingObj[guard]))
			{
				m_movingObj[explosion]->collide(*m_movingObj[guard]);

			}
		}
		for (const auto& staticObj : m_staticObj)
		{
			if (m_movingObj[explosion]->checkCollision(*staticObj))
			{
				m_movingObj[explosion]->collide(*staticObj);
			}
		}
		if (m_movingObj[explosion]->checkCollision(m_player))
		{
			m_sound.setBuffer(ResourcesManager::getInstance().getSound("hit"));
			m_sound.setVolume(100.f);
			m_sound.play();
			m_movingObj[explosion]->collide(m_player);
			resetLevel();
			break;
		}
	}
}

//-----------------------------------------------------------------------------
void GameController::checkVaildDraw()
{
	auto explosion = m_movingObj.size() - NUM_OF_EXPLOSION;
	for (; explosion < m_movingObj.size(); explosion++)
	{
		for (const auto& staticObj : m_staticObj)
		{
			if (m_movingObj[explosion]->checkCollision(*staticObj))
			{
				m_movingObj[explosion]->collide(*staticObj);
			}
		}
	}
	handleErasing();
}

//-----------------------------------------------------------------------------
void GameController::handleLoadingLevel(sf::Clock& clock)
{
	m_movingObj.clear();
	m_staticObj.clear();
	if (m_map.loadLevel(m_level) == END_GAME)
	{
		m_win = true;
		calculateScore();
		m_scoreboard.updateScore(m_player.getScore());
		return;
	}
	Guard::resetNumOfGuards();
	m_map.LoadBoard(m_movingObj, m_staticObj, m_player);

	m_timer = sf::seconds(120);
	clock.restart();
}

//-----------------------------------------------------------------------------
void GameController::handleMusicTransition(bool toGameplay)
{
	if (toGameplay && !m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic("screen").stop();
		if (ResourcesManager::getInstance().getMusic("game").getStatus() != sf::Music::Playing)
		{
			ResourcesManager::getInstance().getMusic("game").play();
		}
		m_inGameplay = true;
	}
	else if (!toGameplay && m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic("game").stop();
		ResourcesManager::getInstance().getMusic("screen").play();
		m_inGameplay = false;
	}
	else
	{
		ResourcesManager::getInstance().getMusic("screen").play();
	}
}

//-----------------------------------------------------------------------------
void GameController::handleMuting()
{
	if (ResourcesManager::getInstance().getMusic("game").getStatus() == sf::Music::Playing)
	{
		ResourcesManager::getInstance().getMusic("game").pause();
	}
	else
	{
		ResourcesManager::getInstance().getMusic("game").play();
	}
}

//-----------------------------------------------------------------------------
void GameController::handleSocreboard()
{
	m_scoreboard.updateTime(m_timer);
	m_scoreboard.updateLevel(m_level);
	m_scoreboard.updateLives(m_player.getLife());
	m_scoreboard.updateScore(m_player.getScore());
}

//-----------------------------------------------------------------------------
void GameController::handlePresents()
{
	switch (m_player.getPresent())
	{
	case TIME:
	{
		addTime();
		break;
	}
	case KILL:
	{
		removeGuard();
		break;

	}
	}
	m_player.setPresent(DEFAULT);
}

//-----------------------------------------------------------------------------
void GameController::removeGuard()
{
	if (Guard::getNumOfGuardsAlive() != 0)
	{
		srand(time(NULL));
		int index = rand() % Enemy::getNumOfGuardsAlive();
		m_movingObj[index]->setLife(true);
	}
}

//-----------------------------------------------------------------------------
void GameController::addTime()
{
	m_timer += sf::seconds(ADDED_TIME);
	m_scoreboard.updateTime(m_timer);
}

//-----------------------------------------------------------------------------
void GameController::lostWindow()
{
	// to do a Lost board
	ResourcesManager::getInstance().getMusic("game").stop();
	m_sound.setBuffer(ResourcesManager::getInstance().getSound("loss"));
	m_sound.setVolume(100.f);
	m_sound.play();

	sf::Sprite lostWindow;
	lostWindow.setTexture(ResourcesManager::getInstance().getTexture("game over"));
	m_window.clear();
	m_window.draw(lostWindow);
	m_window.display();
	sf::sleep(sf::seconds(2));
	m_window.close();
}

///-----------------------------------------------------------------------------
void GameController::winWindow()
{
	// to do a win board
	ResourcesManager::getInstance().getMusic("game").stop();
	m_sound.setBuffer(ResourcesManager::getInstance().getSound("win"));
	m_sound.setVolume(100.f);
	m_sound.play();

	sf::Sprite winWindow;
	winWindow.setTexture(ResourcesManager::getInstance().getTexture("win"));
	m_window.clear();
	m_window.draw(winWindow);
	m_window.draw(m_scoreboard.getScore());
	m_window.display();
	sf::sleep(sf::seconds(3));
	m_window.close();
}

//-----------------------------------------------------------------------------
void GameController::handleKeyPressed(sf::Event::KeyEvent event)
{
	if (event.code == sf::Keyboard::Escape)
	{
		m_window.close();
		newGame();
	}
	if (event.code == sf::Keyboard::B)
	{
		setbomb();
	}
	if (event.code == sf::Keyboard::M)
	{
		handleMuting();
	}
}