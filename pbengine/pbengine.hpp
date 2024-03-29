#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Player.hpp>
#include "Chatbox.hpp"
#include <states.hpp>
#include <TileMap.hpp>

#ifndef PBENGINE_H
#define PBENGINE_H
class Engine {
public:
    Engine();
    ~Engine();
    void SetTex(sf::RenderTexture* texture);
    void SetLevel(char level[]);
    void Render();
    void BindPlrList(std::vector<Player*> plrlist);
    void Move(int state);
    void Speed(int speed);
	void HidePlayer();
	void ShowPlayer();
	void HideChatbox();
	void ShowChatbox();
	void MoveView(int ox, int oy);
    void SetMapSize(int width, int height);
	void SetViewToPlayer();
	void ResetView();
    int GetSpeed();
    int GetX();
    int GetY();
	int GetFrame();
	sf::Vector2i GetTileMapOffset();
private:
    sf::RenderTexture* m_texture;
	sf::View m_view;
    sf::Texture m_text;
    sf::Time m_elapsed;
    sf::Time m_elapsed_global;
    sf::Clock m_clock;
    sf::Clock m_clock_global;
    Player m_plr;
    std::vector<Player*> m_plrlist;
    TileMap m_tilemap;
    Chatbox m_chatbox;
    int m_speed = 100;
	bool m_showPlayer = true;
	bool m_viewEnabled = false;
	bool m_showChatbox = false;
    char* m_level;
    int m_levelW, m_levelH;
};
#endif
