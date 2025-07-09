//-----include section-----
#include "MusicManager.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
MusicManager& MusicManager::getInstance()
{
    static MusicManager instance;
    return instance;
}

//-----------------------------------------------------------------------------
MusicManager::MusicManager()
    : m_currentMusicType(MusicType::GAME) // Start with different type to force first music to actually start
    , m_isMuted(false)
    , m_isPaused(false)
    , m_isInitialized(false)
    , m_masterVolume(100.0f)
{
    // Initialize music filenames mapping
    m_musicFiles[MusicType::MENU] = "menuMusic.ogg";
    m_musicFiles[MusicType::GAME] = "gameMusic.ogg";
    m_musicFiles[MusicType::WIN] = "winMusic.ogg";
    m_musicFiles[MusicType::LOSE] = "loseMusic.ogg";
    
    // Initialize default volumes for each music type
    m_musicVolumes[MusicType::MENU] = 50.0f;
    m_musicVolumes[MusicType::GAME] = 50.0f;
    m_musicVolumes[MusicType::WIN] = 60.0f;   // Slightly louder for celebration
    m_musicVolumes[MusicType::LOSE] = 40.0f;  // Quieter for somber mood
}

//-----------------------------------------------------------------------------
bool MusicManager::initialize()
{
    if (m_isInitialized) return true;
    
    if (loadMusicFiles())
    {
        m_isInitialized = true;
        return true;
    }
    
    std::cerr << "[MusicManager] Failed to initialize music system.\n";
    return false;
}

//-----------------------------------------------------------------------------
bool MusicManager::loadMusicFiles()
{
    bool allLoaded = true;
    
    for (const auto& [musicType, filename] : m_musicFiles)
    {
        auto music = std::make_unique<sf::Music>();
        std::string errorMessage = "[MusicManager] Failed to load: " + filename;
        if (!music->openFromFile(filename))
        {
            throw std::runtime_error(errorMessage);
        }

        // Configure music properties
        music->setLoop(true);
        music->setVolume(m_musicVolumes[musicType]);
        
        // Store music in our storage
        m_musicTracks[musicType] = std::move(music);
    }
    
    return allLoaded;
}

//-----------------------------------------------------------------------------
void MusicManager::setCurrentMusic(MusicType musicType, TransitionType transition)
{
    if (!m_isInitialized || m_isMuted) return;
    
    if (m_currentMusicType == musicType) return; // Already playing
    
    switch (transition)
    {
        case TransitionType::IMMEDIATE:
            stopAllMusic();
            startMusic(musicType);
            m_currentMusicType = musicType;
            break;
            
        case TransitionType::FADE_OUT:
            // Start fade out of current music
            m_fadeState.isActive = true;
            m_fadeState.targetMusic = musicType;
            m_fadeState.fadeOutVolume = getMusic(m_currentMusicType).getVolume();
            break;
            
        case TransitionType::CROSSFADE:
            // TODO: Implement crossfade if needed
            stopAllMusic();
            startMusic(musicType);
            m_currentMusicType = musicType;
            break;
    }
}

//-----------------------------------------------------------------------------
void MusicManager::pauseMusic()
{
    if (!m_isInitialized || m_isPaused) return;
    
    getMusic(m_currentMusicType).pause();
    m_isPaused = true;
}

//-----------------------------------------------------------------------------
void MusicManager::resumeMusic()
{
    if (!m_isInitialized || !m_isPaused || m_isMuted) return;
    
    getMusic(m_currentMusicType).play();
    m_isPaused = false;
}

//-----------------------------------------------------------------------------
void MusicManager::muteMusic()
{
    if (!m_isInitialized || m_isMuted) return;
    
    stopAllMusic();
    m_isMuted = true;
}

//-----------------------------------------------------------------------------
void MusicManager::unmuteMusic()
{
    if (!m_isInitialized || !m_isMuted) return;
    
    m_isMuted = false;
    if (!m_isPaused)
    {
        startMusic(m_currentMusicType);
    }
}

//-----------------------------------------------------------------------------
bool MusicManager::isMuted() const
{
    return m_isMuted;
}

//-----------------------------------------------------------------------------
MusicManager::MusicType MusicManager::getCurrentMusicType() const
{
    return m_currentMusicType;
}

//-----------------------------------------------------------------------------
void MusicManager::setMasterVolume(float volume)
{
    m_masterVolume = std::max(0.0f, std::min(100.0f, volume));
    
    // Update current playing music volume
    if (m_isInitialized && !m_isMuted)
    {
        float adjustedVolume = (m_musicVolumes[m_currentMusicType] * m_masterVolume) / 100.0f;
        getMusic(m_currentMusicType).setVolume(adjustedVolume);
    }
}

//-----------------------------------------------------------------------------
void MusicManager::setMusicTypeVolume(MusicType musicType, float volume)
{
    m_musicVolumes[musicType] = std::max(0.0f, std::min(100.0f, volume));
    
    // Update volume if this music is currently playing
    if (m_isInitialized && musicType == m_currentMusicType && !m_isMuted)
    {
        float adjustedVolume = (volume * m_masterVolume) / 100.0f;
        getMusic(musicType).setVolume(adjustedVolume);
    }
}

//-----------------------------------------------------------------------------
void MusicManager::update(float deltaTime)
{
    if (!m_isInitialized || !m_fadeState.isActive) return;
    
    // Handle fade out transition
    m_fadeState.fadeOutVolume -= m_fadeState.fadeSpeed * deltaTime;
    
    if (m_fadeState.fadeOutVolume <= 0.0f)
    {
        // Fade out complete, switch to new music
        stopAllMusic();
        startMusic(m_fadeState.targetMusic);
        m_currentMusicType = m_fadeState.targetMusic;
        m_fadeState.isActive = false;
    }
    else
    {
        // Update fading volume
        getMusic(m_currentMusicType).setVolume(m_fadeState.fadeOutVolume);
    }
}

//-----------------------------------------------------------------------------
void MusicManager::stopAllMusic()
{
    if (!m_isInitialized) return;
    
    for (auto& [musicType, music] : m_musicTracks)
    {
        if (music) music->stop();
    }
}

//-----------------------------------------------------------------------------
void MusicManager::startMusic(MusicType musicType)
{
    if (!m_isInitialized || m_isMuted) return;
    
    sf::Music& music = getMusic(musicType);
    float adjustedVolume = (m_musicVolumes[musicType] * m_masterVolume) / 100.0f;
    music.setVolume(adjustedVolume);
    music.play();
}

//-----------------------------------------------------------------------------
sf::Music& MusicManager::getMusic(MusicType musicType)
{
    return *m_musicTracks[musicType];
}

//-----------------------------------------------------------------------------
const std::string& MusicManager::getFileName(MusicType musicType)
{
    return m_musicFiles[musicType];
} 