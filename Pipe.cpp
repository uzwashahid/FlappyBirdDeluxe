#include "Pipe.h"

sf::Texture& Pipe::getPlaceholderTexture() {
    static sf::Texture placeholder;
    return placeholder;
}

Pipe::Pipe()
    : topPipe(getPlaceholderTexture()), bottomPipe(getPlaceholderTexture())
{
    active = false;
    scored = false;
}

void Pipe::init(const std::string& texturePath, float x, float gapY, float gapSize) {
    texture.loadFromFile(texturePath);

    bottomPipe.setTexture(texture, true);
    bottomPipe.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 48 })); 
    bottomPipe.setPosition({ x, gapY + gapSize / 2.f });

    topPipe.setTexture(texture, true);
    topPipe.setTextureRect(sf::IntRect({ 0, 0 }, { 32, 48 })); 
    topPipe.setScale({ 1.f, -1.f });
    topPipe.setPosition({ x, gapY - gapSize / 2.f });

    active = true;
    scored = false;
}

void Pipe::update(float deltaTime, float speed) {
    topPipe.move({ -speed * deltaTime, 0.f });
    bottomPipe.move({ -speed * deltaTime, 0.f });
}

void Pipe::draw(sf::RenderWindow& window) {
    window.draw(topPipe);
    window.draw(bottomPipe);
}

bool Pipe::isOffScreen() const {
    sf::FloatRect bounds = topPipe.getGlobalBounds();
    return bounds.position.x + bounds.size.x < 0.f;
}

sf::FloatRect Pipe::getTopBounds() const { return topPipe.getGlobalBounds(); }
sf::FloatRect Pipe::getBottomBounds() const { return bottomPipe.getGlobalBounds(); }