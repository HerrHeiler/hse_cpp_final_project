#include "Game.hpp"
#include "MainMenuState.hpp" 


Game::Game() : window(sf::VideoMode(sf::Vector2u{800u, 600u}), "Average HSE Student Routine") {
    //start menu
    stateManager.Push(std::make_unique<MainMenuState>(stateManager));
}

void Game::Run() {

    sf::Clock clock; 

    while (window.isOpen()) {

        sf::Time dt = clock.restart(); 

        ProcessEvents();
        Update(dt);
        Render();
    }
}



void Game::ProcessEvents() {
    while (auto eventOpt = window.pollEvent()) {
        const sf::Event& event = *eventOpt;
        if (event.is<sf::Event::Closed>()) {
            window.close();
        }
        stateManager.HandleEvent(event);
    }
}



void Game::Update(sf::Time dt) {
    stateManager.Update(dt);
}



void Game::Render() {
    stateManager.Render(window);
    window.display();
}