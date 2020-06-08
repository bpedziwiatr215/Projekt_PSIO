#ifndef SPAWNER_H
#define SPAWNER_H
#include <vector>
#include <Enemy.h>

std::vector<enemy> SpawnWave1() //przygotowanie obcych
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

sf::Text TextGenerator(std::string StartingText,float TextSize,sf::Color TextColor, float x, float y) //przygotowanie takstu
{
    sf::Text TextToGenerate;
    TextToGenerate.setString(StartingText);
    TextToGenerate.setCharacterSize(TextSize);
    TextToGenerate.setFillColor(TextColor);
    TextToGenerate.setPosition(x, y);
    return TextToGenerate;
}

#endif // SPAWNER_H
