#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

struct positive_coordinat
{
    void checkInvariant()
    {
#ifndef NDEBUG
        if (x < 0.0 || y < 0.0)
            throw std::logic_error("a iyerciyged 3eyfewfu ide i3edhu ue oo");
#endif
    }

private:

    double x;
    double y;
};

class splashBlock
{
    const float splashBlockHeight;
    const float splashBlockWidth;
    float splashBlock_x;
    float splashBlock_y;
    sf::RectangleShape block;
public:

    splashBlock(const float height, const float width, const float posX, const float posY)
        :splashBlockHeight(height),  splashBlockWidth(width), splashBlock_x(posX), splashBlock_y(posY)
    {
        block.setSize(sf::Vector2f(splashBlockHeight, splashBlockWidth));
        block.setPosition(sf::Vector2f(splashBlock_x, splashBlock_y));
        block.setFillColor(sf::Color(255, 127, 63));
    }

    void displash(sf::RenderWindow &window)
    {
        window.draw(block);
    }

};

int main()
{
    splashBlock splashy(10,10,100,100);
    int posX=300;
    int windowSizeX=700;
    int windowSizeY = 900;
    int playerSizeX=25;
    int playerSizeY=40;
    int playerSpeedX=10;
    float jumpingForce = 0;
    float gravity = 1;
    int speed = 7;
    bool isGrounded =true;
    bool movingRight =false;
    bool movingLeft = false;
    bool jumpReady = true;
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

    blocksSizeX.push_back(150);
    blocksSizeY.push_back(100);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(100);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(50);

    blocksSizeX.push_back(50);
    blocksSizeY.push_back(900);
    }

        int i =0;
        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(100);
        blocksY.push_back(windowSizeY);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(300);
        blocksY.push_back(-200);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(500);
        blocksY.push_back(810);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(500);
        blocksY.push_back(500);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(100);
        blocksY.push_back(300);
        i+=1;

        blocks.push_back(sf::RectangleShape(sf::Vector2f(blocksSizeX[i], blocksSizeY[i])));
        blocksX.push_back(20);
        blocksY.push_back(0);

    window.setFramerateLimit(70);
    window.setKeyRepeatEnabled(true);
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

    blocksY[0]-=2;
    //Every block with that is moving down: blockMovingDown = true
    blocksY[1]+=2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
        return 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
            playerSpeedX=-speed;
            posX += playerSpeedX;
            movingLeft =true;
    }
    else
    {
       movingLeft =false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
            playerSpeedX=speed;
            posX += playerSpeedX;
            movingRight =true;
    }
    else
    {
       movingRight =false;
    }
    if(posY+playerSizeY==windowSizeY || posY+playerSizeY>windowSizeY)
    {
        isGrounded =true;
        //std::cout<<"1 \n";
        //collidingGround=true;
        posY=windowSizeY-playerSizeY;
    }
    else
    {
       //collidingGround=false;
       isGrounded = false;
    }

    //Colision detection
    for(unsigned i=0; i<blocks.size(); ++i)
    {
        //Standing on a block
        if((posY+playerSizeY >blocksY[i] && posY+playerSizeY < blocksY[i]+20) || posY==blocksY[i]-playerSizeY)
        {
            if(posX + playerSizeX> blocksX[i] && posX < blocksX[i]+blocksSizeX[i])
            {
         //       collidingGround =true;
                //std::cout<<"1 \n";
                if(jumpingForce>0)
                {
                    isGrounded=true;
                    //Needs to be a true or false statement: if( blockMovingDown ==true)

                    if(i!=1)
                    {
                        posY = blocksY[i]-playerSizeY;
                    }
                    else
                    {
                        posY = blocksY[i]-playerSizeY;
                        posY+=2;
                    }
                }

            }
        }
        else
        {
           // collidingGround =false;
        }

        //Hitting a block with your head
        if(posY > blocksY[i]+20 && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX + playerSizeX> blocksX[i] && posX < blocksX[i]+blocksSizeX[i])
            {
                if(jumpingForce<0)
                {
                        jumpingForce=0;
                }

                if(isGrounded==true)
                {
                    std::cout<<"You Dead";
                }
                    //std::cout<<"Colldinghead true"; //delete
            }
        }
        //else
        //{
          //  collidingHead =false;
        //}

        //Colliding left side player
        if(posY +playerSizeY > blocksY[i] && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX > blocksX[i] + blocksSizeX[i]-20 && posX< blocksX[i] +blocksSizeX[i])
            {
                    if(movingLeft==true)
                    {
                        isGrounded=false;
                        posX=blocksX[i]+blocksSizeX[i];
                        posY+=2;
                        jumpingForce=0;
                        if(posX ==blocksX[i]+blocksSizeX[i])
                        {
                        posY+=1;
                        }
                   }

            }
        }

        //Colliding Right side player
        if(posY +playerSizeY > blocksY[i] && posY < blocksY[i]+blocksSizeY[i])
          {
            if(posX +playerSizeX <blocksX[i] + 20 && posX + playerSizeX> blocksX[i])
            {
                    if(movingRight==true)
                    {
                        //std::cout<<"Collide";
                        isGrounded=false;
                        posX=blocksX[i]-playerSizeX;
                        posY+=2;
                        jumpingForce=0;
                        if(posX ==blocksX[i]-playerSizeX)
                        {
                        posY+=1;
                        }
                    }
            }

        }
    }

    if(isGrounded==true)
    {
        //std::cout<<"Grounded"; //delete

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
          {
                if (jumpReady ==true)
                {
                    jumpingForce=-22;
                    isGrounded=false;
                }

                jumpReady = false;
          }
          else
          {
            jumpReady=true;
          }
     }

    if(isGrounded ==false)
    {
    if(jumpingForce<=14)
    jumpingForce+=gravity;
    posY += jumpingForce;
    }

    sf::RectangleShape player(sf::Vector2f(playerSizeX, playerSizeY));
    player.setPosition(posX, posY);
    player.setOrigin(sf::Vector2f(0,0));

    if(blocksY[1]>windowSizeY)
    {
        blocksY[1]=0;
    }
    if(blocksY[0]<0)
    {
        blocksY[0]=windowSizeY;
    }


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
    splashy.displash(window);
    window.display();
    }
    return 0;
}

