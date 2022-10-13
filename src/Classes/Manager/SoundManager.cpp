#include "SoundManager.h"

SoundManager::SoundManager() {
	for (int i = 0; i < 4; i++) {
		this->musicList.push_back(new sf::Music());
		this->musicList.at(i)->openFromFile("music/0" + std::to_string(i + 1) + ".ogg");
	}
	this->playMusic(0);

	srand(time(NULL));

}

void SoundManager::update() {
	std::cout << this->sfxList.size() << std::endl;
	if (this->currentMusic->getStatus() == 0) {
		int randomId = -1;
		do {
			randomId = rand() % this->nbMaxMusic;
		} while (randomId == this->currentMusicId);
		this->playMusic(randomId);
	}

	this->clearFinishedSfx();
}

void SoundManager::playMusic(int id) {
	if(this->currentMusic)
		this->currentMusic->stop();
	this->currentMusic = this->musicList.at(id);
	this->currentMusicId = id;
	this->currentMusic->play();
}

void SoundManager::playSoundEffect(sf::SoundBuffer* soundBuffer) {
	this->sfxList.push_back(sf::Sound());

	this->sfxList.at(this->sfxList.size() - 1).setBuffer(*soundBuffer);
	this->sfxList.at(this->sfxList.size() - 1).play();
}

void SoundManager::clearFinishedSfx() {
	for (int i = 0; i < this->sfxList.size(); i++) {
		if (sfxList.at(i).getStatus() == sf::Sound::Stopped) {
			sfxList.erase(sfxList.begin() + i);
		}
	}
}