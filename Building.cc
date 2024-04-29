#include "Building.h"

Building::Building(int index,std::string name,int level,std::vector<std::shared_ptr<Player>> currPlayer,string owner ,int currTuition): 
        index(index),name(name),currPlayer(currPlayer),level(level),owner(owner),currTuition(currTuition){}

Building::Building(const Building& other):index(other.index),name(other.name),currPlayer(other.currPlayer),level(other.level),owner(other.owner),currTuition(other.currTuition){}

int Building:: getIdx() const{
    return index;
}


std::vector<string> Building::getCurrPlayerName() const{
    std::vector<string> nameList;
    for(auto i: currPlayer){
        nameList.push_back(i.get()->getName());
    }
    return nameList;
}

string Building::getOwner() const{
    return owner;
}

int Building:: getLevel() const{
    return level;
}

buildingType Building::getType(){
    return general;
}

bool Building::performAction(shared_ptr<Player> player, vector<shared_ptr<Player>> players){}