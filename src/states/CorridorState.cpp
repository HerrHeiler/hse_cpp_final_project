#include "CorridorState.hpp"


CorridorState::CorridorState(StateManager& sm, ResourceManager& rm, IStudent& student) 
    : manager(sm)
    , m_world(std::make_unique<World>(rm, sm, student)) 
    , m_instruction(rm.GetFont("default"), "Press 'E' to interact with items", 16)
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
    m_world->HandleEvent(event);
}

void CorridorState::Update(float dt) {
    m_world->Update(dt);
}

void CorridorState::Render(sf::RenderWindow& window) {
    window.clear();
    m_world->Render(window);
    window.draw(m_instruction);
}