#include <string>
//using namespace std;

class GRIDCOPY;

class Player
{
public:

    //std::string* grid;
    std::string* Grid;
    Player(std::string* p);
    virtual void move(int& row, int& col, int turn) = 0;
    void display();
    int generateRandomNumber(); 

};

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string* p);
    void move(int& row, int& col, int turn);
};

class RandomBot : public Player
{
public:
    RandomBot(std::string* p);
    void move(int& row, int& col, int turn);

};

class TreeBot : public Player
{
public:
    TreeBot(std::string* p);
    void move(int& row, int& col, int turn);  
    int evaluate(int row, int col, char FP, char CP, GRIDCOPY TempGrid, int turn);
    bool validmove(int row, int col, GRIDCOPY GC);
    bool winner(char& PWIN, GRIDCOPY GC);
};