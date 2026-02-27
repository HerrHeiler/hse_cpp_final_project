#include "World.hpp"

World::World(ResourceManager& resources)
    : m_resources(resources)

    , m_background(resources.GetTexture("corridor")) 
    , m_student(resources.GetTexture("student")) 
{
    sf::Vector2u texSize = resources.GetTexture("corridor").getSize();
    m_background.setScale({
        800.0f / texSize.x, 
        600.0f / texSize.y
    });
}

void World::Update(sf::Time dt) {
    m_student.Update(dt);

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

void World::Render(sf::RenderWindow& window) {
    window.draw(m_background);
    m_student.Render(window);
}