#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "formation.h"
#include "EnemyBullet.h"
#include <vector>
#include <sstream>
#include <iomanip>
#include <Spawner.h>


int main()
{

    sf::Music music;

    if (!music.openFromFile("Sound/Main.wav"))
    {
        std::cout << "ERROR" << std::endl;
    }

    music.play();

    sf::SoundBuffer Laser;
    sf::SoundBuffer EnemyLaser;
    Laser.loadFromFile("Sound/Laser.wav");
    EnemyLaser.loadFromFile("Sound/EnemyLaser.wav");
    sf::Sound FriendlyGun;
    sf::Sound EnemyGun;
    EnemyGun.setBuffer(EnemyLaser);
    FriendlyGun.setBuffer(Laser);
    std::vector<enemy> alienVec = SpawnWave1();

    sf::Sprite Button;
    Button.setPosition(100,950);
    sf::Texture heart;
    heart.loadFromFile("Images/Heart");
    Button.setTexture(heart);
    int Score;
    int bodycount=0;


    sf::Font font;
    font.loadFromFile("Text/Open24.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("0");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);
    text.setPosition(1650, 0);
    sf::Text TimePlayed;
    TimePlayed.setFont(font);
    TimePlayed.setString("0");
    TimePlayed.setCharacterSize(100);
    TimePlayed.setFillColor(sf::Color::Green);
    TimePlayed.setPosition(0, 0);
    sf::Text Game;
    Game.setFont(font);
    Game.setString("GAME OVER");
    Game.setCharacterSize(170);
    Game.setFillColor(sf::Color::Red);
    Game.setPosition(0, 100);
    sf::Text PlayerHealth;
    PlayerHealth.setFont(font);
    PlayerHealth.setString("10");
    PlayerHealth.setCharacterSize(100);
    PlayerHealth.setFillColor(sf::Color::Red);
    PlayerHealth.setPosition(0, 900);
    sf::Text Kills;
    Kills.setFont(font);
    Kills.setString("0");
    Kills.setCharacterSize(100);
    Kills.setFillColor(sf::Color::Cyan);
    Kills.setPosition(1700, 900);



    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
    sf::Texture background;
    background.loadFromFile("Images/Kosmos.png");
    sf::Sprite tlo;
    tlo.setTexture(background);
    Player player(sf::Vector2f(120.0, 60.0), sf::Vector2f(900.0, 900.0),"Images/fighter.png");
    sf::Clock clock;
    formation collisionbox(sf::Vector2f(1052.0, 400.0), sf::Vector2f(0.0, 100.0));
    collisionbox.setFillColor(sf::Color::Transparent);
    std::vector<Bullet> bulletVec;
    std::vector<EnemyBullet> EnemybulletVec;

    float Timer=0;
    float EnemyTimer=0;
    float GlobalTimer=0;
    bool isFiring = false;
    bool isEnemyFiring=false;
    int cycle=0;
    int RandomAlienNumber=4;

    //Main Loop:
    while (window.isOpen()) {


        sf::Time elapsed = clock.restart();
        Timer=Timer+elapsed.asSeconds();
        EnemyTimer=EnemyTimer+elapsed.asSeconds();
        GlobalTimer=GlobalTimer+elapsed.asSeconds();
        bodycount=0;
        sf::Event Event;

        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {

            case sf::Event::Closed:
                window.close();
            default:{break;}
            }


            window.setKeyRepeatEnabled(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&isFiring==false&&Timer>=0.3){
                isFiring = true;
                Timer=0;
            }


        }

        if(EnemyTimer>=0.3)
        {
            isEnemyFiring=true;
            cycle++;
            EnemyTimer=0;
        }
        if(cycle>=3)
        {
            RandomAlienNumber = rand()%36;
            cycle=0;
        }

        window.clear();
        window.draw(tlo);
        collisionbox.animate(elapsed);
        bool krawedz =collisionbox.borders();
        window.draw(collisionbox);
        for( auto &it : alienVec)
        {

            it.movement(elapsed);
            if(krawedz==true)
            {
                it.changecourse();
            }
        }



        if (isFiring == true) {
            Bullet newBullet(sf::Vector2f(3, 25));
            newBullet.setPos(sf::Vector2f(player.getX()+45, player.getY()));
            bulletVec.push_back(newBullet);
            FriendlyGun.play();
            isFiring=false;
        }


        if (isEnemyFiring == true) {

            if(alienVec[RandomAlienNumber].getX()>0)
            {
                EnemyBullet newEnemyBullet(sf::Vector2f(5, 25));
                newEnemyBullet.setPos(sf::Vector2f(alienVec[RandomAlienNumber].getX()+45, alienVec[RandomAlienNumber].getY()+20));
                EnemybulletVec.push_back(newEnemyBullet);

                EnemyGun.play();

                isEnemyFiring=false;
            }
        }


        for (size_t i = 0; i < EnemybulletVec.size(); i++) {
            if(EnemybulletVec[i].getTop()<1080)
            {
                EnemybulletVec[i].draw(window);
                EnemybulletVec[i].fire(0.3);
            }


        }
        for (size_t i = 0; i < bulletVec.size(); i++) {
            if(bulletVec[i].getTop()>0)
            {
            bulletVec[i].draw(window);
            bulletVec[i].fire(3);
            }

        }

        for(auto &it : alienVec)
        {
            if(it.getX()<-100)
            {
                bodycount++;

            }

        }

        if(player.GetHealth()<=0)
        { music.stop();
            window.close();
            sf::RenderWindow window2(sf::VideoMode(800, 600), "Faliure");
            while (window2.isOpen()) {
                sf::Event Event2;

                //Event Loop:
                while (window2.pollEvent(Event2)) {
                    switch (Event2.type) {

                    case sf::Event::Closed:
                        window2.close();
                    default:{break;}
                    }}
                window2.draw(Game);
                window2.display();
            }
        }
        if(bodycount==36)
        {
            alienVec=SpawnWave1();
            collisionbox.setPosition(sf::Vector2f(20.0, 100.0));
            for(size_t i =0; i<alienVec.size(); i++)
            {
                if(collisionbox.GetDirection()!=alienVec[i].GetVelocity())
                    alienVec[i].changecourse();
            }
        }
        if(Score>40000)
        {

            Game.setString("YOU WIN");
            Game.setFillColor(sf::Color::Green);
            { music.stop();
                window.close();
                sf::RenderWindow window2(sf::VideoMode(800, 600), "Succes");
                while (window2.isOpen()) {
                    sf::Event Event2;

                    //Event Loop:
                    while (window2.pollEvent(Event2)) {
                        switch (Event2.type) {

                        case sf::Event::Closed:
                            window2.close();
                        default:{break;}
                        }}
                    window2.draw(Game);
                    window2.display();
                }
            }
        }
        for (size_t i = 0; i < bulletVec.size(); i++)
        {
            for( auto &it : alienVec)
            {
                if(it.checkColl(bulletVec[i])==true)
                {
                    Score=Score+100;
                    bulletVec[i].setPos(sf::Vector2f(-3000,-3000));
                }
            }
        }
        for (size_t i = 0; i < EnemybulletVec.size(); i++)
        {
            if(player.checkColl(EnemybulletVec[i])==true)
            {
                Score=Score-1000;
                EnemybulletVec[i].setPos(sf::Vector2f(5000,5000));
            }
        }


        std::string s = std::to_string(Score);
        std::string time = std::to_string(GlobalTimer);
        std::string HP=std::to_string(player.GetHealth());
        std::string kill =std::to_string(abs(36-bodycount));
        for( auto &it : alienVec)
        {
            it.draw(window);
        }
        player.animate2(elapsed);
        player.draw(window);
        PlayerHealth.setString(HP);
        text.setString(s);
        TimePlayed.setString(time);
        Kills.setString(kill);
        window.draw(text);
        window.draw(TimePlayed);
        window.draw(PlayerHealth);
        window.draw(Kills);
        window.draw(Button);
        window.display();

    }




    return 0;
}
