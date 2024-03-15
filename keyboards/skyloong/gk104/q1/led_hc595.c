//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifndef HC595_ST_PIN
#    error hc595: no storage register clock pins defined!
#endif

#ifndef HC595_SH_PIN
#    error hc595: no shift register clock pins defined!
#endif

#ifndef HC595_DS
#    error hc595: no serial data input pins defined!
#endif

/*
 *LED display driver.74HC595 Serial to parallel control LED field on/off.
 *  data(default):1-on/0-off (left low bit)
 *    bit0 --- NUM indicator
 *    bit1 --- CAPS indicator
 *    bit2 --- SCR indicator
 *    bit3 --- WinLock indicator
 *    bit4 --- Skyloong LOGO display
 *    bit5 --- Win layer indicator
 *    bit6 --- MAC layer indicator
 */
#define NUM_ON 0b10000000
#define CAPS_ON 0b01000000
#define SCR_ON 0b00100000
#define WINLK_ON 0b00010000
#define SKYLOONG 0b00001000
#define WIN_ON 0b00000010
#define MAC_ON 0b00000100

#define CLOCK_TIME 15

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void select_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    };
}

static inline void clockPulse(uint16_t n) {
    writePinHigh(HC595_SH_PIN);
    writePinHigh(HC595_ST_PIN);
    select_delay(n);
    writePinLow(HC595_SH_PIN);
    writePinLow(HC595_ST_PIN);
}

static void s_serial_to_parallel(uint8_t data) { // Serial port to parallel port function
    setPinOutput_writeLow(HC595_DS);
    setPinOutput_writeLow(HC595_SH_PIN);
    setPinOutput_writeLow(HC595_ST_PIN);
    for(uint8_t i = 0; i < 8; i++) {
        if(data & 0x01){
            writePinHigh(HC595_DS);
        }else{
            writePinLow(HC595_DS);
        }
        clockPulse(ClockTime);
        data >>= 1; // Move the data one digit to the right
    }
}

