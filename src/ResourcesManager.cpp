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
	//std::cout << "Getting texture: " << name << std::endl;
    auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        throw std::runtime_error(errorMessage);
    }
	//std::cout << "Found texture: " << name << std::endl;
    return it->second;
}

//------------------------------------------------------------------------------
void ResourcesManager::loadTexture()
{
    std::vector<std::pair<std::string, std::string>> textures =
    {
        {"background","gamebackground.png"},
        {"player_machine_gun", "player_machine_gun.png"},
        {"player_rifle", "player_rifle.png"},
        {"player_bazooka", "player_bazooka.png"},
        {"simple_enemy_machine_gun", "simple_enemy_machine_gun.png"},
        {"wall","wall.png"},
        {"startScreen", "startScreen.png"},
        {"start game", "start game.png"},
        {"exit", "exit.png"},
        {"help", "help.png"},
        {"help game screen", "help2.png"},
        {"pause", "pauseButton.png"},
        {"resume", "resume.png"},
        {"help screen", "help screen.png"},
        {"return", "return.png"},
        {"SimpleEnemy", "Enemy.png"},
        {"SmartEnemy", "Enemy.png"},
        {"BfsEnemy", "boss.png"},
        {"life", "life.png"},
        {"bulletIcon", "bulletIcon.png"},
        {"clock", "clock.png"},
        {"obstacle1","obstacle1.png"},
        {"obstacle2","obstacle2.png"},
        {"obstacle3","obstacle3.png"},
        {"game over", "lose_screen.png"},
        {"start menu", "home.png"}
        /*{"win", "win_screen.png"}*/
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
        {"shot", "shot.ogg"},
        {"death", "death.ogg"},
        {"explosion", "explosion.ogg"},
        {"health", "addHealth.ogg"}
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
    if (!m_font.loadFromFile("ARCADE_N.TTF"))
    {
        throw std::runtime_error("Failed to load font ARCADE_N.TTF (the font)");
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
    std::string errorMessage = "Could not find sound: " + name;
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
    std::ifstream file("help.txt");
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