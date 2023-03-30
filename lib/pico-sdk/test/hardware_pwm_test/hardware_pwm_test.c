/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/test.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/resets.h"
#include "hardware/pwm.h"

PICOTEST_MODULE_NAME("PWM", "PWM SDK Test harness");

/* In a struct for future expansion of the interrupt testv */
struct interrupt_state {
    int count;
} interrupt_states[NUM_PWM_SLICES] = {0};

void on_pwm_wrap() {
    for (int pwm = 0; pwm < NUM_PWM_SLICES; pwm++) {
        // See if this pwm, is the one that fired.
        if (pwm_get_irq_status_mask() & (1 << pwm)) {
            // Clear the interrupt flag that brought us here
            pwm_clear_irq(pwm);

            interrupt_states[pwm].count++;
        }
    }
}

int main() {
    reset_block(RESETS_RESET_PWM_BITS);
    unreset_block_wait(RESETS_RESET_PWM_BITS);

    setup_default_uart();

    PICOTEST_START();

    pwm_config config = pwm_get_default_config();


    // Test that config sets works on all PWMs by comparing what we pass in
    // via the API with what the registers contains afterwards

    pwm_config_set_phase_correct(&config, true);
    pwm_config_set_clkdiv(&config, 42.5);
    pwm_config_set_clkdiv_mode(&config, PWM_DIV_B_HIGH);
    pwm_config_set_output_polarity(&config, false, true);
    pwm_config_set_wrap(&config, 0x1234);

    PICOTEST_START_SECTION("PWM config init tests");
        for (int pwm = 0; pwm < NUM_PWM_SLICES; pwm++) {
            pwm_slice_hw_t *slice = &pwm_hw->slice[pwm];

            pwm_init(pwm, &config, false);

            uint div = (uint)(42.5f * (float)(1 << PWM_CH0_DIV_INT_LSB));

            PICOTEST_CHECK_CHANNEL(pwm, slice->top == config.top, "HW top does not match requested config");
            //PICOTEST_CHECK_CHANNEL(pwm, slice->ctr == 0x1234, "HW counter does not match config");
            PICOTEST_CHECK_CHANNEL(pwm, slice->cc == PWM_CH0_CC_RESET, "HW compares does not match config");
            PICOTEST_CHECK_CHANNEL(pwm, slice->div == div, "HW divider  does not match config");
            PICOTEST_CHECK_CHANNEL(pwm, slice->csr ==
                                        (1 << PWM_CH0_CSR_PH_CORRECT_LSB | 0 << PWM_CH0_CSR_A_INV_LSB | 1 << PWM_CH0_CSR_B_INV_LSB |
                                         PWM_CH0_CSR_DIVMODE_VALUE_LEVEL << PWM_CH0_CSR_DIVMODE_LSB), "HW CSR does not match config");
        }
    PICOTEST_END_SECTION();


    // Need to test the SDK APIs do the right thing

    PICOTEST_START_SECTION("PWM SDK API tests");
        for (int pwm = 0; pwm < NUM_PWM_SLICES; pwm++) {
            pwm_slice_hw_t *slice = &pwm_hw->slice[pwm];
            int v = 100 + pwm * 10;

            pwm_set_wrap(pwm, v);
            PICOTEST_CHECK_CHANNEL(pwm, slice->top == v, "pwm_set_wrap() failed to set register");

            pwm_set_both_levels(pwm, v + 1, v);
            PICOTEST_CHECK_CHANNEL(pwm, slice->cc == (((v) << PWM_CH0_CC_B_LSB) | ((v + 1) << PWM_CH0_CC_A_LSB)),
                                   "pwm_set_both_levels() failed to set register");

            float divider = 100.5;
            int i = (int16_t) divider;
            int f = (int8_t) ((divider - i) * 16);
            pwm_set_clkdiv(pwm, divider);
            PICOTEST_CHECK_CHANNEL(pwm, slice->div == (i << 4 | f), "pwm_set_clkdiv() failed to set register");

            i++;
            pwm_set_clkdiv_int_frac(pwm, i, f);
            PICOTEST_CHECK_CHANNEL(pwm, slice->div == (i << 4 | f),
                                   "pwm_set_clkdiv_int_frac() failed to set register");

            int c = 1234;
            pwm_set_counter(pwm, c);
            PICOTEST_CHECK_CHANNEL(pwm, slice->ctr == c, "pwm_set_counter() failed to set register");

            int cc = pwm_get_counter(pwm);
            PICOTEST_CHECK_CHANNEL(pwm, slice->ctr == cc && cc == c, "pwm_get_counter() failed to get register");

            pwm_set_output_polarity(pwm, false, false);
            PICOTEST_CHECK_CHANNEL(pwm,
                                   !(slice->csr & PWM_CH0_CSR_A_INV_BITS) && !(slice->csr & PWM_CH0_CSR_B_INV_BITS),
                                   "pwm_set_output_polarity() (F/F)");

            pwm_set_output_polarity(pwm, true, false);
            PICOTEST_CHECK_CHANNEL(pwm, (slice->csr & PWM_CH0_CSR_A_INV_BITS) && !(slice->csr & PWM_CH0_CSR_B_INV_BITS),
                                   "pwm_set_output_polarity() (T/F)");

            pwm_set_output_polarity(pwm, false, true);
            PICOTEST_CHECK_CHANNEL(pwm, !(slice->csr & PWM_CH0_CSR_A_INV_BITS) && (slice->csr & PWM_CH0_CSR_B_INV_BITS),
                                   "pwm_set_output_polarity() (F/T)");

            pwm_set_output_polarity(pwm, true, true);
            PICOTEST_CHECK_CHANNEL(pwm, (slice->csr & PWM_CH0_CSR_A_INV_BITS) && (slice->csr & PWM_CH0_CSR_B_INV_BITS),
                                   "pwm_set_output_polarity() (T/T)");

            pwm_set_phase_correct(pwm, true);
            PICOTEST_CHECK_CHANNEL(pwm, (slice->csr & PWM_CH0_CSR_PH_CORRECT_BITS), "pwm_set_phase_correct(T)");

            pwm_set_phase_correct(pwm, false);
            PICOTEST_CHECK_CHANNEL(pwm, !(slice->csr & PWM_CH0_CSR_PH_CORRECT_BITS), "pwm_set_phase_correct(F)");

            for (int m = PWM_DIV_FREE_RUNNING; m <= PWM_DIV_B_FALLING; m++) {
                pwm_set_clkdiv_mode(pwm, m);
                PICOTEST_CHECK_CHANNEL(pwm, ((slice->csr & PWM_CH0_CSR_DIVMODE_BITS) >> PWM_CH0_CSR_DIVMODE_LSB) == m,
                                       "pwm_set_clkdiv_mode");
            }
        }
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("PWM IRQ tests");

        irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
        irq_set_enabled(PWM_IRQ_WRAP, true);

        config = pwm_get_default_config();

        // Slow down the interrupt rate a load, don't need it high.
        // This give about 40 per second on Picoboard
        pwm_config_set_clkdiv(&config, 50);

        for (int pwm = 0; pwm < NUM_PWM_SLICES; pwm++) {
            pwm_init(pwm, &config, false);
            pwm_clear_irq(pwm);
            pwm_set_irq_enabled(pwm, true);
        }

        // Now enable all the PWM at the same time.
        pwm_set_mask_enabled(0xff);

        sleep_ms(1000);

        int err = 0;

        for (int p = 0; p < NUM_PWM_SLICES; p++) {
            PICOTEST_CHECK_CHANNEL(p, interrupt_states[p].count != 0, "No interrupts detected from PWM %d\n");
        }

    PICOTEST_END_SECTION();

    PICOTEST_END_TEST();
}

