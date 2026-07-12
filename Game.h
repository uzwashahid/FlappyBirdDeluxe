#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bird.h"
#include "Background.h"
#include "PipeManager.h"
#include "ScoreManager.h"

enum class GameState { MENU, PLAYING, GAME_OVER };

class Game {
public:
    Game();
    void run();

private:
    void handleInput();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void resetGame();
    void centerText(sf::Text& text, float windowWidth, float y);

    sf::RenderWindow window;
    sf::Clock clock;
    GameState state;

    Background background;
    Bird bird;
    PipeManager pipeManager;
    ScoreManager scoreManager;

    sf::Font font;
    sf::Text bestText;
    sf::Text scoreText;
    sf::Text messageText;
    sf::Text gameOverText;
 sf::Text finalScoreText;
    sf::Text titleText;
    sf::Text titleText2;

    sf::SoundBuffer flapBuffer;
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer scoreBuffer;
    sf::Sound flapSound;
    sf::Sound hitSound;
    sf::Sound scoreSound;

    float pipeSpeed;
};
