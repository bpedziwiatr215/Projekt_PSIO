#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <SFML/Graphics.hpp>
class EnemyBullet
{
public:
    EnemyBullet(sf::Vector2f size)
    {
        bullet2.setSize(size);
        bullet2.setFillColor(sf::Color::Magenta);
    }

    void fire(float speed)
    {
        bullet2.move(0, speed);
    }

    int getRight()
    {
        return bullet2.getPosition().x + bullet2.getSize().x;
    }

    int getLeft()
    {
        return bullet2.getPosition().x;
    }

    int getTop()
    {
        return bullet2.getPosition().y;
    }

    int getBottom()
    {
        return bullet2.getPosition().y + bullet2.getSize().y;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(bullet2);
    }

    void setPos(sf::Vector2f newPos)
    {
        bullet2.setPosition(newPos);
    }

private:
sf::RectangleShape bullet2;
};
#endif // ENEMYBULLET_H
