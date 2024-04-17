#include "QSFMLCanvas.hpp"

class MyCanvas : public QSFMLCanvas
{
public :

    MyCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size)
    {

    }

private :

    void OnInit()
    {
        // Load the texture
        myTexture.loadFromFile("test.png");

        // Setup the sprite
        mySprite.setTexture(myTexture);
        mySprite.setOrigin(mySprite.getScale() / 2.f);
    }

    void OnUpdate()
    {
        // Clear screen
        sf::RenderWindow::clear(sf::Color(0, 128, 0));

        // Rotate the sprite
        mySprite.rotate(0.01f);

        // Draw it
        draw(mySprite);
    }

    sf::Texture myTexture;
    sf::Sprite  mySprite;
};
