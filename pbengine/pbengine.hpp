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
    void BindPlrList(std::vector<Player*> plrlist);
    void Move(int state);
    void Speed(int speed);
    int GetSpeed();
    int GetX();
    int GetY();
private:
    sf::RenderTexture* m_texture;
    sf::Texture m_text;
    sf::Time m_elapsed;
    sf::Time m_elapsed_global;
    sf::Clock m_clock;
    sf::Clock m_clock_global;
    Player m_plr;
    std::vector<Player*> m_plrlist;
    int m_speed = 100;
};
#endif