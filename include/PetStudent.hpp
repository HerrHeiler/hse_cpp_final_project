#pragma once
#include "IStudent.hpp"
#include <SFML/Graphics.hpp>

class PetStudent : public IStudent {
public:
    explicit PetStudent(const sf::Texture& texture);

    void Update(float dt) override;
    void UpdateEnvironment(RoomType type, float dt) override;
    void HandleEvent(const sf::Event& event) override;

    void ModifyStats(float dEnergy, float dKnowledge, float dMentalState) override;
    void AddTime(float minutes) override;
    void ResetStats() override;

    void Render(sf::RenderTarget& target) override;
    void SetPosition(float x, float y) override;
    sf::Vector2f GetPosition() const override;
    sf::FloatRect GetBounds() const override;

    float GetEnergy() const override;
    float GetKnowledge() const override;
    float GetMentalState() const override;
    std::string GetTimeString() const override;

private:
    sf::Sprite m_sprite;
    float m_speed{120.f};

    float m_energy{80.f};
    float m_knowledge{0.f};
    float m_mental{80.f};
    float m_timeMinutes{8.f * 60.f};
};
