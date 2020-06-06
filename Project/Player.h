#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <EnemyBullet.h>
class Player :public sf::Sprite {
public:
    Player(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &filename) : sf::Sprite()
    {
        player.setPosition(position);
        t1.loadFromFile(filename);
        player.setTexture(t1);

    }



    void bounce2(const sf::Time &elapsed, float movespeed)
    {
        auto bounds = player.getGlobalBounds();
        std::cout<<bounds.left<<std::endl;


        if (bounds.left + bounds.width > 1920&&sf::Keyboard::D)
        {
            player.move(-movespeed * elapsed.asSeconds(), 0);
        }


        if (bounds.left < 0&&sf::Keyboard::S)
        {
            player.move(movespeed * elapsed.asSeconds(),0);
        }

        if (bounds.top < 0&&sf::Keyboard::W)
        {
            player.move(0, movespeed * elapsed.asSeconds());
        }
        if (bounds.top + bounds.height > 1080&&sf::Keyboard::S)
        {
            player.move(0, -movespeed * elapsed.asSeconds());
        }
    }

    void animate2(sf::Time elapsed)
    {
        float moveSpeed =500;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.move(sf::Vector2f(0, -moveSpeed * elapsed.asSeconds()));
        bounce2(elapsed, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.move(sf::Vector2f(0, moveSpeed * elapsed.asSeconds()));
        bounce2(elapsed, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
       player.move(sf::Vector2f(-moveSpeed * elapsed.asSeconds(), 0));
       bounce2(elapsed, moveSpeed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
       player.move(sf::Vector2f(moveSpeed * elapsed.asSeconds(), 0));
       bounce2(elapsed, moveSpeed);
    }
    }

    int getX() {
        return player.getPosition().x;
    }

    int getY() {
        return player.getPosition().y;
    }

    void draw(sf::RenderWindow &window) {
        window.draw(player);
    }

    double checkColl(EnemyBullet bullet) {
       if (player.getGlobalBounds().contains(bullet.getRight(), bullet.getBottom()))
        {
            std::cout<<"Gracz Trafiony!"<<std::endl;
           bullet.setPos(sf::Vector2f(-100000000,-1000000000));
            health=health-1;
           if(health<0)
           {
            return -10;

           }
        }
    }
int score=0;
int health=100;
private:

    sf::Texture t1;
    sf::Sprite player;


};

#endif // PLAYER_H
