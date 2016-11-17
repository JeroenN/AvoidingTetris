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
    float oneTime =1;
    bool isGrounded =false;
    bool sliding=false;
    //bool keyReleased=true;
    std::vector<sf::RectangleShape> blocks;
    std::vector<float> blocksX;
    std::vector<float> blocksY;
    std::vector<float> blocksSizeX;
    std::vector<float> blocksSizeY;
    int posY = windowSizeY-playerSizeY;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);
    //Dit, de push backs, komen allemaal in de main of in een functie in iedergeval moet het een for loop hebben,
    //hierdoor kunnen er meerdere bloken zijn.
    for(int i=0; i< 5; ++i)
    {
    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(300);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);
    }

        int i =0;
        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(100);
        blocksY.push_back(700);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(300);
        blocksY.push_back(500);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(500);
        blocksY.push_back(300);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(500);
        blocksY.push_back(700);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(100);
        blocksY.push_back(300);

    window.setFramerateLimit(70);
    window.setKeyRepeatEnabled(false);
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
        if((posY+playerSizeY >blocksY[i] && posY+playerSizeY < blocksY[i]+20) || posY==blocksY[i]-playerSizeY)
        {
            if(posX + playerSizeX> blocksX[i] && posX < blocksX[i]+blocksSizeX[i])
            {

                if(jumpingForce>0)
                {
                    isGrounded=true;
                    posY = blocksY[i]-playerSizeY;
                    oneTime=0;
                }

            }
        }

        if(posY > blocksY[i]+20 && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX + playerSizeX> blocksX[i] && posX < blocksX[i]+blocksSizeX[i])
            {
                if(jumpingForce<0)
                {
                    if(oneTime>1)
                    {
                        //std::cout<<"Collide";
                        isGrounded=false;
                        jumpingForce=0;
                        oneTime=0;
                    }
                }


            }
        }
        oneTime+=0.1;
        if(posY +playerSizeY > blocksY[i] && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX > blocksX[i] + blocksSizeX[i]-20 && posX< blocksX[i] +blocksSizeX[i])
            {

                        std::cout<<"Collide";
                        //isGrounded=false;
                        posX=blocksX[i]+blocksSizeX[i];
                        jumpingForce=0;
                        //oneTime=0;
                        if(posX ==blocksX[i]+blocksSizeX[i])
                        {
                        posY+=2;
                        isGrounded=true;
                        sliding=true;
                        }

            }
            else
            {
                sliding=false;
            }
        }

        if(posY +playerSizeY > blocksY[i] && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX +playerSizeX <blocksX[i] + 20 && posX + playerSizeX> blocksX[i])
            {

                        std::cout<<"Collide";
                        isGrounded=false;
                        posX=blocksX[i]-playerSizeX+1;
                        posY+=2;
                        jumpingForce=0;
                        //oneTime=0;
                        if(posX ==blocksX[i]-playerSizeX)
                        {
                        posY+=2;
                        isGrounded=true;
                        sliding=true;
                        }

            }
            else
            {
                sliding=false;
            }
        }
    }



    if(isGrounded==true)
    {
        //if (event.type == sf::Event::KeyPressed)
        if (event.key.code == ' ')
        {
            //if (event.key.code == sf::Keyboard::Space)
            //{
            if(sliding==true)
            {
                posX-=50;
            }
            jumpingForce=-22;
            isGrounded = false;
            //}
        }
     }
    //if(sf::Keyboard::isKeyReleased )
    if(isGrounded == false)
    {
        //std::cout<< jumpingForce<< "\n";
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

