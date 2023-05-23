#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
	extern rgblight_config_t rgblight_config; // To pull layer status for RGBLIGHT
#endif

//HSV colors for the leds
//#define HSV_BLACK         0,   0,   0
#define HSV_BLUE        170, 255, 255
#define HSV_GOLD         36, 255, 255
#define HSV_GREEN        85, 255, 255
#define HSV_MAGENTA     213, 255, 255
#define HSV_RED           0, 255, 255
//#define HSV_ORANGE       21, 255, 255
//#define HSV_TEAL        128, 255, 128
//#define HSV_OFF         HSV_BLACK

// Layers
enum sofle_layers {
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    KC_COLEMAK = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_PLOWER,
    KC_PRAISE,
};

// Tap Dance declarations
enum {
    TD_LCMK,
    TD_RCMK,
    TD_NUM,
    TD_ARS,
};

#include "layout.h"
#include "my_oled.h"
#include "my_encoder.h"
#include "my_rgb.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_PLOWER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_LOWER);
            }
            return false;
        case KC_PRAISE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_RAISE);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;

        /* KEYBOARD PET STATUS START */
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
        /* KEYBOARD PET STATUS END */
    }
    return true;
};

/* COMBOS
const uint16_t PROGMEM CMB_B[] = {KC_O, KC_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(CMB_B, KC_B),
    COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
}; */
