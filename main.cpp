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
    int playerSizeX=25;
    int playerSizeY=40;
    int playerSpeedX=10;
    float jumpingForce = -22;
    float gravity = 1;
    bool isGrounded =false;
    std::vector<sf::RectangleShape> blocks;
    std::vector<float> blocksX;
    std::vector<float> blocksY;
    int posY = windowSizeY-playerSizeY;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);
    //Dit, de push backs, komen allemaal in de main of in een functie in iedergeval moet het een for loop hebben,
    //hierdoor kunnen er meerdere bloken zijn.
    blocks.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
    blocksX.push_back(100);
    blocksY.push_back(700);

    blocks.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
    blocksX.push_back(300);
    blocksY.push_back(500);

    blocks.push_back(sf::RectangleShape(sf::Vector2f(50, 50)));
    blocksX.push_back(500);
    blocksY.push_back(300);
    window.setFramerateLimit(70);
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
            playerSpeedX=-10;
            posX += playerSpeedX;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
            playerSpeedX=10;
            posX += playerSpeedX;
    }
    if(posY+playerSizeY==windowSizeY || posY+playerSizeY>windowSizeY)
    {
        isGrounded =true;
        posY=windowSizeY-playerSizeY;
        //std::cout<<"STOP JUMPING";
    }
    else
    {
        isGrounded = false;
    }
    for(unsigned i=0; i<blocks.size(); ++i)
    {
        if((posY+playerSizeY>blocksY[i] && posY<blocksY[i]+50) || posY+playerSizeY==blocksY[i])
        {

            if(posX + playerSizeX> blocksX[i] && posX < blocksX[i]+50)
            {
                if(jumpingForce>0)
                {
                    isGrounded=true;
                    posY = blocksY[i]-playerSizeY;
                }
                if(jumpingForce<0)
                {
                    isGrounded=false;
                    jumpingForce=0;
                }
            }
        }


    }



    if(isGrounded==true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            jumpingForce=-22;
            isGrounded = false;
        }
     }
    if(isGrounded == false)
    {
        std::cout<< jumpingForce<< "\n";
        if(jumpingForce<=14)
        jumpingForce+=gravity;
        posY += jumpingForce;
    }
    sf::RectangleShape player(sf::Vector2f(playerSizeX, playerSizeY));
    player.setPosition(posX, posY);
    player.setOrigin(sf::Vector2f(0,0));

    for(unsigned i=0; i<blocks.size(); ++i)
    {
        //blocks[i].setFillColor(sf::Color(100,0,0));
        blocks[i].setPosition(blocksX[i], blocksY[i]);
        //blocks[i].setOrigin(sf::Vector2f(10,10));
    }
    window.clear();
    window.draw(player);
    for(const auto block: blocks)
    window.draw(block);
    window.display();
    }
    return 0;
}

