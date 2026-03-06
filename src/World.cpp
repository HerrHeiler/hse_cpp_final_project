#include "World.hpp"
#include "RoomState.hpp"


World::World(ResourceManager& rm, StateManager& sm)
    : resourceManager(rm)
    , manager(sm)
    , student(resourceManager.GetTexture("student"))
    , m_background(resourceManager.GetTexture("corridor"))
    , currentRoom(RoomType::Home)
{
    sf::Vector2u texSize = resourceManager.GetTexture("corridor").getSize();
    m_background.setScale({
        800.0f / static_cast<float>(texSize.x),
        600.0f / static_cast<float>(texSize.y)
    });

    LoadDoors();
}

void World::LoadDoors() {
    const sf::Font& font = resourceManager.GetFont("default");
    doors.emplace_back(sf::FloatRect({50.f, 200.f}, {80.f, 150.f}), RoomType::Home, "Home apartment", font);
    doors.emplace_back(sf::FloatRect({250.f, 200.f}, {80.f, 150.f}), RoomType::Lecture, "Lecture hall", font);
    doors.emplace_back(sf::FloatRect({450.f, 200.f}, {80.f, 150.f}), RoomType::Seminar, "Seminar room", font);
    doors.emplace_back(sf::FloatRect({650.f, 200.f}, {80.f, 150.f}), RoomType::Cafeteria, "Cafeteria", font);
}

void World::Update(float deltaTime) {
    student.Update(deltaTime);

    sf::Vector2f pos = student.GetPosition();
    sf::FloatRect bounds = student.GetBounds();

    if (pos.x < 0.f) student.SetPosition(0.f, pos.y);
    if (pos.y < 0.f) student.SetPosition(pos.x, 0.f);
    if (pos.x + bounds.size.x > 800.f) student.SetPosition(800.f - bounds.size.x, pos.y);
    if (pos.y + bounds.size.y > 600.f) student.SetPosition(pos.x, 600.f - bounds.size.y);

    sf::FloatRect studentBounds = student.GetBounds();
    
    bool ePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    CheckDoorCollision(studentBounds, ePressed);
}

void World::Render(sf::RenderTarget& target) {
    target.draw(m_background);
    for (const auto& door : doors) {
        target.draw(door.shape);
        target.draw(door.text);
    }    
    student.Render(target);
}

void World::CheckDoorCollision(const sf::FloatRect& studentBounds, bool ePressed) {
    if (!ePressed) return;
    for (const auto& door : doors) {
        if (studentBounds.findIntersection(door.bounds).has_value()) {
            currentRoom = door.target;
            manager.Push(std::make_unique<RoomState>(manager, resourceManager, currentRoom));
            return;
        }
    }
}

void World::HandleEvent(const sf::Event& event) {
    student.HandleEvent(event);
}