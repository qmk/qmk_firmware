/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "keymap_german.h"

enum combos {
    AE,
    OE,
    UE,
    SZ
};

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, DE_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [AE] = COMBO(ae_combo, DE_AE),
  [OE] = COMBO(oe_combo, DE_OE),
  [UE] = COMBO(ue_combo, DE_UE),
  [SZ] = COMBO(sz_combo, DE_SS)
};

enum planck_layers {
  _QWERTZ,
  _NUMPD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTZ = SAFE_RANGE,
  NUMPD,
  SCROLL
};

bool scroll = false;

#ifdef AUDIO_ENABLE
    float ping_song[][2] = SONG(PING_SOUND);
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ
 * ,-----------------------------------------------------------------------------------.
 * | RtEnc|   Q  |   W  |   E  |   R  |   T  |   Z  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   +  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SfTab|   Y  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |SfEnt |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  GUI | NumPd|  Alt |  Num |    Space    |  Sym |  Del | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTZ] = LAYOUT_planck_grid(
    SCROLL,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    DE_Z,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    KC_H,    KC_J,    KC_K,    KC_L, DE_PLUS,    DE_MINS,
LSFT_T(KC_TAB),DE_Y,  KC_X,    KC_C,    KC_V,   KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT,   KC_UP,    SC_SENT,
    KC_LCTL, KC_LGUI, NUMPD,   KC_LALT, LOWER,  KC_SPC,  KC_SPC,   RAISE,  KC_DEL, KC_LEFT, KC_DOWN,  KC_RGHT
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   8  |   9  |   /  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NLCK |   4  |   5  |   6  |   -  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   +  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   .  |   0  |   ,  |NumOFF|    Enter    |Raise |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPD] = LAYOUT_planck_grid(
 SFT_T(KC_PASTE),KC_P7,   KC_P8, KC_P9,  DE_SLSH, _______, _______, _______, _______, _______, _______,  _______,
    KC_NUM,     KC_P4,   KC_P5, KC_P6,  DE_MINS, _______, _______, _______, _______, _______, _______,  _______,
    _______,    KC_P1,   KC_P2, KC_P3,  DE_PLUS, _______, _______, _______, _______, _______, _______,  _______,
 CTL_T(KC_COPY),KC_DOT,  KC_P0, KC_COMM, NUMPD,  KC_ENT,  KC_ENT,  _______, _______, _______, _______,  _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ^  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F10 |  F11 |  F12 |  F13 |  F14 |  F15 |      |      |      |Pg Up |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Home |Pg Dn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   _______, _______,
    _______, KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, _______, _______, KC_PGUP, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,  KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   "  |   §  |   $  |   %  |   &  |   /  |   (  |   )  |   =  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   °  |      |      |      |      |      |   |  |   ?  |   [  |   ]  |   '  |   |  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   \  |   <  |   >  |   {  |   }  | Vol+ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Brt- | Vol- | Brt+ |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, DE_SLSH, DE_LPRN, DE_RPRN, DE_EQL,  KC_BSPC,
    KC_TILD, _______, _______, _______, _______, _______, DE_PIPE, DE_QUES, DE_LBRC, DE_RBRC, DE_QUOT, DE_HASH,
    _______, _______, _______, _______, _______, DE_BSLS, DE_LABK, DE_RABK, DE_LCBR, DE_RCBR, KC_VOLU, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BRID, KC_VOLD, KC_BRIU
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |PowOff|      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    KC_PWR,  _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;*/
    case NUMPD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(ping_song);
        #endif
        if (layer_state_is(_NUMPD)) {
          layer_off(_NUMPD);
        } else {
          layer_on(_NUMPD);
        }
      }
      return false;
      break;
    case SCROLL:
      if (record->event.pressed) {
          scroll = true;
      } else {
          scroll = false;
      }
    default:
      return true;
  }
}

void encoder_update(bool clockwise) {
  if (layer_state_is(_NUMPD)){
    if (clockwise) {
        tap_code(KC_RIGHT);
    } else {
        tap_code(KC_LEFT);
    }
  } else if (scroll) { //scroll fast mode
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void matrix_scan_user(void) {
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
const rgblight_segment_t PROGMEM numbers_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {3, 4, HSV_GREEN}
);
const rgblight_segment_t PROGMEM symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 5, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 4, HSV_RED}       // Light 4 LEDs, starting with LED 6
);
const rgblight_segment_t PROGMEM config_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 6, HSV_YELLOW}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    numbers_layer,
    symbols_layer,
    numpad_layer,   // Overrides other layers
    config_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (!(layer_state_is(_NUMPD))) {
        state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    }
    rgblight_set_layer_state(2, layer_state_cmp(state, 1));
    rgblight_set_layer_state(0, layer_state_cmp(state, 2));
    rgblight_set_layer_state(1, layer_state_cmp(state, 3));
    rgblight_set_layer_state(3, layer_state_cmp(state, 4));
    return state;
}
