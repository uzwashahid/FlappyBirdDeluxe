#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Bird {
public:
    Bird(const std::string& texturePath, float startX, float startY);

    void flap();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void reset(float startX, float startY);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float gravity;
    float flapStrength;
    float rotation;
};