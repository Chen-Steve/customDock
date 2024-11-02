#include "Dock.hpp"
#include <iostream>

Dock::Dock() {
    // Create window at bottom of screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(800, 70), "Dock",
                 sf::Style::None | sf::Style::Titlebar);

    // Position window at bottom center of screen
    window.setPosition(sf::Vector2i(
        (desktop.width - window.getSize().x) / 2,
        desktop.height - window.getSize().y - 10
    ));

    // Setup semi-transparent background
    background.setSize(sf::Vector2f(window.getSize()));
    background.setFillColor(sf::Color(255, 255, 255, 40));

    // Load font with error checking
    if (!font.loadFromFile("resources/font.ttf")) {
        std::cout << "Error loading font from resources/font.ttf" << std::endl;
        exit(1);
    }
    std::cout << "Font loaded successfully" << std::endl;
}

void Dock::addItem(const std::string& iconPath, const std::string& label,
                   const std::string& execPath) {
    sf::Texture texture;
    if (!texture.loadFromFile(iconPath)) {
        std::cout << "Error loading texture from " << iconPath << std::endl;
        return;
    }
    std::cout << "Loaded texture: " << iconPath << std::endl;

    items.emplace_back(texture, label, execPath, font);

    // Arrange items
    float spacing = 10.0f;
    float startX = (window.getSize().x -
                   (items.size() * 48 + (items.size() - 1) * spacing)) / 2;

    for (size_t i = 0; i < items.size(); ++i) {
        float x = startX + i * (48 + spacing);
        items[i].setPosition(x, window.getSize().y / 2);
    }
}

void Dock::run() {
    std::cout << "Starting dock application..." << std::endl;
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Dock::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto& item : items) {
                if (item.getBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    item.launch();
                }
            }
        }
    }
}

void Dock::update() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    for (auto& item : items) {
        item.update(mousePos.x, mousePos.y);
    }
}

void Dock::render() {
    window.clear(sf::Color::Transparent);
    window.draw(background);

    for (auto& item : items) {
        item.draw(window);
    }

    window.display();
}
