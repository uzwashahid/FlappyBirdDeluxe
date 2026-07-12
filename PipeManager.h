#pragma once
#include "Pipe.h"
#include <string>

const int MAX_PIPES = 10;

class PipeManager {
public:
    PipeManager(const std::string& texturePath, float windowWidth, float windowHeight);

    void update(float deltaTime, float speed);
    void draw(sf::RenderWindow& window);
    void reset();

    Pipe pipes[MAX_PIPES];

private:
    std::string texturePath;
    float spawnTimer;
    float spawnInterval;
    float windowW, windowH;

    void spawnPipe();
};