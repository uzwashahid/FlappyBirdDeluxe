#include "ScoreManager.h"
#include <fstream>

ScoreManager::ScoreManager(const std::string& saveFilePath) : filePath(saveFilePath) {
    score = 0;
    loadHighScore();
}

void ScoreManager::loadHighScore() {
    std::ifstream file(filePath);
    if (file.is_open()) {
        file >> highScore;
    }
    else {
        highScore = 0;
    }
}

void ScoreManager::addPoint() {
    score++;
}

void ScoreManager::reset() {
    score = 0;
}

int ScoreManager::getScore() const { return score; }
int ScoreManager::getHighScore() const { return highScore; }

void ScoreManager::saveHighScoreIfNeeded() {
    if (score > highScore) {
        highScore = score;
        std::ofstream file(filePath);
        file << highScore;
    }
}