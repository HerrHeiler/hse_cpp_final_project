#include "CorridorState.hpp"

CorridorState::CorridorState(StateManager& stateManager) 
    : manager(stateManager)
    , m_world(m_resources) 
{
}

void CorridorState::HandleEvent(const sf::Event& event) {
    // todo
}

void CorridorState::Update(sf::Time dt) {
    m_world.Update(dt);
}

void CorridorState::Render(sf::RenderWindow& window) {
    window.clear();
    m_world.Render(window);
}