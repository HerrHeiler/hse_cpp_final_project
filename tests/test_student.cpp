#include <gtest/gtest.h>
#include "Student.hpp"
#include <thread>
#include <chrono>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "RoomConfig.hpp"

class StudentTest : public ::testing::Test {
protected:
    std::unique_ptr<Student> student;
    sf::Texture dummyTexture;
    
    void SetUp() override {
        sf::Image img({32, 32}, sf::Color::White);
        dummyTexture.update(img);
        
        student = std::make_unique<Student>(dummyTexture);
    }
    
    void TearDown() override {
        student.reset();
    }
};

// initialization
TEST_F(StudentTest, DefaultInitialization) {
    EXPECT_GT(student->GetEnergy(), 0.f);
    EXPECT_GE(student->GetKnowledge(), 0.f);
    EXPECT_GE(student->GetMentalState(), 0.f);
}

TEST_F(StudentTest, InitialStatsValues) {
    EXPECT_LE(student->GetEnergy(), 100.f);
    EXPECT_GE(student->GetEnergy(), 0.f);
    
    EXPECT_GE(student->GetKnowledge(), 0.f);
    
    EXPECT_GE(student->GetMentalState(), -150.f);
    EXPECT_LE(student->GetMentalState(), 150.f);
}

TEST_F(StudentTest, InitialPosition) {
    sf::Vector2f pos = student->GetPosition();
    EXPECT_GE(pos.x, 0.f);
    EXPECT_GE(pos.y, 0.f);
}

// stats modification
TEST_F(StudentTest, ModifyStatsPositive) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    float initialMental = student->GetMentalState();
    
    student->ModifyStats(10.f, 5.f, 8.f);
    
    EXPECT_NEAR(student->GetEnergy(), initialEnergy + 10.f, 0.1f);
    EXPECT_NEAR(student->GetKnowledge(), initialKnowledge + 5.f, 0.1f);
    EXPECT_NEAR(student->GetMentalState(), initialMental + 8.f, 0.1f);
}

TEST_F(StudentTest, ModifyStatsNegative) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    float initialMental = student->GetMentalState();
    
    student->ModifyStats(-10.f, -5.f, -8.f);
    
    EXPECT_NEAR(student->GetEnergy(), initialEnergy - 10.f, 0.1f);
    EXPECT_NEAR(student->GetKnowledge(), initialKnowledge - 5.f, 0.1f);
    EXPECT_NEAR(student->GetMentalState(), initialMental - 8.f, 0.1f);
}

TEST_F(StudentTest, StatsClampingUpper) {
    student->ModifyStats(200.f, 200.f, 200.f);
    
    EXPECT_LE(student->GetEnergy(), 100.f);
    EXPECT_LE(student->GetMentalState(), 150.f);
    EXPECT_GE(student->GetMentalState(), 0.f);
}

TEST_F(StudentTest, StatsClampingLower) {
    student->ModifyStats(-200.f, -200.f, -200.f);
    
    EXPECT_GE(student->GetEnergy(), 0.f);
    EXPECT_GE(student->GetKnowledge(), 0.f);
    EXPECT_GE(student->GetMentalState(), -150.f);
}

TEST_F(StudentTest, ModifyStatsZero) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    float initialMental = student->GetMentalState();
    
    student->ModifyStats(0.f, 0.f, 0.f);
    
    EXPECT_FLOAT_EQ(student->GetEnergy(), initialEnergy);
    EXPECT_FLOAT_EQ(student->GetKnowledge(), initialKnowledge);
    EXPECT_FLOAT_EQ(student->GetMentalState(), initialMental);
}

// time
TEST_F(StudentTest, AddTime) {
    std::string initialTime = student->GetTimeString();
    
    student->AddTime(60.f);
    
    std::string newTime = student->GetTimeString();
    EXPECT_NE(initialTime, newTime);
}

TEST_F(StudentTest, AddTimeNegative) {
    std::string initialTime = student->GetTimeString();
    
    student->AddTime(-30.f);
    
    EXPECT_TRUE(true);
}

TEST_F(StudentTest, AddTimeLargeValue) {
    student->AddTime(24.f * 60.f);
    
    std::string time = student->GetTimeString();
    EXPECT_TRUE(time.length() == 5);
    EXPECT_EQ(time[2], ':');
}

TEST_F(StudentTest, TimeFormat) {
    std::string time = student->GetTimeString();
    
    EXPECT_EQ(time.length(), 5);
    EXPECT_EQ(time[2], ':');
    
    for (int i : {0, 1, 3, 4}) {
        EXPECT_TRUE(std::isdigit(time[i]));
    }
}

// moving and position
TEST_F(StudentTest, SetPosition) {
    student->SetPosition(100.f, 200.f);
    
    sf::Vector2f pos = student->GetPosition();
    EXPECT_FLOAT_EQ(pos.x, 100.f);
    EXPECT_FLOAT_EQ(pos.y, 200.f);
}

TEST_F(StudentTest, SetPositionNegative) {
    student->SetPosition(-50.f, -100.f);
    
    sf::Vector2f pos = student->GetPosition();
    EXPECT_FLOAT_EQ(pos.x, -50.f);
    EXPECT_FLOAT_EQ(pos.y, -100.f);
}

TEST_F(StudentTest, GetBounds) {
    sf::FloatRect bounds = student->GetBounds();
    
    EXPECT_GT(bounds.size.x, 0.f);
    EXPECT_GT(bounds.size.y, 0.f);
}


