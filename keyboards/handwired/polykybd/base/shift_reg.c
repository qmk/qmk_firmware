#include "shift_reg.h"
#include QMK_KEYBOARD_H

#define NOP_WAIT(x)                                  \
    do {                                            \
        for (int i = 0; i < x; i++) { \
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
        NOP_WAIT(20);//wait_us(10);
        writePinHigh(SR_NMR_PIN);
        NOP_WAIT(2);//wait_us(2);
    #endif
}
/*
static uint8_t last_bit_idx = 0xff;

void sr_shift_out_bit_cached(uint8_t bit_idx, uint8_t max_idx) {
    if(last_bit_idx!=bit_idx) {
        if(last_bit_idx>max_idx) {
            writePin(SR_DATA_PIN, 1);
            NOP_WAIT(1);
            writePinLow(SR_CLK_PIN);
            NOP_WAIT(1);
            writePinHigh(SR_CLK_PIN);
            last_bit_idx=0;
        }
        if(bit_idx<last_bit_idx) {
            for (uint8_t i = 0; i < bit_idx-last_bit_idx; i++) {
                writePin(SR_DATA_PIN, 0);
                NOP_WAIT(1);
                writePinLow(SR_CLK_PIN);
                NOP_WAIT(1);
                writePinHigh(SR_CLK_PIN);
            }
            last_bit_idx = bit_idx;
        }
    }
}
*/

static bool all_zeros=false;

void sr_shift_once(void) {
        writePin(SR_DATA_PIN, 1);
        NOP_WAIT(1);
        writePinLow(SR_CLK_PIN);
        NOP_WAIT(1);
        writePinHigh(SR_CLK_PIN);
}

void sr_shift_once_latch(void) {
    sr_shift_once();
    writePinHigh(SR_LATCH_PIN);
    NOP_WAIT(1);
    writePinLow(SR_LATCH_PIN);
    all_zeros=false;
}

void sr_shift_out(uint8_t val) {
    for (uint8_t i = 0; i < 8; i++) {
        writePin(SR_DATA_PIN, !!(val & (1 << (7 - i))));
        NOP_WAIT(1);
        writePinLow(SR_CLK_PIN);
        NOP_WAIT(1);
        writePinHigh(SR_CLK_PIN);
        //wait_us(1);
    }
}

void sr_shift_out_latch(uint8_t val) {
    //setPinOutput(SR_DATA_PIN);
    //setPinOutput(SR_CLK_PIN);
    //setPinOutput(SR_LATCH_PIN);
    //writePinLow(SR_LATCH_PIN);
    sr_shift_out(val);
    //NOP_WAIT(2);
    writePinHigh(SR_LATCH_PIN);
    NOP_WAIT(1);
    writePinLow(SR_LATCH_PIN);
    //wait_us(1);
    all_zeros=false;
}

void sr_shift_out_buffer_latch(const uint8_t* val, uint8_t len) {
    //setPinOutput(SR_DATA_PIN);
    //setPinOutput(SR_CLK_PIN);
    //setPinOutput(SR_LATCH_PIN);
    //writePinLow(SR_LATCH_PIN);
    for(uint8_t i=0;i<len;++i) {
        sr_shift_out(val[i]);
    }
    //NOP_WAIT(2);
    writePinHigh(SR_LATCH_PIN);
    NOP_WAIT(1);
    writePinLow(SR_LATCH_PIN);
    //wait_us(1);
    all_zeros=false;
}

void sr_shift_out_0_latch(uint8_t times) {
    if(!all_zeros) {
        //setPinOutput(SR_DATA_PIN);
        //setPinOutput(SR_CLK_PIN);
        //setPinOutput(SR_LATCH_PIN);
        //writePinLow(SR_LATCH_PIN);
        for(uint8_t i=0;i<times;++i) {
            sr_shift_out(0);
        }
        //NOP_WAIT(2);
        writePinHigh(SR_LATCH_PIN);
        NOP_WAIT(1);
        writePinLow(SR_LATCH_PIN);
        //wait_us(1);
        all_zeros = true;
    }
}
