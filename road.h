#pragma once
#include <SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
#include<fstream>

//CLASS TO Draw Wires

class DrawQuad
{
private:
    sf::ConvexShape shape;

public:
    DrawQuad(sf::RenderWindow &app, sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2)
    {
        shape.setPointCount(4);
        shape.setFillColor(c);
        shape.setPoint(0,sf::Vector2f(x1-w1,y1));
        shape.setPoint(1,sf::Vector2f(x2-w2,y2));
        shape.setPoint(2,sf::Vector2f(x2+w2,y2));
        shape.setPoint(3,sf::Vector2f(x1+w1,y1));
        app.draw(shape);
    }

    ~DrawQuad() {}
};




   