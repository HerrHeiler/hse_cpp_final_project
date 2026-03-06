#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp" 
#include <SFML/Graphics.hpp> 

class MainMenuState : public State {
public:

    MainMenuState(StateManager& stateManager); 
    
    void HandleEvent(const sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager; 
    ResourceManager m_resources;
    sf::Text m_text;
};