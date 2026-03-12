#include <gtest/gtest.h>
#include "Student.hpp"
#include <SFML/Graphics.hpp>

TEST(WorldTimeTest, InitialTimeIsCorrect) {
    sf::Texture dummyTex; 
    Student student(dummyTex);
    EXPECT_EQ(student.GetTimeString(), "09:30");
}

TEST(WorldTimeTest, AddTimeWorks) {
    sf::Texture dummyTex;
    Student student(dummyTex);
    
    student.AddTime(80.f); 
    EXPECT_EQ(student.GetTimeString(), "10:50");
}

TEST(WorldTimeTest, TimeOverMidnight) {
    sf::Texture dummyTex;
    Student student(dummyTex);
    student.AddTime(900.f); 
    EXPECT_EQ(student.GetTimeString(), "00:30");
}


TEST(WorldTimeTest, ResetStatsRestoresTime) {
    sf::Texture dummyTex;
    Student student(dummyTex);
    student.AddTime(300.f); 
    EXPECT_NE(student.GetTimeString(), "09:30");
    student.ResetStats();
    EXPECT_EQ(student.GetTimeString(), "09:30");
}