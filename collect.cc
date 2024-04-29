#include "collect.h"

CollectOSAP::CollectOSAP(const Building &building):Building(building){}

buildingType CollectOSAP::getType(){
    return nonproperty;
}


bool CollectOSAP::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players){
        player->addMoney(200);
        std::cout << "You collected $200 from Collect OSAP." << std::endl;
        return true;
}

noFunction::noFunction(const Building &building):Building(building){}

buildingType noFunction::getType(){
    return nonproperty;
}

bool noFunction::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) {
    std::cout << "Nothing happens." << std::endl;
    return true;
}


Tuition::Tuition(const Building &building):Building(building){}

buildingType Tuition::getType(){
    return nonproperty;
}


bool Tuition ::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players){
    cout << "option 1: pay 300, option 2: pay 10% of your worht" << endl;
    int option;
    while(true){
        cin >> option;
        if(option == 1){
            if(player->charge(300)){
                return true;
            }else{
                player->setBankrupt();
                player->setOweMoeny(300);
                return false;
            }
        }
        else if(option == 2){
            int asset = player->getAsset();
            int charge = asset /10;
            if(player->charge(charge)){
                return true;
            }else{
                player->setBankrupt();
                player->setOweMoeny(charge);
                return false;
            }
        }else{
            
            cerr <<  "invalid command, retype 1 or 2" << endl;
        }
    }
}

CoopFee::CoopFee(const Building &building):Building(building){}

buildingType CoopFee::getType(){
    return nonproperty;
}


bool CoopFee::performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players){
    if(player->charge(150)){
        return true;
    }else{
        player->setBankrupt();
        player->setOweMoeny(150);
        return false;
    }
}