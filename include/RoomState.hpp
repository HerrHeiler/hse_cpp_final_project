#pragma once
#include "State.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "Door.hpp" 
#include <SFML/Graphics.hpp>
#include "Student.hpp"
#include <optional>
#include <variant>
#include <memory>
#include <string>
#include <functional>

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
    std::unique_ptr<sf::Texture> m_roomTexture;

    std::optional<sf::Text> m_title;       
    std::optional<sf::Text> m_hint;  
    std::optional<sf::Text> m_secretHint;
    std::optional<sf::Text> m_timeUI;
    std::optional<sf::Text> m_energyUI;
    std::optional<sf::Text> m_knowledgeUI;
    std::optional<sf::Text> m_mentalUI;
    std::optional<sf::Text> m_achievement;

    sf::RectangleShape m_infoBox;  
    sf::RectangleShape m_statsBox;
    sf::RectangleShape m_achievementBox;
    sf::RectangleShape m_confirmBox;
    std::optional<sf::Text> m_confirmText;   
    
    bool m_isGlitchActive; 
    float m_glitchTimer{0.f};
    float m_glitchDuration{2.f};
    bool m_statsApplied{false};

    bool m_isActionActive{false};
    float m_actionTimer{0.f};

    sf::FloatRect m_lectureZone;          
    bool m_showConfirmation{false};        
         

    void InitUI();
    void UpdateUI();
    std::string getHintForRoom() const;
    void performRoomAction(float dt);

    float calculateStatsBoxY() const;

    using RoomAction = std::variant<
        std::monostate,
        std::function<void(float)>
    >;

    RoomAction getRoomAction() const;
    
};