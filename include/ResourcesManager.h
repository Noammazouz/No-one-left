#pragma once

//-----include section-----
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <fstream>
#include "Const.h"

//-----class section-----
class ResourcesManager 
{
public:
	~ResourcesManager();

	static ResourcesManager& getInstance();

	const sf::Texture& getTexture(std::string name) const;
	sf::Music& getMusic(std::string name);
	const sf::Font& getFont() const;
	sf::SoundBuffer& getSound(std::string name);
	void show() const;
	std::vector<sf::Text> getHelpText() const;

private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	void loadTexture();
	void initializeMusic();
	void initializeFont();
	void intializeHelpText();

	sf::Music m_screenMusic;
	sf::Music m_gameMusic;
	sf::Music m_menuMusic;
	sf::Font m_font;
	std::vector<sf::Text> m_helpText;
	std::unordered_map<std::string, sf::SoundBuffer> m_music;
	std::unordered_map<std::string, sf::Texture> m_textures;
};
