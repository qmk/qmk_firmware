#include "quantum.h"
#include "backlight.h"
#include <hal.h>
#include "debug.h"

// Maximum duty cycle limit
#ifndef BACKLIGHT_LIMIT_VAL
#    define BACKLIGHT_LIMIT_VAL 255
#endif

#ifndef BACKLIGHT_PAL_MODE
#    if defined(USE_GPIOV1)
#        define BACKLIGHT_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
// GPIOV2 && GPIOV3
#        define BACKLIGHT_PAL_MODE 5
#    endif
#endif

// GENERIC
#ifndef BACKLIGHT_PWM_DRIVER
#    define BACKLIGHT_PWM_DRIVER PWMD4
#endif
#ifndef BACKLIGHT_PWM_CHANNEL
#    define BACKLIGHT_PWM_CHANNEL 3
#endif

// Support for pins which are on TIM1_CH1N - requires STM32_PWM_USE_ADVANCED
#ifdef BACKLIGHT_PWM_COMPLEMENTARY_OUTPUT
#    if BACKLIGHT_ON_STATE == 1
#        define PWM_OUTPUT_MODE PWM_COMPLEMENTARY_OUTPUT_ACTIVE_LOW;
#    else
#        define PWM_OUTPUT_MODE PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH;
#    endif
#else
#    if BACKLIGHT_ON_STATE == 1
#        define PWM_OUTPUT_MODE PWM_OUTPUT_ACTIVE_HIGH;
#    else
#        define PWM_OUTPUT_MODE PWM_OUTPUT_ACTIVE_LOW;
#    endif
#endif

static PWMConfig pwmCFG = {0xFFFF, /* PWM clock frequency  */
                           256,    /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
                           NULL,   /* Breathing Callback */
                           {       /* Default all channels to disabled - Channels will be configured durring init */
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL}},
                           0, /* HW dependent part.*/
                           0};

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)     // if below 8% of max
        return v / 9;  // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL);  // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL)  // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}

static uint32_t rescale_limit_val(uint32_t val) {
    // rescale the supplied backlight value to be in terms of the value limit
    return (val * (BACKLIGHT_LIMIT_VAL + 1)) / 256;
}

void backlight_init_ports(void) {
#ifdef USE_GPIOV1
    palSetPadMode(PAL_PORT(BACKLIGHT_PIN), PAL_PAD(BACKLIGHT_PIN), BACKLIGHT_PAL_MODE);
#else
    palSetPadMode(PAL_PORT(BACKLIGHT_PIN), PAL_PAD(BACKLIGHT_PIN), PAL_MODE_ALTERNATE(BACKLIGHT_PAL_MODE));
#endif

    pwmCFG.channels[BACKLIGHT_PWM_CHANNEL - 1].mode = PWM_OUTPUT_MODE;
    pwmStart(&BACKLIGHT_PWM_DRIVER, &pwmCFG);

    backlight_set(get_backlight_level());

#ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#endif
}

void backlight_set(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;

    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1);
    } else {
        // Turn backlight on
        uint32_t duty = (uint32_t)(cie_lightness(rescale_limit_val(0xFFFF * (uint32_t)level / BACKLIGHT_LEVELS)));
        pwmEnableChannel(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&BACKLIGHT_PWM_DRIVER, 0xFFFF, duty));
    }
}

void backlight_task(void) {}

#ifdef BACKLIGHT_BREATHING

#    define BREATHING_STEPS 128

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void breathing_callback(PWMDriver *pwmp);

bool is_breathing(void) { return pwmCFG.callback != NULL; }

void breathing_enable(void) {
    pwmCFG.callback = breathing_callback;
    pwmEnablePeriodicNotification(&BACKLIGHT_PWM_DRIVER);
}

void breathing_disable(void) {
    pwmCFG.callback = NULL;
    pwmDisablePeriodicNotification(&BACKLIGHT_PWM_DRIVER);

    // Restore backlight level
    backlight_set(get_backlight_level());
}

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) { return v / BACKLIGHT_LEVELS * get_backlight_level(); }

void breathing_callback(PWMDriver *pwmp) {
    uint8_t  breathing_period = get_breathing_period();
    uint16_t interval         = (uint16_t)breathing_period * 256 / BREATHING_STEPS;

    // resetting after one period to prevent ugly reset at overflow.
    static uint16_t breathing_counter = 0;
    breathing_counter                 = (breathing_counter + 1) % (breathing_period * 256);
    uint8_t  index                    = breathing_counter / interval % BREATHING_STEPS;
    uint32_t duty                     = cie_lightness(rescale_limit_val(scale_backlight(breathing_table[index] * 256)));

    chSysLockFromISR();
    pwmEnableChannelI(pwmp, BACKLIGHT_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&BACKLIGHT_PWM_DRIVER, 0xFFFF, duty));
    chSysUnlockFromISR();
}

// TODO: integrate generic pulse solution
void breathing_pulse(void) {
    backlight_set(is_backlight_enabled() ? 0 : BACKLIGHT_LEVELS);
    wait_ms(10);
    backlight_set(is_backlight_enabled() ? get_backlight_level() : 0);
}

#endif
