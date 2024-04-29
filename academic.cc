#include "academic.h"

AcademicBuilding::AcademicBuilding(const Building& building, 
                     const std::vector<int>& monopolyIndices, 
                     int purchase, 
                     int improvement, 
                     const std::vector<int>& tuition,
                     bool improvementEnabled)
    : Building(building),
      monopolyBlockIndices(monopolyIndices),
      purchaseCost(purchase),
      improvementCost(improvement),
      tuitionWithImprovements(tuition),
      improvementEnabled(improvementEnabled){
        currTuition = tuitionWithImprovements[level];
      }

buildingType AcademicBuilding:: getType(){
  return academic;
}

bool AcademicBuilding::performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players){
  if(player->getName() == this->getOwner() && improvementEnabled){
    cout << "do you want to improve this building? y or n" << endl;
    char cmd;
    cin >> cmd;
    if(cmd == 'y'){
      player->charge(improvementCost);
      this->level ++;
      currTuition = tuitionWithImprovements[this->level];
    }
    return true;
  }
  else if(owner == "none"){
    return true;
  }
  else if(player->charge(currTuition)){
    cout << "player " << player->getName() <<" paid " <<currTuition <<", game continue" << endl;
    for(auto i : players){
      if(i->getName() == owner){
        i->addMoney(currTuition);
        break;
      }
    }
    return true;
  }else{
    player->setBankrupt();
    player->setOweMoeny(currTuition);
    return false;
  }
}

