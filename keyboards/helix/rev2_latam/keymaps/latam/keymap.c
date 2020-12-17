#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
uint8_t                  RGB_current_mode;
HSV                      CURRENT_COLOR;
bool                     caps_is_active = false;
void keyboard_post_init_user(void) {
    rgblight_enable();  // Enables RGB, without saving settings
    rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 5);
    RGB_current_mode = rgblight_config.mode;
    rgblight_sethsv(HSV_RED);
    CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
}
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number { _QWERTY = 0, _LOWER, _RAISE };

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, RGBRST };

#define LOWER MO(1)
#define RAISE MO(2)

// HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_QWERTY] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_QUOT, KC_NUHS, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_ESC, KC_LGUI, KC_LALT, MO(2), MO(1), KC_SPC, KC_SPC, KC_RALT, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_RCTL),

                                                              [_LOWER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_MUTE, KC_MPLY, KC_BTN1, KC_BTN2, KC_TRNS, KC_PSCR, KC_TRNS, KC_INS, KC_MINS, KC_EQL, KC_TRNS, KC_NO, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_NUBS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_TRNS),

                                                              [_RAISE] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_M_R, RGB_M_K, RGB_M_SN, RGB_M_SW, RGB_TOG, KC_NO, KC_NO, RGB_RMOD, RGB_MOD, KC_NO, KC_NO, KC_NO, RGB_M_G, RGB_M_B, RGB_M_P, RGB_M_T, RGB_M_X, KC_NO, KC_NO, RGB_HUD, RGB_HUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)};

// define variables for reactive RGB
bool TOG_STATUS = false;

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                    if (!caps_is_active) {
                        RGB_current_mode = rgblight_config.mode;
                        CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                    }
                    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv(HSV_BLUE);
#endif
                }
                layer_on(_LOWER);
            } else {
#ifdef RGBLIGHT_ENABLE
                if (!caps_is_active) {
                    rgblight_mode(RGB_current_mode);
                    rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                } else {
                    rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                    rgblight_sethsv(HSV_WHITE);
                }
#endif
                TOG_STATUS = false;
                layer_off(_LOWER);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                // not sure how to have keyboard check mode and set it to a variable, so my work around
                // uses another variable that would be set to true after the first time a reactive key is pressed.
                if (TOG_STATUS) {  // TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
                } else {
                    TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                   if (!caps_is_active) {
                        RGB_current_mode = rgblight_config.mode;
                        CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                    }
                    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_sethsv(HSV_RED);
#endif
                }
                layer_on(_RAISE);
            } else {
#ifdef RGBLIGHT_ENABLE
                if (!caps_is_active) {
                    rgblight_mode(RGB_current_mode);
                    rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                } else {
                    rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                    rgblight_sethsv(HSV_WHITE);
                }
#endif
                layer_off(_RAISE);
                TOG_STATUS = false;
            }
            return false;
            break;
            // led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_RMOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step_reverse();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
            // Estos faltan agregar...
            // RGB_SPI,RGB_VAI,RGB_SAI,
            // RGB_SPD,RGB_VAD,RGB_SAD,
        case RGB_M_R:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD + 1);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_K:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_KNIGHT);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_SN:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_SNAKE);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_SW:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 3);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_G:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_TWINKLE + 5);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_B:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_BREATHING + 3);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_P:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_T:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 5);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_M_X:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            return false;
            break;
        case RGB_HUI:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                RGB_current_mode = rgblight_config.mode;
                rgblight_increase_hue();
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
            }
#endif
            return false;
            break;
        case RGB_HUD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                RGB_current_mode = rgblight_config.mode;
                rgblight_decrease_hue();
                CURRENT_COLOR = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
            }
#endif
            return false;
            break;
        case RGB_TOG:
            if (record->event.pressed) {
                if (!rgblight_config.enable) {
                    rgblight_enable();
                    rgblight_mode(RGBLIGHT_MODE_STATIC_GRADIENT + 5);
                    RGB_current_mode = rgblight_config.mode;
                    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                } else {
                    rgblight_disable();
                }
            }
            return false;
            break;
        case KC_CAPS:
            if (record->event.pressed) {
                register_code(KC_CAPS);
                caps_is_active = !caps_is_active;
                if (caps_is_active) {
                    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
                    rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
                    rgblight_sethsv(HSV_WHITE);
                } else if (!caps_is_active) {
                    unregister_code(KC_CAPS);
                    rgblight_mode(RGB_current_mode);
                    rgblight_sethsv(CURRENT_COLOR.h, CURRENT_COLOR.s, CURRENT_COLOR.v);
                }
            }
            return false;
            break;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
    startup_user();
#endif
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
    CURRENT_COLOR    = (HSV){rgblight_config.hue, rgblight_config.sat, rgblight_config.val};
#endif
// SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED
    iota_gfx_init(!has_usb());  // turns on the display
#endif
}
