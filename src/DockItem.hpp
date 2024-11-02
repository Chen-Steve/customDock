#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>

class DockItem {
private:
    sf::Sprite icon;
    sf::Text label;
    float originalScale;
    float currentScale;
    bool isHovered;
    std::string execPath;
    sf::Vector2f position;

public:
    DockItem(const sf::Texture& texture, const std::string& labelText, 
             const std::string& executablePath, const sf::Font& font);
    void update(float mouseX, float mouseY);
    void draw(sf::RenderWindow& window);
    void launch() const;
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& pos);
}; 