#pragma once
#include <SFML/Graphics.hpp>

class Student {
public:
    Student(const sf::Texture& texture);

    // = move
    void Update(float dt);

    // = draw
    void Render(sf::RenderTarget& target);

    // positioning
    void SetPosition(float x, float y);         
    sf::Vector2f GetPosition() const;           
    sf::FloatRect GetBounds() const;  

    void HandleEvent(const sf::Event& event);

private:
    sf::Sprite m_sprite;
    float m_speed;
};