#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <list>

class SoundManager {
private:
	std::vector<sf::Music*> musicList;
	std::list<sf::Sound> sfxList;

	sf::Music* currentMusic;
	int currentMusicId;

	int nbMaxMusic = 4;

	bool canPlay = false;
	bool bossMusic = false;

	void clearFinishedSfx();

public:
	SoundManager();
	void update();
	
	void playMusic(int id);
	void playBossMusic(sf::Music* music);
	void endBossMusic(sf::Music* music);

	void playSoundEffect(sf::SoundBuffer* soundBuffer);

	void setCanPlay(bool canPlay);
};