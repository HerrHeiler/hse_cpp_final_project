#include "RoomState.hpp"
#include <SFML/Window/Event.hpp>

RoomState::RoomState(StateManager& stateManager, ResourceManager& resources, RoomType type) 
    : manager(stateManager)
    , roomType(type)
    , m_resources(resources)
    , m_background(resources.GetTexture("student"))  //temporary background - student pic
    , m_title(resources.GetFont("default"), "", 30)
    , m_hint(resources.GetFont("default"), "Press ESC to return to corridor", 16)
    , m_student(resources.GetTexture("student"))
    , m_achievement(resources.GetFont("default"), "ACHIEVEMENT UNLOCKED:\nDAREDEVIL!", 18)
    , m_isGlitchActive(false)
    , m_glitchTimer(sf::Time::Zero)
    , m_secretHint(resources.GetFont("default"), "", 15)
{
    // for temporary background 
    sf::Vector2u texSize = resources.GetTexture("student").getSize();
    m_background.setScale({800.0f / texSize.x, 600.0f / texSize.y});
    m_background.setColor(sf::Color(100, 100, 100)); 


    std::string roomName = "Unknown Room";
    if (type == RoomType::Home) roomName = "Welcome Home!";
    else if (type == RoomType::Lecture) {
        roomName = "OH! CALCULUS is awesome :)";
        m_hint.setString("Press ESC to return");
        m_secretHint.setString("psst... press 'f' to use phone");
        m_secretHint.setFillColor(sf::Color(120, 120, 120)); 
        m_secretHint.setPosition({10.f, 570.f});
    } 
    else if (type == RoomType::Seminar) roomName = "Try to work, golden fish!";
    else if (type == RoomType::Cafeteria) roomName = "Yummy room";

    m_title.setString(roomName);
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition({50.f, 50.f}); 

    m_hint.setFillColor(sf::Color::Yellow);
    m_hint.setPosition({50.f, 120.f});


    m_achievement.setFillColor(sf::Color::Red);
    m_achievement.setPosition({450.f, 20.f});

    sf::FloatRect textBounds = m_achievement.getGlobalBounds();
    m_achievementBox.setSize({textBounds.size.x + 20.f, textBounds.size.y + 20.f}); 
    m_achievementBox.setFillColor(sf::Color::Black);
    m_achievementBox.setOutlineColor(sf::Color::Red);
    m_achievementBox.setOutlineThickness(2.f);
    m_achievementBox.setPosition({textBounds.position.x - 10.f, textBounds.position.y - 10.f});

    m_student.SetPosition(400.f, 400.f);
}


void RoomState::HandleEvent(const sf::Event& event) {

    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        if (!m_isGlitchActive && keyEvent->code == sf::Keyboard::Key::Escape) {
            manager.Pop(); 
        }
        
        if (roomType == RoomType::Lecture && keyEvent->code == sf::Keyboard::Key::F) {
            if (!m_isGlitchActive) {

                m_isGlitchActive = true;
                m_glitchTimer = sf::Time::Zero;

                m_background.setTexture(m_resources.GetTexture("corridor"));

                sf::Vector2u cSize = m_resources.GetTexture("corridor").getSize();
                m_background.setScale({800.0f / cSize.x, 600.0f / cSize.y});
            }
        }
    }
}

void RoomState::Update(sf::Time dt) {
    m_student.Update(dt.asSeconds());

    if (m_isGlitchActive) {
        m_glitchTimer += dt;
        

        float offsetX = (rand() % 20) - 10.0f;
        float offsetY = (rand() % 20) - 10.0f;
        m_background.setPosition({offsetX, offsetY});

        int intensity = (rand() % 150) + 50; 
        m_background.setColor(sf::Color(intensity, intensity, intensity));

        if (m_glitchTimer.asSeconds() > 2.0f) {
            m_isGlitchActive = false;
            
            m_background.setTexture(m_resources.GetTexture("student"));
            sf::Vector2u sSize = m_resources.GetTexture("student").getSize();
            m_background.setScale({800.0f / sSize.x, 600.0f / sSize.y});
            m_background.setColor(sf::Color(100, 100, 100)); 
            m_background.setPosition({0.f, 0.f});
        }
    }

    sf::Vector2f pos = m_student.GetPosition();
    sf::FloatRect bounds = m_student.GetBounds();
    
    if (pos.x < 0.f) m_student.SetPosition(0.f, pos.y);
    if (pos.y < 0.f) m_student.SetPosition(pos.x, 0.f);
    
    if (pos.x + bounds.size.x > 800.f) {
        m_student.SetPosition(800.f - bounds.size.x, pos.y);
    }
    if (pos.y + bounds.size.y > 600.f) {
        m_student.SetPosition(pos.x, 600.f - bounds.size.y);
    }
}

void RoomState::Render(sf::RenderWindow& window) {
    if (m_isGlitchActive) {
        if (rand() % 3 == 0) window.clear(sf::Color(50, 50, 50));
        else window.clear(sf::Color::Black);
    } else {
        window.clear(sf::Color::Black);
    }


    window.draw(m_background);

    if (!m_isGlitchActive) {
        window.draw(m_title);
        window.draw(m_hint);
        window.draw(m_secretHint);
    }
    
    m_student.Render(window);

    if (m_isGlitchActive) {
        window.draw(m_achievementBox);
        window.draw(m_achievement);
    }
}