#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include "RoomType.hpp"

class IStudent {
public:
    virtual ~IStudent() = default;

    virtual void Update(float dt) = 0;
    virtual void UpdateEnvironment(RoomType type, float dt) = 0;
    virtual void HandleEvent(const sf::Event& event) = 0;

    virtual void ModifyStats(float dEnergy, float dKnowledge, float dMentalState) = 0;
    virtual void AddTime(float minutes) = 0;
    virtual void ResetStats() = 0;

    virtual void Render(sf::RenderTarget& target) = 0;
    virtual void SetPosition(float x, float y) = 0;
    virtual sf::Vector2f GetPosition() const = 0;
    virtual sf::FloatRect GetBounds() const = 0;

    virtual float GetEnergy() const = 0;
    virtual float GetKnowledge() const = 0;
    virtual float GetMentalState() const = 0;
    virtual std::string GetTimeString() const = 0;
};
