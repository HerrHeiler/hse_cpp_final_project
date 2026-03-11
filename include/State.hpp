#pragma once
#include <SFML/Graphics.hpp>

class ResourceManager;
class StateManager;
class Student;

class State {
public:
    virtual ~State() = default;

    //to be implemented:
    virtual void HandleEvent(const sf::Event& event) = 0; 
    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;

    virtual void OnStartGame(ResourceManager&, StateManager&, Student&) {}
};