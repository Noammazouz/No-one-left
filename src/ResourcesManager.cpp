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
        {"wall","wall.png"},
        {"startScreen", "startScreen.png"},
        {START_NEW_GAME_BUTTON, "start game.png"},
        {EXIT_BUTTON, "exit.png"},
        {"help", "help.png"},
        {HELP_MENU_BUTTON_FOR_PAUSE, "help2.png"},
        {"pause", "pauseButton.png"},
        {"resume", "resume.png"},
        {"help screen", "help screen.png"},
        {"return", "return.png"},
        {SIMPLE_ENEMY_RIFLE, "simple_enemy_rifle.png"},
        {"smart_enemy_rifle", "smart_enemy_rifle.png"},
        {"bfs_enemy_rifle", "bfs_enemy_rifle.png"},
        {"life", "life.png"},
        {"bulletIcon", "bulletIcon.png"},
        {"clock", "clock.png"},
        {"obstacle1","obstacle1.png"},
        {"obstacle2","obstacle2.png"},
        {"obstacle3","obstacle3.png"},
        {"game over", "lose_screen.png"},
        {START_MENU_BUTTON, "home.png"},
        {"winning screen", "win screen background.png"},
        {"projectile", "Sprite_Effects_Exhaust_02_000.png"},
        {"rifle", "rifle.png"},
        {"medkit", "medkit.png"},
        {"Bullet", "Bullet.png"},
        {REMOVE_TIME_NAME, "clock.png"},
        {REMOVE_ENEMY_NAME, "skull.png"},
        {"bomb", "bomb.png"},
        {BOMBS_ICON, "bombIcon.png"},
        {"explosion", "Explosion.png"},
        {"enemeis icon", "enemiesIcon.png"},
        {"machine gun", "machine_gun.png"},
        {"bazooka", "Bazooka-sized.png"}
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
        {"present", "present.ogg"},
        {"shoot", "shoot.ogg"},
        {"death", "death.ogg"},
        {"health", "addHealth.ogg"},
        {"win sound effect", "win.ogg"}
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
    if (name == "menu")
    {
        return m_menuMusic;
    }
    else if (name == "game")
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