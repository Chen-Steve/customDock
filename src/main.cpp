#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dock.hpp"

int main() {
    std::cout << "Starting application..." << std::endl;
    
    try {
        Dock dock;
        
        // Test with just the window first, no icons
        dock.run();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "Unknown error occurred" << std::endl;
        return 1;
    }
    
    return 0;
} 