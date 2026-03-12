#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "World.hpp"
#include "IStudent.hpp"
#include <memory>

class ResourceManager;
class Student;

class CorridorState : public State {
public:
    explicit CorridorState(StateManager& sm, ResourceManager& rm, IStudent& student);
    
    void HandleEvent(const sf::Event& event) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager;
    std::unique_ptr<World> m_world;
    sf::Text m_instruction;
};