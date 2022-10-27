#include "SoundManager.h"

SoundManager::SoundManager() {
	// Load regular music named "01-05".ogg
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
		// Clear sfx that are stopped (Reached end of audio file)
		this->clearFinishedSfx();
		// If the current music has ended, play another regular music that is not the current one
		if (!this->bossMusic && this->currentMusic->getStatus() == 0) {
			int randomId = -1;
			do {
				randomId = rand() % this->nbMaxMusic;
			} while (randomId == this->currentMusicId);
			this->playMusic(randomId);
		}
	}
	// If a fade out order has been given, proceed
	if (this->fadeOut) {
		int timestamp = this->fadeOut->getElapsedTime().asMilliseconds();
		// Make a scale 
		float scale = 100.f / this->fadeOutDuration;
		// Clamp the volume to the range 0-100
		int volume = std::max(std::min((int)(timestamp * scale), 100), 0);
		this->currentMusic->setVolume(100 - volume);
		// If fadeout ended, delete the clock to break out of the fade out order
		if (timestamp >= this->fadeOutDuration) {
			delete this->fadeOut;
			this->fadeOut = nullptr;
		}
	}
}

void SoundManager::playMusic(int id) {
	// Stop the current music
	if (this->currentMusic)
		this->currentMusic->stop();
	// Play the targeted music and update current music
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
	// Stop current music
	this->currentMusic->stop();
	this->currentMusic = music;
	// Play boss music and loop it
	music->play();
	music->setLoop(true);
	this->bossMusic = true;
}

void SoundManager::endBossMusic(sf::Music* music) {
	// Stop boss music
	music->stop();
	music->setLoop(false);
	this->bossMusic = false;
	// Play regular music
	this->playMusic(4);
}

void SoundManager::playSoundEffect(sf::SoundBuffer* soundBuffer) {
	// Copy the sound buffer (Necessary to prevent a OpenAl bug)
	sf::SoundBuffer* temp = new sf::SoundBuffer(*soundBuffer);

	// Create a new sound and play it
	this->sfxList.push_back(sf::Sound());
	this->sfxList.back().setBuffer(*temp);
	this->sfxList.back().play();
}

void SoundManager::clearFinishedSfx() {
	// Clear all sound that are ended
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