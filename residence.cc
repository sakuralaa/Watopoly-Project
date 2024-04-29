#include "residence.h"

Residence::Residence(const Building& building,std::vector<int> otherBlockIndices,int purchaseCost, std::vector<int> rentWithMutipleOwned):
                    Building(building),otherBlockIndices(otherBlockIndices),purchaseCost(purchaseCost),rentWithMutipleOwned(rentWithMutipleOwned){
                        currTuition = rentWithMutipleOwned[0];
                    }

buildingType Residence::getType(){
    return residence;
}

bool Residence::performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players){
    if(player->getName() != owner){
        if(player->charge(currTuition)){
            cout << "you paid " <<currTuition <<", game continue" << endl;
            for(auto i: players){
                if(i->getName() == owner){
                    i->addMoney(currTuition);
                }
            }
            return true;
        }else{
            player->setBankrupt();
            player->setOweMoeny(currTuition);
            return false;
        }
    }
    return true;
}