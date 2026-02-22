#include <ResourceManager.hpp>

void ResourceManager::LoadTexture(const std::string& id) {
    sf::Texture texture;

    if (id == "corridor") {
        if (!texture.loadFromFile("assets/textures/corridor.png"))
            throw std::runtime_error("Error while loading 'corridor.png' file occured");
    } else if (id == "student") {
        if (!texture.loadFromFile("assets/textures/student.png"))
            throw std::runtime_error("Error while loading 'student.png' file occured");
    } else {
            throw std::runtime_error("Error incorrect id of texture" + id);
    }

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
