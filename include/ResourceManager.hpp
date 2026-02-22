#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    const sf::Texture& GetTexture(const std::string& id);
    const sf::Font&    GetFont(const std::string& id);

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font>    m_fonts;

    void LoadTexture(const std::string& id);
    void LoadFont(const std::string& id);
};
