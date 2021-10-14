#include <iostream>
#include <SFML/Graphics.hpp>
#include <pbengine.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    //if (!initEngine(window)) {
    //    std::cerr << "Engine Error" << std::endl;
    //}
    Engine engine(window);
    return 0;
}