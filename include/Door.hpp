#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "RoomType.hpp"

struct Door {
    sf::FloatRect bounds;
    RoomType target;
    std::string label;
    sf::RectangleShape shape;
    sf::Text text;

    Door(const Door&) = default;
    Door& operator=(const Door&) = default;
    Door(Door&&) = default;
    Door& operator=(Door&&) = default;
    
    Door(sf::FloatRect b, RoomType t, std::string l, const sf::Font& font)
        : bounds(b), 
          target(t), 
          label(l),
          shape(b.size),
          text(font, l, 16)
    {
        shape.setPosition(b.position);
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2.f);
        
        text.setFillColor(sf::Color::White);
        sf::FloatRect tb = text.getLocalBounds();
        text.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
        text.setPosition({
            b.position.x + b.size.x / 2.f, 
            b.position.y + b.size.y / 2.f
        });
    }
};