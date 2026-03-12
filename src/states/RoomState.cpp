#include "RoomState.hpp"
#include "RoomConfig.hpp"
#include <SFML/Window/Event.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include "MainMenuState.hpp"

RoomState::RoomState(StateManager& stateManager, ResourceManager& resources, RoomType type, IStudent& student)
    : manager(stateManager)
    , currentRoom(type)
    , resourceManager(resources)
    , m_background(resources.GetTexture("student"))
    , m_student(student)
    , m_isGlitchActive(false)
    , m_glitchTimer(0.f)
    , m_glitchDuration(2.f)
    , m_statsApplied(false)
    , m_showConfirmation(false)
    , m_roomTexture(nullptr)
    , m_roomActionImpl(nullptr)
{
    m_title.emplace(resources.GetFont("default"), "", 24);
    m_hint.emplace(resources.GetFont("default"), "Press ESC to return to corridor", 14);
    m_secretHint.emplace(resources.GetFont("default"), "", 15);
    m_energyUI.emplace(resources.GetFont("default"), "Energy: 100", 16);
    m_knowledgeUI.emplace(resources.GetFont("default"), "Knowledge: 0", 16);
    m_mentalUI.emplace(resources.GetFont("default"), "Mental State: 50", 16);
    m_confirmText.emplace(
        resources.GetFont("default"),
        "Listen to lecture?\n(+50 Knowledge, -30 Energy)\n\nPress ENTER to confirm",
        20
    );
    m_achievement.emplace(
        resources.GetFont("default"),
        "ACHIEVEMENT UNLOCKED:\nDAREDEVIL!",
        18
    );

    const auto config = getRoomConfig(type);
    const std::string textureId = std::string(getTextureIdForRoom(type));

    std::string roomName = "Unknown Room";


    try {
        const sf::Texture& tex = resources.GetTexture(textureId);
        m_roomTexture = std::make_unique<sf::Texture>(tex);
        m_background.setTexture(*m_roomTexture, true);
    } catch (const std::exception& e) {
        std::cerr << "[RoomState] Warning: " << e.what()
                  << ", fallback to 'student' texture\n";
        const sf::Texture& fallback = resources.GetTexture("student");
        m_roomTexture = std::make_unique<sf::Texture>(fallback);
        m_background.setTexture(*m_roomTexture, true);
    }

    sf::Texture bgTex = m_background.getTexture();
    sf::Vector2u texSize = bgTex.getSize();
    if (texSize.x > 0 && texSize.y > 0) {
        m_background.setScale(sf::Vector2f(
            800.f / texSize.x,
            600.f / texSize.y
        ));
    }

    if (type == RoomType::Home) {
        m_roomActionImpl = std::make_unique<HomeRestAction>();
        roomName = "Welcome Home!";
        m_hint->setString(
            "Press ESC to return\n"
            "Press 'S' to sleep (End Day)\n"
            "Press 'P' to pray (+5 Mental, 15 min)\n"
            "Press SPACE to rest\n"
            "(+Energy, +Mental)"
        );
    } else if (type == RoomType::Lecture) {
        m_roomActionImpl = std::make_unique<LectureAction>();
        roomName = "OH! CALCULUS is awesome :)";

        m_lectureZone = sf::FloatRect(
            sf::Vector2f(300.f, 200.f),
            sf::Vector2f(200.f, 150.f)
        );

        m_hint->setString(
            "Press ESC to return\n"
            "Press SPACE to study\n"
            "(+Knowledge, -Energy)"
        );

        m_secretHint->setString("psst... press 'f' to use phone");
        m_secretHint->setFillColor(sf::Color::Black);
        sf::FloatRect shBounds = m_secretHint->getLocalBounds();
        m_secretHint->setOrigin(sf::Vector2f(
            shBounds.position.x + shBounds.size.x / 2.f,
            shBounds.position.y + shBounds.size.y / 2.f
        ));
        m_secretHint->setPosition({400.f, 570.f});
    } else if (type == RoomType::Seminar) {
        m_roomActionImpl = std::make_unique<SeminarAction>();
        roomName = "Try to work, golden fish!";
        m_hint->setString(
            "Press ESC to return\n"
            "Press and hold SPACE to study\n"
            "(+Knowledge, --Energy, ---Mental)"
        );
    } else if (type == RoomType::Cafeteria) {
        m_roomActionImpl = std::make_unique<CafeteriaAction>();
        roomName = "Yummy room";
        m_hint->setString(
            "Press ESC to return\n"
            "Press SPACE to eat\n"
            "(+Energy, -Mental)"
        );
    }

    m_title->setString(roomName);
    m_title->setFillColor(sf::Color::White);
    m_title->setPosition({10.f, 10.f});

    m_hint->setFillColor(sf::Color::Yellow);
    m_hint->setPosition({10.f, 45.f});


    sf::FloatRect titleBounds = m_title->getGlobalBounds();
    sf::FloatRect hintBounds  = m_hint->getGlobalBounds();

    float boxWidth  = std::max(titleBounds.size.x, hintBounds.size.x) + 30.f;
    float boxHeight = titleBounds.size.y + hintBounds.size.y + 35.f;

    sf::Color panelColor(71, 74, 80);
    m_infoBox.setFillColor(panelColor);
    m_infoBox.setPosition({0.f, 0.f});
    m_infoBox.setSize({boxWidth, boxHeight});

    m_statsBox.setFillColor(panelColor);
    m_statsBox.setPosition({0.f, calculateStatsBoxY()});
    m_statsBox.setSize({170.f, 115.f});

    m_achievement->setFillColor(sf::Color::Red);
    m_achievement->setPosition({290.f, 20.f});

    sf::FloatRect textBounds = m_achievement->getGlobalBounds();
    m_achievementBox.setSize({textBounds.size.x + 20.f, textBounds.size.y + 20.f});
    m_achievementBox.setFillColor(sf::Color::Black);
    m_achievementBox.setOutlineColor(sf::Color::Red);
    m_achievementBox.setOutlineThickness(2.f);
    m_achievementBox.setPosition(
        {textBounds.position.x - 5.f, textBounds.position.y - 5.f}
    );


    m_confirmBox.setSize({400.f, 200.f});
    m_confirmBox.setFillColor(sf::Color(0, 0, 0, 230));
    m_confirmBox.setOutlineColor(sf::Color::White);
    m_confirmBox.setOutlineThickness(2.f);
    m_confirmBox.setOrigin({200.f, 100.f});
    m_confirmBox.setPosition({400.f, 300.f});

    sf::FloatRect confirmBounds = m_confirmText->getLocalBounds();
    m_confirmText->setOrigin(sf::Vector2f(
        confirmBounds.position.x + confirmBounds.size.x  / 2.f,
        confirmBounds.position.y  + confirmBounds.size.y / 2.f
    ));
    m_confirmText->setPosition({400.f, 300.f});

    m_student.UpdateEnvironment(currentRoom, 1.0f);
    m_statsApplied = true;

    InitUI();
    UpdateUI();

    m_student.SetPosition(400.f, 400.f);
}


