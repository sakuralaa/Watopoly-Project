#ifndef NORMAL_DICE_STRATEGY_H
#define NORMAL_DICE_STRATEGY_H

#include "dicestrategy.h"
#include "PRNG.h"
#include <utility>

class NormalDiceStrategy : public DiceStrategy {
public:
    std::pair<int, int> roll() override;
};

#endif


