#include "Game.hpp"
#include "MainMenuState.hpp"
#include <SFML/Window/Keyboard.hpp>

Game::Game() 
    : window(sf::VideoMode(sf::Vector2u{800u, 600u}), "Average HSE Student Routine")
    , humanStudent(resourceManager.GetTexture("student"))
    , petStudent(resourceManager.GetTexture("pet"))
{
    window.setFramerateLimit(60);

    resourceManager.LoadFont("default");
    resourceManager.LoadTexture("corridor");
    resourceManager.LoadTexture("student");
    resourceManager.LoadTexture("lecture_bg");
    resourceManager.LoadTexture("home_room");
    resourceManager.LoadTexture("seminar_room");
    resourceManager.LoadTexture("cafeteria_room");
    resourceManager.LoadTexture("pet");

    IStudent* student = &humanStudent;

    stateManager.Push(std::make_unique<MainMenuState>(
        stateManager,
        resourceManager,
        *student
    ));
}

Game::~Game() = default;

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
        if (const auto* key = event.getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Tab) {
                if (student == &humanStudent)
                    student = &petStudent;
                else
                    student = &humanStudent;
                stateManager.Change(std::make_unique<MainMenuState>(
                    stateManager,
                    resourceManager,
                    *student
                ));
            }
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