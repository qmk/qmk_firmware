 /* Copyright 2017 F_YUUCHI
  * Copyright 2020 Drashna Jaelre <@drashna>
  * Copyright 2020 Ben Roesner (keycapsss.com)
  * Copyright 2022 Vii33 (https://github.com/vii33/mecha-keyboard-lily58l)
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */


#include QMK_KEYBOARD_H
#include "enums.h"
#include "oled.h"
#include "process_record_user.h"

extern uint8_t is_master;


/* Layer quick names */
#define LOWER MO(_LOWER)
#define UPPER MO(_UPPER)
#define MOD   MO(_MOD)
#define GAME  TG(_GAME)

/* Key quick names */
#define QC_AT   S(KC_2)           // @
#define QC_EUR  ALGR(KC_5)        // €
#define QC_SS   ALGR(KC_S)        // ß
#define QC_SECT S(ALGR(KC_S))     // §
#define QC_DEG  S(ALGR(KC_SCLN))  // °
#define QC_HAT  S(KC_6)           // ^
#define QC_AND  S(KC_7)           // &
#define QC_DQUT S(KC_QUOT)        // "

#define QC_UNDO LCTL(KC_Z)
#define QC_REDO LCTL(KC_Y)
#define QC_CTLX LCTL(KC_X)
#define QC_CTLC LCTL(KC_C)
#define QC_CTLV LCTL(KC_V)

#define GMESCN  LSFT(KC_F11)
#define CTALDEL LCTL(LALT(KC_DEL)) // CTRL+ALT+DEL
#define WINSCNS SGUI(KC_S)         // WIN+SHIFT+S

#define WRDLFT  C(KC_LEFT)         // CTRL+LEFT (Word left)
#define WRDRGT  C(KC_RIGHT)        // CTRL+RIGHT (Word right)


/* Animation Speeds */
//const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};
const uint8_t RGBLED_SNAKE_INTERVALS[] PROGMEM = {200, 150, 100};


#ifdef RGBLIGHT_LAYERS
/* Lightning Layers as status indicators. -> Array of segments */
const rgblight_segment_t PROGMEM mod_indicator[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 4, HSV_GREEN}   // First segment: Turn on 5 LEDs starting with #4~~
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    mod_indicator   // 0
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;    // Enable the LED layers
}

/* Callback when layer changes */
layer_state_t layer_state_set_user(layer_state_t state) {
    /* Set my_rgb_layer 0 when comparison is true (here: _MOD Layer active) */
    rgblight_set_layer_state(0, layer_state_cmp(state, _MOD));
    return state;
}
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY Example
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |UPPER |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */


[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,   KC_3,    KC_4,   KC_5,                          KC_6,   KC_7,    KC_8,     KC_9,    KC_0,    KC_MINS, 
  KC_TAB,   KC_Q,   KC_W,   KC_E,    KC_R,   KC_T,                          KC_Z,   KC_U,    KC_I,     KC_O,    KC_P,    CC_UE, 
  CC_QUOT,  KC_A,   GUI_S,  ALT_D,   CTL_F,  KC_G,                           KC_H,   CTL_J,   ALT_K,    GUI_L,   CC_OE,   CC_AE, 
  CC_APHO,  KC_Y,   KC_X,   KC_C,    KC_V,   KC_B,  KC_MUTE,      _______,  KC_N,   KC_M,    CC_SCOLN, CC_COLN, CC_EXLM, KC_ENTER, 
                            CC_SLH,  MOD,    LOWER, SHFT_SP,      SHFT_SP,  UPPER,  KC_BSPC, KC_DEL
),


[_LOWER] = LAYOUT(
  _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11, 
  _______,  XXXXXXX, WINSCNS, QC_UNDO, QC_REDO, KC_ENTER,                     XXXXXXX, WRDLFT,  KC_UP,   WRDRGT,   KC_PGUP, KC_F12, 
  XXXXXXX,  KC_DEL,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT,  KC_PGDN, XXXXXXX, 
  XXXXXXX,  KC_BSPC, QC_CTLX, QC_CTLC, QC_CTLV, XXXXXXX, _______,   _______,  XXXXXXX, KC_HOME, KC_BSPC, KC_END,   XXXXXXX, KC_ENT, 
                              _______, _______, _______, _______,   KC_LSFT,  _______, KC_BSPC, KC_DEL
),


