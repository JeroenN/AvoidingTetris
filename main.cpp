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
        :block()
    {
        block.setSize(sf::Vector2f(height, width));
        block.setPosition(sf::Vector2f(posX, posY));
        block.setFillColor(sf::Color(255, 127, 63));
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

    void setPositionBlock(float posX, float posY)
    {
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

std::vector<standingBlock> create_L_block() noexcept
{
    std::vector<standingBlock> v;
    v.push_back(standingBlock(30,30,100,0));
    v.push_back(standingBlock(30,30,100,30));
    v.push_back(standingBlock(30,30,100,60));
    v.push_back(standingBlock(30,30,130,60));
    return v;
}

///Does the player have a collission with a standing block at his/her right side?
bool player_collides_right(
    const float posX,
    const float posY,
    const float playerSizeX,
    const float playerSizeY,
    const standingBlock& standingBlock
)
{
    bool movingRight=false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            movingRight =true;
    }
    else{
       movingRight =false;
    }

    return posY +playerSizeY > standingBlock.getPosY()
      && posY < standingBlock.getPosY()+standingBlock.getHeight()
      && posX +playerSizeX <standingBlock.getPosX() + 20
      && posX + playerSizeX> standingBlock.getPosX()
      && movingRight
    ;
}

///Does the player have collission with a standing block at his/her left side?
bool player_collides_left(
    const float posX,
    const float posY,
    const float playerSizeY,
    const standingBlock& standingBlock
    //const bool movingLeft
)
{
    bool movingLeft=false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            movingLeft =true;
    }
    else{
       movingLeft =false;
    }
    return posY +playerSizeY > standingBlock.getPosY()
      && posY < standingBlock.getPosY()+standingBlock.getHeight()
      && posX > standingBlock.getPosX() + standingBlock.getWidth()-20
      && posX< standingBlock.getPosX() +standingBlock.getWidth()
      && movingLeft
     ;
}

bool player_collides_head(
        const float posX,
        const float posY,
        const float playerSizeX,
        const standingBlock& standingBlock

        )
{
   return posY > standingBlock.getPosY()+20
       && posY < standingBlock.getPosY()+standingBlock.getHeight()
       && posX + playerSizeX> standingBlock.getPosX()
       && posX < standingBlock.getPosX()+standingBlock.getWidth()
      ;
}

bool player_collides_bottem(
        const float posX,
        const float posY,
        const float playerSizeX,
        const float playerSizeY,
        const standingBlock& standingBlock
      )
{
      if((posY+playerSizeY >standingBlock.getPosY()
      && posY+playerSizeY < standingBlock.getPosY()+20)
      || posY==standingBlock.getPosY()-playerSizeY)
      {

      if(
       posX + playerSizeX> standingBlock.getPosX()
       && posX < standingBlock.getPosX()+standingBlock.getWidth())
        {
          return true;
        }
     }

      return false;
}

float moving_player_horizontally(float posX)
{
    float speed =8;
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

float jumping_gravity(float jumpingForce, bool isGrounded)
{
    float gravity=0.9;
    if(isGrounded ==false)
    {
        if(jumpingForce<=14)
        jumpingForce+=gravity;
    }
    return jumpingForce;
}
float player_screenborder_collision(float posX, float windowSizeX, float playerSizeX)
{
    if(posX<0)
    {
        posX=0;
    }
    if(posX+playerSizeX>windowSizeX)
    {
        posX= windowSizeX-playerSizeX;
    }
    return posX;
}

int main()
{
   // std::vector<standingBlock> standingBlocks = create_standing_blocks();
    std::vector<standingBlock> standingBlocks = create_L_block();
    int posX=300;
    int windowSizeX=700;
    int windowSizeY = 900;
    int playerSizeX=25;
    int playerSizeY=40;
    float jumpingForce = 0;
    bool isGrounded =true;
    float slidingSpeed =3;
    float blockSpeedMovingDown =1;
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
    for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
    {
        standingBlocks[i].moveDown(standingBlocks[i].getPosX(),standingBlocks[i].getPosY(),blockSpeedMovingDown);
        if(900<standingBlocks[i].getPosY())
        {
            standingBlocks[i].setPositionBlock(100, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
        return 0;
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

        if(player_collides_bottem(
            posX,
            posY,
            playerSizeX,
            playerSizeY,
            standingBlocks[i]) == true)
        {
            if(jumpingForce>0)
            {
                isGrounded=true;
                //Needs to be a true or false statement: if( blockMovingDown ==true)
                posY = standingBlocks[i].getPosY()-playerSizeY;
                std::cout<<posY<<"\n";
               // if(i==0)

                posY+=blockSpeedMovingDown;

            }
        }

        //Hitting a block with your head
        if(player_collides_head(
            posX,
            posY,
            playerSizeX,
            standingBlocks[i]) == true)
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


        //Collding left side player
        if (player_collides_left(
            posX,
            posY,
            playerSizeY,
            standingBlocks[i]) == true)
        {
            isGrounded=false;
            posX=standingBlocks[i].getPosX()+standingBlocks[i].getWidth();
           // posY+=2;
            jumpingForce=0;
                if(posX ==standingBlocks[i].getWidth()+standingBlocks[i].getPosX())
                {
                    posY+=slidingSpeed;
                }

            }

        if(posY==standingBlocks[i].getPosY()-playerSizeY &&
          posX + playerSizeX > standingBlocks[i].getPosX()  &&
          posX < standingBlocks[i].getPosX()+standingBlocks[i].getWidth())
        {
           slidingSpeed=0;
        }
        else
        {
            slidingSpeed=3;
        }

        //Colliding Right side player
        if (player_collides_right(
            posX,
            posY,
            playerSizeX,
            playerSizeY,
            standingBlocks[i]) == true)
        {
            isGrounded=false;
            posX=standingBlocks[i].getPosX()-playerSizeX;
            //posY+=2;
            jumpingForce=0;
            if(posX ==standingBlocks[i].getPosX()-playerSizeX)
            {
            posY+=slidingSpeed;
            }

        }
    }
    posX= player_screenborder_collision(posX,windowSizeX, playerSizeX);

    if(isGrounded==true)
    {
          if(jump_player_vertically()==true)
          {
              jumpingForce=-22;
              isGrounded =false;
          }
     }
    jumpingForce= jumping_gravity(jumpingForce, isGrounded);
    if(!isGrounded)
    {
    posY+=jumpingForce;
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

