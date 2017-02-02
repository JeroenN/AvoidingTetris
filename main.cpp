#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

class standingBlock
{
    /*
    const float standingBlockHeight;
    const float standingBlockWidth;
    float standingBlock_x;
    float standingBlock_y;
    */
    sf::RectangleShape block;

public:
    standingBlock(const float height, const float width, const float posX, const float posY)
       // :standingBlockHeight(height),  standingBlockWidth(width), standingBlock_x(posX), standingBlock_y(posY)
        :block()
    {
        block.setSize(sf::Vector2f(height, width));
        block.setPosition(sf::Vector2f(posX, posY));
        block.setFillColor(sf::Color(255, 127, 63));
    }

    float getHeight()
    {
        return block.getSize().x;
    }
    float getWidth()
    {
        return block.getSize().y;
    }
    float getPosX()
    {
        return block.getPosition().x;
    }
    float getPosY()
    {
        return block.getPosition().y;
    }
    void changePosY()
    {

    }

    void displash(sf::RenderWindow &window)
    {
        window.draw(block);
    }

};

int main()
{
    std::vector<standingBlock> standingBlocks;
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
    int posY = windowSizeY-playerSizeY;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);

    standingBlocks.push_back(standingBlock(100,100,50,100));
    standingBlocks.push_back(standingBlock(100,100,300,500));
    standingBlocks.push_back(standingBlock(50,50,300,810));
    standingBlocks.push_back(standingBlock(50,50,450,700));
    standingBlocks.push_back(standingBlock(50,50,200, 300));

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

    //blocksY[0]-=2;
    //Every block with that is moving down: blockMovingDown = true
    //blocksY[1]+=2;
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
        posY=windowSizeY-playerSizeY;
    }
    else
    {
       isGrounded = false;
    }

    //Colision detection
    for(unsigned i=0; i<standingBlocks.size(); ++i)
    {
        //Standing on a block
        if((posY+playerSizeY >standingBlocks[i].getPosY() && posY+playerSizeY < standingBlocks[i].getPosY()+20) || posY==standingBlocks[i].getPosY()-playerSizeY)
        {
            if(posX + playerSizeX> standingBlocks[i].getPosX() && posX < standingBlocks[i].getPosX()+standingBlocks[i].getWidth())
            {
                if(jumpingForce>0)
                {
                    isGrounded=true;
                    //Needs to be a true or false statement: if( blockMovingDown ==true)
                    if(i!=1)
                    {
                        posY = standingBlocks[i].getPosY()-playerSizeY;
                    }
                    else
                    {
                        posY = standingBlocks[i].getPosY()-playerSizeY;
                        posY+=2;
                    }
                }

            }
        }

        //Hitting a block with your head
        if(posY > standingBlocks[i].getPosY()+20 && posY < standingBlocks[i].getPosY()+standingBlocks[i].getHeight())
          {
            if(posX + playerSizeX> standingBlocks[i].getPosX() && posX < standingBlocks[i].getPosX()+standingBlocks[i].getWidth())
            {
                if(jumpingForce<0)
                {
                        jumpingForce=0;
                }
                if(isGrounded==true)
                {
                    std::cout<<"You Dead";
                }
            }
        }

        //Colliding left side player
        if(posY +playerSizeY > standingBlocks[i].getPosY() && posY < standingBlocks[i].getPosY()+standingBlocks[i].getHeight())
          {
            if(posX > standingBlocks[i].getPosX() + standingBlocks[i].getWidth()-20 && posX< standingBlocks[i].getPosX() +standingBlocks[i].getWidth())
            {
                    if(movingLeft==true)
                    {
                        isGrounded=false;
                        posX=standingBlocks[i].getPosX()+standingBlocks[i].getWidth();
                        posY+=2;
                        jumpingForce=0;
                        if(posX ==standingBlocks[i].getWidth()+standingBlocks[i].getPosY())
                        {
                        posY+=1;
                        }
                   }

            }
        }

        //Colliding Right side player
        if(posY +playerSizeY > standingBlocks[i].getPosY() && posY < standingBlocks[i].getPosY()+standingBlocks[i].getHeight())
          {
            if(posX +playerSizeX <standingBlocks[i].getPosX() + 20 && posX + playerSizeX> standingBlocks[i].getPosX())
            {
                    if(movingRight==true)
                    {
                        //std::cout<<"Collide";
                        isGrounded=false;
                        posX=standingBlocks[i].getPosX()-playerSizeX;
                        posY+=2;
                        jumpingForce=0;
                        if(posX ==standingBlocks[i].getPosX()-playerSizeX)
                        {
                        posY+=1;
                        }
                    }
            }

        }
    }

    if(isGrounded==true)
    {
        for(unsigned i=0; i<standingBlocks.size(); ++i)
        {
        if(posY-standingBlocks[i].getPosY()>50)
        {
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
/*
    if(blocksY[1]>windowSizeY)
    {
        blocksY[1]=0;
    }
    if(blocksY[0]<0)
    {
        blocksY[0]=windowSizeY;
    }
*/

  /*  for(unsigned i=0; i<blocks.size(); ++i)
    {
        //blocks[i].setFillColor(sf::Color(100,0,0));
        blocks[i].setPosition(blocksX[i], blocksY[i]);
        //blocks[i].setOrigin(sf::Vector2f(10,10));
    }
    */
    window.clear();
    window.draw(player);
    for(const auto block: blocks)
    window.draw(block);
    for(unsigned i=0; i<standingBlocks.size(); ++i)
    standingBlocks[i].displash(window);
    //splashy.displash(window);
    window.display();
    }
    return 0;
}

