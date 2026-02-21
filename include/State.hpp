#pragma once
#include <SFML/Graphics.hpp>



class State {
public:
    virtual ~State() = default;

    //to be implemented:
    virtual void HandleEvent(const sf::Event& event) = 0; 
    virtual void Update(sf::Time dt) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
};