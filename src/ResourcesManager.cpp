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

//------------------------------------------------------------------------------
const sf::Texture& ResourcesManager::getTexture(std::string name) const
{
	//std::cout << "Getting texture: " << name << std::endl;
    auto it = m_textures.find(name);
    if (it == m_textures.end())
    {
        std::cout << "Could not find texture: " << name << std::endl;
    }
	//std::cout << "Found texture: " << name << std::endl;
    return it->second;
}

//------------------------------------------------------------------------------
void ResourcesManager::loadTexture()
{
    std::vector<std::pair<std::string, std::string>> textures =
    {
        {"background","gamebackgroundGPT.png"},
        {"Player", "Player.png"},
        {"wall","wall.png"},
        {"startScreen", "startScreen.png"},
        {"start game", "start game.png"},
        {"exit", "exit.png"},
        {"help", "help.png"},
        {"pause", "pauseButton.png"},
        {"resume", "start game.png"},
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
        {"obstacle3","obstacle3.png"}
        /*{"guard", "Guard.png"},
        {"player", "Robot.png"},
        {"rock", "Rock.png"},
        {"empty", "empty.png"},
        {"menu", "menu.png"},
        {"backround", "helpBackground.png"},
        {"start game", "start game.png"},
        {"exit", "exit.png"},
        {"help", "help.png"},
        {"return", "return.png"},
        {"explation", "help screen.png"},
        {"bomb", "bomb.png"},
        {"freeze", "freeze.png"},
        {"explosion", "Explosion.png"},
        {"add time", "add_time.png"},
        {"add life", "m_medkit.png"},
        {"kill guard", "o_water.png"},
        {"game over", "lose_screen.png"},
        {"win", "win_screen.png"}*/
    };

    for (const auto& [name, filePath] : textures)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(filePath))
        {
            std::cout << "Failed to load texture " << filePath << std::endl;
        }
		texture.setSmooth(true); // Enable smooth scaling for the texture
        // Insert the texture into the unordered_map
        m_textures.emplace(name, std::move(texture));
    }
}

//------------------------------------------------------------------------------
void ResourcesManager::initializeMusic()
{
    //if (!m_menuMusic.openFromFile("menuMusic.ogg"))
    //{
    //    std::cerr << "Error loading menu music" << std::endl;
    //}
    //if (!m_gameMusic.openFromFile("Liquidzz.ogg"))
    //{
    //    std::cerr << "Error loading game music" << std::endl;
    //}
    //m_menuMusic.setLoop(true);
    //m_gameMusic.setLoop(true);
    //m_menuMusic.setVolume(50.f);
    //m_gameMusic.setVolume(50.f);


    //std::vector<std::pair<std::string, std::string>> music =
    //{
    //    {"hit", "hit.ogg"},
    //    {"door", "door_sound.ogg"},
    //    {"loss", "loss.ogg"},
    //    {"explosion", "explosion.ogg"},
    //    {"win", "win.ogg"}
    //};

    //for (const auto& [name, filePath] : music)
    //{
    //    sf::SoundBuffer sound;
    //    if (!sound.loadFromFile(filePath))
    //    {
    //        std::cout << "Failed to load texture " << filePath << std::endl;
    //    }

    //    // Insert the soundBuffer into the unordered_map
    //    m_music[name] = sound;
    //}
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
    auto it = m_music.find(name);
    if (it == m_music.end())
    {
        //std::cout << "Could not find sound: " << name << std::endl;
    }
    return it->second;
}