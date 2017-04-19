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
        posY+=1;
        block.setPosition(sf::Vector2f(posX, posY));
    }
};
//T block
std::vector<standingBlock> create_standing_blocks() noexcept
{
    std::vector<standingBlock> v;
    v.push_back(standingBlock(90,30,250,570));
    v.push_back(standingBlock(30,30,280,540));
    return v;
}
//L block
std::vector<standingBlock> create_L_block() noexcept
{
    std::vector<standingBlock> v;
    v.push_back(standingBlock(30,30,80,760));
    v.push_back(standingBlock(30,30,80,790));
    v.push_back(standingBlock(60,30,80,820));
    return v;
}
//| block
std::vector<standingBlock> create_i_block() noexcept
{
    std::vector<standingBlock> q;
    q.push_back(standingBlock(30,30,400,0));
    q.push_back(standingBlock(30,30,400,30));
    q.push_back(standingBlock(30,30,400,60));
    q.push_back(standingBlock(30,30,400,90));
    return q;
}
std::vector<standingBlock> create_z_block() noexcept
{
    std::vector<standingBlock> u;
    u.push_back(standingBlock(60,30,100,330));
    u.push_back(standingBlock(60,30,130,360));
    return u;
}
std::vector<standingBlock> create_square_block() noexcept
{
    std::vector<standingBlock> p;
    p.push_back(standingBlock(60,30,400, 280));
    p.push_back(standingBlock(60,30,400,310));
    return p;
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
    if (posY +playerSizeY > standingBlock.getPosY()
     && posY < standingBlock.getPosY()+standingBlock.getHeight())
    {
     if((posX +playerSizeX <standingBlock.getPosX() + 20
     && posX + playerSizeX> standingBlock.getPosX())
     || posX +playerSizeX== standingBlock.getPosX())
     {
         return true;
     }
  }
  return false;
}

///Does the player have collission with a standing block at his/her left side?
bool player_collides_left(
    const float posX,
    const float posY,
    const float playerSizeY,
    const standingBlock& standingBlock
)
{
      if(posY +playerSizeY > standingBlock.getPosY()
      && posY < standingBlock.getPosY()+standingBlock.getHeight())
      {
         if(( posX > standingBlock.getPosX() + standingBlock.getWidth()-20
         && posX< standingBlock.getPosX() +standingBlock.getWidth())
         || posX == standingBlock.getPosX() +standingBlock.getWidth())
         {
         return true;
         }
     }
      return false;
}

bool player_collides_head(
        const float posX,
        const float posY,
        const float playerSizeX,
        const standingBlock& standingBlock

        )
{
   return posY > standingBlock.getPosY()+8
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
      if((posY+playerSizeY >standingBlock.getPosY()-8
      && posY+playerSizeY < standingBlock.getPosY())
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

float moving_player_horizontally(float posX, bool collidingLeft, bool collidingRight)
{
    float speed =7;
    if (collidingRight == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
            posX += speed;
    }
    if (collidingLeft == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
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
    float gravity=1.15;
    if(isGrounded ==false)
    {
        if(jumpingForce<=9)
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

    std::vector<standingBlock> standingBlocks = create_L_block();
    {
      std::vector<standingBlock> v = create_standing_blocks();
      std::copy(std::begin(v), std::end(v), std::back_inserter(standingBlocks));

      std::vector<standingBlock> p = create_square_block();
      std::copy(std::begin(p), std::end(p), std::back_inserter(standingBlocks));

      std::vector<standingBlock> q = create_i_block();
      std::copy(std::begin(q), std::end(q), std::back_inserter(standingBlocks));

      std::vector<standingBlock> u = create_z_block();
      std::copy(std::begin(u), std::end(u), std::back_inserter(standingBlocks));
    }
    int posX=300;
    int windowSizeX=700;
    int windowSizeY = 900;
    int playerSizeX=25;
    int playerSizeY=40;
    float jumpingForce = 0;
    bool isGrounded =true;
    //float slidingSpeed =3;
    float blockSpeedMovingDown =2;
    bool collidingLeft = false;
    bool collidingRight = false;
    std::vector<sf::RectangleShape> blocks;
    int posY = windowSizeY-playerSizeY;
    sf::RenderWindow window(
       sf::VideoMode(windowSizeX, windowSizeY),
       "mt",
       sf::Style::Titlebar | sf::Style::Close);
    sf::RectangleShape player(sf::Vector2f(playerSizeX, playerSizeY));
    player.setOrigin(sf::Vector2f(0,0));

    window.setFramerateLimit(66);
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
            player.setPosition(posX, posY);
    for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
    {
        standingBlocks[i].moveDown(standingBlocks[i].getPosX(),standingBlocks[i].getPosY(),blockSpeedMovingDown);
        if(900<standingBlocks[i].getPosY()&&i!=3)
        {
            standingBlocks[i].setPositionBlock(standingBlocks[i].getPosX(), 0);
        }
        if(900<standingBlocks[i].getPosY()&&i==3)
        {
            standingBlocks[i].setPositionBlock(standingBlocks[i].getPosX(), 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
        return 0;
    }




    posX = moving_player_horizontally(posX, collidingLeft, collidingRight);
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
            posX=standingBlocks[i].getPosX()+standingBlocks[i].getWidth();
            collidingLeft =true;
            i=standingBlocks.size()+1;
        }
        else
        {
            collidingLeft =false;
        }
        //Colliding Right side player
            if (player_collides_right(
                posX,
                posY,
                playerSizeX,
                playerSizeY,
                standingBlocks[i]) == true)
            {
                posX=standingBlocks[i].getPosX()-playerSizeX;
                collidingRight=true;
                i=standingBlocks.size()+1;
            }
            else
            {
                collidingRight=false;
            }
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
                    posY = standingBlocks[i].getPosY()-playerSizeY;
                    //posY+=blockSpeedMovingDown;
                }
            }
        if(collidingRight==true || collidingLeft==true)
        {
            for(int j=0; j< static_cast<int>(standingBlocks.size()); ++j)
            {
                std::cout<<j<<"\n";
                if(player_collides_bottem(
                    posX,
                    posY,
                    playerSizeX,
                    playerSizeY,
                    standingBlocks[j]) == true)
                {
                    std::cout<<"staph";
                    if(jumpingForce>0)
                    {
                        isGrounded=true;
                        posY = standingBlocks[j].getPosY()-playerSizeY;
                        //posY+=blockSpeedMovingDown;
                    }
                }
                if(player_collides_head(
                    posX,
                    posY,
                    playerSizeX,
                    standingBlocks[j]) == true)
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
        }

    }

    posX= player_screenborder_collision(posX,windowSizeX, playerSizeX);

    if(isGrounded==true)
    {
          if(jump_player_vertically()==true)
          {
              jumpingForce=-25;
              isGrounded =false;
          }
     }

    jumpingForce= jumping_gravity(jumpingForce, isGrounded);
    if(!isGrounded)
    {
    posY+=jumpingForce;
    }


    window.clear();
    window.draw(player);
    //window.draw(convex);
    //for(const auto block: blocks)
    //window.draw(block);
    for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
    standingBlocks[i].displash(window);
    //for(int i=0; i<static_cast<int>(standingBlocks.size()); ++i)
    //standingBlocks[i].displash(window);
    //splashy.displash(window);
    window.display();
    }
    return 0;
}
