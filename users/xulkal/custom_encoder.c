#include "custom_encoder.h"

#ifdef ENCODER_ENABLE
const uint16_t PROGMEM encoders[][2] = {
    { KC_PGUP, KC_PGDN },
    { KC_DOWN, KC_UP }
}

void encoder_update_user(uint8_t index, bool clockwise)
{
    tap_code16(pgm_read_word(&encoders[index][clockwise]));
}
#endif
