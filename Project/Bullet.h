#ifndef BULLET_H
#define BULLET_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include "T-90.h"
class Bullet {
public:
    Bullet(sf::Vector2f size) {
        bullet.setSize(size);
        bullet.setFillColor(sf::Color::Yellow);
    }

    void fire(int speed) {
        bullet.move(0, -speed);
    }

    int getRight() {
        return bullet.getPosition().x + bullet.getSize().x;
    }

    int getLeft() {
        return bullet.getPosition().x;
    }

    int getTop() {
        return bullet.getPosition().y;
    }

    int getBottom() {
        return bullet.getPosition().y + bullet.getSize().y;
    }

    void draw(sf::RenderWindow &window) {
        window.draw(bullet);
    }

    void setPos(sf::Vector2f newPos) {
        bullet.setPosition(newPos);
    }

   // void checkColl(enemy enemy) {
//        if (enemy.getGlobalBounds().contains(getRight(),getBottom()))
   //     {
      //      setPos(sf::Vector2f(-100000000,-1000000000));
     //   }
 //   }
sf::RectangleShape bullet;

private:

};
#endif // BULLET_H
