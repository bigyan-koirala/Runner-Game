#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cmath>
#include<iostream>
#include<iomanip>
#include "line.h"
#include "road.h"
#include "generator.h"
#include "menu.h"
#include"Scoreboard.h"
#include<sstream>
#include"Score.h"


using namespace sf;




//Player follows parabolic path to change between wires//
float GetParabolicY(int positionPartition, int noOfPartitions, float currentY, int radius = 0.195 * width)
{
    if (positionPartition < noOfPartitions) {
        float x = ((float)positionPartition / (float)noOfPartitions) * 2 * radius;
        return radius * abs(radius - x) / (float)radius;
    }
    else return height/2;
}

int main()
{
    sf::RenderWindow Load_Menu(sf::VideoMode(width, height), "Wire Run",Style::Close);

    if(LoadMenu(Load_Menu,true)== true)
        Load_Menu.close();
    else if(LoadMenu(Load_Menu,true)==false)
        return 0;

    sf::RenderWindow app(VideoMode(width, height),"Wire Run", Style::Close);
    app.setFramerateLimit(45);

//-----------------------GETTING THINGS READY--------------------------//
   //----LOAD BACKGROUND----//
    Texture background_img;
    background_img.loadFromFile("gb.png");
    background_img.setRepeated(true);

    Sprite background(background_img);
    background.setTextureRect(IntRect(0,0,5000,792));
    background.setPosition(-1500,-300);
//-------------------------------------------------------------//
   //---CREATE SCORE TEXT------//
    Font font;
    font.loadFromFile("bb.ttf");
    Text score_text;
    score_text.setPosition(width-1000, 25);
    score_text.setFont(font);
//------------------------------------------------------------//
   //----CREATE COLLIDER-------//
    CircleShape collider(30);
    float colliderX = width/2-40;
    float colliderY = height/2+200;
    collider.setPosition(colliderX,colliderY);

   //------PLAYER SETUP--------//
    Vector2f playerSize(210.0f,350.0f); //size of each frame

    Texture playerFoto;
    playerFoto.loadFromFile("man.png");

    Sprite player(playerFoto);
    player.setPosition(width/2-75,height/2-50);

    int framesNum = 27;
    float animDuration = 0.45; //seconds

    Clock clockForPlayer;
    float deltatime=0; //for elapsed time
//-------------------------------------------------------------------------//
   //----LOAD OBSTACLES----//
    Texture t[20];
    Sprite obstacle[20];
    for(int i=1; i<16; i++)
    {
        t[i].loadFromFile("images/"+patch::to_string(i)+".png");
        t[i].setSmooth(true);
        obstacle[i].setTexture(t[i]);
    }
   //----LOAD COIN----//
    Texture tcoin;
    tcoin.loadFromFile("coin.png");
    tcoin.setSmooth(true);
    Sprite coin;
    coin.setTexture(tcoin);
    



   //----LOAD SOUNDS-------//
    
    sf::SoundBuffer coinbuff;
    coinbuff.loadFromFile("sound\\coin sound.ogg");
    sf::Sound playCoin(coinbuff);

    sf::SoundBuffer collisonbuff;
    collisonbuff.loadFromFile("sound\\impact sound.ogg");
    sf:: Sound collideSound(collisonbuff);

    sf::Music gameMusic;
    gameMusic.openFromFile("sound\\gsound.ogg");
    gameMusic.setLoop(true);

/////Generating coins, obstacles and lines in 3D
    generateLines();
    generateObstacles(obstacle);
    generateCoins(coin);

//-----------------SOME INITIALIZERS-----------------------------//
    int N = lines.size(); //total number of lines
    int posZ=0;
    int posX=0;
    int score = 0;
    int coins = 0;
    int coin_collected = 0;

    bool isAlive = true;
    int speed=200;

    Clock clockForScore;
    Clock clockForCoin;
    float collideTime = 0;

//Initializers for player movement
    bool isJumping =false;
    float moveSpeed = 300.f;

    int holdTime = 350; //milliseconds
    int partitionPosition = 0, maxFramesForJump = 25;
    bool moveRight=false, moveLeft=false;
    float currentX = colliderX;


//--------------------WINDOW STARTS-------------------------------//

    app.setKeyRepeatEnabled(false);
    gameMusic.play();
    Clock rightClock;
    Clock leftClock;
    float x, y, prevX=0, prevY=0;

   while(app.isOpen())
   {
      
       
        
        if(Keyboard::isKeyPressed(Keyboard::Right))
        {   
            
            Time timeRight = rightClock.getElapsedTime();
                
            if (timeRight.asMilliseconds()>holdTime)
            {
                 if (collider.getPosition().x < colliderX + 0.39*width)
                 {
                     if (partitionPosition > maxFramesForJump) partitionPosition = 0;
                    //collider.move(0.39 * width, 0); 
                    moveRight = true;
                    currentX = player.getPosition().x;
                    //prevX = prevY = 0;
                    rightClock.restart();                   

                 }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            Time timeLeft = leftClock.getElapsedTime();
            if (timeLeft.asMilliseconds() > holdTime)
            {
                if (collider.getPosition().x > colliderX - 0.39*width)
                {
                    if (partitionPosition > maxFramesForJump) partitionPosition = 0;

                    currentX = player.getPosition().x;
                    moveLeft = true;
                   // prevX = prevY = 0;
                    leftClock.restart();
                }
             }

        }
        
        
       
        if (moveRight) 
        {
           // x = ; y = GetParabolicY(partitionPosition, maxFramesForJump, player.getPosition().y);
            collider.setPosition((currentX+ (((float)partitionPosition / maxFramesForJump) * 0.4 * width)), GetParabolicY(partitionPosition, maxFramesForJump, player.getPosition().y));
            player.setPosition((currentX+ (((float)partitionPosition / maxFramesForJump) * 0.4 * width)), GetParabolicY(partitionPosition, maxFramesForJump, player.getPosition().y));
           // std::cout << player.getPosition().x<<" "<< player.getPosition().y<<"\n";
            
        }
        if (moveLeft)
        {
            collider.setPosition((currentX - ((float)partitionPosition / maxFramesForJump) * 0.4 * width), GetParabolicY(partitionPosition, maxFramesForJump, player.getPosition().y));
            player.setPosition((currentX - ((float)partitionPosition / maxFramesForJump) * 0.4 * width), GetParabolicY(partitionPosition, maxFramesForJump, player.getPosition().y));
        }

        
        if (partitionPosition > maxFramesForJump)
        {
            partitionPosition = maxFramesForJump;         
            moveLeft = moveRight= false;
        }
       


        if (collider.getPosition().x < colliderX - 0.4 * width || player.getPosition().x < colliderX - 0.4 * width)
        {
            collider.setPosition(colliderX - 0.4 * width,collider.getPosition().y);
            player.setPosition(colliderX - 0.4 * width,player.getPosition().y);
        }
        if (collider.getPosition().x > colliderX + 0.4 * width || player.getPosition().x > colliderX + 0.4 * width)
        {
            collider.setPosition(colliderX + 0.4 * width,collider.getPosition().y);
            player.setPosition(colliderX + 0.4 * width,player.getPosition().y);
        }

//----------X, Y, Z POSITIONs INITIALIZE---------------------//
        float x=0, dx=0;
        int maxy = height;
      //----INCREASE SPEED AFTER 2000POINTS----//
        if(score>30)
        {
            speed=300;
            animDuration = 0.57;
        }

        if(isAlive)
            posZ+=speed;//moves the environment with same speed as player

        int startPos=posZ/segL;

        //MOving the background
        if(isAlive)
            if(speed>0)
                background.move(-lines[startPos].getCurve()*2,0);

       if(isAlive)
            score = clockForScore.getElapsedTime().asMilliseconds()/1000;
            //coins= clockForCoin.getElapsedTime().asMilliseconds()/2000;

            score_text.setString("Scores: "+patch::to_string(score)+"\nCoin: "+patch::to_string(coins));

        //------COIN Collision Test----//   
        if(isAlive)
        if(lines[startPos].getCoinBounds().intersects(player.getGlobalBounds()))
            {
                coin_collected++;
                playCoin.play();
            }

        

       
        //------COLLISION DETECTION------//
        if(isAlive)
        if(lines[startPos+10].getObstacleBounds().intersects(collider.getGlobalBounds()))
        {
            collideSound.play();
            isAlive = false;
        }
        
        app.clear();
        app.draw(background);

        float outerLineWidth = 0.8f, innerLineThickness = 0.05f, outerLineThickness = 0.7f;

        partitionPosition++;
        //std::cout << partitionPosition;
    //--------THIS IS THE MAIN LOOP FOR RUNNING--------//
        for(int n=startPos; n<startPos+300; n++)
        {
            Line &l = lines[n]; //Line &l is reference to each line being drawn

            l.projectToScreen(posX-x, 1500,posZ - (n>=N?N*segL:0));

            x+=dx;
            dx+=l.getCurve();

            if(l.getY()>=maxy)
                continue;

            Line p = lines[(n-1)%N]; //previous line

        //----------DEFINE COLORS---------------//
            Color environment = (n/5)%2?Color(2,41,2):Color(100,0,0);
            Color road = Color(255,100,0);
          
            
        //----------DRAWING ROADS AND ENVIROMENT-------------------//
            DrawQuad env(app, environment,0,p.getY(),width,0,l.getY(),width);

            DrawQuad side(app, road, p.getX(),p.getY(), p.getW()* outerLineWidth, l.getX(),l.getY(), l.getW()* outerLineWidth);

            DrawQuad road_lane(app,environment,p.getX(),p.getY(),p.getW()* outerLineThickness,l.getX(),l.getY(),l.getW()* outerLineThickness);
            
            DrawQuad m_side(app, road, p.getX(), p.getY(), p.getW() * innerLineThickness, l.getX(), l.getY(), l.getW() * innerLineThickness);

        }



    //-------drawing obstacles and coins----------//
        for(int n=startPos+500; n>startPos; n--)
        {
           lines[n].drawSprite(app);
           lines[n].drawCoin(app);
        }


    //------PLAYER ANIMATION-----------//
        if(isAlive)
            deltatime += clockForPlayer.restart().asSeconds();

        //---Get Current Frame----//
        int animFrame = static_cast<int>((deltatime/animDuration)*framesNum)%framesNum;

        //---Set Sprite Rectangle Based on Frame---//
        player.setTextureRect(IntRect(animFrame * playerSize.x, 10, playerSize.x, playerSize.y));

        if (isAlive)
        {
            app.draw(player);
            app.draw(score_text);
        }


     //------SCORE BOARD-------//
        if(isAlive==false)
        {
            collideTime+=clockForScore.restart().asSeconds();

            if(collideTime>2)
                ScoreBoard scoreboard(app,font,score,coin_collected);

            Event ev;
            while(app.pollEvent(ev))
            {
                if(ev.type==Event::Closed) app.close();

                if(ev.type==Event::KeyPressed)
                {
                    if(ev.key.code==Keyboard::Return)
                        if(LoadMenu(app,false))
                        {
                            posZ = 0;
                            posX = 0;
                            score = 0;
                            coin_collected = 0;
                            isAlive = true;
                        }

                }
            }
        }

        app.display();
    }
return 0;
}