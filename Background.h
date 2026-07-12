#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Background {
public:
    Background(const std::string& texturePath, float windowWidth, float windowHeight);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};