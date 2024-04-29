#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "Building.h"


class Residence:public Building{
    friend class BuildingObserver;
    friend class GameBoard;
private:
    std::vector<int> otherBlockIndices;
    int purchaseCost;
    std::vector<int> rentWithMutipleOwned;

public:
    Residence(const Building& building,std::vector<int> otherBlockIndices,int purchaseCost, std::vector<int> rentWithMutipleOwned);

    buildingType getType() override;
    bool performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players) override;
};

#endif