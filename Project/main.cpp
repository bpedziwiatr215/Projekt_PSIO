#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <sstream>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "formation.h"
#include "EnemyBullet.h"
#include "Spawner.h"


int main()
{
//muzyka oraz dzwiek
//-------------------------------------------------------------------------------------------------------------------------------------
    sf::Music music;
    music.openFromFile("Sound/Main.wav");
    music.play();

    sf::SoundBuffer Laser;
    sf::SoundBuffer EnemyLaser;
    Laser.loadFromFile("Sound/Laser.wav");
    EnemyLaser.loadFromFile("Sound/EnemyLaser.wav");
    sf::Sound FriendlyGun;
    sf::Sound EnemyGun;
    EnemyGun.setBuffer(EnemyLaser);
    FriendlyGun.setBuffer(Laser);

    std::vector<enemy> alienVec = SpawnWave1();//spawn 1 fali

//powolanie przyciskow obslugujacych sklep
//-------------------------------------------------------------------------------------------------------------------------------------
    sf::Texture heart;
    heart.loadFromFile("Images/Heart.png");
    sf::Sprite Button;
    Button.setPosition(150,950);
    Button.setTexture(heart);
    sf::Sprite Button2;
    Button2.setPosition(225,950);
    Button2.setTexture(heart);
    Button2.setColor(sf::Color::Yellow);
    sf::Sprite Button3;
    Button3.setPosition(300,950);
    Button3.setTexture(heart);
    Button3.setColor(sf::Color::Blue);

//Napisy oraz liczniki w formie tekstu wyswietlanego w oknach
//---------------------------------------------------------------------------------------------------------------------------------------
    sf::Font font;
    font.loadFromFile("Text/Open24.ttf");
    sf::Text ScoreCount=TextGenerator("0",100,sf::Color::Black,1650,0);
    ScoreCount.setFont(font);
    sf::Text Time= TextGenerator("0",100,sf::Color::Green,0,0);
    Time.setFont(font);
    sf::Text Game=TextGenerator("GAME OVER",170,sf::Color::Red,0,100);
    Game.setFont(font);
    sf::Text PlayerHealth=TextGenerator("10",100,sf::Color::Red,0,900);
    PlayerHealth.setFont(font);
    sf::Text Kills=TextGenerator("0",100,sf::Color::Cyan,1800,900);
    Kills.setFont(font);

//----------------------------------------------------------------------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "BudgetInvaders");//glowne okno gry

    sf::Texture background; //stworzenie tla
    background.loadFromFile("Images/Kosmos.png");
    sf::Sprite tlo;
    tlo.setTexture(background);

    Player player(sf::Vector2f(900.0, 900.0),"Images/fighter.png"); //Utworzenie obiektu gracza

    sf::Clock clock; // deklaracja zegara

    formation collisionbox(sf::Vector2f(1052.0, 400.0), sf::Vector2f(0.0, 100.0)); //utworzenie tla formacji obcych obslugujacego zmiane kierunku lotu UFO
    collisionbox.setFillColor(sf::Color::Transparent);

    std::vector<Bullet> bulletVec; // deklaracje wektorow ktore beda przechowywac pociski
    std::vector<EnemyBullet> EnemybulletVec;


//deklaracje oraz definicje potrzebych zmiennych
//----------------------------------------------------------------------------------------------------------------------------------------
    int Score=0; //poczatkowe wartosci punktow, zestrzelonych UFO oraz stanu serii strzelajacego obcego
    int bodycount=0;
    int cycle=0;

    int RandomAlienNumber=4; //numer pierwszego strzelajacego obcego

    int HealthTransactionCount=0; //poczatkowa liczba zawartych transakcji w sklepie na zdrowie, szybkostrzelnosc oraz predkosc
    int RPMTransactionCount=0;
    int SpeedTransactionCount=0;

    double RPMModifier=0;

    float PlayerTimer=0; //pozycje poczatkowe zegarow
    float EnemyTimer=0;
    float GlobalTimer=0;

    bool isFiring = false; //poczatkowy stan "spustu broni" gracza i UFO
    bool isEnemyFiring=false;
//poczatek glownej petla
//----------------------------------------------------------------------------------------------------------------------------------------
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart(); //zegary odpowiedzialne za szybkostrzelnosci oraz czas gry
        PlayerTimer=PlayerTimer+elapsed.asSeconds();
        EnemyTimer=EnemyTimer+elapsed.asSeconds();
        GlobalTimer=GlobalTimer+elapsed.asSeconds();

        bodycount=0;//reset licznika zestrzelen

        bool edge =collisionbox.borders();
        sf::Event Event;

        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
            case sf::Event::Closed: //zamykanie okna
                window.close();
            default:{break;}
            }
        }
//Movement UFO oraz killcount
//----------------------------------------------------------------------------------------------------------------------------------------
        for(auto &it:alienVec) //poruszanie sie UFO
        {
            it.movement(elapsed);
            if(edge==true)
            {
                it.changecourse();
            }
        }

        for(auto &it : alienVec) //Licznik zestrzelonych Obcych w fali
        {
            if(it.getX()<-100)
            {
                bodycount++;
            }
        }
//porazka
//----------------------------------------------------------------------------------------------------------------------------------------
        if(player.GetHealth()<=0) //warunek przegranej
        {
            music.stop();
            window.close();
            sf::RenderWindow window2(sf::VideoMode(800, 600), "Faliure"); //ekran porazki
            while (window2.isOpen())
            {
                sf::Event Event2;
                while (window2.pollEvent(Event2))
                {
                    switch(Event2.type)
                    {
                    case sf::Event::Closed:
                        window2.close();
                    default:{break;}
                    }
                }
                window2.draw(Game);
                window2.display();
            }
        }
