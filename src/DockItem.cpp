#include "DockItem.hpp"
#include <cmath>
#include <cstddef>

DockItem::DockItem(const sf::Texture& texture, const std::string& labelText, 
                   const std::string& executablePath, const sf::Font& font) {
    icon.setTexture(texture);
    
    // Set initial scale and origin
    originalScale = 48.0f / texture.getSize().x;
    icon.setScale(originalScale, originalScale);
    icon.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    
    // Setup label
    label.setFont(font);
    label.setString(labelText);
    label.setCharacterSize(12);
    label.setFillColor(sf::Color::White);
    
    execPath = executablePath;
    isHovered = false;
    currentScale = originalScale;
}

void DockItem::update(float mouseX, float mouseY) {
    sf::FloatRect bounds = icon.getGlobalBounds();
    
    // Calculate distance for magnification effect
    float distance = std::abs(mouseX - (bounds.left + bounds.width / 2.0f));
    float maxDistance = 100.0f;
    
    if (distance < maxDistance) {
        float scale = 1.0f - (distance / maxDistance);
        currentScale = originalScale * (1.0f + scale * 0.5f);
    } else {
        currentScale = originalScale;
    }
    
    icon.setScale(currentScale, currentScale);
}

void DockItem::launch() const {
    #ifdef _WIN32
        ShellExecuteA(NULL, "open", execPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    #else
        system(execPath.c_str());
    #endif
}

void DockItem::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
    icon.setPosition(position);
    
    // Center the label above the icon
    label.setPosition(
        position.x - label.getLocalBounds().width / 2.0f,
        position.y - icon.getGlobalBounds().height / 2.0f - label.getLocalBounds().height - 5
    );
}

void DockItem::setPosition(const sf::Vector2f& pos) {
    setPosition(pos.x, pos.y);
}

void DockItem::draw(sf::RenderWindow& window) {
    window.draw(icon);
    if (isHovered) {
        window.draw(label);
    }
}

sf::FloatRect DockItem::getBounds() const {
    return icon.getGlobalBounds();
} 