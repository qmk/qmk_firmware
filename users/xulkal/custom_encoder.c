#include "custom_encoder.h"
#include "custom_keycodes.h"

#ifdef RGB_OLED_MENU
#include "custom_rgb.h"

// I'm lazy and like constants over calculations, also using it as a compile time check
#if defined(RGB_MATRIX_ENABLE)
    #define RGB_FUNCTION_COUNT 6
#elif defined(RGBLIGHT_ENABLE)
    #define RGB_FUNCTION_COUNT 5
#endif

typedef void (*rgb_f)(void);

const rgb_f rgb_functions[RGB_FUNCTION_COUNT][2] = {
#if defined(RGB_MATRIX_ENABLE)
    { rgb_matrix_increase_hue,      rgb_matrix_decrease_hue     },
    { rgb_matrix_increase_sat,      rgb_matrix_decrease_sat     },
    { rgb_matrix_increase_val,      rgb_matrix_decrease_val     },
    { rgb_matrix_increase_speed,    rgb_matrix_decrease_speed   },
    { rgb_matrix_step,              rgb_matrix_step_reverse     },
    { rgb_matrix_increase_flags,    rgb_matrix_decrease_flags   }
#elif defined(RGBLIGHT_ENABLE)
    { rgblight_increase_hue,        rgblight_decrease_hue       },
    { rgblight_increase_sat,        rgblight_decrease_sat       },
    { rgblight_increase_val,        rgblight_decrease_val       },
    { rgblight_increase_speed,      rgblight_decrease_speed     },
    { rgblight_step,                rgblight_step_reverse       }
#endif
};

// Start at the end for mode
uint8_t rgb_encoder_state = 4;

bool process_record_encoder(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
        case RGB_ENC:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    rgb_encoder_state = (rgb_encoder_state - 1);
                    if (rgb_encoder_state >= RGB_FUNCTION_COUNT)
                        rgb_encoder_state = RGB_FUNCTION_COUNT - 1;
                } else {
                    rgb_encoder_state = (rgb_encoder_state + 1) % RGB_FUNCTION_COUNT;
                }
            }
            return false;
    }
    return true;
}
#endif // RGB_OLED_MENU

const uint16_t PROGMEM encoders[][2] = {
    { KC_PGUP, KC_PGDN },
    { KC_VOLU, KC_VOLD }
};

void encoder_update_user(uint8_t index, bool clockwise)
{
    if (!is_keyboard_master())
        return;

#ifdef RGB_OLED_MENU
    if (index == RGB_OLED_MENU)
        (*rgb_functions[rgb_encoder_state][clockwise])();
    else
#endif // RGB_OLED_MENU
        tap_code16(pgm_read_word(&encoders[index][clockwise]));
}
