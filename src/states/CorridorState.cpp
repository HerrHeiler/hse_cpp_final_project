#include "CorridorState.hpp"

CorridorState::CorridorState(StateManager& stateManager) 
    : manager(stateManager)
    , m_resources()
    , m_world(m_resources, manager) 
{
}

void CorridorState::HandleEvent(const sf::Event& event) {
    m_world.HandleEvent(event);
}

void CorridorState::Update(sf::Time dt) {
    m_world.Update(dt.asSeconds());
}

void CorridorState::Render(sf::RenderWindow& window) {
    window.clear();
    m_world.Render(window);
}