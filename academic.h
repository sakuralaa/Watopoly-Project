#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "Building.h"

class AcademicBuilding : public Building {
    friend class BuildingObserver;
    friend class GameBoard;
private:
    std::vector<int> monopolyBlockIndices;
    int purchaseCost;
    int improvementCost;
    std::vector<int> tuitionWithImprovements;
    bool improvementEnabled;
    

public:
    AcademicBuilding(const Building& building, 
                     const std::vector<int>& monopolyIndices, 
                     int purchase, 
                     int improvement, 
                     const std::vector<int>& tuition,
                     bool improvementEnabled =false);

    buildingType getType() override;
    bool performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players) override;
};



#endif