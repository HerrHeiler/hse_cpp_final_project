#include "CorridorState.hpp"

CorridorState::CorridorState(StateManager& stateManager) 
    : manager(stateManager)
    , m_world(m_resources, manager) 
    , m_instruction(m_resources.GetFont("default"), "Press 'E' to interact with items", 16)
{
    sf::FloatRect bounds = m_instruction.getLocalBounds();
    m_instruction.setOrigin({bounds.position.x + bounds.size.x / 2.0f, 
                             bounds.position.y + bounds.size.y / 2.0f});
    
    m_instruction.setPosition({400.0f, 570.0f});
    m_instruction.setFillColor(sf::Color::White);
    m_instruction.setOutlineColor(sf::Color::Black); 
    m_instruction.setOutlineThickness(1.0f);
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
    window.draw(m_instruction);
}