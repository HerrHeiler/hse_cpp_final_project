#pragma once
#include <stack>
#include <memory> 
#include "State.hpp"

class State;

class StateManager {
public:
    
    //to add new screen:
    void Push(std::unique_ptr<State> state);
    
    // to close the uppermost screen:
    void Pop();
    
    // to change screens:
    void Change(std::unique_ptr<State> state);


    void HandleEvent(const sf::Event& event);
    void Update(float dt);
    void Render(sf::RenderWindow& window);

    State* GetCurrentState();

private:
    std::stack<std::unique_ptr<State>> states;
};