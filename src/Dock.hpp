#pragma once

#include <SFML/Graphics.hpp>
#include "DockItem.hpp"

class Dock {
private:
    std::vector<DockItem> items;
    sf::RenderWindow window;
    sf::RectangleShape background;
    sf::Font font;

public:
    Dock();
    void run();
    void addItem(const std::string& iconPath, const std::string& label, 
                 const std::string& execPath);
private:
    void handleEvents();
    void update();
    void render();
}; 