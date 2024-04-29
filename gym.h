#ifndef _GYM_H_
#define _GYM_H_

#include "Building.h"
#include "gameboard.h"

class GameBoard;

class Gym : public Building {
    friend class BuildingObserver;
    friend class GameBoard;
    vector<int> otherBlockIndices;
    GameBoard* gameBoard;
    int purchaseCost;
    bool ownedTwo;

public:
    Gym(const Building& building, vector<int> otherBlockIndices, GameBoard* gameBoard, int purchaseCost,bool ownedTwo = false);

    bool performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players) override;
};



#endif