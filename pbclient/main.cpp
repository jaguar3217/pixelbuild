#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <pbengine.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 256), "Pixelbuild");
    window.setActive(true);
    sf::RenderTexture texture;
    if (!texture.create(512, 256, true)) // enable depth buffer
    {
        std::cerr << "[main] Cannot create sf::RenderTexture\n";
    }
    Engine engine;
    engine.SetTex(&texture);
    std::cout << "code after Engine init\n";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        engine.Render();
        const sf::Texture& _texture = texture.getTexture();
        sf::Sprite sprite(_texture);
        window.draw(sprite);
        window.display();
    }
    return 0;
}