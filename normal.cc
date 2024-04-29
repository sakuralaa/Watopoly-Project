#include "normal.h"

std::pair<int, int> NormalDiceStrategy::roll() {
    int a = prng(1, 6);
    int b = prng(1, 6);
    return {a, b};
}
