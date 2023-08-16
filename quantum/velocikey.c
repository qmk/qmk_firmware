#include "velocikey.h"
#include "timer.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "util.h"

#define TYPING_SPEED_MAX_VALUE 200
uint8_t typing_speed = 0;

bool velocikey_enabled(void) {
    return eeprom_read_byte(EECONFIG_VELOCIKEY) == 1;
}

void velocikey_toggle(void) {
    if (velocikey_enabled())
        eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    else
        eeprom_update_byte(EECONFIG_VELOCIKEY, 1);
}

void velocikey_accelerate(void) {
    if (typing_speed < TYPING_SPEED_MAX_VALUE) typing_speed += (TYPING_SPEED_MAX_VALUE / 100);
}

void velocikey_decelerate(void) {
    static uint16_t decay_timer = 0;

    if (timer_elapsed(decay_timer) > 500 || decay_timer == 0) {
        if (typing_speed > 0) typing_speed -= 1;
        // Decay a little faster at half of max speed
        if (typing_speed > TYPING_SPEED_MAX_VALUE / 2) typing_speed -= 1;
        // Decay even faster at 3/4 of max speed
        if (typing_speed > TYPING_SPEED_MAX_VALUE / 4 * 3) typing_speed -= 2;
        decay_timer = timer_read();
    }
}

uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue) {
    return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / TYPING_SPEED_MAX_VALUE));
}
