#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "IStudent.hpp"
#include "ResourceManager.hpp" 
#include <SFML/Graphics.hpp> 

class ResourceManager;
// class Student;

class MainMenuState : public State {
public:

    MainMenuState(StateManager& sm, ResourceManager& rm, IStudent& student);
    
    void HandleEvent(const sf::Event& event) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& stateManager; 
    ResourceManager& resourceManager;
    IStudent& student;
    sf::Text m_text;
};