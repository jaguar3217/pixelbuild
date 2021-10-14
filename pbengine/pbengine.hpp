#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef PBENGINE_H
#define PBENGINE_H
bool initEngine(sf::RenderWindow& window);
class Engine {
public:
    Engine(sf::RenderWindow& window);
};
#endif