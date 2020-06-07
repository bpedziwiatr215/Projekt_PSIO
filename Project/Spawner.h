#ifndef SPAWNER_H
#define SPAWNER_H
#include <vector>
#include <Enemy.h>



std::vector<enemy> SpawnWave1()
{
    std::vector<enemy> alienVec;
    for(int i=120; i<4800; i=i+120)
    {
        if(i>1200&&i<2400)
        {
          sf::Vector2f position(i-1320, 200);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i>2400&&i<3600)
        {
          sf::Vector2f position(i-2520, 300);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i>3600&&i<4800)
        {
          sf::Vector2f position(i-3720, 400);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i<1200)
        {
        sf::Vector2f position(i-120, 100);
        alienVec.emplace_back(enemy(position,3));
        }

    }
    for( auto &rec : alienVec)
    {
            rec.setTexture("Images/spaceship.png");
    }
    return alienVec;
}
std::vector<enemy> SpawnWave2()
{
    std::vector<enemy> alienVec;
    for(int i=120; i<4800; i=i+120)
    {
        if(i>1200&&i<2200)
        {
          sf::Vector2f position(i-1260, 200);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i>2200&&i<3100)
        {
          sf::Vector2f position(i-2160, 300);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i>3100&&i<3760)
        {
          sf::Vector2f position(i-2940, 400);
          alienVec.emplace_back(enemy(position,3));
        }
        if(i<1200)
        {
        sf::Vector2f position(i-120, 100);
        alienVec.emplace_back(enemy(position,3));
        }

    }
    for( auto &rec : alienVec)
    {
            rec.setTexture("Images/spaceship.png");
    }
    return alienVec;
}

#endif // SPAWNER_H
