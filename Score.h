#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
namespace patch
{
    template < typename t > std::string to_string(const t& n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();

    }
}
class Score {
public:

    bool checkHighScore(int score, int coin)
    {
        int hscore, hcoin;
        std::ifstream ifile("score.txt", std::ios::in | std::ios::app);

        if (ifile)
        {
            ifile.read((char*)&hscore, sizeof(hscore));
            ifile.read((char*)&hcoin, sizeof(hcoin));
            ifile.close();
        }

        if (hscore <= score)
        {
            std::ofstream ofile("score.txt", std::ios::out);
            ofile.write((char*)&score, sizeof(score));
            ofile.write((char*)&coin, sizeof(coin));
            ofile.close();

            return true;
        }
        else
            return false;
    }
};
