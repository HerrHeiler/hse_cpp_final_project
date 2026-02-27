#pragma once
#include <SFML/Graphics.hpp>

class Student {
public:
    Student(const sf::Texture& texture);

    // = move
    void Update(sf::Time dt);

    // = draw
    void Render(sf::RenderWindow& window);

    // positioning
    void SetPosition(float x, float y);         
    sf::Vector2f GetPosition() const;           
    sf::FloatRect GetBounds() const;  

private:
    sf::Sprite m_sprite;
    float m_speed;
};