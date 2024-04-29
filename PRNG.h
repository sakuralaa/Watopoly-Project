// Pseudo Random Number Generator : generate repeatable sequence of values that
//   appear random by scrambling the bits of a 32-bit integer value.
//
// Interface :
//   PRNG(s) - set starting seed 
//   seed() - read seed
//   seed(s) - reset seed
//   prng() - generate random value in range [0,UINT_MAX]
//   prng(u) - generate random value in range [0,u]
//   prng(l,u) - generate random value in range [l,u]
//
// Examples : generate random number between 5-21
//   prng() % 17 + 5	values 0-16 + 5 = 5-21
//   prng( 16 ) + 5
//   prng( 5, 21 )

// PRNG.h
#ifndef PRNG_H
#define PRNG_H

#include <cstdint>
#include <cassert>

class PRNG {
    uint32_t seed_;	// same results on 32/64-bit architectures
public:
    PRNG(uint32_t s = 362436069);
    uint32_t seed();
    void seed(uint32_t s);
    uint32_t operator()();
    uint32_t operator()(uint32_t u);
    uint32_t operator()(uint32_t l, uint32_t u);
};

extern PRNG prng; // Declaration for global PRNG object

#endif // PRNG_H

