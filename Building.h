#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <string>
#include <vector>
#include <memory>
#include "player.h"


class Player;

enum buildingType{general,academic,residence,gym,nonproperty};

class Building{
    friend class GameBoard;
    friend class GoToTims;
    int index;
    std::string name;
    std::vector<std::shared_ptr<Player>> currPlayer;

protected:
    int level;
    string owner;
    int currTuition;


public:
    Building(int index,std::string name,int level = 0,std::vector<std::shared_ptr<Player>> currPlayer = {},string owner = "none" ,int currTuition = 0);
    Building(const Building &other);
    int getIdx() const;
    std::vector<string> getCurrPlayerName() const;
    string getOwner() const;
    int getLevel() const;
    virtual buildingType getType();
    virtual bool performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players);
};

#endif