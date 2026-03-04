#include "Student.hpp"
#include <SFML/Window/Keyboard.hpp>

Student::Student(const sf::Texture& texture) 
    : m_sprite(texture)
    , m_speed(200.f) 
{
    m_sprite.setPosition({400.f, 300.f}); 
}

void Student::Update(float dt) {
    sf::Vector2f movement({0.f, 0.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= m_speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += m_speed;

    m_sprite.move(movement * dt);
}

void Student::Render(sf::RenderTarget& target) {
    target.draw(m_sprite);
}

void Student::SetPosition(float x, float y) {
    m_sprite.setPosition({x, y});
}

sf::Vector2f Student::GetPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect Student::GetBounds() const {
    return m_sprite.getGlobalBounds();
}

void Student::HandleEvent(const sf::Event& event) {}