//zwyciestwo
//----------------------------------------------------------------------------------------------------------------------------------------
        if(Score>40000&&bodycount==36) //warunki wygranej
        {
            Game.setString("YOU WIN");
            Game.setFillColor(sf::Color::Green);
            music.stop();
            window.close();
            sf::RenderWindow window2(sf::VideoMode(800, 600), "Succes"); //ekran wygranej
            while(window2.isOpen())
            {
                sf::Event Event2;
                while (window2.pollEvent(Event2))
                {
                    switch (Event2.type)
                    {
                    case sf::Event::Closed:
                        window2.close();
                    default:{break;}
                    }
                }
                window2.draw(Game);
                window2.display();
            }

        }
//spawn nastepnych fal
//----------------------------------------------------------------------------------------------------------------------------------------
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
//obsluga wystrzalow gracza
//----------------------------------------------------------------------------------------------------------------------------------------
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&isFiring==false&&PlayerTimer>=0.3-RPMModifier) //strzelanie gracza + szybkostrzelnosc
        {
            isFiring = true;
            PlayerTimer=0;
        }

        if(isFiring == true)//strzelanie gracza (tworzenie pociskow)
        {
            Bullet newBullet(sf::Vector2f(3, 25));
            newBullet.setPos(sf::Vector2f(player.getX()+45, player.getY()));
            bulletVec.push_back(newBullet);
            FriendlyGun.play();
            isFiring=false;
        }
//obsluga wystrzalow UFO
//----------------------------------------------------------------------------------------------------------------------------------------
        if(EnemyTimer>=0.3) //szybkostrzelnosc UFO
        {
            isEnemyFiring=true;
            cycle++;
            EnemyTimer=0;
        }

        if(cycle>=3) //zmiana strzelajacego UFO
        {
            RandomAlienNumber = rand()%36;
            cycle=0;
        }

        if(isEnemyFiring == true)
        {
            if(alienVec[RandomAlienNumber].getX()>0)
            {
                EnemyBullet newEnemyBullet(sf::Vector2f(5, 25));
                newEnemyBullet.setPos(sf::Vector2f(alienVec[RandomAlienNumber].getX()+45, alienVec[RandomAlienNumber].getY()+20));
                EnemybulletVec.push_back(newEnemyBullet);
                EnemyGun.play();
                isEnemyFiring=false;
            }
        }
//obsluga trafien
//----------------------------------------------------------------------------------------------------------------------------------------
        for (size_t i = 0; i < bulletVec.size(); i++)
        {
            for( auto &it : alienVec)
            {
                if(it.checkColl(bulletVec[i])==true)
                {
                    Score=Score+300;
                    bulletVec[i].setPos(sf::Vector2f(-100,-100));
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

        sf::Vector2i vec=sf::Mouse::getPosition(window);


//obsluga skelu
//----------------------------------------------------------------------------------------------------------------------------------------
         if(Button.getGlobalBounds().contains(vec.x, vec.y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Score>1000&&HealthTransactionCount<3)
         {
             player.Heal();
             Score=Score-1000;
             HealthTransactionCount++;
         }

         if(Button2.getGlobalBounds().contains(vec.x, vec.y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Score>200&&RPMTransactionCount<7)
         {
             Score=Score-500;
             RPMTransactionCount++;
             RPMModifier=RPMModifier+0.015;
         }

         if(Button3.getGlobalBounds().contains(vec.x, vec.y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)&&Score>500&&SpeedTransactionCount<5)
         {
             Score=Score-500;
             SpeedTransactionCount++;
             player.Boost();
         }
//update wyswietlanych licznikow
//----------------------------------------------------------------------------------------------------------------------------------------


        std::string score = std::to_string(Score);
        std::string time = std::to_string(GlobalTimer);
        std::string HP=std::to_string(player.GetHealth());
        std::string kill =std::to_string(abs(36-bodycount));

        PlayerHealth.setString(HP);
        ScoreCount.setString(score);
        Time.setString(time);
        Kills.setString(kill);
//wyrysowanie wszystkiego na ekranie
//----------------------------------------------------------------------------------------------------------------------------------------

        window.clear();
        window.draw(tlo);
        collisionbox.animate(elapsed);
        window.draw(collisionbox);
        for (size_t i = 0; i < EnemybulletVec.size(); i++)
        {
            if(EnemybulletVec[i].getTop()<1080)
            {
                EnemybulletVec[i].draw(window);
                EnemybulletVec[i].fire(0.3);
            }
        }

        for (size_t i = 0; i < bulletVec.size(); i++)
        {
            if(bulletVec[i].getTop()>0)
            {
            bulletVec[i].draw(window);
            bulletVec[i].fire(3);
            }
        }

        for( auto &it : alienVec)
        {
            it.draw(window);
        }

        if(HealthTransactionCount<3) //maksymalne liczby transakcji w sklepie
        {
        window.draw(Button);
        }
        if(RPMTransactionCount<7)
        {
        window.draw(Button2);
        }
        if(SpeedTransactionCount<5)
        {
        window.draw(Button3);
        }

        player.animate(elapsed);
        player.draw(window);       
        window.draw(ScoreCount);
        window.draw(Time);
        window.draw(PlayerHealth);
        window.draw(Kills);
        window.display();

    }
    return 0;
}
