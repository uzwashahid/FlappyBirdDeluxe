#pragma once
#include <string>

class ScoreManager {
public:
    ScoreManager(const std::string& saveFilePath);

    void addPoint();
    void reset();
    int getScore() const;
    int getHighScore() const;
    void saveHighScoreIfNeeded();

private:
    int score;
    int highScore;
    std::string filePath;

    void loadHighScore();
};