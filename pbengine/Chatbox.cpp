#include "Chatbox.hpp"

Chatbox::Chatbox()
{
	m_frame.setSize(sf::Vector2f(198, 105));
	m_frame.move(8, 8);
	m_frame.setFillColor(sf::Color(0, 0, 0, 447));

	m_font.loadFromFile("/usr/share/fonts/TTF/JetBrainsMono-Regular.ttf");

	// Test code
	addMessage("[SERVER] Test 12345");
	addMessage("[SERVER] Test 67890");
}

Chatbox::~Chatbox()
{
}

void Chatbox::addMessage(sf::String message)
{
	m_messages.push_back(message);
}

void Chatbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_frame, states);
	if (m_messages.size() >= 10)
		for (int i = 0; i < 10; i++)
		{
			sf::Text text;
			text.setFont(m_font);
			text.setString(m_messages[m_messages.size() - 11 + i]);
			text.setCharacterSize(11);
			text.setFillColor(sf::Color::White);
			text.move(16, 16 + 11 * i);
			target.draw(text, states);
		}
	else
		for (int i = 0; i < m_messages.size(); i++)
		{
			sf::Text text;
			text.setFont(m_font);
			text.setString(m_messages[i]);
			text.setCharacterSize(11);
			text.setFillColor(sf::Color::White);
			text.move(16, 16 + 11 * i);
			target.draw(text, states);
		}
}
