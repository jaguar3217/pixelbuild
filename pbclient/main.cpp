#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <pbengine.hpp>
#include <states.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    sf::RenderTexture texture;
    if (!texture.create(512, 256, true)) // enable depth buffer
    {
        std::cerr << "[main] Cannot create sf::RenderTexture\n";
    }
    Engine engine;
    engine.SetTex(&texture);
    std::cout << "code after Engine declaration\n";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            engine.Move(PLAYER_UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            engine.Move(PLAYER_LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            engine.Move(PLAYER_DOWN);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            engine.Move(PLAYER_RIGHT);
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
        window.display();
    }
    return 0;
}