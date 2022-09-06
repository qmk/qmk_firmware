#include "process_records.h"
#include "custom_keycodes.h"

#ifdef RGB_ENABLE
#include "custom_rgb.h"
#endif

#ifdef TRILAYER_ENABLED
uint32_t layer_state_set_user(uint32_t state)
{
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    static uint16_t reset_timer;

#ifndef TAP_DANCE_ENABLE
    if (!process_custom_tap_dance(keycode, record))
        return false;
#endif

    switch (keycode)
    {
        case RGBRST:
#ifdef RGB_ENABLE
            if (record->event.pressed)
                rgb_reset();
#endif
            return false;
        case RESET:
            {
                if (record->event.pressed)
                    reset_timer = timer_read() + 500;
                else if (timer_expired(timer_read(), reset_timer))
                    reset_keyboard();
            }
            return false;
#if defined(RGB_MATRIX_TOG_LAYERS) && defined(RGB_ENABLE)
        case RGB_TOG:
            if (record->event.pressed) {
              rgb_matrix_increase_flags();
            }
            return false;
#endif
  }

  return process_record_encoder(keycode, record) && process_record_keymap(keycode, record);
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
    return true;
}

__attribute__ ((weak))
bool process_record_encoder(uint16_t keycode, keyrecord_t *record)
{
    return true;
}
