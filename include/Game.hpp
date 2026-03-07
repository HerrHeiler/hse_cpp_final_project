#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.hpp"
#include "Student.hpp"
#include "ResourceManager.hpp"

class Game {
private:
    
    void ProcessEvents();
    void Update(float dt);
    void Render();

    StateManager stateManager;
    ResourceManager resourceManager;
    Student* student{nullptr};

    sf::RenderWindow window;

public:
    Game(); 
    ~Game(); 
    void Run();

};