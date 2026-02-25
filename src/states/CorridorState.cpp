#include "CorridorState.hpp"

CorridorState::CorridorState(StateManager& stateManager)
    : manager(stateManager)
    , m_student(m_resources.GetTexture("student"))
{
}

void CorridorState::HandleEvent(const sf::Event& event) {
    // todo
}

void CorridorState::Update(sf::Time dt) {
    m_student.Update(dt);
}

void CorridorState::Render(sf::RenderWindow& window) {
    window.clear(sf::Color(100, 100, 100)); 
    m_student.Render(window);
}