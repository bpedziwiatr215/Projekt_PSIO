#ifndef FORMATION_H
#define FORMATION_H
#include <SFML/Graphics.hpp>
#include <iostream>
class formation : public sf::RectangleShape {
public:
    formation(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size) {
        setPosition(position);
   }

    void animate(sf::Time elapsed)
    {
        move(sf::Vector2f(moveSpeed * elapsed.asSeconds(),0));
    }


    bool borders()
    {

            auto bounds = getGlobalBounds();
            std::cout<<bounds.left<<std::endl;


            if (bounds.left + bounds.width > 1920)
            {
                moveSpeed=moveSpeed*-1;

                return true;

            }
            if (bounds.left < 0)
            {
                    moveSpeed=moveSpeed*-1;

                    return true;

            }
    }


private:

   float moveSpeed =100;
    sf::RectangleShape box;
    float position =100;

};
#endif // FORMATION_H
