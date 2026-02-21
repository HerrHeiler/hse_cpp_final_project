#pragma once
#include <stack>
#include <memory> 
#include "State.hpp"

class StateManager {
public:
    
    //to add new screen:
    void Push(std::unique_ptr<State> state);
    
    // to close the uppermost screen:
    void Pop();
    
    // to change screens:
    void Change(std::unique_ptr<State> state);


    void HandleEvent(const sf::Event& event);
    void Update(sf::Time dt);
    void Render(sf::RenderWindow& window);

private:
    std::stack<std::unique_ptr<State>> states;
};