#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <vector>
#include <memory>
#include <string>
#include <iostream>
using namespace std;


class Player{
    friend class GameBoard;
    friend class GoToTims;
    friend class DCTimsLine;
    string name;
    int timCups;
    int currPosition;
    int asset;
    vector<int> property;
    bool isTrapped;
    bool isBankrupt;
    int oweMoney;
    int turnsTrap;

public:
    Player(string name, int timCups = 0,int currPos = 0, float asset = 0, vector<int> property = {}, bool isTrapped = false,
    bool isBankrupt = false,int oweMoney = 0,int trunsTrap = 0);
    string getName() const;
    int getPosition() const;
    void move(int steps);
    bool charge(int amount);
    void setBankrupt();
    void setTrap();
    void addMoney(int amount);
    void setOweMoeny(int amount);
    int getAsset();
};


#endif