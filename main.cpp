#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>



int main()
{

    int posX=100;
    int windowSizeX=700;
    int windowSizeY = 900;
    int playerSizeX=30;
    int playerSizeY=45;
    int playerSpeedX=10;
    int jumpingForce = -100;
    float gravity = 9.81;

    int posY = windowSizeY-playerSizeY-10;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(60);
    while(window.isOpen())
        {
            sf::Event event;


            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return 0;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
            posX -= playerSpeedX;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
            posX += playerSpeedX;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        std::cout<< jumpingForce<< "\n";
        jumpingForce+=gravity;
        posY -= jumpingForce;

    }

    sf::RectangleShape player(sf::Vector2f(playerSizeX, playerSizeY));
    player.setPosition(posX, posY);
    player.setOrigin(sf::Vector2f(0,0));

    window.clear();
    window.draw(player);
    window.display();
    }
    return 0;
}

