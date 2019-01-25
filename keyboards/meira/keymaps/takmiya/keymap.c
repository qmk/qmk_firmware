/* Copyright 2017 Cole Markham
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
#include "meira.h"
#include "issi.h"
#include "lighting.h"

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        /* Qwerty
         * ,-----------------------------------------------------------------------------------.
         * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
         * |------+------+------+------+------+-------------+------+------+------+------+------|
         * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
         * |------+------+------+------+------+------|------+------+------+------+------+------|
         * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |//GUI |Enter |
         * |------+------+------+------+------+------+------+------+------+------+------+------|
         * | Ctrl | GUI  | Alt  | GUI  |Lower |Space |Enter |Raise | Left | Down |  Up  |Right |
         * `-----------------------------------------------------------------------------------'
         */
        [_QWERTY] = KEYMAP( \
                KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
                KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
                KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  GUI_T(KC_SLSH),  KC_ENT, \
                KC_LCTL,  KC_LGUI, KC_LALT, KC_RGUI, LOWER,   KC_SPC,  KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
        ),

        /* Lower
         * ,-----------------------------------------------------------------------------------.
         * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | DEL  |
         * |------+------+------+------+------+-------------+------+------+------+------+------|
         * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
         * |------+------+------+------+------+------|------+------+------+------+------+------|
         * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
         * |------+------+------+------+------+------+------+------+------+------+------+------|
         * |      |      |      |      |      |      |      |      | Home | PgUp | PgDn | End  |
         * `-----------------------------------------------------------------------------------'
         */
        [_LOWER] = KEYMAP( \
                KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL, \
                _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE, \
                _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), _______, _______,  _______, \
                _______, _______, _______, _______, _______, _______, _______, _______,    KC_HOME,    KC_PGDN, KC_PGUP, KC_END \
        ),

        /* Raise
         * ,-----------------------------------------------------------------------------------.
         * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | DEL  |
         * |------+------+------+------+------+-------------+------+------+------+------+------|
         * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
         * |------+------+------+------+------+------|------+------+------+------+------+------|
         * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
         * |------+------+------+------+------+------+------+------+------+------+------+------|
         * |      |      |      |      |      |      |      |      | Home | PgUp | PgDn | End  |
         * `-----------------------------------------------------------------------------------'
         */
        [_RAISE] = KEYMAP( \
                KC_GRV , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
                _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
                _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END \
        ),

        /* Adjust (Lower + Raise)
         * ,-----------------------------------------------------------------------------------.
         * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
         * |------+------+------+------+------+-------------+------+------+------+------+------|
         * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
         * |------+------+------+------+------+------|------+------+------+------+------+------|
         * |      |      |      |      |      |      |      |      |      |      |      |      |
         * |------+------+------+------+------+------+------+------+------+------+------+------|
         * |      |      |      |      |      |             |      |      |      |      |      |
         * `-----------------------------------------------------------------------------------'
         */
        [_ADJUST] =  KEYMAP( \
                BL_TOGG, RESET,   _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_PSCR, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_DEL, \
                BL_STEP, RGB_MOD, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                _______, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
        )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
#ifdef RGBLIGHT_ENABLE
    rgblight_mode(RGB_current_mode);
#endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
//        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(16);
#endif
            }
            layer_on(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
#endif
            TOG_STATUS = false;
            layer_off(_LOWER);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            //not sure how to have keyboard check mode and set it to a variable, so my work around
            //uses another variable that would be set to true after the first time a reactive key is pressed.
            if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
            } else {
                TOG_STATUS = !TOG_STATUS;
#ifdef RGBLIGHT_ENABLE
                rgblight_mode(15);
#endif
            }
            layer_on(_RAISE);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        } else {
#ifdef RGBLIGHT_ENABLE
            rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
#endif
            layer_off(_RAISE);
            TOG_STATUS = false;
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case ADJUST:
        // FIXME add RGB feedback
        if (record->event.pressed) {
            layer_on(_ADJUST);
        } else {
            layer_off(_ADJUST);
        }
        return false;
        break;
    case BL_TOGG:
#ifdef ISSI_ENABLE
        if (record->event.pressed) {
            print("Enabling backlight\n");
            issi_init();
        }
#endif
        return false;
        break;
    case BL_STEP:
        if (record->event.pressed) {
            print("Stepping backlight\n");
#ifdef BACKLIGHT_ENABLE
            print("Really stepping backlight\n");
            backlight_step();
#endif

        }
        return false;
        break;
        //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
#ifdef RGBLIGHT_ENABLE
    case RGB_MOD:
        if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
        }
        return false;
        break;
#endif
//    case BL_INC:
//    		meira_inc_backlight_level();
//    	      return false;
//    		break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

}
