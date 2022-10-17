#include "MenuManager.h"

MenuManager::MenuManager(std::string a)  {
    this->cursorTexture.loadFromFile("images/Knife.png");
    this->backgroundTexture.loadFromFile("images/mainMenu.png");
    this->thunderTexture.loadFromFile("images/thunderEffect.png");
    this->font.loadFromFile("font/mainMenu.ttf");

    this->currentColor = sf::Color(255, 255, 255, 255);

    this->backgroundImage = sf::Sprite();
    backgroundImage.setTexture(backgroundTexture);
    this->cursorSprite = sf::Sprite();
    cursorSprite.setTexture(cursorTexture);

    this->thunderEffect = sf::Sprite();
    this->thunderEffect.setTexture(thunderTexture);
    this->thunderEffect.setColor(sf::Color(255, 255, 255, 0));

    this->playButton = sf::Text();
    this->playButton.setFont(this->font);
    this->playButton.setString("Start");
    this->playButton.setCharacterSize(100);
    this->playButton.setFillColor(sf::Color::White);
    this->playButton.setPosition(sf::Vector2f(400, 400));

    this->selectLevel = sf::Text();
    this->selectLevel.setFont(this->font);
    this->selectLevel.setString("Select a level");
    this->selectLevel.setCharacterSize(100);
    this->selectLevel.setFillColor(sf::Color::White);
    this->selectLevel.setPosition(sf::Vector2f(400, 550));

    this->exitButton = sf::Text();
    this->exitButton.setFont(this->font);
    this->exitButton.setString("Exit");
    this->exitButton.setCharacterSize(100);
    this->exitButton.setFillColor(sf::Color::White);
    this->exitButton.setPosition(sf::Vector2f(400, 700));

    this->cursorMap = {
        {0, sf::Vector2f(this->playButton.getPosition() + sf::Vector2f(50 + this->playButton.getGlobalBounds().width, this->playButton.getGlobalBounds().height / 2))},
        {1, sf::Vector2f(this->selectLevel.getPosition() + sf::Vector2f(50 + this->selectLevel.getGlobalBounds().width, this->selectLevel.getGlobalBounds().height / 2))},
        {2, sf::Vector2f(this->exitButton.getPosition() + sf::Vector2f(50 + this->exitButton.getGlobalBounds().width, this->exitButton.getGlobalBounds().height / 2))}
    };

    this->music.openFromFile("music/mainMenu.ogg");
    this->music.play();
    this->music.setLoop(true);
    
    this->thunderBuffer.loadFromFile("sfx/Thunder.ogg");
    this->thunder.setBuffer(thunderBuffer);
}

bool MenuManager::update(sf::RenderTarget* renderTarget) {
    if (this->fadeOutClock) {
        int timestamp = this->fadeOutClock->getElapsedTime().asMilliseconds();
        if (timestamp > 1000 && !stopFadeOut) {
            this->thunderEffect.setColor(sf::Color(255, 255, 255, 0));
            int currentTime = (1000 - timestamp) / 4;
            if (currentTime > 255)
                currentTime = 255;
            this->currentColor.a = currentTime;
            if (this->currentColor.a <= 10) {
                this->stopFadeOut = true;
                this->currentColor.a = 0;
            }            
        }
        else if (timestamp < 1000) {
            int currentTime = timestamp / 4;
            if (currentTime > 255)
                currentTime = 255;
            this->thunderEffect.setColor(sf::Color(255, 255, 255, 255 - currentTime));
        }
    }
    this->cursorSprite.setPosition(this->cursorMap[this->currentPosision]);
    this->draw(renderTarget);

    if (stopFadeOut) {
        return false;
    }
    return true;
}

void MenuManager::processSelection(sf::RenderTarget* target) {
    switch (this->currentPosision) {
    case 0:
        this->fadeOutClock = new sf::Clock();
        this->thunder.play();
        this->blockInput = true;
        break;
    case 1:
        break;
    case 2:
        ((sf::RenderWindow*)target)->close();
        break;
    }
}

void MenuManager::draw(sf::RenderTarget* renderTarget) {
    backgroundImage.setColor(this->currentColor);
    renderTarget->draw(this->backgroundImage);

    playButton.setFillColor(this->currentColor);
    renderTarget->draw(this->playButton);

    selectLevel.setFillColor(this->currentColor);
    renderTarget->draw(this->selectLevel);

    exitButton.setFillColor(this->currentColor);
    renderTarget->draw(this->exitButton);

    cursorSprite.setColor(this->currentColor);
    renderTarget->draw(this->cursorSprite);

    renderTarget->draw(this->thunderEffect);
}

const void MenuManager::processInput(sf::Event event, sf::RenderTarget* target) {
    switch (event.type) {
    case sf::Event::Closed:
        ((sf::RenderWindow*)target)->close();
        break;
    case sf::Event::KeyPressed:
        switch (event.key.code) {
        case sf::Keyboard::Up:
            if(!blockInput)
                this->currentPosision -= this->currentPosision == 0 ? 0 : 1;
            break;
        case sf::Keyboard::Down:
            if (!blockInput)
                this->currentPosision += this->currentPosision == this->maxPosition ? 0 : 1;
            break;
        case sf::Keyboard::Enter:
            if (!blockInput)
                this->processSelection(target);
            break;
        }
    }
}