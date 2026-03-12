#include "PetStudent.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

PetStudent::PetStudent(const sf::Texture& texture)
    : m_sprite(texture)
{
    m_sprite.setPosition({360.f, 320.f});
}

void PetStudent::Update(float dt) {
    (void)dt;
}

void PetStudent::UpdateEnvironment(RoomType type, float dt) {
    float dE = 0.f, dK = 0.f, dM = 0.f;

    switch (type) {
        case RoomType::Home:
            dE = +2.f * dt;
            dM = +3.f * dt;
            break;
        case RoomType::Cafeteria:
            dE = +1.f * dt;
            dM = +1.f * dt;
            break;
        default:
            dM = -0.1f * dt;
            break;
    }

    ModifyStats(dE, dK, dM);
}

void PetStudent::HandleEvent(const sf::Event& event) {
    (void)event;
}

void PetStudent::ModifyStats(float dE, float dK, float dM) {
    m_energy   = std::clamp(m_energy   + dE, 0.f, 100.f);
    m_knowledge = std::max(m_knowledge + dK, 0.f);
    m_mental   = std::clamp(m_mental   + dM, -100.f, 150.f);
}

void PetStudent::AddTime(float minutes) {
    m_timeMinutes += minutes;
}

void PetStudent::ResetStats() {
    m_energy = 80.f;
    m_knowledge = 0.f;
    m_mental = 80.f;
    m_timeMinutes = 8.f * 60.f;
}

void PetStudent::Render(sf::RenderTarget& target) {
    target.draw(m_sprite);
}

void PetStudent::SetPosition(float x, float y) {
    m_sprite.setPosition({x, y});
}

sf::Vector2f PetStudent::GetPosition() const {
    return m_sprite.getPosition();
}

sf::FloatRect PetStudent::GetBounds() const {
    return m_sprite.getGlobalBounds();
}

float PetStudent::GetEnergy() const      { return m_energy; }
float PetStudent::GetKnowledge() const   { return m_knowledge; }
float PetStudent::GetMentalState() const { return m_mental; }

std::string PetStudent::GetTimeString() const {
    int totalMins = static_cast<int>(m_timeMinutes);
    int hours = (totalMins / 60) % 24;
    int mins = totalMins % 60;

    std::string hStr = (hours < 10 ? "0" : "") + std::to_string(hours);
    std::string mStr = (mins  < 10 ? "0" : "") + std::to_string(mins);
    return hStr + ":" + mStr;
}