void RoomState::HandleEvent(const sf::Event& event) {
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {

        if (m_showConfirmation) {
            if (keyEvent->code == sf::Keyboard::Key::Enter) {
                m_student.ModifyStats(-30.f, 50.f, -10.f); 
                m_student.AddTime(80.f); 
                m_showConfirmation = false;
            } 
            else if (keyEvent->code == sf::Keyboard::Key::Escape) {
                m_showConfirmation = false;
            }
            return; 
        }

        if (keyEvent->code == sf::Keyboard::Key::Space) {
            m_isActionActive = true;
        }

        if (!m_isGlitchActive && keyEvent->code == sf::Keyboard::Key::Escape) {
            manager.Pop(); 
            return;
        }
        if (currentRoom == RoomType::Lecture && keyEvent->code == sf::Keyboard::Key::E) {
            if (m_student.GetBounds().findIntersection(m_lectureZone).has_value()) {
                if (m_student.GetEnergy() > 0.f) {
                    m_showConfirmation = true;
                }
            }
        }
        if (currentRoom == RoomType::Lecture && keyEvent->code == sf::Keyboard::Key::F) {
            if (!m_isGlitchActive) {
                m_isGlitchActive = true;
                m_glitchTimer = 0.f;

                m_background.setTexture(resourceManager.GetTexture("corridor"));
                sf::Vector2u cSize = resourceManager.GetTexture("corridor").getSize();
                m_background.setScale({800.0f / cSize.x, 600.0f / cSize.y});
            }
        }

        if (currentRoom == RoomType::Home && keyEvent->code == sf::Keyboard::Key::S) {
            m_student.ResetStats();
            manager.Change(std::make_unique<MainMenuState>(manager, resourceManager, m_student)); 
            return;
        }

        if (currentRoom == RoomType::Home && keyEvent->code == sf::Keyboard::Key::P) {
            m_student.ModifyStats(0.f, 0.f, 5.f); 
            m_student.AddTime(15.f);              
        }
    }
    if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>()) {
        if (keyEvent->code == sf::Keyboard::Key::Space) {
            m_isActionActive = false;
            m_actionTimer = 0.f;
            m_hint->setFillColor(sf::Color::Yellow);
        }
    }

    m_student.HandleEvent(event);
}

