#include <iostream>
#include <SFML/Graphics.hpp>
#include <pbengine.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    window.setActive(false);
    Engine engine(window);
    return 0;
}