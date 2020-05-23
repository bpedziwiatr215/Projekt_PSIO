#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size) {
        setPosition(position);
    }
    bool getstance()
    {
        return stance;
    }
    void changestancetrue()
    {
        stance=true;
    }
    void changestancefalse()
    {
        stance=false;
    }
    void animate(const sf::Time &elapsed, const sf::Event &event)
    {
        if(stance==false)
        {
        move(velocity_x_ * elapsed.asSeconds(), velocity_y_ * elapsed.asSeconds());
        rotate(velocity_r_ * elapsed.asSeconds());
        bounce();
        }
        if(stance==true)
        {
            if (event.type == sf::Event::EventType::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Left:
                {   bounce2(elapsed);
                    move(-velocity_x_ * elapsed.asSeconds(), 0 * elapsed.asSeconds());
                    break;
                }
                case sf::Keyboard::Right:
                {   bounce2(elapsed);
                    move(velocity_x_ * elapsed.asSeconds(), 0 * elapsed.asSeconds());
                    break;
                }
                case sf::Keyboard::Up:
                {   bounce2(elapsed);
                    move(0 * elapsed.asSeconds(), -velocity_y_ * elapsed.asSeconds());
                    break;
                }
                case sf::Keyboard::Down:
                {   bounce2(elapsed);
                    move(0 * elapsed.asSeconds(), velocity_y_ * elapsed.asSeconds());
                    break;
                }
                case sf::Keyboard::Q:
                {
                    rotate(-velocity_r_ * elapsed.asSeconds());
                }
                case sf::Keyboard::E:
                {
                    rotate(velocity_r_ * elapsed.asSeconds());
                }
                default:{break;}
                }

            }
        }

    }
    void setSpeed(float velocity_x, float velocity_y, float velocity_r) {
        velocity_x_ = velocity_x;
        velocity_y_ = velocity_y;
        velocity_r_ = velocity_r;
    }
    float velocity_x_ = 0;
    float velocity_y_ = 0;
    float velocity_r_ = 0;
private:
    bool stance=false;
    void bounce()
    {
        auto bounds = getGlobalBounds();
        if (bounds.left < bounds_left_) {
            velocity_x_ = std::abs(velocity_x_);
        }
        if (bounds.left + bounds.width > bounds_right_) {
            velocity_x_ = -std::abs(velocity_x_);
        }
        if (bounds.top < bounds_top_) {
            velocity_y_ = std::abs(velocity_y_);
        }
        if (bounds.top + bounds.height > bounds_bottom_) {
            velocity_y_ = -std::abs(velocity_y_);
        }
    }
    void bounce2(const sf::Time &elapsed)
    {
        auto bounds = getGlobalBounds();
        if (bounds.left < bounds_left_&&sf::Keyboard::Left) {
            move(velocity_x_ * elapsed.asSeconds(), 0 * elapsed.asSeconds());
        }
        if (bounds.left + bounds.width > bounds_right_&&sf::Keyboard::Right) {
            move(-velocity_x_ * elapsed.asSeconds(), 0 * elapsed.asSeconds());
        }
        if (bounds.top < bounds_top_&&sf::Keyboard::Up) {
            move(0 * elapsed.asSeconds(), velocity_y_ * elapsed.asSeconds());
        }
        if (bounds.top + bounds.height > bounds_bottom_&&sf::Keyboard::Down) {
            move(0 * elapsed.asSeconds(), -velocity_y_ * elapsed.asSeconds());
        }
    }
    float bounds_left_ = 0;
    float bounds_right_ = 800;
    float bounds_top_ = 0;
    float bounds_bottom_ = 600;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    CustomRectangleShape my_rectangle(sf::Vector2f(120.0, 60.0), sf::Vector2f(500.0, 400.0));
    my_rectangle.setFillColor(sf::Color(100, 50, 250));
    CustomRectangleShape my_rectangle2(sf::Vector2f(120.0, 60.0), sf::Vector2f(300.0, 200.0));
    my_rectangle2.setFillColor(sf::Color(60, 140, 250));

    sf::Clock clock;

    std::vector<CustomRectangleShape> rectangles;

    for (int i=0; i<10; i++)
    {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for (auto &rec : rectangles) {
        rec.setFillColor(sf::Color(255, 255, 255));
        rec.setSpeed(100, 200, 10);
    }
    for(const auto &rec : rectangles)
    {
       sf::Vector2f poz =  rec.getPosition();
       sf::Vector2f siz = rec.getSize();
        std::cout<<poz.x<< " "<<siz.x<<" "<<poz.y<<" " << siz.y<<std::endl;
    }
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int R=rand()%255;
        int G=rand()%255;
        int B=rand()%255;
        for(size_t i=0; i< rectangles.size();i++)
        {
                sf::Vector2i vec=sf::Mouse::getPosition(window);
                 if(rectangles[i].getGlobalBounds().contains(vec.x, vec.y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left))
                 {
                    rectangles[i].changestancetrue();
                    rectangles[i].setFillColor(sf::Color(R, G, B));
                    rectangles[i].velocity_x_=200;
                    rectangles[i].velocity_y_=200;
                 }

                 {
                   if(rectangles[i].getGlobalBounds().contains(vec.x, vec.y)&&sf::Mouse::isButtonPressed(sf::Mouse::Right))
                   rectangles[i].changestancefalse();
                 }
                if(rectangles[i].getstance()==false)
                {
                 rectangles[i].setFillColor(sf::Color(255, 255, 255));
                }
            }
        for(size_t i=0; i< rectangles.size();i++)
        {
            rectangles[i].animate(elapsed,event);
        }


        window.clear(sf::Color::Black);
        for(const auto &rec : rectangles)
        {
                window.draw(rec);
        }
        window.display();


    }

    return 0;
}
