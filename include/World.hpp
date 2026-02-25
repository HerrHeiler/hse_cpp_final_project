#pragma once
#include "Student.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>

class World {
public:
    // world creation
    World(ResourceManager& resources);

    void Update(sf::Time dt);
    void Render(sf::RenderWindow& window);

private:
    ResourceManager& m_resources;          
};