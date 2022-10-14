#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <time.h>

class SoundManager {
private:
	std::vector<sf::Music*> musicList;
	std::vector<sf::Sound> sfxList;

	sf::Music* currentMusic;
	int currentMusicId;

	int nbMaxMusic = 5;

	bool bossMusic = false;

	void clearFinishedSfx();
	void playMusic(int id);

public:
	SoundManager();
	void update();

	void playBossMusic(sf::Music* music);
	void endBossMusic(sf::Music* music);

	void playSoundEffect(sf::SoundBuffer* soundBuffer);
};