#pragma once
#include "RoomType.hpp"
#include <string_view>
#include <functional>

struct RoomConfig {
    std::string_view name;
    std::string_view hint;
    float energyMod;
    float knowledgeMod;
    float moodMod;
};

constexpr RoomConfig getRoomConfig(RoomType type) {
    switch (type) {
        case RoomType::Home:
            return {"Home Apartment", "Press SPACE to rest\n(+Energy, +Mood)", 12.0f, 0.0f, 8.0f};
        case RoomType::Lecture:
            return {"Lecture Hall", "Press SPACE to study\n(+Knowledge, -Energy)", -8.0f, 10.0f, -2.0f};
        case RoomType::Seminar:
            return {"Seminar Room", "Press SPACE to work\n(+Knowledge, --Energy)", -15.0f, 20.0f, -3.0f};
        case RoomType::Cafeteria:
            return {"Cafeteria", "Press SPACE to eat\n(+Energy, -Mood)", 15.0f, 0.0f, -1.0f};
        case RoomType::Corridor:
        default:
            return {"Corridor", "Walk to a room", -0.5f, 0.0f, 0.0f};
    }
}

constexpr bool isValidTextureId(std::string_view id) {
    return id == "corridor" || id == "student" || id == "lecture_bg" ||
           id == "home_room" || id == "seminar_room" || id == "cafeteria_room";
}

constexpr std::string_view getTextureIdForRoom(RoomType type) {
    switch (type) {
        case RoomType::Home: return "home_room";
        case RoomType::Lecture: return "lecture_bg";
        case RoomType::Seminar: return "seminar_room";
        case RoomType::Cafeteria: return "cafeteria_room";
        case RoomType::Corridor:
        default: return "corridor";
    }
}