#include <iostream>
#include <SFML/Graphics.hpp>
#include <pbengine.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    window.setActive(false);
    //if (!initEngine(window)) {
    //    std::cerr << "Engine Error" << std::endl;
    //}
    Engine engine(window);
    window.close();
    return 0;
}