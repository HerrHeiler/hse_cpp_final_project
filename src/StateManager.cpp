#include "StateManager.hpp"

void StateManager::Push(std::unique_ptr<State> state) {
    states.push(std::move(state));
}

void StateManager::Pop() {
    if (!states.empty()) {
        states.pop(); 
    }
}

void StateManager::Change(std::unique_ptr<State> state) {
    if (!states.empty()) {
        states.pop(); 
    }
    states.push(std::move(state)); 
}



void StateManager::HandleEvent(const sf::Event& event) {
    if (!states.empty()) {
        states.top()->HandleEvent(event); //takes uppermost one
    }
}

void StateManager::Update(sf::Time dt) {
    if (!states.empty()) {
        states.top()->Update(dt);
    }
}

void StateManager::Render(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->Render(window);
    }
}