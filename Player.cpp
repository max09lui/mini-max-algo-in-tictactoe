#pragma once

#include "Player.h"
#include <random>
#include <iostream>
#include <string>

using namespace std;

class GRIDCOPY;

Player::Player(string* p)
{
    Grid = p;
}

void Player::display()
{
    //system("CLS");
    cout << "------" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            cout << Grid[i][j];
        }
        cout << "|" << endl;
    }
    cout << "------" << endl;
}

int Player::generateRandomNumber()
{
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 2);
    return distribution(generator);
}

HumanPlayer::HumanPlayer(string* p)
    : Player(p)
{}
void HumanPlayer::move(int& row, int& col, int turn)
{
    cin >> row;
    cin >> col;
}

RandomBot::RandomBot(string* p)
    : Player(p)
{}

void RandomBot::move(int& row, int& col, int turn)
{


    //row = rand() % 3;
    //col = rand() % 3;
    row = generateRandomNumber();
    col = generateRandomNumber();
}

class GRIDCOPY// add game functions to simulate game to get to end for result score 
{
public:
    string grid[3] = { "   ",
                        "   ",
                        "   " };
    GRIDCOPY(string* p)
    {
        for (int i = 0; i < 3; i++)
        {

            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = p[i][j];
            }

        }
    }
    GRIDCOPY(const GRIDCOPY& G)
    {
        for (int i = 0; i < 3; i++)
        {
            grid[i] = G.grid[i];

        }
    }
    void display()
    {
        //system("CLS");
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
    void move(int row, int col, int turn)
    {
        
        if (turn % 2 != 0)
        {
            grid[row][col]= 'X';
        }
        else
        {
            grid[row][col] = 'O';
        }

        
    }

};


TreeBot::TreeBot(string* p)
    : Player(p)
{

}

bool TreeBot::validmove(int row, int col, GRIDCOPY GC)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            if (GC.grid[i][j] != ' ')
            {
                count++;
            }
        }
    }

    if (count == 9)
    {
        return false;
    }


    if (GC.grid[row][col] == ' ')
    {
        //cout << "sdgsdgsdgsd" << endl;
        return true;
    }
    else
    {
        //cout << "invalid move, move again" << endl;
        return false;
    }

}
bool TreeBot::winner(char& PWIN, GRIDCOPY GC)
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
                if (GC.grid[i][j] == P)
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
                if (GC.grid[j][i] == P)
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
            if (GC.grid[i][i] == P)
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
            if (GC.grid[2 - i][i] == P)
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
            if (GC.grid[i][j] != ' ')
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



void TreeBot::move(int& row, int& col, int turn)
{
    int r = 0, c = 0;
    int cscore = 0; 
    char P, CP;

    if (turn % 2 != 0)
    {
        P = 'X';
        CP = 'O';
    }
    else
    {
        P = 'O';
        CP = 'X';
    }

    GRIDCOPY g(Grid);

    

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (validmove(i, j, g) == true)
            {
                
                
                int score = evaluate(i, j, P, CP, g, turn);
                //cout << r << " " << c<< " --- " << i << " " << j << endl;
                //cout << score << " " << cscore << endl;

                if (score > cscore)
                {
                    //cout << "AAA" << endl;
                    r = i;
                    c = j;

                }
            }
            
        }
    }

    row = r;
    col = c;
}

int TreeBot::evaluate(int row, int col, char FP, char CP, GRIDCOPY TempGrid, int turn)
{
    GRIDCOPY GC(TempGrid);

    //GC.display();

    GC.move(row, col, turn);
    //GC.display();

    /*if (turn == 2)
    {
        GC.display();
        return 1;
    }*/

    
    


    char PWIN;
    //cout << turn << endl;
    //cout << "WINNER " << winner(PWIN, GC) << endl;

    
    if (winner(PWIN, GC)== true)//winner check func 
    {
        //cout << "Game end" << endl;
        if (PWIN == FP)
        {
            
            return 10;
        }
        else if (PWIN == 'T')
        {
            return 3;
        }
        else
        {
            return 1;
        }

    }

    //cout<<"*** "<<validmove(0, 0, grid) << endl; 

    if (CP == 'X')// dont need? 
    {
        CP = 'O';
    }
    else
    {
        CP = 'X';
    }
    
    
    int cscore = 0;
    int r = 0;
    int c = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            //GC.display();
            //cout << i << " " << j << " " << validmove(i, j, GC) << endl;
            if (validmove(i, j, GC) == true)
            {
                

                int score= evaluate(i, j, FP, CP, GC, turn + 1);
                /*if (r == 0 && c == 0)
                {
                    cout << score << endl;
                }*/

                //cout << score << endl;

                if (score >= cscore)
                {   
                    
                    //cout <<"("<< i << " ," << j << ") *** stored: (" << r << "," << c <<")"<< endl;
                    //cout << cscore << " - " << score << endl;


                    cscore = score; 
                    r = i;
                    c = j;

                }
            }
            
            /*else
            {
                
                return -1;
            }*/
            
        }
    }
    
    
    //GC.display();
    //return cscore;
    return cscore;
}

/*
int main()
{

    string grid[3] = { "A  ",
                       "   ",
                       "   " };

    GRIDCOPY g(grid);
    //Player* p = new TreeBot(grid);
    TreeBot p(grid);
    RandomBot p2(grid);
    
    
    //cout<<p.validmove(0, 0, grid);


    
    int row = 1, col = 1;
    p.move(row, col, 1);
    cout << row << " " << col << endl; 
    
    //p2.move(row, col, 2);
    //cout << row << " " << col << endl;
    //p.move(row, col, 3);
    //cout << row << " " << col << endl;

}
*/