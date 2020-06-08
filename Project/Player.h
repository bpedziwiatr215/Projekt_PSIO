#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <EnemyBullet.h>
class Player :public sf::Sprite {
public:
    Player(const sf::Vector2f &position, const std::string &filename):sf::Sprite()
    {
        player.setPosition(position);
        t1.loadFromFile(filename);
        player.setTexture(t1);
    }

    void animate(sf::Time elapsed)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.move(sf::Vector2f(0, -moveSpeed * elapsed.asSeconds()));
            bounce(elapsed, moveSpeed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.move(sf::Vector2f(0, moveSpeed * elapsed.asSeconds()));
            bounce(elapsed, moveSpeed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
           player.move(sf::Vector2f(-moveSpeed * elapsed.asSeconds(), 0));
           bounce(elapsed, moveSpeed);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
           player.move(sf::Vector2f(moveSpeed * elapsed.asSeconds(), 0));
           bounce(elapsed, moveSpeed);
        }
    }

    void bounce(const sf::Time &elapsed, float movespeed)
    {
        auto bounds = player.getGlobalBounds();
        if (bounds.left + bounds.width > 1920)
        {
            player.move(-movespeed * elapsed.asSeconds(), 0);
        }


        if (bounds.left < 0)
        {
            player.move(movespeed * elapsed.asSeconds(),0);
        }

        if (bounds.top < 600)
        {
            player.move(0, movespeed * elapsed.asSeconds());
        }
        if (bounds.top + bounds.height > 1080)
        {
            player.move(0, -movespeed * elapsed.asSeconds());
        }
    }

//------------------------------------------------------------------
    int getX()
    {
        return player.getPosition().x;
    }

    int getY()
    {
        return player.getPosition().y;
    }
    int GetHealth()
    {
        return health;
    }

    void Heal()
    {
        health=health+1;
    }

    void Boost()
    {
       moveSpeed=moveSpeed+50;
    }
//---------------------------------------------------------------------

    bool checkColl(EnemyBullet bullet)
    {
       if (player.getGlobalBounds().contains(bullet.getRight(), bullet.getBottom()))
        {
            health=health-1;
           return true;
        }
       return false;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(player);
    }

int score=0;
private:
    sf::Texture t1;
    sf::Sprite player;
    int health=10;
    float moveSpeed =500;
};
#endif // PLAYER_H
