#pragma once

#include <stdint.h>
#include <stdbool.h>

/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODERS_PAD_A { 0 }
#define ENCODERS_PAD_B { 1 }

typedef uint8_t pin_t;

extern bool pins[];
extern bool pinIsInputHigh[];

#define setPinInputHigh(pin) (mockSetPinInputHigh(pin))
#define readPin(pin) (mockReadPin(pin))

uint8_t mockSetPinInputHigh(pin_t pin);

bool mockReadPin(pin_t pin);

bool setPin(pin_t pin, bool val);
