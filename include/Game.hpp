#pragma once
#include <SFML/Graphics.hpp>
#include "StateManager.hpp"

class Game {
private:
    
    void ProcessEvents();      
    void Update(sf::Time dt);  
    void Render();             
    StateManager stateManager;

    sf::RenderWindow window; 
public:
    Game(); 
    void Run(); 


};