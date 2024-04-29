#ifndef TESTING_DICE_STRATEGY_H
#define TESTING_DICE_STRATEGY_H

#include "dicestrategy.h"
#include <utility> 
#include <iostream>

class TestingDiceStrategy : public DiceStrategy {
public:
    std::pair<int, int> roll() override;
};

#endif
