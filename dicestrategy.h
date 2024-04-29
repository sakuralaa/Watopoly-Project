#ifndef DICE_STRATEGY_H
#define DICE_STRATEGY_H

#include <utility> // For std::pair

class DiceStrategy {
public:
    virtual std::pair<int, int> roll() = 0; // Pure virtual function
    virtual ~DiceStrategy() {} // Virtual destructor
};

#endif // DICE_STRATEGY_H
