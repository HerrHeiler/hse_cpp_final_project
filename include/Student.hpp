#pragma once
#include <SFML/Graphics.hpp>
#include "RoomType.hpp"

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

    void ModifyStats(float dEnergy, float dKnowledge, float dMentalState);

    float GetMentalState() const { return mental_state; }
    float GetEnergy() const { return energy; }
    float GetKnowledge() const { return knowledge; }

    void UpdateEnvironment(RoomType type, float dt);

private:
    sf::Sprite sprite;
    float speed;

    float mental_state;
    float energy;
    float knowledge;
};