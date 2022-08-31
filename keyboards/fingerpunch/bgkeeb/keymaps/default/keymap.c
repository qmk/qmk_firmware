#include QMK_KEYBOARD_H

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#include "color.h"
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

bool is_caps_lock_on;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  | LOWER| Enter|   '  |    |BckSpc| Space| RAISE|
 *                  `--------------------'    `--------------------.
 */

// Default config uses home row mods. So hold each of the keys on the home row to use ctrl, gui, alt, or shift
[_QWERTY] = LAYOUT_split_3x5_4(
  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,
  LCTL_T(KC_A), LGUI_T(KC_S), LALT_T(KC_D), LSFT_T(KC_F), KC_G,         KC_H,    RSFT_T(KC_J), RALT_T(KC_K), RGUI_T(KC_L), RCTL_T(KC_SCLN),
  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,
                KC_MUTE,      LOWER,        KC_ENT,       KC_QUOT,      KC_BSPC, KC_SPC,       RAISE,        LCTL(KC_BSPC)
),

/* Colemak
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   R  |   S  |   T  |   G  |           |   M  |   N  |   E  |   I  |   O  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .  |   /  |
 * `-------------+--------------------'           `----------------------------------'
 *        |      |      |                                       |      |      |
 *        `------+------'                                       `------+------'
 *                  ,--------------------.    ,--------------------.
 *                  | LOWER| Enter|   '  |    |BckSpc| Space| RAISE|
 *                  `--------------------'    `--------------------.
 */

// Default config uses home row mods. So hold each of the keys on the home row to use ctrl, gui, alt, or shift
[_COLEMAK] = LAYOUT_split_3x5_4(
  KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,         KC_J,    KC_L,         KC_U,         KC_Y,         KC_SCLN,
  LCTL_T(KC_A), LGUI_T(KC_R), LALT_T(KC_S), LSFT_T(KC_T), KC_G,         KC_M,    RSFT_T(KC_N), RALT_T(KC_E), RGUI_T(KC_I), RCTL_T(KC_O),
  KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,         KC_K,    KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,
                KC_MUTE,      LOWER,        KC_ENT,       KC_QUOT,      KC_BSPC, KC_SPC,       RAISE,        LCTL(KC_BSPC)
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Left | Down |  Up  | Right| Tab |           |      |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt |      |           |      |      |      |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *        |      |      |                                       |      |      |
 *        `------+------'                                       `------+------'
 *                  ,--------------------.    ,--------------------.
 *                  | LOWER|      |      |    |      |      | RAISE|
 *                  `--------------------'    `--------------------.
 */
[_RAISE] = LAYOUT_split_3x5_4(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
  KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, _______,      _______, _______, _______, KC_BSLS, KC_QUOT,
           _______, _______, _______, _______,      _______, _______, _______, _______
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |      |      |      |      |           |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   ~  |      |      |      |           |      |      |      |   |  |   '  |
 * `----------------------------------'           `----------------------------------'
 *        |      |      |                                       |      |      |
 *        `------+------'                                       `------+------'
 *                  ,--------------------.    ,--------------------.
 *                  | LOWER|      |      |    |  Del |      | RAISE|
 *                  `--------------------'    `--------------------.
 */
[_LOWER] = LAYOUT_split_3x5_4(
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
  KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_DQT,
           _______, _______, _______, _______,      KC_DEL,  _______, _______, _______
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * | RGB_T| RGB_R| RGB_F|      |QWERTY|           |   F1 |  F2  |  F3  |  F4  |  F5 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SPD_I| HUE_I| SAT_I| VAL_I|COLEMK|           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | SPD_D| HUE_D| SAT_D| VAL_D|      |           |  F11 |  F12 |      |      | Reset|
 * `----------------------------------'           `----------------------------------'
 *        |      |      |                                       |      |      |
 *        `------+------'                                       `------+------'
 *                  ,--------------------.    ,--------------------.
 *                  | LOWER|      |      |    |      |      | RAISE|
 *                  `--------------------'    `--------------------.
 */
[_ADJUST] =  LAYOUT_split_3x5_4(
  RGB_TOG, RGB_RMOD, RGB_MOD, _______, TO(_QWERTY),       KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,
  RGB_SPI, RGB_HUI,  RGB_SAI, RGB_VAI, TO(_COLEMAK),      KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,
  RGB_SPD, RGB_HUD,  RGB_SAD, RGB_VAD, _______,           KC_F11,  KC_F12,  _______, _______,  RESET,
           _______,  _______, _______, _______,           _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef PIMORONI_TRACKBALL_ENABLE
    switch(get_highest_layer(state)) {
        case _QWERTY:
            if (is_caps_lock_on) {
                pimoroni_trackball_set_rgbw(RGB_RED, 0x00);
            } else {
                pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
            }
            break;
        case _COLEMAK:
            pimoroni_trackball_set_rgbw(RGB_GREEN, 0x00);
            break;
        case _LOWER:
            pimoroni_trackball_set_rgbw(RGB_PURPLE, 0x00);
            break;
        case _RAISE:
            pimoroni_trackball_set_rgbw(RGB_YELLOW, 0x00);
            break;
        case _ADJUST:
            pimoroni_trackball_set_rgbw(RGB_ORANGE, 0x00);
            break;
        default: //  for any other layers, or the default layer
            if (is_caps_lock_on) {
                pimoroni_trackball_set_rgbw(RGB_RED, 0x00);
            } else {
                pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
            }
            break;
    }
    #endif
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void keyboard_post_init_user(void) {
    is_caps_lock_on = false;
    #ifdef PIMORONI_TRACKBALL_ENABLE
    pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPSLOCK:
            if (record->event.pressed) {
                if (is_caps_lock_on) {
                    is_caps_lock_on = false;
                } else {
                    is_caps_lock_on = true;
                }
            }
            break;
        default:
            break;
    }

    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // default behavior if undefined
    if (index == 0) {
        // Conditional to reverse the direction of encoder number 1
        // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
        #ifdef ENCODERS_A_REVERSE
        if (!clockwise) {
        #else
        if (clockwise) {
        #endif
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
      // Conditional to reverse the direction of encoder number 1
      // The reason I have this is that for some of my boards, it supports two different types of encoders, and they may differ in direction
      #ifdef ENCODERS_B_REVERSE
      if (!clockwise) {
      #else
      if (clockwise) {
      #endif
        tap_code16(C(KC_RGHT));
      }
      else{
        tap_code16(C(KC_LEFT));
      }
    }

    return true;
}
#endif

