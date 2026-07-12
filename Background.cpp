#include "Background.h"

Background::Background(const std::string& texturePath, float windowWidth, float windowHeight)
    : sprite(texture)
{
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture, true);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale({ windowWidth / bounds.size.x, windowHeight / bounds.size.y });
    sprite.setPosition({ 0.f, 0.f });
}

void Background::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}