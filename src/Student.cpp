#include "Student.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Student::Student(const sf::Texture& texture) 
    : sprite(texture)
    , speed(200.f)
    , energy(100.f)
    , knowledge(0.f)
    , mental_state(0.f)
{
    sprite.setPosition({400.f, 300.f}); 
}

void Student::Update(float dt) {
    sf::Vector2f movement({0.f, 0.f});

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += speed;

    sprite.move(movement * dt);
}

void Student::UpdateEnvironment(RoomType type, float dt) {
    float dE = 0.f, dK = 0.f, dM = 0.f;

    switch (type) {
        case RoomType::Lecture:
            dK = 5.0f * dt; 
            dE = -5.0f * dt;
            dM = -1.0f * dt;
            break;
        case RoomType::Seminar:
            dK = 35.0f * dt;
            dE = -25.0f * dt;
            break;
        case RoomType::Home:
            dE = 10.0f * dt;
            dM = 15.0f * dt;
            break;
        case RoomType::Cafeteria:
            dE = 12.0f * dt;
            dM = -1.0f * dt;
            break;
        case RoomType::Corridor:
        default:
            dE = -0.5f * dt;
            break;
    }

    ModifyStats(dE, dK, dM);
}

void Student::ModifyStats(float dEnergy, float dKnowledge, float dMentalState) {
    energy += dEnergy;
    knowledge += dKnowledge;
    mental_state += dMentalState;

    if (energy < 0.f) energy = 0.f;
    if (energy > 100.f) energy = 100.f;

    if (mental_state < -100.f) mental_state = -100.f;
    if (mental_state > 150.f) mental_state = 150.f;

    if (knowledge < 0.f) knowledge = 0.f;
}

void Student::Render(sf::RenderTarget& target) {
    target.draw(sprite);
}

void Student::SetPosition(float x, float y) {
    sprite.setPosition({x, y});
}

sf::Vector2f Student::GetPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Student::GetBounds() const {
    return sprite.getGlobalBounds();
}

void Student::HandleEvent(const sf::Event& event) {}


void Student::AddTime(float minutes) {
    m_timeMinutes += minutes;
}

std::string Student::GetTimeString() const {
    int totalMins = static_cast<int>(m_timeMinutes);
    int hours = (totalMins / 60) % 24;
    int mins = totalMins % 60;
    
    std::string hStr = (hours < 10 ? "0" : "") + std::to_string(hours);
    std::string mStr = (mins < 10 ? "0" : "") + std::to_string(mins);
    
    return hStr + ":" + mStr;
}


void Student::ResetStats() {
    energy = 100.f;          
    m_timeMinutes = 570.f;   
}