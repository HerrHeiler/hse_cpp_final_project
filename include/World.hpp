#pragma once

#include <vector>
#include <optional>
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Student.hpp"
#include "ResourceManager.hpp"
#include "Door.hpp"
#include "StateManager.hpp"
#include "RoomType.hpp"


class World : public State {
public:
    World(ResourceManager& rm, StateManager& sm, IStudent& student);

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void HandleEvent(const sf::Event& event) override;

    RoomType GetCurrentRoom() const { return currentRoom; }

private:
    void LoadDoors();
    void CheckDoorCollision(const sf::FloatRect& studentBounds, bool ePressed);
    void InitUI();
    void UpdateUI();

    ResourceManager& resourceManager;
    StateManager& manager;
    IStudent& student;

    std::vector<Door> doors;
    sf::Sprite m_background;
    RoomType currentRoom;

    const sf::Font* m_uiFont{nullptr};
    std::optional<sf::Text> m_energyText;
    std::optional<sf::Text> m_knowledgeText;
    std::optional<sf::Text> m_mental_stateText;
    std::optional<sf::Text> m_timeText;
};
