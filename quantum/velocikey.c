#include "velocikey.h"
#include "timer.h"
#include "eeconfig.h"
#include "eeprom.h"

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#    define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

// customization options
#ifndef VELOCIKEY_MAX_TYPING_SPEED
#    define VELOCIKEY_MAX_TYPING_SPEED 200
#endif
#ifndef VELOCIKEY_ACCEL_RATE
#    define VELOCIKEY_ACCEL_RATE VELOCIKEY_MAX_TYPING_SPEED / 100
#endif
#ifndef VELOCIKEY_DECAY_RATE_1
#    define VELOCIKEY_DECAY_RATE_1 1
#endif
#ifndef VELOCIKEY_DECAY_RATE_2
#    define VELOCIKEY_DECAY_RATE_2 1
#endif
#ifndef VELOCIKEY_DECAY_RATE_3
#    define VELOCIKEY_DECAY_RATE_3 2
#endif
#ifndef VELOCIKEY_DECAY_RATE_2_LIMIT
#    define VELOCIKEY_DECAY_RATE_2_LIMIT VELOCIKEY_MAX_TYPING_SPEED / 2
#endif
#ifndef VELOCIKEY_DECAY_RATE_3_LIMIT
#    define VELOCIKEY_DECAY_RATE_3_LIMIT VELOCIKEY_MAX_TYPING_SPEED / 4 * 3
#endif

uint8_t typing_speed = 0;

bool velocikey_enabled(void) { return eeprom_read_byte(EECONFIG_VELOCIKEY) == 1; }

void velocikey_toggle(void) {
    if (velocikey_enabled())
        eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    else
        eeprom_update_byte(EECONFIG_VELOCIKEY, 1);
}

void velocikey_accelerate(void) {
    if (typing_speed < VELOCIKEY_MAX_TYPING_SPEED) typing_speed += (VELOCIKEY_ACCEL_RATE);
}

void velocikey_decelerate(void) {
    static uint16_t decay_timer = 0;

    if (timer_elapsed(decay_timer) > 500 || decay_timer == 0) {
        if (typing_speed > 0) typing_speed -= VELOCIKEY_DECAY_RATE_1;
        // Decay a little faster at half of max speed
        if (typing_speed > VELOCIKEY_DECAY_RATE_2_LIMIT) typing_speed -= VELOCIKEY_DECAY_RATE_2;
        // Decay even faster at 3/4 of max speed
        if (typing_speed > VELOCIKEY_DECAY_RATE_3_LIMIT) typing_speed -= VELOCIKEY_DECAY_RATE_3;
        decay_timer = timer_read();
    }
}

uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue) { return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / VELOCIKEY_MAX_TYPING_SPEED)); }
