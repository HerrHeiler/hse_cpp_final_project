#pragma once
#include <SFML/Graphics.hpp>

class Student {
public:
    Student(const sf::Texture& texture);

    // = move
    void Update(sf::Time dt);

    // = draw
    void Render(sf::RenderWindow& window);

private:
    sf::Sprite m_sprite;
    float m_speed;
};