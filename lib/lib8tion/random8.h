#ifndef __INC_LIB8TION_RANDOM_H
#define __INC_LIB8TION_RANDOM_H
///@ingroup lib8tion

///@defgroup Random Fast random number generators
/// Fast 8- and 16- bit unsigned random numbers.
///  Significantly faster than Arduino random(), but
///  also somewhat less random.  You can add entropy.
///@{

// X(n+1) = (2053 * X(n)) + 13849)
#define FASTLED_RAND16_2053  ((uint16_t)(2053))
#define FASTLED_RAND16_13849 ((uint16_t)(13849))

/// random number seed
extern uint16_t rand16seed;// = RAND16_SEED;

/// Generate an 8-bit random number
LIB8STATIC uint8_t random8(void)
{
    rand16seed = (rand16seed * FASTLED_RAND16_2053) + FASTLED_RAND16_13849;
    // return the sum of the high and low bytes, for better
    //  mixing and non-sequential correlation
    return (uint8_t)(((uint8_t)(rand16seed & 0xFF)) +
                     ((uint8_t)(rand16seed >> 8)));
}

/// Generate a 16 bit random number
LIB8STATIC uint16_t random16(void)
{
    rand16seed = (rand16seed * FASTLED_RAND16_2053) + FASTLED_RAND16_13849;
    return rand16seed;
}

/// Generate an 8-bit random number between 0 and lim
/// @param lim the upper bound for the result
LIB8STATIC uint8_t random8_max(uint8_t lim)
{
    uint8_t r = random8();
    r = (r*lim) >> 8;
    return r;
}

/// Generate an 8-bit random number in the given range
/// @param min the lower bound for the random number
/// @param lim the upper bound for the random number
LIB8STATIC uint8_t random8_min_max(uint8_t min, uint8_t lim)
{
    uint8_t delta = lim - min;
    uint8_t r = random8_max(delta) + min;
    return r;
}

/// Generate an 16-bit random number between 0 and lim
/// @param lim the upper bound for the result
LIB8STATIC uint16_t random16_max(uint16_t lim)
{
    uint16_t r = random16();
    uint32_t p = (uint32_t)lim * (uint32_t)r;
    r = p >> 16;
    return r;
}

/// Generate an 16-bit random number in the given range
/// @param min the lower bound for the random number
/// @param lim the upper bound for the random number
LIB8STATIC uint16_t random16_min_max( uint16_t min, uint16_t lim)
{
    uint16_t delta = lim - min;
    uint16_t r = random16_max(delta) + min;
    return r;
}

/// Set the 16-bit seed used for the random number generator
LIB8STATIC void random16_set_seed(uint16_t seed)
{
    rand16seed = seed;
}

/// Get the current seed value for the random number generator
LIB8STATIC uint16_t random16_get_seed(void)
{
    return rand16seed;
}

/// Add entropy into the random number generator
LIB8STATIC void random16_add_entropy(uint16_t entropy)
{
    rand16seed += entropy;
}

///@}

#endif
