#include "MainMenuState.hpp"
#include "CorridorState.hpp" 
#include <SFML/Window/Event.hpp> 


MainMenuState::MainMenuState(StateManager& stateManager) : manager(stateManager) {}

void MainMenuState::HandleEvent(const sf::Event& event) {

        //on enter change to corridor
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (keyEvent->code == sf::Keyboard::Key::Enter) {
            manager.Change(std::make_unique<CorridorState>(manager));
        }
    }
}

void MainMenuState::Update(sf::Time dt) {
    // todo
}

void MainMenuState::Render(sf::RenderWindow& window) {
    //todo text, now: color
    window.clear(sf::Color(0, 50, 100));
}