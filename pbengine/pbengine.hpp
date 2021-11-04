#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#ifndef PBENGINE_H
#define PBENGINE_H
class Engine {
public:
    Engine()
    : m_thread(&Engine::Init, this)
    {
    }
    void SetTex(sf::RenderTexture* texture);
    void Render();
private:
    void Init();
    sf::Thread m_thread;
    sf::RenderTexture* m_texture;
};
#endif