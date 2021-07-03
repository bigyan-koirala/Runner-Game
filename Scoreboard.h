#pragma once

#include <SFML/Graphics.hpp>
#include"Score.h"
class ScoreBoard:public Score
{
private:
    sf::RectangleShape box;
    sf::Text text[2];
    sf::Font font;

public:
    ScoreBoard(sf::RenderWindow& app, sf::Font font, int score, int coin)
    {
        font.loadFromFile("Adventure.otf");
        box.setSize(sf::Vector2f(310, 160));
        box.setPosition(width / 2 , height / 2 );
        box.setFillColor(sf::Color(10, 150, 100));
        box.setOutlineColor(sf::Color::Red);
        box.setOutlineThickness(3);

        text[0].setPosition(box.getPosition().x + 15, box.getPosition().y + 10);
        text[0].setFillColor(sf::Color(136, 1, 131));
        text[0].setFont(font);
        text[0].setCharacterSize(28);
        text[0].setString("GAME OVER:");

        text[1].setPosition(box.getPosition().x + 25, box.getPosition().y + 50);
        text[1].setFillColor(sf::Color(4, 181, 162));
        text[1].setFont(font);
        text[1].setCharacterSize(20);


        if (Score::checkHighScore(score, coin) == true)
            text[1].setString("Score: " + patch::to_string(score) + "\nCoin: " + patch::to_string(coin) + "\n\n  \tNEW HIGHSCORE");
        else
            text[1].setString("Score: " + patch::to_string(score) + "\nCoin: " + patch::to_string(coin));


        app.draw(box);
        app.draw(text[0]);
        app.draw(text[1]);
    }



    ~ScoreBoard() {}
};

