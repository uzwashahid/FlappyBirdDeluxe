#include "Game.h"

Game::Game()
    : window(sf::VideoMode({ 480, 720 }), "Flappy Bird Deluxe"),
    background("Assets/Textures/background.jpg", 480.f, 720.f),
    bird("Assets/Textures/bird.png", 240.f, 220.f),
    pipeManager("Assets/Textures/pipe.png", 480.f, 720.f),
    scoreManager("highscore.txt"),
    scoreText(font),
    bestText(font),
    titleText(font),
    titleText2(font),
    messageText(font),
    gameOverText(font),
    finalScoreText(font),
    flapSound(flapBuffer),
    hitSound(hitBuffer),
    scoreSound(scoreBuffer)
{
    state = GameState::MENU;
    pipeSpeed = 200.f;

    font.openFromFile("Assets/Fonts/font.ttf");

    // Score text
    scoreText.setCharacterSize(18);
    scoreText.setString("Score: 0");
    {
        sf::FloatRect s = scoreText.getLocalBounds();
        scoreText.setOrigin({ s.position.x, s.position.y });
        scoreText.setPosition({ 10.f, 10.f });
    }

    // Best score text
    bestText.setCharacterSize(18);
    bestText.setString("Best Score: 0");
    {
        sf::FloatRect b = bestText.getLocalBounds();
        bestText.setOrigin({ b.position.x + b.size.x, b.position.y });
        bestText.setPosition({ 470.f, 10.f });
    }

    // Title
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setString("Flappy Bird");
    centerText(titleText, 480.f, 110.f);

    titleText2.setCharacterSize(30);
    titleText2.setFillColor(sf::Color::White);
    titleText2.setStyle(sf::Text::Bold);
    titleText2.setString("Deluxe");
    centerText(titleText2, 480.f, 150.f);

    messageText.setCharacterSize(18);
    messageText.setFillColor(sf::Color::White);
    messageText.setString("Press SPACE to start");
    centerText(messageText, 480.f, 360.f);

    gameOverText.setCharacterSize(28);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!");
    centerText(gameOverText, 480.f, 320.f);

    
    finalScoreText.setCharacterSize(20);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString("Score: 0");
    centerText(finalScoreText, 480.f, 360.f);

    flapBuffer.loadFromFile("Assets/Sounds/flap.mp3");
    hitBuffer.loadFromFile("Assets/Sounds/hit.mp3");
    scoreBuffer.loadFromFile("Assets/Sounds/score.mp3");
}

void Game::centerText(sf::Text& text, float windowWidth, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ windowWidth / 2.f, y });
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        handleInput();
        update(deltaTime);
        render();
    }
}

void Game::handleInput() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                if (state == GameState::MENU) {
                    state = GameState::PLAYING;
                }
                else if (state == GameState::PLAYING) {
                    bird.flap();
                    flapSound.play();
                }
                else if (state == GameState::GAME_OVER) {
                    resetGame();
                    state = GameState::MENU;
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (state != GameState::PLAYING) return;

    bird.update(deltaTime);

    pipeSpeed = 200.f + scoreManager.getScore() * 5.f;
    pipeManager.update(deltaTime, pipeSpeed);

    checkCollisions();

    scoreText.setString("Score: " + std::to_string(scoreManager.getScore()));
    {
        sf::FloatRect s = scoreText.getLocalBounds();
        scoreText.setOrigin({ s.position.x, s.position.y });
        scoreText.setPosition({ 10.f, 10.f });
    }

    bestText.setString("Best Score: " + std::to_string(scoreManager.getHighScore()));
    {
        sf::FloatRect b = bestText.getLocalBounds();
        bestText.setOrigin({ b.position.x + b.size.x, b.position.y });
        bestText.setPosition({ 470.f, 10.f });
    }
}

void Game::checkCollisions() {
    sf::FloatRect birdBounds = bird.getBounds();

    if (birdBounds.position.y < 0.f || birdBounds.position.y > 720.f) {
        hitSound.play();
        scoreManager.saveHighScoreIfNeeded();
        state = GameState::GAME_OVER;

        finalScoreText.setString("Score: " + std::to_string(scoreManager.getScore()));
        centerText(finalScoreText, 480.f, 360.f);

        messageText.setString("Press SPACE to retry");
        centerText(messageText, 480.f, 400.f);
        return;
    }

    for (int i = 0; i < MAX_PIPES; i++) {
        if (!pipeManager.pipes[i].active) continue;

        Pipe& pipe = pipeManager.pipes[i];
        sf::FloatRect topBounds = pipe.getTopBounds();
        sf::FloatRect bottomBounds = pipe.getBottomBounds();

        bool hitTop = birdBounds.findIntersection(topBounds).has_value();
        bool hitBottom = birdBounds.findIntersection(bottomBounds).has_value();

        if (hitTop || hitBottom) {
            hitSound.play();
            scoreManager.saveHighScoreIfNeeded();
            state = GameState::GAME_OVER;

            finalScoreText.setString("Score: " + std::to_string(scoreManager.getScore()));
            centerText(finalScoreText, 480.f, 360.f);

            messageText.setString("Press SPACE to retry");
            centerText(messageText, 480.f, 400.f);
        }

        if (!pipe.scored && topBounds.position.x + topBounds.size.x < birdBounds.position.x) {
            pipe.scored = true;
            scoreManager.addPoint();
            scoreSound.play();
        }
    }
}

void Game::render() {
    window.clear(sf::Color(135, 206, 235));
    background.draw(window);
    bird.draw(window);
    pipeManager.draw(window);

    if (state == GameState::PLAYING) {
        window.draw(scoreText);
        window.draw(bestText);
    }
    else if (state == GameState::GAME_OVER) {
        window.draw(gameOverText);
        window.draw(finalScoreText);
        window.draw(messageText);
    }
    else { // MENU
        window.draw(titleText);
        window.draw(titleText2);
        window.draw(messageText);
    }

    window.display();
}

void Game::resetGame() {
    bird.reset(240.f, 220.f);
    pipeManager.reset();
    scoreManager.reset();

    scoreText.setString("Score: 0");
    {
        sf::FloatRect s = scoreText.getLocalBounds();
        scoreText.setOrigin({ s.position.x, s.position.y });
        scoreText.setPosition({ 10.f, 10.f });
    }

    bestText.setString("Best Score: " + std::to_string(scoreManager.getHighScore()));
    {
        sf::FloatRect b = bestText.getLocalBounds();
        bestText.setOrigin({ b.position.x + b.size.x, b.position.y });
        bestText.setPosition({ 470.f, 10.f });
    }

    messageText.setString("Press SPACE to start");
    centerText(messageText, 480.f, 360.f);
}
