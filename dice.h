#ifndef _DICE_H_
#define _DICE_H_

#include "PRNG.h"
#include <iomanip>
using namespace std;
#include <unistd.h>
#include "PRNG.h"


class Dice {
public:
    static void initializePRNG();
    static int roll();
};

#endif