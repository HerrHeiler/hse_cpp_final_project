#include "MainMenuState.hpp"
#include "CorridorState.hpp"
#include <SFML/Window/Event.hpp>
#include "ResourceManager.hpp"
#include "Student.hpp"


MainMenuState::MainMenuState(StateManager& sm, ResourceManager& rm, Student& st)
    : stateManager(sm)
    , resourceManager(rm)
    , student(st)
    , m_text(resourceManager.GetFont("default"), "Press Enter to start\na new wonderful day!", 30)
{
    sf::FloatRect bounds = m_text.getLocalBounds();
    
    m_text.setOrigin({bounds.position.x + bounds.size.x / 2.0f, 
                      bounds.position.y + bounds.size.y / 2.0f});
                      
    m_text.setPosition({400.0f, 300.0f});
    
    m_text.setFillColor(sf::Color(150, 150, 150));
}

void MainMenuState::HandleEvent(const sf::Event& event) {
    // on enter change to corridor
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            stateManager.Change(std::make_unique<CorridorState>(stateManager, resourceManager, student));
        }
    }
}

void MainMenuState::Update(float dt) {
}

void MainMenuState::Render(sf::RenderWindow& window) {

    window.clear(sf::Color::Black);
    window.draw(m_text);
}
