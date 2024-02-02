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

/**
 *  74HC595 Skyloong LED display Driver
 *  data(default):1-on/0-off
 *    bit0 --- MAC layer indicator
 *    bit1 --- Win layer indicator
 *    bit2 --- CAPS indicator
 *    bit3 --- NUM indicator
 *    bit4 --- SCR indicator
 *    bit7 --- Skyloong LOGO display
 *
**/
#ifndef ClockTime
#    define ClockTime 15
#endif

//enable mac layer indicator on LED diaplay
#ifndef MAC_ON
#    define MAC_ON  0b00000001
#endif

//enable win layer indicator on LED diaplay
#ifndef WIN_ON
#    define WIN_ON  0b00000010
#endif

//enable caps lock indicator on LED diaplay
#ifndef CAPS_ON
#    define CAPS_ON  0b00000100
#endif

//enable number lock indicator on LED diaplay
#ifndef NUM_ON
#    define NUM_ON  0b00001000
#endif

//enable scroll lock indicator on LED diaplay
#ifndef SCR_ON
#    define SCR_ON  0b00010000
#endif

//Skyloong LOGO display on
#ifndef SKYLOONG
#    define SKYLOONG 0b10000000
#endif

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

