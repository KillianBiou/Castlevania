#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <list>

// A class that manage all the sound/music in the game state (Not menu)
class SoundManager {
private:
	// All the playable music
	std::vector<sf::Music*> musicList;
	// All the sfx being played
	std::list<sf::Sound> sfxList;
	
	// Music for easter eggs
	sf::Music* horrorMusic;

	// Pointer toward the current music played
	sf::Music* currentMusic;

	sf::Clock* fadeOut;
	int fadeOutDuration;

	int currentMusicId;

	int nbMaxMusic = 4;

	bool canPlay = false;
	bool bossMusic = false;

	void clearFinishedSfx();

public:
	SoundManager();

	// Update loop
	void update();
	// Fonction to stop the music with a specified time fadeout
	void progressiveFadeOut(int milliseconds);
	
	// Play the music with the given ID
	void playMusic(int id);
	// Play the easter egg music
	void playHorrorMusic();
	// Play the given music and cut the current one
	void playBossMusic(sf::Music* music);
	// Cut boss music and play a regular one
	void endBossMusic(sf::Music* music);

	// Play a given sfx
	void playSoundEffect(sf::SoundBuffer* soundBuffer);

	// Make the manager stop playing music
	void setCanPlay(bool canPlay);
};