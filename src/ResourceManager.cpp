#include "ResourceManager.hpp"
#include <filesystem>
#include <stdexcept>

void ResourceManager::LoadTexture(const std::string& id) {
    sf::Texture texture;

    std::filesystem::path path;
    if (id == "corridor") {
        path = "assets/textures/corridor.png";
    } else if (id == "student") {
        path = "assets/textures/student.png";
    } else if (id == "lecture_bg") {
        path = "assets/textures/lecture.png";
    } else if (id == "home_room") {
        path = "assets/textures/home_room.png";
    } else if (id == "seminar_room") {
        path = "assets/textures/seminar_room.png";
    } else if (id == "cafeteria_room") {
        path = "assets/textures/cafeteria_room.png";
    } else if (id == "pet") {
        path = "assets/textures/pet.png";
    } else {
        throw std::runtime_error("Error: incorrect texture id: " + id);
    }

    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Error while loading '" + path.string() + "'");
    }

    texture.setSmooth(true);

    m_textures.emplace(id, std::move(texture));
}

const sf::Texture& ResourceManager::GetTexture(const std::string& id) {
    auto it = m_textures.find(id);
    if (it == m_textures.end()) {
        LoadTexture(id);
        it = m_textures.find(id);
    }
    return it->second;
}

void ResourceManager::LoadFont(const std::string& id) {
    sf::Font font;
    
    if (id == "default") {
        std::filesystem::path path = "assets/fonts/OpenSans-Light.ttf";
        if (!font.openFromFile(path)) {
            throw std::runtime_error("Error while loading '" + path.string() + "'");
        }
    } else {
        throw std::runtime_error("Error: incorrect font id: " + id);
    }
    
    m_fonts.emplace(id, std::move(font));
}

const sf::Font& ResourceManager::GetFont(const std::string& id) {
    auto it = m_fonts.find(id);
    if (it == m_fonts.end()) {
        LoadFont(id);
        it = m_fonts.find(id);
    }
    return it->second;
}