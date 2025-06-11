#include "GameScreen.h"



GameScreen::GameScreen()
	: worldBounds(0.f, 0.f, MAP_WIDTH, MAP_HEIGHT)
{
	initButtons();
}
//-------------------------------------
void GameScreen::run(sf::RenderWindow& window, int& m_currrentScreen)
{
	Screen::run(window, m_currrentScreen);
	m_view.setCenter(m_player.getPos());
	m_view.setCenter(clampViewPosition(worldBounds));
	window.setView(m_view);
}
//---------
void GameScreen::activate(sf::Clock& clock, int& m_currrentScreen)
{
	if (m_paused)
	{
		handleMusicTransition(false);
		return;
	}
	handleMusicTransition(true);

	handleLoadingLevel();
	if (m_staticObj.empty()) {
		std::cerr << "[WARN] No static objects were loaded—are you sure your CSV has entries?\n";
	}

	m_player.setDirection(sf::Vector2f());


	move(clock);
	handleCollision();
	explosion();
	handleErasing();
	handleSocreboard();
	if (m_player.getWin())
	{
		m_sound.setBuffer(ResourcesManager::getInstance().getSound("door"));
		m_sound.setVolume(100.f);
		m_sound.setPlayingOffset(sf::seconds(0.95f));
		m_sound.play();
		calculateScore();
		if (m_win)
		{
			m_currrentScreen = WIN_SCREEN;
			return;
		}
	}
	if (m_player.getLife() == END_GAME)
	{
		m_currrentScreen = LOSE_SCREEN;
		return;
	}

}

//-------------------------------------
void GameScreen::initButtons()
{
	sf::Vector2f pos(20.f, 20.f); // Fixed top-left with padding
	m_buttons.emplace_back("pause", pos);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::vector<std::string> buttonNames = { "resume", "exit" };
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(desktop.width * WINDOW_RATIO / 2),
			static_cast<float>(desktop.height * WINDOW_RATIO / 5 + 300 * index));
		m_buttons.emplace_back(buttonNames[index], position);
	}
}


//-------------------------------------
void GameScreen::draw(sf::RenderWindow& window)
{

	// Draw game world
	sf::Sprite backround;
	sf::Texture texure = ResourcesManager::getInstance().getTexture("background");
	texure.setRepeated(true);
	texure.setSmooth(true);

	backround.setTexture(texure);
	backround.setTextureRect(sf::IntRect(0, 0, MAP_WIDTH, MAP_HEIGHT));
	window.draw(backround);

	for (auto& obj : m_staticObj)
		obj->draw(window);

	m_player.draw(window);

	// Switch to default view to draw UI
	window.setView(window.getDefaultView());

	if (m_paused)
		drawButtons(window); // Menu buttons
	else
		m_buttons[PAUSE].draw(window); // Only pause button
}

//-------------------------------------
void GameScreen::move(sf::Clock& clock)
{
	const auto deltaTime = clock.restart();

	int index = 0;
	m_player.update(deltaTime);
	/*for (const auto& movingObj : m_movingObj)
	{
		if (index < Enemy::getNumOfGuardsAlive())
		{
			movingObj->setDirection(m_player.getPosition());
		}
		movingObj->update(deltaTime);
		index++;
	}*/
	
}
//-------------------------------------
void GameScreen::handleCollision()
{
	/*for (const auto& staticObj : m_staticObj)
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

	for (int guard = 0; guard < Enemy::getNumOfGuardsAlive(); ++guard)
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

	for (int moveObj = 0; moveObj < (Enemy::getNumOfGuardsAlive() - 1); ++moveObj)
	{
		for (int nextMoveObj = moveObj + 1; nextMoveObj < Enemy::getNumOfGuardsAlive(); ++nextMoveObj)
		{
			if (m_movingObj[moveObj]->checkCollision(*m_movingObj[nextMoveObj]))
			{
				m_movingObj[moveObj]->collide(*m_movingObj[nextMoveObj]);
			}
		}
	}*/
}
//-------------------------------------
void GameScreen::setbomb()
{
	//m_movingObj.push_back(std::make_unique<Bombs>(sf::Vector2f(m_player.getPosition()), ResourcesManager::getInstance().getTexture("bomb")));
}
//-------------------------------------
void GameScreen::handleErasing()
{
	/*std::erase_if(m_movingObj, [](const auto& item)
		{return item->isDead(); });

	std::erase_if(m_staticObj, [](const auto& item)
		{return item->isDead(); });*/
}
//-------------------------------------
void GameScreen::explosion()
{
	/*auto bomb = Enemy::getNumOfGuardsAlive();

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
	}*/
}
//-------------------------------------
void GameScreen::calculateScore()
{
	/*int points = 0;
	points += ENDING_LEVEL;
	points += (Enemy::getNumOfStartingGuards() * POINT_FOR_GUARD);
	points += (std::abs(Enemy::getNumOfGuardsAlive() - Enemy::getNumOfStartingGuards()) * KILL_GUARD);
	m_player.setScore(points);*/
}
//-------------------------------------
void GameScreen::setExpoDirection(int index)
{
	/*for (int direction = 0; direction < NUM_OF_DIRECTION; direction++)
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
}*/
}
//-------------------------------------
void GameScreen::checkExpo()
{
	/*auto explosion = m_movingObj.size() - NUM_OF_EXPLOSION;
	for (; explosion < m_movingObj.size(); explosion++)
	{
		for (int guard = 0; guard < Enemy::getNumOfGuardsAlive(); guard++)
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
	}*/
}
//-------------------------------------
void GameScreen::checkVaildDraw()
{
	/*auto explosion = m_movingObj.size() - NUM_OF_EXPLOSION;
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
	handleErasing();*/
}
//---------------------------------
void GameScreen::handleLoadingLevel()
{
	m_movingObj.clear();
	m_staticObj.clear();

	m_map.loadFromCSV(/*m_movingObj,*/ m_staticObj, m_player);

	m_timer = sf::seconds(120);
}