void RoomState::Update(float dt) {
    if (m_showConfirmation) return;
    m_student.Update(dt);

    if (m_isActionActive) {
        performRoomAction(dt);
    }



    UpdateUI();


    if (currentRoom == RoomType::Lecture && m_hint.has_value()) {
        if (m_student.GetBounds().findIntersection(m_lectureZone).has_value()) {
            if (m_student.GetEnergy() > 0.f) {
                m_hint->setString("Press 'E' to listen to lecture");
            } else {
                m_hint->setString("You are too tired to listen..."); 
            }
        } else {
            m_hint->setString("Press ESC to return");
        }

        sf::FloatRect titleBounds = m_title->getGlobalBounds();
    sf::FloatRect hintBounds = m_hint->getGlobalBounds();

    float boxWidth = std::max(titleBounds.size.x, hintBounds.size.x) + 30.f;
    float boxHeight = titleBounds.size.y + hintBounds.size.y + 35.f;

    m_infoBox.setSize({boxWidth, boxHeight});
    }



    if (m_isGlitchActive) {
        m_glitchTimer += dt;
        
        float offsetX = (std::rand() % 20) - 10.0f;
        float offsetY = (std::rand() % 20) - 10.0f;
        m_background.setPosition({offsetX, offsetY});

        int intensity = (std::rand() % 150) + 50; 
        m_background.setColor(sf::Color(intensity, intensity, intensity));

        if (m_glitchTimer > 2.0f) {
            m_isGlitchActive = false;
    
        if (currentRoom == RoomType::Lecture && m_roomTexture) {
            m_background.setTexture(*m_roomTexture);
            m_background.setColor(sf::Color::White);
            sf::Vector2u sSize = m_roomTexture->getSize();
            m_background.setScale({800.f / sSize.x, 600.f / sSize.y});
        } else {
            m_background.setTexture(resourceManager.GetTexture("student"));
            m_background.setColor(sf::Color::White);
        }
        
        m_background.setPosition({0.f, 0.f});
        }
    }

    sf::Vector2f pos = m_student.GetPosition();
    sf::FloatRect bounds = m_student.GetBounds();
    
    if (pos.x < 0.f) m_student.SetPosition(0.f, pos.y);
    if (pos.y < 0.f) m_student.SetPosition(pos.x, 0.f);
    if (pos.x + bounds.size.x > 800.f) m_student.SetPosition(800.f - bounds.size.x, pos.y);
    if (pos.y + bounds.size.y > 600.f) m_student.SetPosition(pos.x, 600.f - bounds.size.y);
}

