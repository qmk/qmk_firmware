#pragma once

#include <stdint.h>
#include <stdbool.h>

#define SPLIT_KEYBOARD
/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODERS_PAD_A { 0 }
#define ENCODERS_PAD_B { 1 }
#define ENCODERS_PAD_A_RIGHT { 2 }
#define ENCODERS_PAD_B_RIGHT { 3 }

typedef uint8_t pin_t;
extern bool isLeftHand;
void encoder_state_raw(uint8_t* slave_state);
void encoder_update_raw(uint8_t* slave_state);

extern bool pins[];
extern bool pinIsInputHigh[];

#define setPinInputHigh(pin) (mockSetPinInputHigh(pin))
#define readPin(pin) (mockReadPin(pin))

uint8_t mockSetPinInputHigh(pin_t pin);

bool mockReadPin(pin_t pin);

bool setPin(pin_t pin, bool val);
