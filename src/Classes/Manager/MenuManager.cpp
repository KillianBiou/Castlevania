#include "MenuManager.h"
#include "GameMaster.h"
#include "GameManager.h"

MenuManager::MenuManager(GameMaster* gameMaster): gameMaster(gameMaster) {
    this->cursorTexture.loadFromFile("images/Knife.png");
    this->backgroundTexture.loadFromFile("images/mainMenu.png");
    this->lvl1Texture.loadFromFile("images/level1Menu.png");
    this->lvl2Texture.loadFromFile("images/level2Menu.png");
    this->thunderTexture.loadFromFile("images/thunderEffect.png");
    this->font.loadFromFile("font/mainMenu.ttf");

    this->currentColor = sf::Color(255, 255, 255, 255);

    this->backgroundImage = sf::Sprite();
    backgroundImage.setTexture(backgroundTexture);
    this->cursorSprite = sf::Sprite();
    cursorSprite.setTexture(cursorTexture);

    this->lvl1Image = sf::Sprite();
    this->lvl1Image.setTexture(this->lvl1Texture);
    this->lvl1Image.setPosition(400, 450);

    this->lvl2Image = sf::Sprite();
    this->lvl2Image.setTexture(this->lvl2Texture);
    this->lvl2Image.setPosition(1000, 450);

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

    this->backButton = sf::Text();
    this->backButton.setFont(this->font);
    this->backButton.setString("Back");
    this->backButton.setCharacterSize(100);
    this->backButton.setFillColor(sf::Color::White);
    this->backButton.setPosition(sf::Vector2f(850, 800));

    this->lvl1Description = sf::Text();
    this->lvl1Description.setFont(this->font);
    this->lvl1Description.setString("Entrance");
    this->lvl1Description.setCharacterSize(75);
    this->lvl1Description.setFillColor(sf::Color::White);
    this->lvl1Description.setPosition(sf::Vector2f(this->lvl1Image.getPosition() + sf::Vector2f(125, 190)));

    this->lvl2Description = sf::Text();
    this->lvl2Description.setFont(this->font);
    this->lvl2Description.setString("Clock Tower");
    this->lvl2Description.setCharacterSize(75);
    this->lvl2Description.setFillColor(sf::Color::White);
    this->lvl2Description.setPosition(sf::Vector2f(this->lvl2Image.getPosition() + sf::Vector2f(100.f, 190)));

    this->cursorMap = {
        {0, sf::Vector2f(this->playButton.getPosition() + sf::Vector2f(50 + this->playButton.getGlobalBounds().width, this->playButton.getGlobalBounds().height / 2))},
        {1, sf::Vector2f(this->selectLevel.getPosition() + sf::Vector2f(50 + this->selectLevel.getGlobalBounds().width, this->selectLevel.getGlobalBounds().height / 2))},
        {2, sf::Vector2f(this->exitButton.getPosition() + sf::Vector2f(50 + this->exitButton.getGlobalBounds().width, this->exitButton.getGlobalBounds().height / 2))}
    };

    this->cursorMapLevelS = {
        {0, sf::Vector2f(this->lvl1Image.getPosition() + sf::Vector2f(50 + this->lvl1Image.getGlobalBounds().width, this->lvl1Image.getGlobalBounds().height / 2))},
        {1, sf::Vector2f(this->lvl2Image.getPosition() + sf::Vector2f(50 + this->lvl2Image.getGlobalBounds().width, this->lvl2Image.getGlobalBounds().height / 2))},
        {2, sf::Vector2f(this->backButton.getPosition() + sf::Vector2f(50 + this->backButton.getGlobalBounds().width, this->backButton.getGlobalBounds().height / 2))}
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
        else if (timestamp >= 3000) {
            this->exit();
        }
    }
    if (this->levelSelection) {
        this->cursorSprite.setPosition(this->cursorMapLevelS[this->currentPosition]);
    }
    else {
        this->cursorSprite.setPosition(this->cursorMap[this->currentPosition]);
    }
    this->draw(renderTarget);

    if (stopFadeOut) {
        return false;
    }
    return true;
}

void MenuManager::processSelection(sf::RenderTarget* target) {
    if (!this->levelSelection) {
        switch (this->currentPosition) {
        case 0:
            this->fadeOutClock = new sf::Clock();
            this->thunder.play();
            this->blockInput = true;
            this->exitCode = LEVEL1;
            break;
        case 1:
            this->currentPosition = 0;
            this->levelSelection = true;
            break;
        case 2:
            ((sf::RenderWindow*)target)->close();
            break;
        }
    }
    else {
        switch (this->currentPosition) {
        case 0:
            this->fadeOutClock = new sf::Clock();
            this->thunder.play();
            this->blockInput = true;
            this->exitCode = LEVEL1;
            break;
        case 1:
            this->fadeOutClock = new sf::Clock();
            this->thunder.play();
            this->blockInput = true;
            this->exitCode = LEVEL2;
            break;
        case 2:
            this->currentPosition = 0;
            this->levelSelection = false;
            break;
        }
    }
}

void MenuManager::exit() {
    this->gameMaster->changeState(GAME);
    this->music.stop();
    this->gameMaster->loadLvl(this->exitCode);
}

void MenuManager::draw(sf::RenderTarget* renderTarget) {
    backgroundImage.setColor(this->currentColor);
    renderTarget->draw(this->backgroundImage);

    if (!this->levelSelection) {
        playButton.setFillColor(this->currentColor);
        renderTarget->draw(this->playButton);

        selectLevel.setFillColor(this->currentColor);
        renderTarget->draw(this->selectLevel);

        exitButton.setFillColor(this->currentColor);
        renderTarget->draw(this->exitButton);
    }
    else {
        lvl1Image.setColor(this->currentColor);
        renderTarget->draw(this->lvl1Image);

        lvl2Image.setColor(this->currentColor);
        renderTarget->draw(this->lvl2Image);

        lvl1Description.setFillColor(sf::Color(190, 190, 190, this->currentColor.a));
        renderTarget->draw(this->lvl1Description);

        lvl2Description.setFillColor(sf::Color(190, 190, 190, this->currentColor.a));
        renderTarget->draw(this->lvl2Description);

        backButton.setFillColor(this->currentColor);
        renderTarget->draw(this->backButton);

        backButton.setFillColor(this->currentColor);
        renderTarget->draw(this->backButton);
    }

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
                this->currentPosition -= this->currentPosition == 0 ? 0 : 1;
            break;
        case sf::Keyboard::Down:
            if (!blockInput)
                this->currentPosition += this->currentPosition == this->maxPosition ? 0 : 1;
            break;
        case sf::Keyboard::Enter:
            if (!blockInput)
                this->processSelection(target);
            break;
        }
    }
}