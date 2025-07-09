//-----includes section-----
#include "ResourcesManager.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
ResourcesManager::ResourcesManager()
{
    loadTexture();
    initializeMusic();
    initializeFont();
    intializeHelpText();
}

//------------------------------------------------------------------------------
ResourcesManager::~ResourcesManager()
{}

//------------------------------------------------------------------------------
ResourcesManager& ResourcesManager::getInstance()
{
    static ResourcesManager inst;
    return inst;
}

//------------------------------------------------------------------------------
void ResourcesManager::show() const
{}

std::vector<sf::Text> ResourcesManager::getHelpText() const
{
    return m_helpText;
}

//------------------------------------------------------------------------------
const sf::Texture& ResourcesManager::getTexture(std::string name) const
{
	std::string errorMessage = "Could not find texture: " + name;
    auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        throw std::runtime_error(errorMessage);
    }
    return it->second;
}

//------------------------------------------------------------------------------
void ResourcesManager::loadTexture()
{
    std::vector<std::pair<std::string, std::string>> textures =
    {
        {GAME_BACKGROUND,"gamebackground.png"},
        {PLAYER_MACHINE_GUN, "player_machine_gun.png"},
        {PLAYER_RIFLE, "player_rifle.png"},
        {PLAYER_BAZOOKA, "player_bazooka.png"},
        {WALL_NAME,"wall.png"},
        {START_SCREEN_BACKGROUND, "startScreen.png"},
        {START_NEW_GAME_BUTTON, "start game.png"},
        {EXIT_BUTTON, "exit.png"},
        {HELP_MENU_BUTTON, "help.png"},
        {HELP_MENU_BUTTON_FOR_PAUSE, "help2.png"},
        {PAUSE_BUTTON, "pauseButton.png"},
        {RESUME_BUTTON, "resume.png"},
        {HELP_SCREEN_BACKGROUND, "help screen.png"},
        {RETURN_BUTTON, "return.png"},
        {SIMPLE_ENEMY_RIFLE, "simple_enemy_rifle.png"},
        {SMART_ENEMY_RIFLE, "smart_enemy_rifle.png"},
        {BFS_ENEMY_RIFLE, "bfs_enemy_rifle.png"},
        {LIFE_ICON, "life.png"},
        {BULLETS_ICON, "bulletIcon.png"},
        {CLOCK_ICON, "clock.png"},
        {OBSTACLE1_NAME,"obstacle1.png"},
        {OBSTACLE2_NAME,"obstacle2.png"},
        {OBSTACLE3_NAME,"obstacle3.png"},
        {LOSE_SCREEN_BACKGROUND, "lose_screen.png"},
        {START_MENU_BUTTON, "home.png"},
        {WIN_SCREEN_BACKGROUND, "win screen background.png"},
        {PROJECTILE_NAME, "Sprite_Effects_Exhaust_02_000.png"},
        {RIFLE_NAME, "rifle.png"},
        {MED_KIT_NAME, "medkit.png"},
        {BULLETS_NAME, "Bullet.png"},
        {REMOVE_TIME_NAME, "clock.png"},
        {REMOVE_ENEMY_NAME, "skull.png"},
        {BOMB_NAME, "bomb_animation.png"},
        {BOMBS_ICON, "bombIcon.png"},
        {EXPLOSION_NAME, "Explosion.png"},
        {ENEMIES_ICON, "enemiesIcon.png"},
        {MACHINE_GUN_NAME, "machine_gun.png"},
        {BAZOOKA_NAME, "Bazooka-sized.png"}
    };

    for (const auto& [name, filePath] : textures)
    {
		std::string errorMessage = "Failed to load texture: " + filePath;
        sf::Texture texture;
        if (!texture.loadFromFile(filePath))
        {
            throw std::runtime_error(errorMessage);
        }

		texture.setSmooth(true);
        m_textures.emplace(name, std::move(texture));
    }
}

//------------------------------------------------------------------------------
void ResourcesManager::initializeMusic()
{ 
    if (!m_menuMusic.openFromFile("menuMusic.ogg"))
    {
        throw std::runtime_error("Error loading menu music");
    }
    
    if (!m_gameMusic.openFromFile("gameMusic.ogg"))
    {
        throw std::runtime_error("Error loading game music");
    }
    
    m_menuMusic.setLoop(true);
    m_gameMusic.setLoop(true);
    m_menuMusic.setVolume(50.f);
    m_gameMusic.setVolume(50.f);


    std::vector<std::pair<std::string, std::string>> music =
    {
        {GAIN_PRESENT_SOUND, "present.ogg"},
        {SHOOTING_SOUND, "shoot.ogg"},
        {LOSING_SOUND, "death.ogg"},
        {GAIN_HEALTH_SOUND, "addHealth.ogg"},
        {WINNING_SOUND, "win.ogg"},
		{EXPLOSION_SOUND, "explosion.ogg"}
    };

    for (const auto& [name, filePath] : music)
    {
        std::string errorMessage = "Failed to load sound: " + filePath;
        sf::SoundBuffer sound;
        if (!sound.loadFromFile(filePath))
        {
            throw std::runtime_error(errorMessage);
        }

        // Insert the soundBuffer into the unordered_map
        m_music[name] = sound;
    }
}

//------------------------------------------------------------------------------
sf::Music& ResourcesManager::getMusic(std::string name)
{
    if (name == MENU_MUSIC)
    {
        return m_menuMusic;
    }
    else if (name == GAME_MUSIC)
    {
        return m_gameMusic;
    }

    return m_menuMusic;
}

//------------------------------------------------------------------------------
void ResourcesManager::initializeFont()
{
	std::string errorMessage = "Failed to load font: " + FONT_NAME;
    if (!m_font.loadFromFile(FONT_NAME))
    {
        throw std::runtime_error(errorMessage);
    }
}

//------------------------------------------------------------------------------
const sf::Font& ResourcesManager::getFont() const
{
    return m_font;
}

//------------------------------------------------------------------------------
sf::SoundBuffer& ResourcesManager::getSound(std::string name)
{
    std::string errorMessage = "Could not find the sound: " + name;
    auto it = m_music.find(name);
    if (it == m_music.end())
    {
        throw std::runtime_error(errorMessage);
    }
    return it->second;
}

//------------------------------------------------------------------------------
void ResourcesManager::intializeHelpText()
{
    std::ifstream file(HELP_FILE_NAME);
    if (!file) 
    {
        throw std::runtime_error("[ERROR] Cannot open help.txt");
        return;
    }

    std::string line;
    float yOffset = 100.f;
    while (std::getline(file, line)) 
    {
        sf::Text text(line, m_font, 20);
        text.setPosition(100.f, yOffset);
        text.setFillColor(sf::Color::White);
        m_helpText.push_back(text);
        yOffset += 28.f;
    }
}