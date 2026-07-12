#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Pipe {
public:
    Pipe();
    void init(const std::string& texturePath, float x, float gapY, float gapSize);

    void update(float deltaTime, float speed);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;

    bool active;
    bool scored;

    sf::FloatRect getTopBounds() const;
    sf::FloatRect getBottomBounds() const;

private:
    static sf::Texture& getPlaceholderTexture();

    sf::Texture texture;
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
};