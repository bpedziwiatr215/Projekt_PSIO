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
    enemy(const sf::Vector2f &position, int hp) : sf::Sprite()
    {
        S.setPosition(position);
       SetHp(hp);
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
    void SetHp(int hp)
    {
        health=hp;
    }

    float GetVelocity()
    {
        return velocity_x;
    }

    int getX() {
        return S.getPosition().x;
    }

    int getY() {
        return S.getPosition().y;
    }
    int health = 1;
    bool checkColl(Bullet bullet)
    {
        if (S.getGlobalBounds().contains(bullet.getRight(), bullet.getBottom()))
        {

            health=health-1;
            if(health<=0)
            {
                t.loadFromFile("Images/explo.png");
                S.setTexture(t);
                S.setPosition(10000000000,1000000000);


            }
            return true;
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
