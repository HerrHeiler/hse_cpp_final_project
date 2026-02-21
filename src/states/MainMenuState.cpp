#include "MainMenuState.hpp"
#include "CorridorState.hpp" 

MainMenuState::MainMenuState(StateManager& stateManager) : manager(stateManager) {}

void MainMenuState::HandleEvent(const sf::Event& event) {

        //on enter change to corridor
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
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