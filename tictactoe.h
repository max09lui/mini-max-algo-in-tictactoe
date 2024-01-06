#pragma once

#include <string>

class Player;

class tictactoe
{
public:
    int turn = 1;
    Player* PlayerX;
    Player* PlayerO;

    /*string grid[3]= {"   ",
                        "   ",
                        "   ", };*/

    std::string* grid;
    tictactoe(Player* p1, Player* p2, std::string g[3]);
    void display();
    void enddisplay(char winner);
    char play();
    bool validmove(int row, int col);
    bool winner(char& PWIN);
    

private:


};
