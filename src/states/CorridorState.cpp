#include "CorridorState.hpp"

CorridorState::CorridorState(StateManager& stateManager) : manager(stateManager) {}

void CorridorState::HandleEvent(const sf::Event& event) {
    // todo
}

void CorridorState::Update(sf::Time dt) {
    //todo
}

void CorridorState::Render(sf::RenderWindow& window) {
    //todo: background, now - color (different from main menu)
    window.clear(sf::Color(20, 100, 20)); 
}