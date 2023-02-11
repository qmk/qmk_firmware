/* Copyright 2021 Aaron Ireland
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

// KBD75 layer indices
enum custom_layers {
    _QWERTY,
    _COLEMAK,
    _DVORAK,
    _FL,
};

enum kbd75_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    DVORAK
};

// Mac OS Custom Macros
#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen

// Aaron's shell macros
#define KC_CTLC LCTL(KC_C)
#define KC_SNU  LCTL(KC_B)              // Used by vim
#define KC_SND  LCTL(KC_D)              // Used by vim

/*   ***************** Aaron's KBD75 v2 Layout ********************
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
 * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │  2U   │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │1.5U │   │   │   │   │   │   │   │   │   │   │   │   │1.5U │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │1.75U │   │   │   │   │   │   │   │   │   │   │   │2.25U   │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │2.25U   │   │   │   │   │   │   │   │   │   │   │1.75U │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │1.25│1.25│1.25│6.25U                   │1U │1U │1U │1U │1U │1U │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 *   ************************************************************/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /*   ******************** 0: QWERTY Base Layer ********************
   *  PSN: Print Screen
   *  PUP: Page Up
   *  PDN: Page Down
   *  BRK: CTRL + C
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │ESC│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│PSN│BRK│DEL│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
   * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │BKSPACE│HOM│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │  `  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PUP│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │ TAB  │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ ENTER  │PDN│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │ SHIFT  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │SHIFT │UP │END│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │ OS │ ALT│CTRL│          SPACE         │OS │CTL│FN │LFT│DWN│RT │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   *   ************************************************************/

  [_QWERTY] = LAYOUT_ansi_1u(
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPW, KC_CTLC, KC_DEL ,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,          KC_HOME,
    KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
    KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,          KC_PGDN,
    KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , KC_END ,
    KC_LGUI, KC_LALT, KC_LCTL,                   KC_SPC ,                                     KC_RGUI, KC_LCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /*   ******************** 1: COLEMAK Base Layer ********************
   *  PSN: Print Screen
   *  PUP: Page Up
   *  PDN: Page Down
   *  BRK: CTRL + C
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │ESC│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│PSN│BRK│DEL│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
   * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │BKSPACE│HOM│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │  `  │ Q │ W │ F │ P │ G │ J │ L │ U │ Y │ ; │ [ │ ] │  \  │PUP│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │ TAB  │ A │ R │ S │ T │ D │ H │ N │ E │ I │ O │ ' │ ENTER  │PDN│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │ SHIFT  │ Z │ X │ C │ V │ B │ K │ M │ , │ . │ / │SHIFT │UP │END│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │ OS │ ALT│CTRL│          SPACE         │OS │CTL│FN │LFT│DWN│RT │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   *   ************************************************************/

  [_COLEMAK] = LAYOUT_ansi_1u(
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPW, KC_CTLC, KC_DEL ,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,          KC_HOME,
    KC_GRV , KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
    KC_TAB , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_QUOT,          KC_ENT ,          KC_PGDN,
    KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , KC_END ,
    KC_LGUI, KC_LALT, KC_LCTL,                   KC_SPC ,                                     KC_RGUI, KC_LCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /*   ******************** 2: DVORAK Base Layer ********************
   *  PSN: Print Screen
   *  PUP: Page Up
   *  PDN: Page Down
   *  BRK: CTRL + C
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │ESC│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│PSN│BRK│DEL│
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
   * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ [ │ ] │BKSPACE│HOM│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │  `  │ ' │ , │ . │ P │ Y │ F │ G │ C │ R │ L │ / │ = │  \  │PUP│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │ TAB  │ A │ O │ E │ U │ I │ D │ H │ T │ N │ S │ - │ ENTER  │PDN│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │ SHIFT  │ ; │ Q │ J │ K │ X │ B │ M │ W │ V │ Z │SHIFT │UP │END│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │ OS │ ALT│CTRL│          SPACE         │OS │CTL│FN │LFT│DWN│RT │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   *   ************************************************************/

  [_DVORAK] = LAYOUT_ansi_1u(
    KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPW, KC_CTLC, KC_DEL ,
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_LBRC, KC_RBRC, KC_BSPC,          KC_HOME,
    KC_GRV , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_SLSH, KC_EQL , KC_BSLS,          KC_PGUP,
    KC_TAB , KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_MINS,          KC_ENT ,          KC_PGDN,
    KC_LSFT,          KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_RSFT,          KC_UP  , KC_END ,
    KC_LGUI, KC_LALT, KC_LCTL,                   KC_SPC ,                                     KC_RGUI, KC_LCTL, MO(_FL), KC_LEFT, KC_DOWN, KC_RGHT
  ),

  /*   ******************** 3: FN Momentary Layer ********************
   *  F13   - Launchpad
   *  SNU   - CTRL + B = Neovim Screen Up
   *  SND   - CTRL + D = Neovim Screen Down
   *  TOG   - Toggle RGB Underglow
   *  MOD   - RGB Underglow Mode
   *  NXT   - FF/Skip
   *  PLY   - Play/Stop
   *  VL    - Volume Down/Up
   *  SN    - Screen Brightness Up/Down
   *  QRT   - QWERTY Layout
   *  CLK   - COLEMAK Layout
   *  DVK   - DVORAK Layout
   *  QK_BOOT - Put PCB into Bootstrap mode
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │PSN│   │   │
   * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
   * │   │TOG│MOD│HU+│HU-│SA+│SA-│VA+│VA-│   │   │   │   │ QK_BOOT │F13│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │ TAB │QRT│   │   │   │   │   │   │   │   │   │   │   │     │SNU│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │ CAPS │   │   │DVK│   │   │   │   │   │   │   │   │        │SND│
   * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │        │   │   │CLK│DEC│TOG│INC│STP│   │   │   │      │SN+│VL0│
   * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │ OS │ ALT│CTRL│          SPACE         │NXT│PLY│XXX│VL-│SN-│VL+│
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   *   ************************************************************/

  [_FL] = LAYOUT_ansi_1u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CAPP, _______, _______,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, QK_BOOT,          KC_F13 ,
    KC_TAB , QWERTY , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_SNU ,
    KC_CAPS, _______, _______, DVORAK , _______, _______, _______, _______, _______, _______, _______, _______,          _______,          KC_SND ,
    _______,          _______, _______, COLEMAK, BL_DOWN, BL_TOGG, BL_UP  , BL_STEP, _______, _______, _______, _______,          KC_PAUS, KC_MUTE,
    KC_LGUI, KC_LALT, KC_LCTL,                   KC_SPC ,                                     KC_MNXT, KC_MPLY, _______, KC_VOLD, KC_SCRL, KC_VOLU
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
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
      break;
  }
  return true;
}
