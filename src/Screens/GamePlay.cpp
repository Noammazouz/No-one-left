//-----include section-----
#include "GamePlay.h"


// Static variables for death handling
static bool s_deathSoundStarted = false;
static sf::Clock s_deathTimer;
static bool s_winSoundStarted = false;
static sf::Clock s_winTimer;

//-----functions section------
//-----------------------------------------------------------------------------
GamePlay::GamePlay()
	: worldBounds(0.f, 0.f, MAP_WIDTH, MAP_HEIGHT)
{
	initButtons();
	handleLoadingLevel();
	if (m_staticObj.empty()) 
	{
		std::cerr << STARIC_OBJECTS_WARNING;
	}
}

//-----------------------------------------------------------------------------
void GamePlay::run(sf::RenderWindow& window, int& m_currentScreen)
{
	if (m_newGame) resetGame();
	Screen::run(window, m_currentScreen);
	m_view.setCenter(m_player.getPosition());
	m_view.setCenter(clampViewPosition(worldBounds));
	window.setView(m_view);
}

//-----------------------------------------------------------------------------
void GamePlay::activate(sf::Clock& clock, int& m_currentScreen)
{
	if (m_paused) return;

	//Always ensure game music is playing when in gameplay
	if (getCurrentMusicState() != MusicState::GAME)
	{
		setMusicState(MusicState::GAME);
	}

	if (m_staticObj.empty()) 
	{
		std::cerr << STARIC_OBJECTS_WARNING;
	}

	//Handle game over states first (both stop normal game processing)
	if (m_player.getLife() <= END_GAME)
	{
		handleDeathState(m_currentScreen);
		return; //STOP all game processing when dead
	}

	if (Enemy::getNumOfEnemiesAlive() <= END_GAME)
	{
		handleWinState(m_currentScreen);
		return; //STOP all game processing when won
	}

	//Only process game logic if player is alive
	move(clock);
	handleCollision();
	handleErasing();
	handleScoreBoard();
}

//-----------------------------------------------------------------------------
void GamePlay::initButtons()
{
	sf::Vector2f pos(20.f, 20.f); // Fixed top-left with padding
	m_buttons.emplace_back(PAUSE_BUTTON, pos);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::vector<std::string> buttonNames = { RESUME_BUTTON, HELP_MENU_BUTTON_FOR_PAUSE };
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(desktop.width * WINDOW_RATIO / 2),
			static_cast<float>(desktop.height * WINDOW_RATIO / 5 + 300 * index));
		m_buttons.emplace_back(buttonNames[index], position);
	}
}

//-----------------------------------------------------------------------------
void GamePlay::draw(sf::RenderWindow& window)
{
	// Draw game world
	sf::Sprite backround;
	sf::Texture texure = ResourcesManager::getInstance().getTexture(GAME_BACKGROUND);
	texure.setRepeated(true);

	backround.setTexture(texure);
	backround.setTextureRect(sf::IntRect(0, 0, MAP_WIDTH, MAP_HEIGHT));
	window.draw(backround);

	for (auto& obj : m_staticObj) 
		obj->draw(window);
	for (auto& enemy : m_movingObj)
		enemy->draw(window);

	m_player.draw(window);

	
	window.setView(window.getDefaultView());

	m_infoBar.draw(window);

	if (m_paused) drawButtons(window); // Menu buttons
	else m_buttons[PAUSE].draw(window); // Only pause button
}

//-----------------------------------------------------------------------------
void GamePlay::move(sf::Clock& clock)
{
	const auto deltaTime = clock.restart();

	m_player.update(deltaTime, sf::Vector2f());
	m_player.handleShooting();

	for (const auto& movingObj : m_movingObj)
	{
	   movingObj->update(deltaTime, m_player.getPosition());
	}
	for (int index = 0; index < Enemy::getNumOfEnemiesAlive(); ++index)
	{
		if (auto* e = dynamic_cast<Enemy*>(m_movingObj[index].get()))
		{
			if (e->wantsToFire())
			{
				addProjectile(e->getPosition(), e->getShottingDirections(), ENEMY);
				e->clearFireFlag();
			}
		}
	}
	m_stopwatch += deltaTime;
}

