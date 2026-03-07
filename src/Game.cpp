#include "Game.hpp"
#include "MainMenuState.hpp"
#include "World.hpp"

Game::Game() 
    : window(sf::VideoMode(sf::Vector2u{800u, 600u}), "Average HSE Student Routine")
{
    window.setFramerateLimit(60);

    resourceManager.LoadFont("default");
    resourceManager.LoadTexture("corridor");
    resourceManager.LoadTexture("student");

    student = new Student(resourceManager.GetTexture("student"));

    stateManager.Push(std::make_unique<MainMenuState>(
        stateManager,
        resourceManager,
        *student
    ));
}

Game::~Game() {
    delete student;
}

void Game::Run() {
    sf::Clock clock; 

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds(); 

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

void Game::Update(float dt) {
    stateManager.Update(dt);
}

void Game::Render() {
    window.clear();
    stateManager.Render(window);
    window.display();
}