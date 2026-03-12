#include "World.hpp"
#include "RoomState.hpp"


World::World(ResourceManager& rm, StateManager& sm, IStudent& student)
    : resourceManager(rm)
    , manager(sm)
    , student(student)
    , m_background(resourceManager.GetTexture("corridor"))
    , currentRoom(RoomType::Home)
{
    sf::Vector2u texSize = resourceManager.GetTexture("corridor").getSize();
    m_background.setScale({
        800.0f / static_cast<float>(texSize.x),
        600.0f / static_cast<float>(texSize.y)
    });

    m_uiFont = &resourceManager.GetFont("default");
    InitUI();
    LoadDoors();
}

void World::InitUI() {
    m_energyText.emplace(*m_uiFont, "Energy: 100", 18);
    m_energyText->setFillColor(sf::Color::White);
    m_energyText->setPosition({12.f, 10.f});

    m_knowledgeText.emplace(*m_uiFont, "Knowledge: 0", 18);
    m_knowledgeText->setFillColor(sf::Color::Yellow);
    m_knowledgeText->setPosition({12.f, 35.f});

    m_mental_stateText.emplace(*m_uiFont, "Mental State: 50", 18);
    m_mental_stateText->setFillColor(sf::Color(0, 200, 0));
    m_mental_stateText->setPosition({12.f, 60.f});

    m_timeText.emplace(*m_uiFont, "Time: 09:30", 22);
    m_timeText->setFillColor(sf::Color::Cyan);
    m_timeText->setPosition({350.f, 10.f}); 


    m_deadInsideText.emplace(resourceManager.GetFont("default"), "ACHIEVEMENT UNLOCKED:\nDEAD INSIDE (Mental -150)", 16);
    m_deadInsideText->setFillColor(sf::Color::White);
    sf::FloatRect diBounds = m_deadInsideText->getLocalBounds();
    m_deadInsideBox.setSize({diBounds.size.x + 20.f, diBounds.size.y + 20.f});
    m_deadInsideBox.setFillColor(sf::Color(20, 20, 20, 230)); 
    m_deadInsideBox.setOutlineColor(sf::Color(138, 43, 226)); 
    m_deadInsideBox.setOutlineThickness(2.f);
    m_deadInsideBox.setPosition({800.f - diBounds.size.x - 30.f, 600.f - diBounds.size.y - 30.f});
    m_deadInsideText->setPosition({800.f - diBounds.size.x - 20.f, 600.f - diBounds.size.y - 20.f});


    m_megamindText.emplace(resourceManager.GetFont("default"), "ACHIEVEMENT UNLOCKED:\nMEGAMIND (Knowledge 200+)", 16);
    m_megamindText->setFillColor(sf::Color(0, 255, 255)); 
    sf::FloatRect mmBounds = m_megamindText->getLocalBounds();
    m_megamindBox.setSize({mmBounds.size.x + 20.f, mmBounds.size.y + 20.f});
    m_megamindBox.setFillColor(sf::Color(20, 20, 20, 230)); 
    m_megamindBox.setOutlineColor(sf::Color(0, 255, 255)); 
    m_megamindBox.setOutlineThickness(2.f);
    m_megamindBox.setPosition({10.f, 600.f - mmBounds.size.y - 30.f});
    m_megamindText->setPosition({20.f, 600.f - mmBounds.size.y - 20.f});
}

void World::UpdateUI() {
    if (m_energyText.has_value())
        m_energyText->setString("Energy: " + std::to_string(static_cast<int>(student.GetEnergy())));
    
    if (m_knowledgeText.has_value())
        m_knowledgeText->setString("Knowledge: " + std::to_string(static_cast<int>(student.GetKnowledge())));
    
    if (m_mental_stateText.has_value())
        m_mental_stateText->setString("Mental State: " + std::to_string(static_cast<int>(student.GetMentalState())));
    
        if (m_timeText.has_value()) {
        m_timeText->setString("Time: " + student.GetTimeString());
    }
}

void World::LoadDoors() {
    const sf::Font& font = resourceManager.GetFont("default");
    doors.push_back(std::make_shared<Door>(sf::FloatRect({50.f, 200.f}, {80.f, 150.f}), RoomType::Home, "Home apartment", font));
    doors.push_back(std::make_shared<Door>(sf::FloatRect({250.f, 200.f}, {80.f, 150.f}), RoomType::Lecture, "Lecture hall", font));
    doors.push_back(std::make_shared<Door>(sf::FloatRect({450.f, 200.f}, {80.f, 150.f}), RoomType::Seminar, "Seminar room", font));
    doors.push_back(std::make_shared<Door>(sf::FloatRect({650.f, 200.f}, {80.f, 150.f}), RoomType::Cafeteria, "Cafeteria", font));
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

    UpdateUI();
}

void World::Render(sf::RenderWindow& window) {
    window.draw(m_background);
    for (const auto& door : doors) {
        window.draw(door->shape);
        window.draw(door->text);
    }    
    student.Render(window);

    if (m_energyText.has_value()) window.draw(m_energyText.value());
    if (m_knowledgeText.has_value()) window.draw(m_knowledgeText.value());
    if (m_mental_stateText.has_value()) window.draw(m_mental_stateText.value());
    if (m_timeText.has_value()) window.draw(m_timeText.value()); 


    if (student.GetMentalState() <= -150.f) {
        window.draw(m_deadInsideBox);
        if (m_deadInsideText.has_value()) window.draw(m_deadInsideText.value());
    }

    if (student.GetKnowledge() >= 200.f) {
        window.draw(m_megamindBox);
        if (m_megamindText.has_value()) window.draw(m_megamindText.value());
    }

}

void World::CheckDoorCollision(const sf::FloatRect& studentBounds, bool ePressed) {
    if (!ePressed) return;
    for (const auto& door : doors) {
        if (studentBounds.findIntersection(door->bounds).has_value()) {
            currentRoom = door->target;
            manager.Push(std::make_unique<RoomState>(manager, resourceManager, currentRoom, student));
            return;
        }
    }
}

void World::HandleEvent(const sf::Event& event) {
    student.HandleEvent(event);
}