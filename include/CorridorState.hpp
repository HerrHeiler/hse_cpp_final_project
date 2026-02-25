#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp" 
#include "Student.hpp"         

class CorridorState : public State {
public:
    CorridorState(StateManager& stateManager);
    
    void HandleEvent(const sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager;
    ResourceManager m_resources; 
    Student m_student;          
};