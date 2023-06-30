/* Copyright 2018 darm
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

// Layer shorthand
#define _BASE     0
#define _LOWER    1
#define _LINVERT  2
#define _RAISE    3
#define _EMOJIFY  4

enum emoji_map {
  UNAM, // unamused 😒
  HEYE, // smiling face with heart shaped eyes 😍
  OK, // ok hand sign 👌
  SMIR, // smirk 😏
  PRAY, // pray 🙏
  CELE, // celebration 🙌
  COOL, // smile with sunglasses 😎
  EYES, // eyes
  THNK, // BIG THONK
  NAIL, // Nailcare 💅
};

const uint32_t unicode_map[] PROGMEM = {
  [UNAM] = 0x1F612,
  [HEYE] = 0x1f60d,
  [OK]   = 0x1F44C,
  [SMIR] = 0x1F60F,
  [PRAY] = 0x1F64F,
  [CELE] = 0x1F64C,
  [COOL] = 0x1F60E,
  [EYES] = 0x1F440,
  [THNK] = 0x1F914,
  [NAIL] = 0x1F485,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_5x15(
    QK_GESC , KC_1  , KC_2    , KC_3    , KC_4    , KC_5    , KC_MPRV , KC_MPLY , KC_MNXT , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC,
    KC_TAB  , KC_Q  , KC_W    , KC_E    , KC_R    , KC_T    , KC_MINS , KC_EQL  , KC_BSLS , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_ENT ,
    MO(3)   , KC_A  , KC_S    , KC_D    , KC_F    , KC_G    , KC_LBRC , KC_MUTE , KC_RBRC , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_QUOT,
    KC_LSFT , KC_Z  , KC_X    , KC_C    , KC_V    , KC_B    , KC_HOME , KC_SLEP , KC_END  , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
    KC_LCTL , MO(4) , KC_LALT , KC_LGUI , KC_SPC  , KC_SPC  , MO(1)   , KC_DEL  , MO(2)   , KC_SPC  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_RGUI,
  ),

  [_LOWER] = LAYOUT_ortho_5x15(
    _______ , _______ , _______ , _______ , _______ , _______ , BL_TOGG , BL_DOWN , BL_UP   , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , KC_WH_L , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_U , BL_STEP , RGB_TOG , RGB_MOD , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , KC_WH_R , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , RGB_HUI , RGB_HUD , RGB_SAI , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , RGB_SAD , RGB_VAI , RGB_VAD , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  ),

  [_LINVERT] = LAYOUT_ortho_5x15(
    _______ , _______ , _______ , _______ , _______ , _______ , BL_TOGG , BL_DOWN , BL_UP   , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , BL_STEP , RGB_TOG , RGB_MOD , KC_WH_U , KC_BTN1 , KC_MS_U , KC_BTN2 , KC_WH_L , _______,
    _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , RGB_SAI , RGB_HUI , RGB_HUD , KC_WH_D , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_R , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , RGB_SAD , RGB_VAI , RGB_VAD , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_RAISE] = LAYOUT_ortho_5x15(
    KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , _______ , _______ , _______ , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12 ,
    _______ , _______ , KC_7    , KC_8    , KC_9    , _______ , _______ , _______ , _______ , _______ , KC_MUTE , KC_VOLD , KC_VOLU , _______ , _______,
    _______ , _______ , KC_4    , KC_5    , KC_6    , _______ , _______ , _______ , _______ , _______ , KC_MPRV , KC_MPLY , KC_MNXT , _______ , _______,
    _______ , _______ , KC_1    , KC_2    , KC_3    , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , KC_0    , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),

  [_EMOJIFY] = LAYOUT_ortho_5x15(
    TO(0)   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , QK_BOOT,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , X(CELE) , X(PRAY) , X(NAIL) , X(OK)   , X(THNK) , _______ , _______ , _______ , X(UNAM) , X(HEYE) , X(COOL) , X(EYES) , X(SMIR) , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  )

};

void matrix_init_user(void) {
  _delay_ms(20); // Gets rid of tick
  set_unicode_input_mode(UNICODE_MODE_LINUX);
}

/* Template for future layers
 [_LAYER_NAME] = LAYOUT_ortho_5x15(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )
};
*/
