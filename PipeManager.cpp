#include "PipeManager.h"
#include <cstdlib>

PipeManager::PipeManager(const std::string& path, float w, float h)
    : texturePath(path), windowW(w), windowH(h) {
    spawnTimer = 0.f;
    spawnInterval = 1.6f;
}

void PipeManager::spawnPipe() {
    for (int i = 0; i < MAX_PIPES; i++) {
        if (!pipes[i].active) {
            float gapY = 150 + std::rand() % (int)(windowH - 300);
            pipes[i].init(texturePath, windowW, gapY, 150.f);
            return;
        }
    }
}

void PipeManager::update(float deltaTime, float speed) {
    spawnTimer += deltaTime;
    if (spawnTimer >= spawnInterval) {
        spawnTimer = 0.f;
        spawnPipe();
    }

    for (int i = 0; i < MAX_PIPES; i++) {
        if (pipes[i].active) {
            pipes[i].update(deltaTime, speed);
            if (pipes[i].isOffScreen()) {
                pipes[i].active = false;
            }
        }
    }
}

void PipeManager::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MAX_PIPES; i++) {
        if (pipes[i].active) {
            pipes[i].draw(window);
        }
    }
}

void PipeManager::reset() {
    for (int i = 0; i < MAX_PIPES; i++) {
        pipes[i].active = false;
    }
    spawnTimer = 0.f;
}