[_UPPER] = LAYOUT(
  _______,  _______,  _______,  _______,  _______,  _______,                     _______,  _______,  _______,  _______, _______, _______, 
  _______,  QC_AT,    KC_TILD,  QC_EUR,   KC_PSCR,  _______,                     KC_PAST,  KC_GT,    KC_LCBR,  KC_RCBR, KC_PMNS, _______,
  KC_PIPE,  XXXXXXX,  QC_SS,    QC_UNDO,  QC_REDO,  CTALDEL,                     KC_PSLS,  KC_EQL,   KC_LPRN,  KC_RPRN, KC_PPLS, QC_DQUT, 
  QC_DEG,   KC_BSPC,  QC_CTLX,  QC_CTLC,  QC_CTLV,  XXXXXXX, _______, _______,   QC_HAT,   KC_LT,    KC_LBRC,  KC_RBRC, QC_AND,  KC_PENT,
                                _______,  _______,  _______, KC_LSFT, _______,   _______,  KC_BSPC,  KC_DEL
),


  [_MOD] = LAYOUT(
    RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_SW, RGB_M_G, RGB_M_SN,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_COMMA, GAME, 
    RGB_MOD, RGB_SAI, RGB_SPI, XXXXXXX,  RGB_M_T, CC_ALRM,                       KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_PERC,
    XXXXXXX, RGB_SAD, RGB_SPD, XXXXXXX,  XXXXXXX, XXXXXXX,                       KC_PSLS,  KC_P4,    KC_P5,    KC_P6,    KC_PMNS,  KC_EQL, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_NUM,  XXXXXXX, CC_SAVRGB,  _______,  KC_P0,    KC_P1,    KC_P2,    KC_P3,    KC_DOT,   KC_PENT, 
                               XXXXXXX,  _______, _______, _______,    _______,  _______,  _______,  _______
),

  [_GAME] = LAYOUT(
    KC_ESC,  KC_1,  KC_2,  KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,     KC_8,    KC_9,   KC_0,     GAME, 
    KC_TAB,  KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,                          KC_Z,    KC_U,     KC_I,    KC_O,   KC_P,     KC_PGUP, 
    KC_LSFT, KC_A,  KC_S,  KC_D,    KC_F,    KC_G,                          KC_H,    KC_J,     KC_K,    KC_L,   KC_F6,    KC_PGDN, 
    KC_LCTL, KC_Y,  KC_X,  KC_C,    KC_V,    KC_B,   GMESCN,        KC_F12, KC_N,    KC_M,     KC_LEFT, KC_UP,  KC_RIGHT, KC_DOWN, 
                           KC_CAPS, KC_LALT, KC_SPC, KC_SPC,        KC_ENT, KC_F7,   KC_BSPC,  KC_DEL
)

};

/* -------------------------------------------------------------------------------- */

/* Different tapping timings */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_S:
        case GUI_L:
            return TAPPING_TERM + 150;
        default:
            return TAPPING_TERM;
    }
}

/* -------------------------------------------------------------------------------- */

/* Rotary encoder */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {             // Encoder on master side
    if (IS_LAYER_ON(_MOD))          // _MOD LAYER
    {
        if ( get_mods() & MOD_MASK_SHIFT ) {
            if (clockwise) {
                rgblight_increase_sat_noeeprom();
            } else {
                rgblight_decrease_sat_noeeprom();
            }
        } else {
            if (clockwise) {
                rgblight_increase_hue_noeeprom();
            } else {
                rgblight_decrease_hue_noeeprom();
            }
        }
    } else {                          // _QWERTY LAYER and others
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
  } else if (index == 1) {        // Encoder on slave side
    if(IS_LAYER_ON(_LOWER)) {       // _LOWER LAYER
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
    } else if (IS_LAYER_ON(_MOD))     // _MOD LAYER
    {
        if ( get_mods() & MOD_MASK_SHIFT ) {
            if (clockwise) {
                rgblight_increase_speed_noeeprom();
            } else {
                rgblight_decrease_speed_noeeprom();
            }
        } else {
            if (clockwise) {
                rgblight_increase_val_noeeprom();
            } else {
                rgblight_decrease_val_noeeprom();
            }
        }
    } else {                          // _QWERTY LAYER and others
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);    
      }
    }
  }
  return true;
}
#endif  // ENCODER_ENABLE
