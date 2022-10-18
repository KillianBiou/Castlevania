#include "SoundManager.h"

SoundManager::SoundManager() {
	for (int i = 0; i < this->nbMaxMusic + 1; i++) {
		this->musicList.push_back(new sf::Music());
		this->musicList.at(i)->openFromFile("music/0" + std::to_string(i + 1) + ".ogg");
	}
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
	this->sfxList.push_back(new sf::Sound());

	this->sfxList.at(this->sfxList.size() - 1)->setBuffer(*temp);
	this->sfxList.at(this->sfxList.size() - 1)->play();
}

void SoundManager::clearFinishedSfx() {
	for (int i = 0; i < this->sfxList.size(); i++) {
		if (sfxList.at(i)->getStatus() == sf::Sound::Stopped && sfxList.at(i)->getPlayingOffset().asMilliseconds() == 0) {
			this->sfxList.erase(std::remove(this->sfxList.begin(), this->sfxList.end(), sfxList.at(i)), this->sfxList.end());

		}
	}
}

void SoundManager::setCanPlay(bool canPlay) {
	this->canPlay = canPlay;
}