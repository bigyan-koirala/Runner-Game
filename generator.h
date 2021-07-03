#pragma once
#include "line.h"

//this is a CONTAINER to contain all the lines being created//
std::vector<Line> lines;

//-------LINE GENERATOR-------------//
     void generateLines()
    {
        for (int i = 0; i < 4000; i++)
        {
            Line line;
            line.z = i * segL;

            if (i > 300 && i < 700)
                line.curve = 0.8; //for right turn in road

            if (i > 1100 && i < 1400)
                line.curve = -0.7; //for left turn in road

            lines.push_back(line); //each line is added to VECTOR CONTAINER
        }
    }

    void generateObstacles(sf::Sprite ob[])
    {
        for (int i = 0; i < 4000; i++)
        {

            if (i > 450 && (i % 311) == 0)
            {
                lines[i].spriteX = -0.4f;
                lines[i].sprite = ob[12];
            }
            if (i > 250 && ((i + 50) % 111) == 0)
            {
                lines[i].spriteX = -1.4f;
                lines[i].sprite = ob[11];
            }

            if (i > 500 && (i) % 111 == 0)
            {
                lines[i].spriteX = 0.78f; lines[i].sprite = ob[13];
            }


        }
    }

     void generateCoins(sf::Sprite& coinn)
    {
        for (int i = 0; i < 4000; i++)
        {
            if (i > 500 && (i + 121) % 59 == 0)
            {
                lines[i].coinX = 3.0f;
                lines[i].coin = coinn;
            }

            if (i > 100 && (i) % 49 == 0)
            {
                lines[i].coinX = 0.0;
                lines[i].coin = coinn;
            }
        }
    }
