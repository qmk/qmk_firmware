#include <Arduino.h>
#include "helpers/sma_filter.hpp"

// On the call operator the next value is given into the filter, with the new average being returned.
uint16_t SMAFilter::operator()(uint16_t value)
{
    // Calculate the new sum by removing the oldest element and adding the new one.
    sum = sum - buffer[index] + value;

    // Overwrite the oldest element in the circular buffer with the new one.
    buffer[index] = value;

    // Move the index by 1 or restart at 0 if the end is reached.
    index = (index + 1) % samples;

    // If the index is 0 here (meaning the circular index just reset), set the fully initialized state to true.
    if(index == 0)
        initialized = true;

    // Divide the number by the amount of samples using bitshifting and return it.
    return sum >> samplesExponent;
}
