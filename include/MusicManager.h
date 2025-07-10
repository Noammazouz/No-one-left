#pragma once

//-----include section-----
#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Audio.hpp>

//-----class section-----
class MusicManager
{
public:
    enum class MusicType
    {
        MENU,
        GAME,
        WIN,
        LOSE
    };

    enum class TransitionType
    {
        IMMEDIATE,      //Stop current, start new immediately
        FADE_OUT,       //Fade out current, then start new
        CROSSFADE       //Fade out current while fading in new
    };

    //Singleton pattern
    static MusicManager& getInstance();
    
    //Initialization - call once at startup
    bool initialize();
    
    //Core functionality
    void setCurrentMusic(MusicType musicType, TransitionType transition = TransitionType::IMMEDIATE);
    void pauseMusic();
    void resumeMusic();
    void muteMusic();
    void unmuteMusic();
    bool isMuted() const;
    MusicType getCurrentMusicType() const;
    
    //Volume control
    void setMasterVolume(float volume);
    void setMusicTypeVolume(MusicType musicType, float volume);
    
    //Update method for fade transitions (call in game loop)
    void update(float deltaTime);

private:
    MusicManager();
    ~MusicManager() = default;
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;
    
    bool loadMusicFiles();
    void stopAllMusic();
    void startMusic(MusicType musicType);
    sf::Music& getMusic(MusicType musicType);
    const std::string& getFileName(MusicType musicType);
    
    //Music objects - now owned by MusicManager
    std::unordered_map<MusicType, std::unique_ptr<sf::Music>> m_musicTracks;
    
    //Music state
    MusicType m_currentMusicType;
    bool m_isMuted;
    bool m_isPaused;
    bool m_isInitialized;
    float m_masterVolume;
    
    //Volume settings for each music type
    std::unordered_map<MusicType, float> m_musicVolumes;
    
    //Music type to filename mapping
    std::unordered_map<MusicType, std::string> m_musicFiles;
    
    //Fade transition state
    struct FadeState
    {
        bool isActive = false;
        MusicType targetMusic = MusicType::MENU;
        float fadeOutVolume = 100.0f;
        float fadeSpeed = 200.0f; // Volume units per second
    } m_fadeState;
}; 