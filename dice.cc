#include "dice.h"

void Dice:: initializePRNG() {
        uint32_t seed = static_cast<uint32_t>(getpid());
        prng.seed(seed);
    }

int Dice::roll() {
    int die1 = prng(1, 6);
    int die2 = prng(1, 6);
    return die1 + die2;
}