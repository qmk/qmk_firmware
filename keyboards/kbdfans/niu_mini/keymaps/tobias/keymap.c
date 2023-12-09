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

// extern keymap_config_t keymap_config;

enum layers {
  _QWERTY,
  _FNL1,
  _MOUSE,
  _LOWER,
  _RAISE,
  _FNL2,
  _ADJUST,
  _GAMEMODE,
  _FNL3,      _LOWER2,
  _RAISE2
};

enum custom_keycodes {
  TBMACRO = SAFE_RANGE,
  DGRMCRO,
  WRKMOD
};

bool bnumlock = false;
bool numlock_changed = false;
bool workmode = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL1 |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  | Bksp |Lower |    Space    |Raise | Bksp | AltGr|   *  | Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12(
  KC_TAB,     KC_Q,    KC_W,    KC_E,       KC_R,   KC_T,   KC_Y,       KC_U,    KC_I,   KC_O,     KC_P,  KC_LBRC,
  TT(_FNL1),  KC_A,    KC_S,    KC_D,       KC_F,   KC_G,   KC_H,       KC_J,    KC_K,   KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,       KC_V,   KC_B,   KC_N,       KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
  KC_LCTL, KC_LGUI, KC_LALT,  KC_DEL, TT(_LOWER), KC_SPC, KC_SPC, TT(_RAISE), KC_BSPC, KC_RALT, KC_NUHS,  KC_ESC
),


