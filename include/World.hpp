#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Student.hpp"
#include "ResourceManager.hpp"
#include "Door.hpp"
#include "StateManager.hpp"


class World {
public:
    World(ResourceManager& rm, StateManager& sm);

    void Update(float deltaTime);
    void Render(sf::RenderTarget& target);
    void HandleEvent(const sf::Event& event);

    RoomType GetCurrentRoom() const { return currentRoom; }

private:
    void LoadDoors();
    void CheckDoorCollision(const sf::FloatRect& studentBounds, bool ePressed);

    ResourceManager& resourceManager;
    StateManager& manager;

    std::vector<Door> doors;
    Student student;
    sf::Sprite m_background;
    RoomType currentRoom;
};
