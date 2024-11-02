cmake_minimum_required(VERSION 3.10)
project(WindowsDock)

set(CMAKE_CXX_STANDARD 17)

# Set SFML path
set(SFML_DIR "C:/Users/Asus/Documents/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(WindowsDock 
    src/main.cpp
    src/Dock.cpp
    src/DockItem.cpp
)

target_link_libraries(WindowsDock 
    sfml-graphics
    sfml-window
    sfml-system
)