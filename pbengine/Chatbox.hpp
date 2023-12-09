#include <SFML/Graphics.hpp>
#include <vector>

class Chatbox : public sf::Drawable, public sf::Transformable
{
public:
	Chatbox();
	~Chatbox();

	void addMessage(sf::String message);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<sf::String> m_messages;
	sf::Font m_font;
	sf::RectangleShape m_frame;
};
