#include "PRNG.h"

PRNG::PRNG(uint32_t s) : seed_(s) {
    assert(seed_ != 0); // Ensure seed is not zero
}

uint32_t PRNG::seed() {
    return seed_;
}

void PRNG::seed(uint32_t s) {
    seed_ = s;
    assert(seed_ != 0); // Ensure new seed is not zero
}

uint32_t PRNG::operator()() {
    seed_ = 36969 * (seed_ & 65535) + (seed_ >> 16); // Scramble bits
    return seed_;
}

uint32_t PRNG::operator()(uint32_t u) {
    assert(u < static_cast<uint32_t>(-1)); // Ensure u is within range
    return operator()() % (u + 1); // Call operator()()
}

uint32_t PRNG::operator()(uint32_t l, uint32_t u) {
    assert(l <= u); // Ensure lower bound is less than or equal to upper bound
    return operator()(u - l) + l; // Call operator()(uint32_t)
}

PRNG prng; // Definition of the global PRNG object