//-----------------------------------------------------------------------------
void GamePlay::handleCollision()
{
	auto& collisionHandler = CollisionFactory::getInstance();
	
	// Player vs Static Objects (walls)
	for (const auto& staticObj : m_staticObj)
	{
		if (m_player.checkCollision(*staticObj))
		{
			collisionHandler.processCollision(m_player, *staticObj);
		}
	}

	// Moving Objects vs Static Objects (enemies vs walls)
	for (const auto& movingObj : m_movingObj)
	{
		bool collided = false;
		for (const auto& staticObj : m_staticObj)
		{
			if (movingObj->checkCollision(*staticObj))
			{
				collisionHandler.processCollision(*movingObj, *staticObj);
				collided = true;
				break;
			}
		}
		if (!collided) 
		{
			// Dynamic-cast to Enemy (or UpdateableObject) and call ClearAvoidance()
			if (auto* enemy = dynamic_cast<Enemy*>(movingObj.get()))
 {
				if (auto* enemy = dynamic_cast<Enemy*>(movingObj.get())) 
				{
					enemy->OnSuccessfulMove();
				}
			}
		}
	}


	// Player vs Enemies
	for (const auto& movingObj : m_movingObj)
	{

		if (m_player.checkCollision(*movingObj))
		{
			/*m_sound.setBuffer(ResourcesManager::getInstance().getSound("death"));
			m_sound.setVolume(100.f);
			m_sound.play();*/
			collisionHandler.processCollision(m_player, *movingObj);
			break;
		}
	}

	for (int moveObj = 0; moveObj < m_movingObj.size() - 1; ++moveObj)
	{
		for (int nextMoveObj = moveObj + 1; nextMoveObj < m_movingObj.size(); ++nextMoveObj)
		{
			auto& movingObject1 = *m_movingObj[moveObj];
			auto& movingObject2 = *m_movingObj[nextMoveObj];

			if (movingObject1.checkCollision(movingObject2))
			{
				collisionHandler.processCollision(movingObject1, movingObject2);
			}
		}
	}
}

//-----------------------------------------------------------------------------
void GamePlay::handleErasing()
{
	std::erase_if(m_movingObj, [](const auto& item)
		{return item->isDead(); });

	std::erase_if(m_staticObj, [](const auto& item)
		{return item->isDead(); });
}

//-----------------------------------------------------------------------------
void GamePlay::handleLoadingLevel()
{
	m_movingObj.clear();
	m_staticObj.clear();
	
	m_map.loadlevelobj(m_movingObj,m_staticObj, m_player, this);
	m_stopwatch = sf::seconds(0);
}

//-----------------------------------------------------------------------------
void GamePlay::handleScoreBoard()
{
	m_infoBar.updateTime(m_stopwatch);
	m_infoBar.updateNumOfBullets(m_player.getNumOfBullets());
	m_infoBar.updateLives(m_player.getLife());
	m_infoBar.updateNumOfEnemiesAlive();
}

//-----------------------------------------------------------------------------
void GamePlay::removeEnemy()
{
	if (Enemy::getNumOfEnemiesAlive() != 0)
	{
		srand(time(NULL));
		int index = rand() % Enemy::getNumOfEnemiesAlive();
		m_movingObj[index]->setLife(true);
	}
}

//-----------------------------------------------------------------------------
void GamePlay::resetGame()
{
	m_newGame = false;
	m_sound.stop();
	Enemy::resetNumOfEnemeis();
	handleLoadingLevel();
	resetGameOverStates();
}

//-----------------------------------------------------------------------------
void GamePlay::decTime()
{
	if (m_stopwatch <= sf::seconds(TIME_TO_REMOVE))
	{
		m_stopwatch = sf::seconds(0); 
		return;
	}
	m_stopwatch -= sf::seconds(TIME_TO_REMOVE);
	m_infoBar.updateTime(m_stopwatch);
}

