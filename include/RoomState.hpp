#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "Door.hpp" 
#include <SFML/Graphics.hpp>
#include "Student.hpp"
#include <optional>

class RoomState : public State {
public:
    RoomState(StateManager& stateManager, ResourceManager& resources, RoomType type, Student& student);

    void HandleEvent(const sf::Event& event) override;
    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    StateManager& manager;
    ResourceManager& resourceManager;
    Student& m_student;
    RoomType currentRoom;
    
    sf::Sprite m_background; 
    std::optional<sf::Text> m_title;       
    std::optional<sf::Text> m_hint;  
    std::optional<sf::Text> m_secretHint;
    std::optional<sf::Text> m_timeUI;

    sf::RectangleShape m_infoBox;  
    sf::RectangleShape m_statsBox;
    
    bool m_isGlitchActive; 
    float m_glitchTimer{0.f};
    float m_glitchDuration{2.f};
    sf::RectangleShape m_achievementBox;
    std::optional<sf::Text> m_achievement;

    std::optional<sf::Text> m_energyUI;
    std::optional<sf::Text> m_knowledgeUI;
    std::optional<sf::Text> m_mentalUI;
    
    bool m_statsApplied{false};

    sf::FloatRect m_lectureZone;          
    bool m_showConfirmation{false};        
    
    sf::RectangleShape m_confirmBox;       
    std::optional<sf::Text> m_confirmText; 

    void InitUI();
    void UpdateUI();
    
};