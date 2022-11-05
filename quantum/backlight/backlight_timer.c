#include "quantum.h"
#include "backlight.h"
#include "backlight_driver_common.h"
#include "debug.h"

#ifndef BACKLIGHT_GPT_DRIVER
#    define BACKLIGHT_GPT_DRIVER GPTD15
#endif

// Platform specific implementations
static void     backlight_timer_configure(bool enable);
static void     backlight_timer_set_duty(uint16_t duty);
static uint16_t backlight_timer_get_duty(void);

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
    if (v <= 5243)    // if below 8% of max
        return v / 9; // same as dividing by 900%
    else {
        uint32_t y = (((uint32_t)v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
        // to get a useful result with integer division, we shift left in the expression above
        // and revert what we've done again after squaring.
        y = y * y * y >> 8;
        if (y > 0xFFFFUL) // prevent overflow
            return 0xFFFFU;
        else
            return (uint16_t)y;
    }
}

void backlight_init_ports(void) {
    backlight_pins_init();

    backlight_set(get_backlight_level());

#ifdef BACKLIGHT_BREATHING
    if (is_backlight_breathing()) {
        breathing_enable();
    }
#endif
}

void backlight_set(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) level = BACKLIGHT_LEVELS;

    backlight_pins_off();

    backlight_timer_set_duty(cie_lightness(0xFFFFU / BACKLIGHT_LEVELS * level));
    backlight_timer_configure(level != 0);
}

static void backlight_timer_top(void) {
#ifdef BACKLIGHT_BREATHING
    if (is_breathing()) {
        breathing_task();
    }
#endif

    if (backlight_timer_get_duty() > 256) {
        backlight_pins_on();
    }
}

static void backlight_timer_cmp(void) {
    backlight_pins_off();
}

void backlight_task(void) {}

#ifdef BACKLIGHT_BREATHING
#    define BREATHING_STEPS 128

static bool     breathing         = false;
static uint16_t breathing_counter = 0;

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) {
    return v / BACKLIGHT_LEVELS * get_backlight_level();
}

void breathing_task(void) {
    uint8_t  breathing_period = get_breathing_period();
    uint16_t interval         = (uint16_t)breathing_period * 256 / BREATHING_STEPS;
    // resetting after one period to prevent ugly reset at overflow.
    breathing_counter = (breathing_counter + 1) % (breathing_period * 256);
    uint8_t index     = breathing_counter / interval % BREATHING_STEPS;

    // printf("index:%u\n", index);

    backlight_timer_set_duty(cie_lightness(scale_backlight((uint16_t)breathing_table[index] * 256)));
}

bool is_breathing(void) {
    return breathing;
}

void breathing_enable(void) {
    breathing_counter = 0;
    breathing         = true;
}
void breathing_disable(void) {
    breathing = false;
}

void breathing_pulse(void) {
    backlight_set(is_backlight_enabled() ? 0 : BACKLIGHT_LEVELS);
    wait_ms(10);
    backlight_set(is_backlight_enabled() ? get_backlight_level() : 0);
}
#endif

#ifdef PROTOCOL_CHIBIOS
// On Platforms where timers fire every tick and have no capture/top events
//   - fake event in the normal timer callback
uint16_t s_duty = 0;

static void timerCallback(void) {
    /* Software PWM
     * timer:1111 1111 1111 1111
     *       \______/| \_______/____  count(0-255)
     *          \    \______________  unused(1)
     *           \__________________  index of step table(0-127)
     */

    // this works for cca 65536 irqs/sec
    static union {
        uint16_t raw;
        struct {
            uint16_t count : 8;
            uint8_t  dummy : 1;
            uint8_t  index : 7;
        } pwm;
    } timer = {.raw = 0};

    timer.raw++;

    if (timer.pwm.count == 0) {
        // LED on
        backlight_timer_top();
    } else if (timer.pwm.count == (s_duty / 256)) {
        // LED off
        backlight_timer_cmp();
    }
}

static void backlight_timer_set_duty(uint16_t duty) {
    s_duty = duty;
}
static uint16_t backlight_timer_get_duty(void) {
    return s_duty;
}

// ChibiOS - Map GPT timer onto Software PWM
static void gptTimerCallback(GPTDriver *gptp) {
    (void)gptp;
    timerCallback();
}

static void backlight_timer_configure(bool enable) {
    static const GPTConfig gptcfg = {1000000, gptTimerCallback, 0, 0};

    static bool s_init = false;
    if (!s_init) {
        gptStart(&BACKLIGHT_GPT_DRIVER, &gptcfg);
        s_init = true;
    }

    if (enable) {
        gptStartContinuous(&BACKLIGHT_GPT_DRIVER, gptcfg.frequency / 0xFFFF);
    } else {
        gptStopTimer(&BACKLIGHT_GPT_DRIVER);
    }
}
#endif
