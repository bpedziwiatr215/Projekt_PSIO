#ifndef T90_H
#define T90_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include <vector>
#include <Player.h>
class enemy :public sf::Sprite
{
public:
    enemy(const sf::Vector2f &position) : sf::Sprite()
    {
        S.setPosition(position);
    }
    void setPos(sf::Vector2f newPos) {
        S.setPosition(newPos);
    }
    void setTexture(std::string filename)
    {
       t.loadFromFile(filename);
       S.setTexture(t);
    }
    void changecourse()
    {

        velocity_x = velocity_x * -1;
    }
    void movement( sf::Time elapsed)
    {


            S.move(velocity_x*elapsed.asSeconds(),0);



    }

    int getX() {
        return S.getPosition().x;
    }

    int getY() {
        return S.getPosition().y;
    }
    int health = 100;
    int checkColl(Bullet bullet)
    {   bool Destroyed=false;
        if (S.getGlobalBounds().contains(bullet.getRight(), bullet.getBottom()))
        {

            health=health-1;
            if(health<0&&Destroyed==false)
            {
                t.loadFromFile("Images/explo.png");
                S.setTexture(t);
                S.setPosition(10000000000,1000000000);
                bullet.setPos(sf::Vector2f(-100000000,-1000000000));
                return 100;
                Destroyed=true;
            }
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(S);
    }
private:
    sf::Texture t;
    sf::Sprite S;

    float velocity_x=100;
};
#endif // T90_H
