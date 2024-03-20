#pragma once

#include <cstdint>

class SMAFilter
{
public:
    // Initialize the SMAFilter instance with the specified sample exponent.
    // (1 = 1 sample, 2 = 4 samples, 3 = 8 samples, ...)
    SMAFilter(uint8_t samplesExponent)
        : samplesExponent(samplesExponent)
        , samples(1 << samplesExponent)
        , buffer(new uint16_t[samples] {0})
    {}

    // The call operator for passing values through the filter.
    uint16_t operator()(uint16_t value);

    // Bool whether the whole buffer has been written at least once.
    bool initialized = false;

private:
    // The amount of samples and the exponent.
    uint8_t samplesExponent;
    uint8_t samples;

    // The buffer containing all values.
    uint16_t *buffer;

    // The index of the oldest and thus next element to overwrite.
    uint8_t index = 0;

    // The sum of all values in the buffer.
    uint32_t sum = 0;
};
