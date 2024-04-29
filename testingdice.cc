#include "testingdice.h"

std::pair<int, int> TestingDiceStrategy::roll() {
    int a, b;
    std::cout << "please input 2 integer here" << std::endl;
    std::cin >> a >> b;
    return {a, b};
}
