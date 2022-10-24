#include "SoundManager.h"

SoundManager::SoundManager() {
	for (int i = 0; i < this->nbMaxMusic + 1; i++) {
		this->musicList.push_back(new sf::Music());
		this->musicList.at(i)->openFromFile("music/0" + std::to_string(i + 1) + ".ogg");
	}
	this->sfxList = {};
}

void SoundManager::update() {
	if (canPlay) {
		this->clearFinishedSfx();
		if (!this->bossMusic && this->currentMusic->getStatus() == 0) {
			int randomId = -1;
			do {
				randomId = rand() % this->nbMaxMusic;
			} while (randomId == this->currentMusicId);
			this->playMusic(randomId);
		}
	}
}

void SoundManager::playMusic(int id) {
	if (this->currentMusic)
		this->currentMusic->stop();
	this->currentMusic = this->musicList.at(id);
	this->currentMusicId = id;
	this->currentMusic->play();
}

void SoundManager::playBossMusic(sf::Music* music) {
	this->currentMusic->stop();
	music->play();
	music->setLoop(true);
	this->bossMusic = true;
}

void SoundManager::endBossMusic(sf::Music* music) {
	music->stop();
	music->setLoop(false);
	this->bossMusic = false;
	this->playMusic(4);
}

void SoundManager::playSoundEffect(sf::SoundBuffer* soundBuffer) {
	sf::SoundBuffer* temp = new sf::SoundBuffer(*soundBuffer);
	this->sfxList.push_back(sf::Sound());

	this->sfxList.back().setBuffer(*temp);
	this->sfxList.back().play();
}

void SoundManager::clearFinishedSfx() {
	std::cout << this->sfxList.size() << std::endl;
	for (std::list<sf::Sound>::iterator i = this->sfxList.begin(); i != this->sfxList.end();) {
		if (i->getStatus() == sf::Sound::Stopped && i->getPlayingOffset().asMilliseconds() == 0) {
			i = this->sfxList.erase(i);
		}
		else {
			i++;
		}
	}
}

void SoundManager::setCanPlay(bool canPlay) {
	this->canPlay = canPlay;
	if (!canPlay) {
		this->currentMusic->stop();
	}
}