/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
//COMBOS
enum combos {
  PB_ESC,
  TG_CAP,
  DV_LPAR,
  FP_MINS,
  LTH_DEL,

  JL_EMAIL,
  MN_SCLN,
  KH_RPAR,
  LU_PLUS,
  RTH_ESC,

  QQT_PSCR,
};
//DEFINE THE COMBO SET UPS (TOTAL 11)
const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {MT(MOD_LSFT,KC_T), KC_G, COMBO_END};
const uint16_t PROGMEM dv_combo[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM lth_combo[] = {KC_TAB, KC_BSPC, COMBO_END};

const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM mn_combo[] = {KC_M, MT(MOD_RSFT,KC_N), COMBO_END};
const uint16_t PROGMEM kh_combo[] = {KC_K, KC_H, COMBO_END};
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM rth_combo[] = {KC_SPC, KC_ENT, COMBO_END};

const uint16_t PROGMEM qqt_combo[] = {KC_Q, KC_QUOT, COMBO_END};

//DEFINE THE COMBO OUTPUTS (TOTAL 11)
combo_t key_combos[COMBO_COUNT] = {
  [PB_ESC] = COMBO(pb_combo, QK_GESC),
  [TG_CAP] = COMBO(tg_combo, CAPS_WORD),
  [DV_LPAR] = COMBO(dv_combo, S(KC_9)),
  [FP_MINS] = COMBO(fp_combo, KC_MINS),
  [LTH_DEL] = COMBO(lth_combo, KC_DEL),  

  [JL_EMAIL] = COMBO_ACTION(jl_combo),
  [MN_SCLN] = COMBO(mn_combo, KC_SCLN),
  [KH_RPAR] = COMBO(kh_combo, S(KC_0)),
  [LU_PLUS] = COMBO(lu_combo, KC_EQL),
  [RTH_ESC] = COMBO(rth_combo, QK_GESC),

  [QQT_PSCR] = COMBO(qqt_combo, KC_PSCR),

};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case JL_EMAIL:
      if (pressed) {
        SEND_STRING("edenc@student.ubc.ca");
      }
      break;

  }
}


enum layer_names {
    _MAIN,
    _FUN,
    _NUM,
    _MEDIA,
    _NAV,
    _MOUSE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_split_3x5_3(
    KC_Q,             KC_W,              KC_F,             KC_P,             KC_B,KC_J,KC_L,              KC_U,              KC_Y,             KC_QUOT,
    MT(MOD_LGUI,KC_A),MT(MOD_LALT,KC_R), MT(MOD_LCTL,KC_S),MT(MOD_LSFT,KC_T),KC_G,KC_M,MT(MOD_RSFT,KC_N), MT(MOD_RCTL,KC_E), MT(MOD_RALT,KC_I),MT(MOD_RGUI,KC_O),
    KC_Z,             KC_X,              KC_C,             KC_D,             KC_V,KC_K,KC_H,              KC_COMM,           KC_DOT,           KC_SLSH,
                      LT(_MEDIA,KC_MUTE),LT(_FUN,KC_TAB),  LT(_NUM,KC_BSPC),           LT(_MOUSE,KC_SPC), LT(_NAV,KC_ENT),   LT(_MEDIA,KC_ESC)
  ),

  [_NUM] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_LBRC, KC_7,    KC_8,    KC_9,    KC_PMNS,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,      KC_RBRC, KC_4,    KC_5,    KC_6,    KC_PAST,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_BSLS, KC_1,    KC_2,    KC_3,    KC_PSLS,
                      XXXXXXX, XXXXXXX, XXXXXXX,      KC_0,    KC_DOT,  KC_PPLS
  ),

  [_NAV] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_HOME, KC_UP,   KC_END,  KC_INS,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_CAPS,      XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    KC_CAPS, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  ),


  [_MEDIA] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_FUN] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4, 
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,      XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,
                      XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_MOUSE] = LAYOUT_split_3x5_3(
   XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_MS_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_RGHT,                 XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
KC_MS_WH_LEFT,KC_MS_WH_UP,KC_MS_WH_DOWN,KC_MS_WH_RIGHT,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSLS, KC_QUOT,
                          KC_MS_BTN2,   KC_MS_BTN3, KC_MS_BTN1, XXXXXXX, XXXXXXX, XXXXXXX
  )


};


//encoders
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    switch (index) {
        case 0:
            // Left encoder
            if (layer == _NAV) {
                tap_code(clockwise ? KC_PGDN: KC_PGUP);
            } else if (layer == _MOUSE) {
                tap_code(clockwise ? KC_MS_WH_DOWN: KC_MS_WH_UP);
            } else {
                tap_code(clockwise ? KC_VOLD : KC_VOLU);
            }
            break;

        case 1:
            // Right encoder
          
            if (layer == _MEDIA) {
                tap_code_delay(clockwise ? KC_VOLU: KC_VOLD, 10);
            }
            else if (layer == _FUN) {
                tap_code16(clockwise ? LCTL(KC_TAB): LCTL(LSFT(KC_TAB)));
            } else {
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
            }
            break;
    }
    return false;
}