#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    void LoadFont(const std::string& id);
    void LoadTexture(const std::string& id);

    const sf::Texture& GetTexture(const std::string& id);
    //sf::Texture& GetTexture(const std::string& id);
    const sf::Font& GetFont(const std::string& id);

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Font> m_fonts;
};
