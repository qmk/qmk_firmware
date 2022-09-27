#include "shift_reg.h"
#include QMK_KEYBOARD_H


#ifndef NOP_FUDGE
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(GD32VF103) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX)
#        define NOP_FUDGE 0.4
#    elif defined(RP2040)
#        define NOP_FUDGE 100
#    else
#        error("NOP_FUDGE configuration required")
#        define NOP_FUDGE 1  // this just pleases the compile so the above error is easier to spot
#    endif
#endif


#define NUMBER_NOPS 6
#define CYCLES_PER_SEC (CPU_CLOCK / NUMBER_NOPS * NOP_FUDGE)
#define NS_PER_SEC (1000000000L)  // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

#define WAIT_NS(x)                                  \
    do {                                            \
        for (int i = 0; i < NS_TO_CYCLES(x); i++) { \
            __asm__ volatile("nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t"              \
                             "nop\n\t");            \
        }                                           \
    } while (0)


void sr_hw_setup(void) {
    #if defined(SR_NMR_PIN)
        setPinOutput(SR_NMR_PIN);
    #endif
    setPinOutput(SR_CLK_PIN);
    setPinOutput(SR_DATA_PIN);
    setPinOutput(SR_LATCH_PIN);

    #if defined(SR_NMR_PIN)
        writePinHigh(SR_NMR_PIN);
    #endif
    writePinHigh(SR_CLK_PIN);
    writePinHigh(SR_DATA_PIN);
    writePinLow(SR_LATCH_PIN);
 }

void sr_init(void) {
    #if defined(SR_NMR_PIN)
        setPinOutput(SR_NMR_PIN);
        writePinLow(SR_NMR_PIN);
        WAIT_NS(20);//wait_us(10);
        writePinHigh(SR_NMR_PIN);
        WAIT_NS(2);//wait_us(2);
    #endif
}

void sr_shift_out(uint8_t val) {
    for (uint8_t i = 0; i < 8; i++) {
        writePin(SR_DATA_PIN, !!(val & (1 << (7 - i))));
        WAIT_NS(1);
        writePinLow(SR_CLK_PIN);
        WAIT_NS(1);
        writePinHigh(SR_CLK_PIN);
        //wait_us(1);
    }
}

void sr_shift_out_latch(uint8_t val) {
    setPinOutput(SR_DATA_PIN);
    setPinOutput(SR_CLK_PIN);
    setPinOutput(SR_LATCH_PIN);
    writePinLow(SR_LATCH_PIN);
    sr_shift_out(val);
    //WAIT_NS(2);
    writePinHigh(SR_LATCH_PIN);
    WAIT_NS(1);
    writePinLow(SR_LATCH_PIN);
    //wait_us(1);
}

void sr_shift_out_buffer_latch(const uint8_t* val, uint8_t len) {
    setPinOutput(SR_DATA_PIN);
    setPinOutput(SR_CLK_PIN);
    setPinOutput(SR_LATCH_PIN);
    writePinLow(SR_LATCH_PIN);
    for(uint8_t i=0;i<len;++i) {
        sr_shift_out(val[i]);
    }
    //WAIT_NS(2);
    writePinHigh(SR_LATCH_PIN);
    WAIT_NS(1);
    writePinLow(SR_LATCH_PIN);
    //wait_us(1);
}
