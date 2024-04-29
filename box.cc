#include "box.h"

const int BOX_WIDTH = 150;
const int BOX_HEIGHT = 50;
const int PERIMETER = 40;
const int SIDE_LENGTH = 10;

Box::Box(const std::string& name, int index,const std::string& owner, std::vector<std::string> currPlayer,int level)
        : name(name), index(index), owner(owner), currPlayer(currPlayer),level(level) {}




int Box:: getIndex() const{
    return index;
}

std::string Box:: getLastPlayer() const{
    return currPlayer.back();
}

std::string Box::getOwner() const{
    return owner;
}

std::string Box:: getName() const{
    return name;
}

int Box:: getLevel() const{
    return level;
}