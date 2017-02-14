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
    sf::RectangleShape block;

public:
    standingBlock(const float height, const float width, const float posX, const float posY)
       // :standingBlockHeight(height),  standingBlockWidth(width), standingBlock_x(posX), standingBlock_y(posY)
        :block()
    {
        block.setSize(sf::Vector2f(height, width));
        block.setPosition(sf::Vector2f(posX, posY));
        block.setFillColor(sf::Color(255, 127, 63));
        //block.setOrigin(sf::Vector2f(0,0));
    }

    float getHeight()const {
        return block.getSize().y;
    }
    float getWidth()const {
        return block.getSize().x;
    }
    float getPosX() const {
        return block.getPosition().x;
    }
    float getPosY()const {
        return block.getPosition().y;
    }

    void displash(sf::RenderWindow &window)
    {
        window.draw(block);
    }

    void moveDown(float posX, float posY, float speedMovingDown)
    {
        posY+=speedMovingDown;
        block.setPosition(sf::Vector2f(posX, posY));
    }

};

std::vector<standingBlock> create_standing_blocks() noexcept
{
    std::vector<standingBlock> v;
    v.push_back(standingBlock(100,100,50,100));
    v.push_back(standingBlock(100,100,300,500));
    v.push_back(standingBlock(50,50,300,810));
    v.push_back(standingBlock(50,50,450,700));
    v.push_back(standingBlock(50,50,200, 300));
    v.push_back(standingBlock(100,500,600, 300));
    return v;
}

///Does the player have a collission with a standing block at his/her right side?
bool player_collides_right(
    const float posX,
    const float posY,
    const float playerSizeX,
    const float playerSizeY,
    const standingBlock& standingBlock,
    const bool movingRight
)
{
    return posY +playerSizeY > standingBlock.getPosY()
      && posY < standingBlock.getPosY()+standingBlock.getHeight()
      && posX +playerSizeX <standingBlock.getPosX() + 20
      && posX + playerSizeX> standingBlock.getPosX()
      && movingRight
    ;
}
float moving_player_horizontally(float posX)
{
    float speed =10;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
            posX += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
            posX -= speed;
    }
    return posX;
}

float jump_player_vertically()
{
    //float jumpingForce=0;
    bool jumpReady=true;
    bool jumping=false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (jumpReady ==true)
        {
            jumping=true;
        }
       jumpReady = false;
    }
    else
    {
      jumpReady=true;
    }
    return jumping;
}

int main()
{
    std::vector<standingBlock> standingBlocks = create_standing_blocks();
    int posX=300;
    int windowSizeX=700;
    int windowSizeY = 900;
    int playerSizeX=25;
    int playerSizeY=40;
    float jumpingForce = 0;
    float gravity = 1;
    bool isGrounded =true;
    bool movingRight =false;
    bool movingLeft = false;
   // bool jumpReady = true;
    std::vector<sf::RectangleShape> blocks;
    int posY = windowSizeY-playerSizeY;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);


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

    standingBlocks[0].moveDown(standingBlocks[0].getPosX(),standingBlocks[0].getPosY(),2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
        return 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
            movingLeft =true;
    }
    else
    {
       movingLeft =false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
            movingRight =true;
    }
    else
    {
       movingRight =false;
    }

    posX = moving_player_horizontally(posX);
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

    for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
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
                    if(i!=0)
                    {
                        posY = standingBlocks[i].getPosY()-playerSizeY;
                    }
                    if(i==0)
                    {
                        posY = standingBlocks[i].getPosY()-playerSizeY;
                        posY+=2;
                    }
                    std::cout<<i<<'\n';

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
                        posY+=1.5;
                        }
                   }

            }
        }

        //Colliding Right side player
        if (player_collides_right(
            posX,
            posY,
            playerSizeX,
            playerSizeY,
            standingBlocks[i],
            movingRight) == true)
        {
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

    if(isGrounded==true)
    {
          if(jump_player_vertically()==true)
          {
              jumpingForce=-22;
              isGrounded =false;
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

    window.clear();
    window.draw(player);
    for(const auto block: blocks)
    window.draw(block);
    for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
    standingBlocks[i].displash(window);
    //splashy.displash(window);
    window.display();
    }
    return 0;
}


