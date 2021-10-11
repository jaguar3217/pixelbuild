#include <iostream>
#include <SFML/Graphics.hpp>
#include <libpbengine.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    if (!initEngine(window)) {
        std::cerr << "Engine Error" << std::endl;
    }
    return 0;
}