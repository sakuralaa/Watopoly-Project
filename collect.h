#ifndef _COLLECTOSAP_H_
#define _COLLECTOSAP_H_

#include "Building.h"
#include <string>

class CollectOSAP : public Building {
public:
    CollectOSAP(const Building &building);
    buildingType getType() override;
    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;
};

class noFunction : public Building {
public:
    noFunction(const Building &building);
    
    buildingType getType() override;

    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;
};


class Tuition: public Building{
public:
    Tuition(const Building &building);
    
    buildingType getType() override;

    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;
};

class CoopFee: public Building{
public:
    CoopFee(const Building &building);
    
    buildingType getType() override;

    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;
};

#endif