#include "quantum.h"
#include "backlight.h"

#if !defined(BACKLIGHT_PIN) && !defined(BACKLIGHT_PINS)
#    error "Backlight pin/pins not defined. Please configure."
#endif

#ifdef BACKLIGHT_BREATHING
#    error "Backlight breathing is not available for software PWM. Please disable."
#endif

static uint16_t s_duty_pattern = 0;

// clang-format off

/** \brief PWM duty patterns
 *
 * We scale the current backlight level to an index within this array. This allows
 * backlight_task to focus on just switching LEDs on/off, and we can predict the duty pattern
 */
static const uint16_t backlight_duty_table[] = {
    0b0000000000000000,
    0b1000000000000000,
    0b1000000010000000,
    0b1000001000010000,
    0b1000100010001000,
    0b1001001001001000,
    0b1010101010101010,
    0b1110111011101110,
    0b1111111111111111,
};
#define backlight_duty_table_size (sizeof(backlight_duty_table) / sizeof(backlight_duty_table[0]))

// clang-format on

static uint8_t scale_backlight(uint8_t v) { return v * (backlight_duty_table_size - 1) / BACKLIGHT_LEVELS; }

void backlight_init_ports(void) { backlight_init_pins(); }

void backlight_set(uint8_t level) { s_duty_pattern = backlight_duty_table[scale_backlight(level)]; }

void backlight_task(void) {
    static uint8_t backlight_tick = 0;

    if (s_duty_pattern & ((uint16_t)1 << backlight_tick)) {
        backlight_pins_on();
    } else {
        backlight_pins_off();
    }
    backlight_tick = (backlight_tick + 1) % 16;
}
