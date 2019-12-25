#include "quantum.h"
#include "backlight.h"
#include <hal.h>
#include "debug.h"

// TODO: remove short term bodge when refactoring BACKLIGHT_CUSTOM_DRIVER out
#ifdef BACKLIGHT_PIN

#    if defined(STM32F0XX) || defined(STM32F0xx)
#        error "Backlight support for STMF072 is not available. Please disable."
#    endif

// GPIOV2 && GPIOV3
#    ifndef BACKLIGHT_PAL_MODE
#        define BACKLIGHT_PAL_MODE 2
#    endif

// GENERIC
#    ifndef BACKLIGHT_PWM_DRIVER
#        define BACKLIGHT_PWM_DRIVER PWMD4
#    endif
#    ifndef BACKLIGHT_PWM_CHANNEL
#        define BACKLIGHT_PWM_CHANNEL 3
#    endif

static void breathing_callback(PWMDriver *pwmp);

static PWMConfig pwmCFG = {0xFFFF, /* PWM clock frequency  */
                           256,    /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
                           NULL,   /* No Callback */
                           {       /* Default all channels to disabled - Channels will be configured durring init */
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL}},
                           0, /* HW dependent part.*/
                           0};

static PWMConfig pwmCFG_breathing = {0xFFFF,             /** PWM clock frequency  */
                                     256,                /* PWM period (in ticks) 1S (1/10kHz=0.1mS 0.1ms*10000 ticks=1S) */
                                     breathing_callback, /* Breathing Callback */
                                     {                   /* Default all channels to disabled - Channels will be configured durring init */
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

void backlight_init_ports(void) {
    // printf("backlight_init_ports()\n");

#    ifdef USE_GPIOV1
    palSetPadMode(PAL_PORT(BACKLIGHT_PIN), PAL_PAD(BACKLIGHT_PIN), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#    else
    palSetPadMode(PAL_PORT(BACKLIGHT_PIN), PAL_PAD(BACKLIGHT_PIN), PAL_MODE_ALTERNATE(BACKLIGHT_PAL_MODE));
#    endif

    pwmCFG.channels[BACKLIGHT_PWM_CHANNEL - 1].mode           = PWM_OUTPUT_ACTIVE_HIGH;
    pwmCFG_breathing.channels[BACKLIGHT_PWM_CHANNEL - 1].mode = PWM_OUTPUT_ACTIVE_HIGH;
    pwmStart(&BACKLIGHT_PWM_DRIVER, &pwmCFG);

    backlight_set(get_backlight_level());
    if (is_backlight_breathing()) {
        breathing_enable();
    }
}

void backlight_set(uint8_t level) {
    // printf("backlight_set(%d)\n", level);
    if (level == 0) {
        // Turn backlight off
        pwmDisableChannel(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1);
    } else {
        // Turn backlight on
        if (!is_breathing()) {
            uint32_t duty = (uint32_t)(cie_lightness(0xFFFF * (uint32_t)level / BACKLIGHT_LEVELS));
            // printf("duty: (%d)\n", duty);
            pwmEnableChannel(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&BACKLIGHT_PWM_DRIVER, 0xFFFF, duty));
        }
    }
}

uint8_t backlight_tick = 0;

void backlight_task(void) {}

#    define BREATHING_NO_HALT 0
#    define BREATHING_HALT_OFF 1
#    define BREATHING_HALT_ON 2
#    define BREATHING_STEPS 128

static uint8_t  breathing_period  = BREATHING_PERIOD;
static uint8_t  breathing_halt    = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

bool is_breathing(void) { return BACKLIGHT_PWM_DRIVER.config == &pwmCFG_breathing; }

static inline void breathing_min(void) { breathing_counter = 0; }

static inline void breathing_max(void) { breathing_counter = breathing_period * 256 / 2; }

void breathing_interrupt_enable(void) {
    pwmStop(&BACKLIGHT_PWM_DRIVER);
    pwmStart(&BACKLIGHT_PWM_DRIVER, &pwmCFG_breathing);
    chSysLockFromISR();
    pwmEnablePeriodicNotification(&BACKLIGHT_PWM_DRIVER);
    pwmEnableChannelI(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&BACKLIGHT_PWM_DRIVER, 0xFFFF, 0xFFFF));
    chSysUnlockFromISR();
}

void breathing_interrupt_disable(void) {
    pwmStop(&BACKLIGHT_PWM_DRIVER);
    pwmStart(&BACKLIGHT_PWM_DRIVER, &pwmCFG);
}

void breathing_enable(void) {
    breathing_counter = 0;
    breathing_halt    = BREATHING_NO_HALT;
    breathing_interrupt_enable();
}

void breathing_pulse(void) {
    if (get_backlight_level() == 0)
        breathing_min();
    else
        breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}

void breathing_disable(void) {
    // printf("breathing_disable()\n");
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void) {
    if (get_backlight_level() == 0)
        breathing_halt = BREATHING_HALT_OFF;
    else
        breathing_halt = BREATHING_HALT_ON;
}

void breathing_toggle(void) {
    if (is_breathing())
        breathing_disable();
    else
        breathing_enable();
}

void breathing_period_set(uint8_t value) {
    if (!value) value = 1;
    breathing_period = value;
}

void breathing_period_default(void) { breathing_period_set(BREATHING_PERIOD); }

void breathing_period_inc(void) { breathing_period_set(breathing_period + 1); }

void breathing_period_dec(void) { breathing_period_set(breathing_period - 1); }

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) { return v / BACKLIGHT_LEVELS * get_backlight_level(); }

static void breathing_callback(PWMDriver *pwmp) {
    (void)pwmp;
    uint16_t interval = (uint16_t)breathing_period * 256 / BREATHING_STEPS;
    // resetting after one period to prevent ugly reset at overflow.
    breathing_counter = (breathing_counter + 1) % (breathing_period * 256);
    uint8_t index     = breathing_counter / interval % BREATHING_STEPS;

    if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) || ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1))) {
        breathing_interrupt_disable();
    }

    uint32_t duty = cie_lightness(scale_backlight(breathing_table[index] * 256));

    chSysLockFromISR();
    pwmEnableChannelI(&BACKLIGHT_PWM_DRIVER, BACKLIGHT_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&BACKLIGHT_PWM_DRIVER, 0xFFFF, duty));
    chSysUnlockFromISR();
}

#else

__attribute__((weak)) void backlight_init_ports(void) {}

__attribute__((weak)) void backlight_set(uint8_t level) {}

__attribute__((weak)) void backlight_task(void) {}

#endif
