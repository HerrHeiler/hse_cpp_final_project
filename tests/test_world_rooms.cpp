#include <gtest/gtest.h>
#include "Door.hpp"
#include "Student.hpp"
#include <SFML/Graphics.hpp>

TEST(WorldRoomsTest, DoorInitialization) {
    sf::FloatRect bounds({10.f, 20.f}, {100.f, 200.f});
    sf::Font font; 
    Door door(bounds, RoomType::Lecture, "lecture room", font);
    
    EXPECT_EQ(door.target, RoomType::Lecture);
    EXPECT_EQ(door.label, "lecture room");
    EXPECT_FLOAT_EQ(door.shape.getPosition().x, 10.f);
}

 
TEST(WorldRoomsTest, LectureRoomEnvironmentLogic) {
    sf::Texture tex;
    Student student(tex);
    
    float initialKnowledge = student.GetKnowledge();
    float initialEnergy = student.GetEnergy();
    student.UpdateEnvironment(RoomType::Lecture, 1.0f);

    EXPECT_FLOAT_EQ(student.GetKnowledge(), initialKnowledge + 3.0f);
    EXPECT_FLOAT_EQ(student.GetEnergy(), initialEnergy - 2.0f);
}



TEST(WorldRoomsTest, StatsLimitsAreEnforced) {
    sf::Texture tex;
    Student student(tex);
    
    student.ModifyStats(-500.f, 0.f, 0.f);
    EXPECT_FLOAT_EQ(student.GetEnergy(), 0.f); 
    
    student.ModifyStats(0.f, 0.f, 500.f);
    EXPECT_FLOAT_EQ(student.GetMentalState(), 150.f); 
    
    student.ModifyStats(0.f, 0.f, -1000.f);
    EXPECT_FLOAT_EQ(student.GetMentalState(), -150.f); 
}