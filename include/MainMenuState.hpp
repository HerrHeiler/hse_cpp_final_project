#pragma once
#include "State.hpp"
#include "StateManager.hpp"


class MainMenuState : public State {
public:

    MainMenuState(StateManager& stateManager); //passing manager to give commands!!
    
    void HandleEvent(const sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager; 
};