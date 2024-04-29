#include "player.h"

Player::Player(string name, int timCups, int currPos, float asset, vector<int> property, bool isTrapped, bool isBankrupt, int oweMoney,int trunsTrap):name(name),timCups(timCups), currPosition(currPos),asset(asset), property(property),isTrapped(isTrapped),
            isBankrupt(isBankrupt),oweMoney(oweMoney),turnsTrap(trunsTrap){}

string Player:: getName() const{
    return name;
}

int Player:: getPosition() const{
    return currPosition;
}

void Player:: move(int steps){
    if(currPosition + steps > 39){
        currPosition = steps + currPosition - 40;
    }else{
        currPosition = currPosition + steps;
    }
}

bool Player::charge(int amount){
    if((asset - amount) >= 0){
        asset -= amount;
        cout << "now you have " << asset << endl;
        return true;
    }else{
        cout << "you are paying more than you have" << endl;
        return false;
    }
}

void Player::setBankrupt(){
    isBankrupt = true;
}

void Player:: setTrap(){
    isTrapped = true;
}

void Player:: addMoney(int amount){
    asset += amount;
}

void Player::setOweMoeny(int amount){
    oweMoney = amount;
}

int Player:: getAsset(){
    return asset;
}



