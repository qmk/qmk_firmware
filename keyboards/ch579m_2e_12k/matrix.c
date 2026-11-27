/*
 * KEY12-V02 / CH579M custom matrix — direct-to-GND switches.
 *
 * PB pins: permanent INPUT_PULLUP, read in bulk.
 * PA pins: driven HIGH briefly per-scan (20mA) then read back.
 *          Between scans, PA key pins float (DIR=0, PU=0, PD_DRV=0).
 *
 * Pin map (col index → pin → position):
 *   0=B2   ENC1 button        7=B15  r3c0
 *   1=B19  r0c0               8=A13  r2c1
 *   2=B20  r1c0               9=A14  r3c1
 *   3=B21  r0c1              10=A6   ENC2 button
 *   4=B22  r2c0              11=A12  r1c1
 *   5=A1   r3c2              12=A15  r0c2
 *   6=A2   r2c2              13=A3   r1c2
 *
 * Encoder phase pins (handled by QMK encoder driver, not in KEY_PINS):
 *   enc1: B0 (phase-A), B1 (phase-B)
 *   enc2: A0 (phase-A), A5 (phase-B)
 *
 * Physical layout:
 *   col:  0    1    2
 *   enc: [A]       [B]
 *   r=0: [C]  [D]  [E]
 *   r=1: [F]  [G]  [H]
 *   r=2: [I]  [J]  [K]
 *   r=3: [L]  [M]  [N]
 */

#include "quantum.h"

static const pin_t KEY_PINS[] = {
    /*  0  */ B2,   /* ENC1 button */
    /*  1  */ B19,  /* r0c0        */
    /*  2  */ B20,  /* r1c0        */
    /*  3  */ B21,  /* r0c1        */
    /*  4  */ B22,  /* r2c0        */
    /*  5  */ A1,   /* r3c2        */
    /*  6  */ A2,   /* r2c2        */
    /*  7  */ B15,  /* r3c0        */
    /*  8  */ A13,  /* r2c1        */
    /*  9  */ A14,  /* r3c1        */
    /* 10  */ A6,   /* ENC2 button */
    /* 11  */ A12,  /* r1c1        */
    /* 12  */ A15,  /* r0c2        */
    /* 13  */ A3,   /* r1c2        */
};
#define N_KEYS ((uint8_t)(sizeof(KEY_PINS) / sizeof(KEY_PINS[0])))

_Static_assert(N_KEYS == MATRIX_COLS, "MATRIX_COLS must equal N_KEYS (14)");

/* Bit position within the port register (0xFF = pin is on the other port) */
static const uint8_t pb_bit[N_KEYS] = {2, 19, 20, 21, 22, 0xFF, 0xFF, 15, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const uint8_t pa_bit[N_KEYS] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 1, 2, 0xFF, 13, 14, 6, 12, 15, 3};

void matrix_init_custom(void) {
    /* Enable digital input for all PA key pins by clearing the analog-input-
     * disable bits in R16_PIN_ANALOG_IE (1 = digital disabled, 0 = enabled):
     *   0x0100 = RB_PIN_ADC8_9_IE   → PA1 (AIN8)
     *   0x0200 = RB_PIN_ADC6_7_IE   → PA2 (AIN7), PA3 (AIN6)
     *   0x0800 = RB_PIN_ADC10_11_IE → PA6 (AIN10)
     *   0x4000 = RB_PIN_ADC2_3_IE   → PA12 (AIN2), PA13 (AIN3)
     *   0x8000 = RB_PIN_ADC4_5_IE   → PA14 (AIN4), PA15 (AIN5) */
    R16_PIN_ANALOG_IE &= ~(0x8000U | 0x4000U | 0x0800U | 0x0200U | 0x0100U);

    for (uint8_t i = 0; i < N_KEYS; i++) {
        if (pb_bit[i] != 0xFF) {
            palSetPadMode(GPIOB, pb_bit[i], PAL_MODE_INPUT_PULLUP);
        } else {
            palSetPadMode(GPIOA, pa_bit[i], PAL_MODE_INPUT);
        }
    }

    /* Encoder phase pins need pull-ups before encoder_init reads them. */
    palSetPadMode(GPIOB, 0, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOB, 1, PAL_MODE_INPUT_PULLUP);
}

#define LOCKOUT_MS 150u

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    uint32_t pb_pin = R32_PB_PIN;

    matrix_row_t row0 = 0;
    for (uint8_t i = 0; i < N_KEYS; i++) {
        uint32_t bit;
        if (pb_bit[i] != 0xFF) {
            bit = (pb_pin >> pb_bit[i]) & 1U;
        } else {
            /* Briefly drive PA pin HIGH at 20mA and read back.
             * When not pressed the pin reads HIGH; when pressed the key switch
             * pulls it to GND, winning the voltage divider → reads LOW. */
            uint32_t mask = (1u << pa_bit[i]);
            R32_PA_OUT    |=  mask;
            R32_PA_PD_DRV |=  mask;
            R32_PA_DIR    |=  mask;
            __asm__ volatile("nop\nnop\nnop\nnop\n" ::: "memory");
            bit = (R32_PA_PIN >> pa_bit[i]) & 1U;
            R32_PA_DIR    &= ~mask;
            R32_PA_PD_DRV &= ~mask;
        }
        if (!bit) row0 |= (matrix_row_t)(1u << i);
    }

    static uint32_t lockout_since = 0;
    static bool     in_lockout    = false;

    uint32_t now = timer_read32();

    if (in_lockout) {
        if (now - lockout_since < LOCKOUT_MS) {
            return false;
        }
        in_lockout = false;
        if (row0 != current_matrix[0]) {
            current_matrix[0] = row0;
            lockout_since      = now;
            in_lockout         = true;
            return true;
        }
        return false;
    }

    if (row0 != current_matrix[0]) {
        current_matrix[0] = row0;
        lockout_since      = now;
        in_lockout         = true;
        return true;
    }

    return false;
}
