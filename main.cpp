#include <iostream>
#include <stdlib.h>
#include <random>
#include "Player.h"
#include "tictactoe.h"

using namespace std;


int main()
{
    int Xnum = 0, Onum=0, Tnum = 0;

    for (int i = 0; i < 30; i++)
    {
        string grid[3] = {  "   ",
                            "   ",
                            "   " };



        Player* p1 = new HumanPlayer(grid);
        Player* p2 = new TreeBot(grid);

        tictactoe game(p1, p2, grid);
        char winner = game.play();

        if (winner == 'X')
        {
            Xnum++;
        }
        else if (winner == 'O')
        {
            Onum++;
        }
        else if (winner == 'T')
        {
            Tnum++;
        }

        cout << "Winners" << endl;
        cout << "X wins: " << Xnum << endl;
        cout << "O wins: " << Onum << endl;
        cout << "Ties: " << Tnum << endl;

    }

    
    
    

    return 0;
}