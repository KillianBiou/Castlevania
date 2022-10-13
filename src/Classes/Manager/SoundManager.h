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

	int nbMaxMusic = 4;

	void clearFinishedSfx();

public:
	SoundManager();
	void update();

	void playMusic(int id);
	void playSoundEffect(sf::SoundBuffer* soundBuffer);
};