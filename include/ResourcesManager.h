#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

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

private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	void loadTexture();
	void initializeMusic();
	void initializeFont();

	sf::Music m_menuMusic;
	sf::Music m_gameMusic;
	sf::Font m_font;
	std::unordered_map<std::string, sf::SoundBuffer> m_music;
	std::unordered_map<std::string, sf::Texture> m_textures;
};
