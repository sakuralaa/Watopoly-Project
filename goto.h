#ifndef _GOTOTIMS_H_
#define _GOTOTIMS_H_

#include "Building.h"
#include "gameboard.h"

class GameBoard;

class GoToTims : public Building {

public:
    GoToTims(const Building &building,GameBoard *game);

    buildingType getType() override {
        return buildingType::nonproperty;
    }

    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;

private:
    GameBoard *game;
};


class DCTimsLine : public Building {
public:
    DCTimsLine(const Building &building, GameBoard *game);

    buildingType getType() override {
        return buildingType::nonproperty;
    }

    bool performAction(std::shared_ptr<Player> player, std::vector<std::shared_ptr<Player>> players) override;

private:
    GameBoard *game;
};


#endif