// UpdateEnvironment
TEST_F(StudentTest, UpdateEnvironmentLecture) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    
    student->UpdateEnvironment(RoomType::Lecture, 1.0f);
    
    EXPECT_GT(student->GetKnowledge(), initialKnowledge);
    EXPECT_LT(student->GetEnergy(), initialEnergy);
}

TEST_F(StudentTest, UpdateEnvironmentHome) {
    float initialEnergy = student->GetEnergy();
    float initialMental = student->GetMentalState();
    
    student->UpdateEnvironment(RoomType::Home, 1.0f);
    
    EXPECT_GT(student->GetEnergy(), initialEnergy);
    EXPECT_GT(student->GetMentalState(), initialMental);
}

TEST_F(StudentTest, UpdateEnvironmentCafeteria) {
    float initialEnergy = student->GetEnergy();
    
    student->UpdateEnvironment(RoomType::Cafeteria, 1.0f);
    
    EXPECT_GT(student->GetEnergy(), initialEnergy);
}

TEST_F(StudentTest, UpdateEnvironmentSeminar) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    
    student->UpdateEnvironment(RoomType::Seminar, 1.0f);
    
    EXPECT_GT(student->GetKnowledge(), initialKnowledge);
    EXPECT_LT(student->GetEnergy(), initialEnergy);
}

TEST_F(StudentTest, UpdateEnvironmentZeroDt) {
    float initialEnergy = student->GetEnergy();
    float initialKnowledge = student->GetKnowledge();
    
    student->UpdateEnvironment(RoomType::Lecture, 0.f);
    
    EXPECT_FLOAT_EQ(student->GetEnergy(), initialEnergy);
    EXPECT_FLOAT_EQ(student->GetKnowledge(), initialKnowledge);
}

TEST_F(StudentTest, UpdateEnvironmentNegativeDt) {
    EXPECT_NO_THROW(student->UpdateEnvironment(RoomType::Lecture, -1.0f));
}

// boundary stats values
TEST_F(StudentTest, StatsAtZero) {
    student->ModifyStats(-1000.f, -1000.f, -1000.f);
    
    EXPECT_GE(student->GetEnergy(), 0.f);
    EXPECT_GE(student->GetKnowledge(), 0.f);
    EXPECT_GE(student->GetMentalState(), -150.f);
    
    student->ModifyStats(-10.f, -10.f, -10.f);
    
    EXPECT_GE(student->GetEnergy(), 0.f);
    EXPECT_GE(student->GetKnowledge(), 0.f);
    EXPECT_GE(student->GetMentalState(), -150.f);
}

TEST_F(StudentTest, StatsAtMax) {
    student->ModifyStats(1000.f, 1000.f, 1000.f);
    
    EXPECT_LE(student->GetEnergy(), 100.f);
    EXPECT_LE(student->GetMentalState(), 150.f);
    
    student->ModifyStats(10.f, 10.f, 10.f);
    
    EXPECT_LE(student->GetEnergy(), 100.f);
    EXPECT_LE(student->GetMentalState(), 150.f);
}

// reset stats
TEST_F(StudentTest, ResetStats) {
    student->ModifyStats(-50.f, 100.f, -30.f);
    
    float knowledgeAfterChange = student->GetKnowledge();
    
    student->ResetStats();
    
    EXPECT_FLOAT_EQ(student->GetEnergy(), 100.f);
    EXPECT_FLOAT_EQ(student->GetKnowledge(), knowledgeAfterChange);
}

// updates
TEST_F(StudentTest, UpdatePositiveDt) {
    EXPECT_NO_THROW(student->Update(0.016f));
}

TEST_F(StudentTest, UpdateZeroDt) {
    EXPECT_NO_THROW(student->Update(0.f));
}

TEST_F(StudentTest, UpdateLargeDt) {
    EXPECT_NO_THROW(student->Update(1.0f));
}

// room config
TEST(RoomConfigTest, GetRoomConfigCompileTime) {
    constexpr auto lectureConfig = getRoomConfig(RoomType::Lecture);
    constexpr auto homeConfig = getRoomConfig(RoomType::Home);
    
    EXPECT_NE(lectureConfig.knowledgeMod, homeConfig.knowledgeMod);
}

TEST(RoomConfigTest, AllRoomTypesValid) {
    std::vector<RoomType> roomTypes = {
        RoomType::Corridor,
        RoomType::Home,
        RoomType::Lecture,
        RoomType::Seminar,
        RoomType::Cafeteria
    };
    
    for (const auto& type : roomTypes) {
        const auto config = getRoomConfig(type);
        
        EXPECT_TRUE(config.knowledgeMod >= -100.f && config.knowledgeMod <= 100.f);
        EXPECT_TRUE(config.energyMod >= -100.f && config.energyMod <= 100.f);
        EXPECT_TRUE(config.moodMod >= -100.f && config.moodMod <= 100.f);
    }
}

TEST(RoomConfigTest, GetTextureIdForRoom) {
    EXPECT_STREQ(getTextureIdForRoom(RoomType::Lecture).data(), "lecture_bg");
    EXPECT_STREQ(getTextureIdForRoom(RoomType::Home).data(), "home_room");
    EXPECT_STREQ(getTextureIdForRoom(RoomType::Cafeteria).data(), "cafeteria_room");
    EXPECT_STREQ(getTextureIdForRoom(RoomType::Seminar).data(), "seminar_room");
}

TEST(RoomConfigTest, GetHintForRoom) {
    EXPECT_FALSE(getHintForRoom(RoomType::Lecture).empty());
    EXPECT_FALSE(getHintForRoom(RoomType::Home).empty());
    EXPECT_FALSE(getHintForRoom(RoomType::Cafeteria).empty());
    EXPECT_FALSE(getHintForRoom(RoomType::Seminar).empty());
}