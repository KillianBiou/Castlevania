#include "SoundManager.h"

SoundManager::SoundManager() {
	for (int i = 0; i < this->nbMaxMusic + 1; i++) {
		this->musicList.push_back(new sf::Music());
		this->musicList.at(i)->openFromFile("music/0" + std::to_string(i + 1) + ".ogg");
	}
	this->horrorMusic = new sf::Music();
	this->horrorMusic->openFromFile("music/HorrorMusic.ogg");
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
	if (this->fadeOut) {
		int timestamp = this->fadeOut->getElapsedTime().asMilliseconds();
		float scale = 100.f / this->fadeOutDuration;
		int volume = std::max(std::min((int)(timestamp * scale), 100), 0);
		this->currentMusic->setVolume(100 - volume);

		if (timestamp >= this->fadeOutDuration) {
			delete this->fadeOut;
			this->fadeOut = nullptr;
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

void SoundManager::playHorrorMusic() {
	if (this->currentMusic)
		this->currentMusic->stop();
	this->currentMusic = this->horrorMusic;
	this->currentMusic->setLoop(true);
	this->currentMusicId = -1;
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
	for (std::list<sf::Sound>::iterator i = this->sfxList.begin(); i != this->sfxList.end();) {
		if (i->getStatus() == sf::Sound::Stopped && i->getPlayingOffset().asMilliseconds() == 0) {
			i = this->sfxList.erase(i);
		}
		else {
			i++;
		}
	}
}

void SoundManager::progressiveFadeOut(int milliseconds) {
	this->fadeOut = new sf::Clock();
	this->fadeOutDuration = milliseconds;
}

void SoundManager::setCanPlay(bool canPlay) {
	this->canPlay = canPlay;
	if (!canPlay) {
		this->currentMusic->stop();
	}
}