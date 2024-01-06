#include <iostream>

#include "tictactoe.h"
#include "Player.h"

using namespace std;

tictactoe::tictactoe(Player* p1, Player* p2, string g[3])
{
    PlayerX = p1;
    PlayerO = p2;
    grid = g;
}


void tictactoe::display()
{
    string title;

    if (turn % 2 != 0)
    {
        title = "X's turn";
    }
    else
    {
        title = "O's turn";
    }

    system("CLS");
    cout << title << endl;
    cout << "------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            cout << grid[i][j];
        }
        cout << "|" << endl;
    }
    cout << "------" << endl;

    for (int i = 0; i < 1000000000; i++)
    {
        i++;
    }

}

void tictactoe::enddisplay(char winner)
{
    system("CLS");
    if (winner == 'X' || winner == 'O')
    {
        cout << "player " << winner << " has won" << endl;
    }
    else
    {
        cout << "Tie game" << endl;
    }


    cout << "------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            cout << grid[i][j];
        }
        cout << "|" << endl;
    }
    cout << "------" << endl;
}

char tictactoe::play()
{
    int row, col;
    char PWIN;

    while (winner(PWIN) == false)
    {
        display();

        cout << "enter row, col" << endl;



        do
        {
            if (turn % 2 != 0)
            {
                PlayerX->move(row, col, turn);
            }
            else
            {
                PlayerO->move(row, col, turn);
            }
            cout << row << " " << col << endl;
            //player+

            //cin >> row;
            //cin >> col;

        } while (validmove(row, col) == false);

        

        if (turn % 2 != 0)
        {
            grid[row][col] = 'X';
        }
        else
        {
            grid[row][col] = 'O';
        }

        turn++;
    }

    enddisplay(PWIN);

    return PWIN;
}

bool tictactoe::validmove(int row, int col)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] != ' ')
            {
                count++;
            }
        }
    }

    if (count == 9)
    {
        return true;
    }


    if (grid[row][col] == ' ')
    {
        return true;
    }
    else
    {
        cout << "invalid move, move again" << endl;
        return false;
    }

}
bool tictactoe::winner(char& PWIN)
{

    for (int a = 0; a < 2; a++)
    {
        char P;
        if (a == 0)
        {
            P = 'X';
        }
        else
        {
            P = 'O';
        }

        for (int i = 0; i < 3; i++)
        {
            int count = 0;

            for (int j = 0; j < 3; j++)// diagonal 
            {
                if (grid[i][j] == P)
                {
                    count++;
                }

                if (count == 3)
                {
                    PWIN = P;
                    return true;
                }

            }

            count = 0;

            for (int j = 0; j < 3; j++)// row 
            {
                if (grid[j][i] == P)
                {
                    count++;
                }

                if (count == 3)
                {
                    PWIN = P;
                    return true;
                }

            }

        }

        int count = 0;

        for (int i = 0; i < 3; i++)// diag 
        {
            if (grid[i][i] == P)
            {
                count++;
            }

            if (count == 3)
            {
                PWIN = P;
                return true;
            }
        }

        count = 0;

        for (int i = 0; i < 3; i++)
        {
            if (grid[2 - i][i] == P)
            {
                PWIN = P;
                count++;
            }

            if (count == 3)
            {
                PWIN = P;
                return true;
            }
        }




    }


    int count = 0;
    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] != ' ')
            {
                count++;
            }
        }
    }

    if (count == 9)
    {
        PWIN = 'T';
        return true;
    }

    //win (diag or row/ col)
    //tie
    return false;
}