/* FNL1
 * ,-----------------------------------------------------------------------------------.
 * |TbMacr| Prev | Play | Next | AltF4| CapsL| Esc  | PgUp |  Up  | PgDn |PrScrn| Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL | Home | Left | Down | Right|      |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | End  |      |      |      |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |   !  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL1] = LAYOUT_ortho_4x12(
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS,  KC_ESC, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_BSPC,
  TT(_FNL1), _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______,  KC_DEL,
  KC_LSFT,    CTLZ,    CTLX,    CTLC,    CTLV, _______,  KC_END, _______, _______, _______, LSFT(KC_MINS), _______,
  _______, _______, CTALDEL, _______, _______, _______, _______, TO(_MOUSE), _______, _______, LSFT(KC_1), _______
),

[_MOUSE] = {
  {     KC_TAB, XXXXXXX, XXXXXXX,      KC_MS_UP,     XXXXXXX,    KC_T, XXXXXXX,    KC_MS_BTN3,   KC_MS_WH_UP,     KC_MS_BTN2, XXXXXXX, KC_MS_ACCEL0  },
  {TO(_QWERTY), XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, XXXXXXX, KC_MS_ACCEL1},
  {_______,        KC_Z,       KC_X,      KC_C,        KC_V, XXXXXXX, XXXXXXX,       XXXXXXX,        XXXXXXX,        XXXXXXX, XXXXXXX, KC_MS_ACCEL2},
  {KC_LCTL,     TO(_QWERTY), KC_LALT, _______, TO(_QWERTY), KC_MS_BTN1, XXXXXXX, TO(_QWERTY), _______, _______, TO(_QWERTY), TO(_QWERTY)}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   §  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ´  |   `  |   @  |   £  |   $  |   €  |   ¨  |   {  |   [  |   ]  |   }  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   <  |   |  |   >  |   °  |      |      |   µ  |   ¨  |   ^  |   ~  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
  KC_GRV,    KC_1,          KC_2,       KC_3,    KC_4,      KC_5,  KC_6,         KC_7,      KC_8,        KC_9,          KC_0,       KC_MINS,
  KC_EQL, S(KC_EQL),   RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_E), KC_RBRC, RALT(KC_7), RALT(KC_8), RALT(KC_9),    RALT(KC_0), RALT(KC_MINS),
  KC_LSFT, KC_NUBS, RALT(KC_NUBS), S(KC_NUBS), DGRMCRO, XXXXXXX, XXXXXXX,   RALT(KC_M),   KC_RBRC,  S(KC_RBRC), RALT(KC_RBRC),       _______,
  _______, _______,       KC_RALT,    _______,TO(_ADJUST), _______, _______,      _______,   _______,     _______,       _______, TO(_QWERTY)
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |  F1  |  F2  |  F3  |  F4  |  Esc | Bksp |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL2 |  F5  |  F6  |  F7  |  F8  |Insert| Home | PgUp |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |  Del | End  | PgDn |   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |      |      |             |   *  |   0  |   ,  |   .  | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
  KC_TAB,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_ESC, KC_BSPC, KC_PSLS,  KC_P7,  KC_P8,  KC_P9, KC_PMNS,
  TT(_FNL2), KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_INS, KC_HOME, KC_PGUP,  KC_P4,  KC_P5,  KC_P6, KC_PPLS,
  KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END, KC_PGDN,  KC_P1,  KC_P2,  KC_P3, KC_PENT,
  _______, _______, KC_LALT, _______, TO(_QWERTY), _______, _______, KC_PAST,  KC_P0,  KC_PDOT, KC_DOT, TO(_QWERTY)
),

/* FNL2
 * ,-----------------------------------------------------------------------------------.
 * |TbMacr| Prev | Play | Next | AltF4| CapsL|      |PrScrn|Insert| Home | PgUp |ScrLck|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL |      |      |  Del | End  | PgDn | Pause|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |  Up  |      | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down | Right| BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL2] = LAYOUT_ortho_4x12(
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS, _______, KC_PSCR,  KC_INS, KC_HOME, KC_PGUP, KC_SCRL,
  _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM,  _______, _______,  KC_DEL,  KC_END, KC_PGDN, KC_PAUS,
  _______,    CTLZ,    CTLX,    CTLC,    CTLV, _______, _______, _______, _______,   KC_UP, _______, KC_ENT,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, TO(_QWERTY)
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | GAME | Reset|      |      |      |      |      |      |      |      |      |LIGHTS|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |BLtogg|BLstep|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |RGBtog|RGBhui|RGBhud|RGBmod|RGBsai|RGBsad|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RGB4 |      |      |      |      |             |      |      |      |  NKO | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12(
  TO(_GAMEMODE), QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, WRKMOD,
    _______, BL_TOGG, BL_STEP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, RGB_TOG, RGB_HUI, RGB_HUD, RGB_MOD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_MODE_FORWARD,
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, RGB_M_P,  RGB_M_R, TO(_QWERTY)
),

/* Game mode
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   [  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL1 |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |   "  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   1  | Lower| Bksp | Alt  |    Space    | Raise| Bksp | BAIL |   *  | Esc  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMEMODE] = LAYOUT_ortho_4x12(
  KC_TAB,     KC_Q,    KC_W,    KC_E,       KC_R,   KC_T,   KC_Y,       KC_U,    KC_I,   KC_O,     KC_P,  KC_LBRC,
  TT(_FNL3),  KC_A,    KC_S,    KC_D,       KC_F,   KC_G,   KC_H,       KC_J,    KC_K,   KC_L,  KC_SCLN,  KC_QUOT,
  KC_LSFT,    KC_Z,    KC_X,    KC_C,       KC_V,   KC_B,   KC_N,       KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
  KC_LCTL, KC_1, MO(_LOWER2),  KC_DEL, KC_LALT, KC_SPC, KC_SPC, MO(_RAISE2), KC_BSPC, TO(_QWERTY), KC_NUHS, KC_ESC
),

/* FNL3
 * ,-----------------------------------------------------------------------------------.
 * |TbMacr| Prev | Play | Next | AltF4| CapsL| Esc  | PgUp |  Up  | PgDn |PrScrn| Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | Vol- | Vol+ | Mute | NumL | Home | Left | Down | Right|      |  Del |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | End  |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_FNL3] = LAYOUT_ortho_4x12(
  TBMACRO, KC_MPRV, KC_MPLY, KC_MNXT,  ALT_F4, KC_CAPS,  KC_ESC, KC_PGUP,   KC_UP, KC_PGDN, KC_PSCR, KC_BSPC,
  _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_NUM,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______,  KC_DEL,
  KC_LSFT, _______, _______, _______, _______, _______,  KC_END, _______, _______, _______, LSFT(KC_MINS), _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LSFT(KC_1), _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Tab |  F1  |  F2  |  F3  |  F4  |  Esc | Bksp |   /  |   7  |   8  |   9  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | FNL2 |  F5  |  F6  |  F7  |  F8  |Insert| Home | PgUp |   4  |   5  |   6  |   +  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |  Del | End  | PgDn |   1  |   2  |   3  | Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  Alt |      |      |             |   *  |   0  |   ,  |   .  | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER2] = LAYOUT_ortho_4x12(
  KC_TAB,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_ESC, KC_BSPC, KC_PSLS,  KC_P7,  KC_P8,  KC_P9, KC_PMNS,
  TT(_FNL2), KC_F5,   KC_F6,   KC_F7,   KC_F8,  KC_INS, KC_HOME, KC_PGUP,  KC_P4,  KC_P5,  KC_P6, KC_PPLS,
  KC_LSFT,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_END, KC_PGDN,  KC_P1,  KC_P2,  KC_P3, KC_PENT,
  _______, _______, _______, _______, _______, _______, _______, KC_PAST,  KC_P0,  KC_PDOT, KC_DOT, TO(_GAMEMODE)
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   §  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ´  |   `  |   @  |   £  |   $  |   €  |   ¨  |   {  |   [  |   ]  |   }  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   <  |   |  |   >  |   °  |      |      |   µ  |   ¨  |   ^  |   ~  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |      |             |      |      |      |      | BAIL |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE2] = LAYOUT_ortho_4x12(
  KC_GRV,    KC_1,          KC_2,       KC_3,    KC_4,      KC_5,  KC_6,         KC_7,      KC_8,        KC_9,          KC_0,       KC_MINS,
  KC_EQL, S(KC_EQL),   RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_E), KC_RBRC, RALT(KC_7), RALT(KC_8), RALT(KC_9),    RALT(KC_0), RALT(KC_MINS),
  KC_LSFT, KC_NUBS, RALT(KC_NUBS), S(KC_NUBS), DGRMCRO, XXXXXXX, XXXXXXX,   RALT(KC_M),   KC_RBRC,  S(KC_RBRC), RALT(KC_RBRC),       _______,
  _______, _______,       KC_RALT,    _______, _______, _______, _______,      _______,   _______,     _______,       _______, TO(_GAMEMODE)
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case TBMACRO:
                SEND_STRING(SS_TAP(X_TAB) SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT) SS_TAP(X_DELETE));
                return false;
            case DGRMCRO:
                if(!bnumlock) {
                    //register_code(KC_NUM);
                    //unregister_code(KC_NUM);
                    tap_code(KC_NUM);
                    bnumlock = true;
                }
                //SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_P0) SS_TAP(X_P1) SS_TAP(X_P7) SS_TAP(X_P6) SS_UP(X_LALT));
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_6) SS_UP(X_LALT) );
                return false;
            case WRKMOD:
                if(!workmode) {
                    workmode = true;
                    return false;
                }
                else {
                    workmode = false;
                    return false;
                }
        }

    }
    return true;
}

void rgbflag(uint8_t r, uint8_t g, uint8_t b) {
  for(int i = 0; i < RGBLED_NUM; i++){
    switch(i) {
      case 0 ... 13:
        // rgblight_setrgb_at(r,g,b,i);
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
        break;
      /* case 9 ... 11:
        // rgblight_setrgb_at(r,g,b,i);
        led[i].r = r;
        led[i].g = g;
        led[i].b = b;
        break; */
      default:
        // rgblight_setrgb_at(0,0,0,i);
        led[i].r = 0;
        led[i].g = 0;
        led[i].b = 0;
        break;
    }
  }
  rgblight_set();
}

