#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "Door.hpp" 
#include <SFML/Graphics.hpp>
#include "Student.hpp"

class RoomState : public State {
public:
    RoomState(StateManager& stateManager, ResourceManager& resources, RoomType type);

    void HandleEvent(const sf::Event& event) override;
    void Update(sf::Time dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager;
    ResourceManager& m_resources;
    RoomType roomType;
    
    sf::Sprite m_background; 
    sf::Text m_title;       
    sf::Text m_hint;  
    sf::Text m_secretHint;
    
    Student m_student;

    bool m_isGlitchActive; 
    sf::Time m_glitchTimer;
    sf::RectangleShape m_achievementBox;
    sf::Text m_achievement;
    
};