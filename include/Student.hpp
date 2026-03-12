#pragma once
#include <SFML/Graphics.hpp>
#include "RoomType.hpp"
#include "IStudent.hpp"

class Student : public IStudent {
public:
    Student(const sf::Texture& texture);

    // = move
    void Update(float dt) override;

    // = draw
    void Render(sf::RenderTarget& target) override;

    // positioning
    void SetPosition(float x, float y) override;         
    sf::Vector2f GetPosition() const override;           
    sf::FloatRect GetBounds() const override;  

    void HandleEvent(const sf::Event& event) override;

    void ModifyStats(float dEnergy, float dKnowledge, float dMentalState) override;

    float GetMentalState() const override { return mental_state; }
    float GetEnergy() const override { return energy; }
    float GetKnowledge() const override { return knowledge; }

    void UpdateEnvironment(RoomType type, float dt) override;

    void AddTime(float minutes) override;
    std::string GetTimeString() const override;

    void ResetStats() override;

private:
    sf::Sprite sprite;
    float speed;

    float mental_state;
    float energy;
    float knowledge;

    float m_timeMinutes{570.f};
};