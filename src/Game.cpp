#include "Game.hpp"
#include "MainMenuState.hpp" 


Game::Game() : window(sf::VideoMode(800, 600), "Average HSE Student Routine") {
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
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
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