#include "process_records.h"
#include "custom_keycodes.h"
#include "timer_utils.h"

#if defined(RGB_MATRIX_ENABLE)
extern void eeconfig_update_rgb_matrix_default(void);
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
    if (!process_tap_dance_double(keycode, record))
        return false;
#endif

    switch (keycode)
    {
        case RGBRST:
            {
#if defined(RGBLIGHT_ENABLE)
                if (record->event.pressed)
                {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                }
#elif defined(RGB_MATRIX_ENABLE)
                if (record->event.pressed)
                    eeconfig_update_rgb_matrix_default();
#endif
            }
            return false;
        case RESET:
            {
                if (record->event.pressed)
                    reset_timer = timer_read() + 500;
                else if (timer_expired(reset_timer))
                    reset_keyboard();
            }
            return false;
  }

  return process_record_keymap(keycode, record);
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record)
{
    return true;
}