//-----------------------------------------------------------------------------
void GamePlay::handleMouseClick(const sf::Vector2f& clickPos, int& screenState)
{
	if (!m_paused)
	{
		if (m_buttons[PAUSE].getBounds().contains(clickPos))
		{
			m_paused = true;
			setMusicState(MusicState::MENU); //Switch to menu music when pausing
			return;
		}
		return; //If not paused, ignore other clicks
	}
	for (int index = 1; index < m_buttons.size(); ++index)
	{
		if (m_buttons[index].getBounds().contains(clickPos))
		{
			switch (index)
			{
				case RESUME:
				{
					m_paused = false;
					setMusicState(MusicState::GAME); //Switch back to game music when resuming
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
sf::Vector2f GamePlay::clampViewPosition(const sf::FloatRect& bounds)
{
	sf::Vector2f center = m_view.getCenter();
	center.x = std::max(bounds.left + m_view.getSize().x / 2.f, std::min(center.x, bounds.left + bounds.width - m_view.getSize().x / 2.f));
	center.y = std::max(bounds.top + m_view.getSize().y / 2.f, std::min(center.y, bounds.top + bounds.height - m_view.getSize().y / 2.f));
	return center;
}

//---------------------------------------------------------------------------------------------------
void GamePlay::handleDeathState(int& m_currentScreen)
{
	if (!s_deathSoundStarted)
	{
		// Play death sound once and stop game music
		setMusicState(MusicState::MENU);
		m_sound.setBuffer(ResourcesManager::getInstance().getSound(LOSING_SOUND));
		m_sound.setVolume(100.f);
		m_sound.setPlayingOffset(sf::seconds(0.2f));
		m_sound.play();
		s_deathSoundStarted = true;
		s_deathTimer.restart();
	}
	else if (s_deathTimer.getElapsedTime().asSeconds() >= 0.8f || m_sound.getStatus() != sf::Sound::Playing)
	{
		// Go to lose screen after 0.8 seconds OR when sound finishes playing
		m_sound.stop();
		m_currentScreen = LOSE_SCREEN;
		m_newGame = true;
		s_deathSoundStarted = false; // Reset for next time
	}
}

//---------------------------------------------------------------------------------------------------
void GamePlay::handleWinState(int& m_currentScreen)
{
	if (!s_winSoundStarted)
	{
		// Play win sound once
		m_sound.setBuffer(ResourcesManager::getInstance().getSound(WINNING_SOUND));
		m_sound.setVolume(200.f);
		m_sound.play();
		s_winSoundStarted = true;
		s_winTimer.restart();
	}
	else if (s_winTimer.getElapsedTime().asSeconds() >= 1.0f || m_sound.getStatus() != sf::Sound::Playing)
	{
		// Go to win screen after 1 second OR when sound finishes playing
		m_sound.stop();
		m_currentScreen = WIN_SCREEN;
		m_newGame = true;
		s_winSoundStarted = false; // Reset for next time
	}
}

//-----------------------------------------------------------------------------
void GamePlay::resetGameOverStates()
{
	// Reset death sound state
	s_deathSoundStarted = false;
	s_deathTimer.restart();

	// Reset win sound state
	s_winSoundStarted = false;
	s_winTimer.restart();
}

//-----------------------------------------------------------------------------
void GamePlay::addProjectile(const sf::Vector2f& pos, std::vector<sf::Vector2f> directions, BulletOwner owner)
{
	m_sound.setBuffer(ResourcesManager::getInstance().getSound(SHOOTING_SOUND));
	m_sound.setVolume(100.f);
	m_sound.setPlayingOffset(sf::seconds(0.2f));
	m_sound.play();

	for (int index = 0; index < directions.size(); ++index)
	{
		m_movingObj.push_back(std::make_unique<Projectile>(pos, directions[index], owner));
	}
}

//----------------------------------------------------------------------------
void GamePlay::playPresentSound()
{
	m_sound.setBuffer(ResourcesManager::getInstance().getSound(GAIN_PRESENT_SOUND));
	m_sound.setVolume(100.f);
	m_sound.setPlayingOffset(sf::seconds(0.2f));
	m_sound.play();
}

void GamePlay::playMedkitSound()
{
	m_sound.setBuffer(ResourcesManager::getInstance().getSound(GAIN_HEALTH_SOUND));
	m_sound.setVolume(100.f);
	m_sound.setPlayingOffset(sf::seconds(0.2f));
	m_sound.play();
}
