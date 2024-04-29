#include "gym.h"

Gym:: Gym(const Building& building, vector<int> otherBlockIndices, GameBoard* gameBoard, int purchaseCost, bool ownedTwo): 
    Building(building),gameBoard(gameBoard), purchaseCost(purchaseCost),ownedTwo(ownedTwo){}

bool Gym::performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players){
        if (player->getName() != owner) {
            auto [die1, die2] = gameBoard->roll();
            int sum = die1 + die2;
            int charge = ownedTwo ? 10*sum : 4*sum;
            if(player->charge(charge)){
                for(auto i: players){
                    if(i->getName() == owner){
                        i->addMoney(charge);
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