void RoomState::Render(sf::RenderWindow& window) {
    if (m_isGlitchActive) {
        if (std::rand() % 3 == 0) window.clear(sf::Color(50, 50, 50));
        else window.clear(sf::Color::Black);
    } else {
        window.clear(sf::Color::Black);
    }

    window.draw(m_background);

    if (!m_isGlitchActive) {
        window.draw(m_infoBox);
        if (m_title.has_value()) window.draw(m_title.value());
        if (m_hint.has_value()) window.draw(m_hint.value());
        if (currentRoom == RoomType::Lecture && m_secretHint.has_value()) {
            window.draw(m_secretHint.value());
        }

        window.draw(m_statsBox);
        if (m_energyUI.has_value()) window.draw(m_energyUI.value());
        if (m_knowledgeUI.has_value()) window.draw(m_knowledgeUI.value());
        if (m_mentalUI.has_value()) window.draw(m_mentalUI.value());
        if (m_timeUI.has_value()) window.draw(m_timeUI.value());

    }
    
    m_student.Render(window);

    
    if (m_isGlitchActive) {
        window.draw(m_achievementBox);
        if (m_achievement.has_value()) window.draw(m_achievement.value());
    }

    if (m_showConfirmation) {
        window.draw(m_confirmBox);
        if (m_confirmText.has_value()) window.draw(m_confirmText.value());
    }


    if (m_student.GetMentalState() <= -150.f) {
        window.draw(m_deadInsideBox);
        if (m_deadInsideText.has_value()) window.draw(m_deadInsideText.value());
    }

    if (m_student.GetKnowledge() >= 200.f) {
        window.draw(m_megamindBox);
        if (m_megamindText.has_value()) window.draw(m_megamindText.value());
    }
    
}

void RoomState::InitUI() {
    m_statsBox.setSize({140.f, 90.f});
    m_statsBox.setFillColor(sf::Color(0, 0, 0, 150));
    m_statsBox.setOutlineColor(sf::Color::White);
    m_statsBox.setOutlineThickness(2.f);

    float statsBoxY = m_hint->getPosition().y + m_hint->getGlobalBounds().size.y + 15.f;
    m_statsBox.setPosition({0.f, calculateStatsBoxY()});

    if (m_energyUI.has_value()) {
        m_energyUI->setFillColor(sf::Color::White);
        m_energyUI->setPosition({10.f, calculateStatsBoxY() + 15.f});
    }
    if (m_knowledgeUI.has_value()) {
        m_knowledgeUI->setFillColor(sf::Color::Yellow);
        m_knowledgeUI->setPosition({10.f, calculateStatsBoxY() + 30.f});
    }
    if (m_mentalUI.has_value()) {
        m_mentalUI->setFillColor(sf::Color(0, 200, 0));
        m_mentalUI->setPosition({10.f, calculateStatsBoxY() + 45.f});
    }
    if (m_timeUI.has_value()) {
        m_timeUI->setFillColor(sf::Color::Cyan);
        m_timeUI->setPosition({10.f, calculateStatsBoxY() + 60.f});
    }


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

void RoomState::UpdateUI() {
    if (m_energyUI.has_value())
        m_energyUI->setString("Energy: " + std::to_string(static_cast<int>(m_student.GetEnergy())));
    
    if (m_knowledgeUI.has_value())
        m_knowledgeUI->setString("Knowledge: " + std::to_string(static_cast<int>(m_student.GetKnowledge())));
    
    if (m_mentalUI.has_value())
        m_mentalUI->setString("Mental state: " + std::to_string(static_cast<int>(m_student.GetMentalState())));

    if (m_timeUI.has_value()) {
        m_timeUI->setString("Time: " + m_student.GetTimeString());
    }
   }


std::string RoomState::getHintForRoom() const {
    const auto config = getRoomConfig(currentRoom);
    return std::string(config.hint);
}

void RoomState::performRoomAction(float dt) {
    RoomAction action = getRoomAction();
    
    std::visit([dt](auto&& func) {
        if constexpr (std::is_invocable_v<decltype(func), float>) {
            func(dt);
        }
    }, action);
    
    m_actionTimer += dt;
    if (static_cast<int>(m_actionTimer * 10) % 2 == 0) {
        m_hint->setFillColor(sf::Color::White);
    } else {
        m_hint->setFillColor(sf::Color::Yellow);
    }
}

float RoomState::calculateStatsBoxY() const {
    if (m_hint.has_value()) {
        return m_hint->getPosition().y + m_hint->getGlobalBounds().size.y + 15.f;
    }
    return 110.f;
}

RoomAction RoomState::getRoomAction() const {
    if (!m_roomActionImpl) {
        return std::monostate{};
    }

    return RoomAction{
        std::function<void(float)>(
            [impl = m_roomActionImpl.get(), this](float dt) {
                impl->Apply(m_student, dt);
            }
        )
    };
}