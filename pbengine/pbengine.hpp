#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Player.hpp>
#include <states.hpp>

#ifndef PBENGINE_H
#define PBENGINE_H
class Engine {
public:
    Engine();
    ~Engine();
    void SetTex(sf::RenderTexture* texture);
    void Render();
    void Move(int state);
private:
    sf::RenderTexture* m_texture;
    sf::Texture m_text;
    Player m_plr;
};
#endif