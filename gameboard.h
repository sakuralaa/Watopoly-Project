#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include "Building.h"
#include "player.h"
#include "observer.h"
#include "academic.h"
#include "buildingobserver.h"
#include "dicestrategy.h"
#include "dice.h"
#include "gym.h"
#include "residence.h"
#include "collect.h"
#include "goto.h"
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Building;
class Observer;
class Player;

extern vector<char> playerList;
extern vector<int> nonPropertyIndex;
extern vector<int> academicIndex;
extern vector<int> residenceIndex;
extern vector<int> gymIndex;

struct AcademicBuildingData {
    std::vector<int> monopolyBlockIndices;
    int purchaseCost;
    int improvementCost;
    std::vector<int> tuitionWithImprovements;
};


class GameBoard{
    friend class GoToTims;
    vector<shared_ptr<Player>> Players;
    vector<shared_ptr<Building>> Buildings;
    shared_ptr<Player> currPlayer;
    size_t currPlayerIdx;
    vector<Observer*> observers;
    unique_ptr<DiceStrategy> diceStrg;

public:
    GameBoard();
    void init();
    bool playerMove(int move);
    bool nextPlayer();
    void attachObserver(Observer* b);
    void loadGame(const std::string& filename);
    void setObserver1Src();
    void bankrupt();
    void setDiceStrategy(unique_ptr<DiceStrategy> dStrategy);
    pair<int,int> roll();
    void auction(shared_ptr<Building> building);
    void all() const;
    bool canRoll = true;
    string getCurrPlayer();

};

#endif