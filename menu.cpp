#include "menu.h"
#include<string>
#include<iostream>

sf::Font Menu::font;
sf::SoundBuffer Menu::sbuffer;
sf::Sound Menu::click_sound;


bool LoadMenu(sf::RenderWindow &app, bool flowIntro)
{
    Menu::LoadAssests();

    bool flowMenu=true;
 
    if(!flowIntro)
        flowMenu = true;

    Menu Menu_items(app.getSize().x, app.getSize().y);
    app.setKeyRepeatEnabled(false);
    while(app.isOpen())
    {
        app.clear();

        if(flowIntro)
        {
            sf::Event ev;
            while(app.pollEvent(ev))
            {
                if(ev.type==sf::Event::Closed)
                    exit(0);
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                flowMenu = true;
                flowIntro = false;
            }
        }

        sf::Event event;
        if(flowMenu)
        {
        while(app.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                {
                    exit(0);
                };

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Down)
                    Menu_items.MoveDown();
            }

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Up)
                    Menu_items.MoveUp();
            }

            if(event.type==sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Return)
                {
                    switch(Menu_items.GetPressedItem())
                    {
                        case 0 : return true;
                        case 1:std::cout<<"Instructions clicked";
                        case 2 : break;
                        case 3 : exit(0);
                    }
                }
            }

        }
            Menu_items.draw(app);
        }


        app.display();
    }

}