//---------------------------------
void GameScreen::handleSocreboard()
{
	/*m_scoreboard.updateTime(m_timer);
	m_scoreboard.updateLevel(m_level);
	m_scoreboard.updateLives(m_player.getLife());
	m_scoreboard.updateScore(m_player.getScore());*/
}

//------------------------
void GameScreen::removeGuard()
{
	/*if (Enemy::getNumOfGuardsAlive() != 0)
	{
		srand(time(NULL));
		int index = rand() % Enemy::getNumOfGuardsAlive();
		m_movingObj[index]->setLife(true);
	}*/
}

//------------------------
void GameScreen::addTime()
{
	/*m_timer += sf::seconds(ADDED_TIME);
	m_scoreboard.updateTime(m_timer);*/
}

//------------------------
void GameScreen::lostWindow()
{
	//// to do a Lost board
	//ResourcesManager::getInstance().getMusic("game").stop();
	//m_sound.setBuffer(ResourcesManager::getInstance().getSound("loss"));
	//m_sound.setVolume(100.f);
	//m_sound.play();

	//sf::Sprite lostWindow;
	//lostWindow.setTexture(ResourcesManager::getInstance().getTexture("game over"));
	//m_window.clear();
	//m_window.draw(lostWindow);
	//m_window.display();
	//sf::sleep(sf::seconds(2));
	//m_window.close();
}

//------------------------
void GameScreen::winWindow()
{
	//// to do a win board
	//ResourcesManager::getInstance().getMusic("game").stop();
	//m_sound.setBuffer(ResourcesManager::getInstance().getSound("win"));
	//m_sound.setVolume(100.f);
	//m_sound.play();

	//sf::Sprite winWindow;
	//winWindow.setTexture(ResourcesManager::getInstance().getTexture("win"));
	//m_window.clear();
	//m_window.draw(winWindow);
	//m_window.draw(m_scoreboard.getScore());
	//m_window.display();
	//sf::sleep(sf::seconds(3));
	//m_window.close();
}

//------------------------
void GameScreen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState)
{
	for (int index = 0; index < m_buttons.size(); ++index)
	{
		if (m_buttons[index].getBounds().contains(clickPos))
		{
			switch (index)
			{
			case PAUSE:
			{
				m_paused = true;
				break;
			}
			case RESUME:
			{
				m_paused = false;
				break;
			}
			case _HELP:
			{
				screenState = HELP_SCREEN;
				break;
			}
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------
sf::Vector2f GameScreen::clampViewPosition(const sf::FloatRect& bounds)
{
	sf::Vector2f center = m_view.getCenter();
	center.x = std::max(bounds.left + m_view.getSize().x / 2.f, std::min(center.x, bounds.left + bounds.width - m_view.getSize().x / 2.f));
	center.y = std::max(bounds.top + m_view.getSize().y / 2.f, std::min(center.y, bounds.top + bounds.height - m_view.getSize().y / 2.f));
	return center;
}