layer_state_t layer_state_set_user(layer_state_t state) {
//  if(rgblight_get_mode() == 1) {
    switch (get_highest_layer(state)) {
    case _QWERTY:
        if(!workmode){
            rgblight_mode(9);
        }
        else if(workmode){
            rgblight_mode(1);
            rgbflag(0x00,  0x00, 0x00);
        }
        if(bnumlock) {
            tap_code(KC_NUM);
        }
        break;
    case _LOWER:
            rgblight_mode(1);
        if(!bnumlock) {
            tap_code(KC_NUM);
        }
        rgbflag(0xFF,  0x00, 0x00);

        break;
    case _ADJUST:
        rgblight_mode(1);
        rgbflag(0xFF,  0xFF, 0xFF);
        if(bnumlock) {
                tap_code(KC_NUM);
        }
        break;
    case _RAISE:
        rgblight_mode(1);
        rgbflag(0x00,  0xFF, 0x00);
        if(bnumlock) {
                tap_code(KC_NUM);
        }
        break;
    case _FNL1:
        rgblight_mode(1);
        rgbflag(0x00,  0x00, 0xFF);
        if(bnumlock) {
                tap_code(KC_NUM);
        }
        break;
    case _GAMEMODE:
            rgblight_mode(1);
            rgbflag(0xFF,  0x00, 0xFF);
        break;
    case _MOUSE:
        rgblight_mode(1);
        rgbflag(0x00,  0xFF, 0xFF);
        if(bnumlock) {
                tap_code(KC_NUM);
        }
        break;
    default: //  for any other layers, or the default layer
        rgblight_mode(1);
        if(bnumlock) {
            tap_code(KC_NUM);
        }
        rgbflag(0xFF,  0xFF, 0xFF);
        break;
    }
 // }
  return state;
}

/* void matrix_scan_user(void) {

    //Layer LED indicators

    uint32_t layer = layer_state;


    if (layer & (1<<2)) {
        if(!bnumlock) {
            numlock_changed = true;
            register_code(KC_NUM);
            unregister_code(KC_NUM);
            bnumlock = true;
        }
    }
}
 */


bool led_update_user(led_t led_state) {
  bnumlock = led_state.num_lock;
  return false;
}
