#include "Bird.h"
#include<iostream>

Bird::Bird(const std::string& texturePath, float startX, float startY)
    : sprite(texture)
{
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    sprite.setTexture(texture, true);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 })); 


    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });
    sprite.setPosition({ startX, startY });
    sprite.setScale({ 2.f, 2.f }); 

    velocity = { 0.f, 0.f };
    gravity = 900.f;
    flapStrength = -350.f;
    rotation = 0.f;
}

void Bird::flap() {
    velocity.y = flapStrength;
}

void Bird::update(float deltaTime) {
    velocity.y += gravity * deltaTime;
    sprite.move({ 0.f, velocity.y * deltaTime });

    float newRotation = velocity.y / 10.f;
    if (newRotation < -30.f) newRotation = -30.f;
    if (newRotation > 90.f) newRotation = 90.f;
    rotation = newRotation;

    sprite.setRotation(sf::degrees(rotation));
}

void Bird::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

void Bird::reset(float startX, float startY) {
    sprite.setPosition({ startX, startY });
    velocity = { 0.f, 0.f };
    rotation = 0.f;
    sprite.setRotation(sf::degrees(0.f));
}