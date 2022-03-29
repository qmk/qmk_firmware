/* Copyright 2019 niltea
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
#ifdef OLED_ENABLE
  #include <string.h>
  #include "lib/oled_helper.h"
#endif

enum custom_keycode {
  Mac_CS = SAFE_RANGE,
  Mac_PS,
  Win_CS,
  Win_PS,
  IOS_CS,
};
enum layerID {
  MAC_CS_1 = 0,
  MAC_CS_2,
  MAC_PS_1,
  MAC_PS_2,
  WIN_CS_1,
  WIN_CS_2,
  WIN_PS_1,
  WIN_PS_2,
  IOS_CS_1,
  IOS_CS_2,
  SETTING,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Mac
    // Clip Studio
    [MAC_CS_1] = LAYOUT(
      KC_TAB,       LGUI(KC_A), KC_E,         KC_P,          LGUI(KC_0),
      MO(MAC_CS_2), KC_M,       KC_BSPC,      KC_B,          KC_HYPR,
                    KC_LSFT,    KC_LGUI,      LGUI(KC_Z),    KC_SPC
    ),
    [MAC_CS_2] = LAYOUT(
      MO(SETTING),  KC_ESC,     KC_G,         KC_R,          LGUI(KC_GRV),
      _______,      LGUI(KC_D), KC_K,         KC_F,          LGUI(KC_S),
                    KC_LALT,    KC_I,         SGUI(KC_Z),    KC_H
    ),
    // Photoshop
    [MAC_PS_1] = LAYOUT(
      KC_TAB,       LGUI(KC_A), KC_E,         KC_B,          LGUI(KC_1),
      MO(MAC_PS_2), KC_L,       LGUI(KC_DEL), LGUI(KC_QUOT), KC_MEH,
                    KC_LSFT,    KC_LGUI,      LGUI(KC_Z),    KC_SPC
    ),
    [MAC_PS_2] = LAYOUT(
      MO(SETTING),  KC_ESC,     KC_G,         KC_R,          KC_ESC,
      _______,      LGUI(KC_D), KC_V,         LGUI(KC_T),    LGUI(KC_S),
                    KC_LALT,    KC_I,         SGUI(KC_Z),    KC_H
    ),

    // Windows
    // Clip Studio
    [WIN_CS_1] = LAYOUT(
      KC_TAB,       LCTL(KC_A), KC_E,         KC_P,          LCTL(KC_0),
      MO(WIN_CS_2), KC_M,       KC_BSPC,      KC_B,          KC_HYPR,
                    KC_LSFT,    KC_LCTRL,     LCTL(KC_Z),    KC_SPC
    ),
    [WIN_CS_2] = LAYOUT(
      MO(SETTING),  KC_ESC,     KC_G,         KC_R,          LCTL(KC_GRV),
      _______,      LCTL(KC_D), KC_K,         KC_F,          LCTL(KC_S),
                    KC_LALT,    KC_I,         C(S(KC_Z)),    KC_H
    ),
    // Photoshop
    [WIN_PS_1] = LAYOUT(
      KC_TAB,       LCTL(KC_A), KC_E,         KC_B,          LCTL(KC_1),
      MO(WIN_PS_2), KC_L,       LCTL(KC_DEL), LCTL(KC_QUOT), KC_MEH,
                    KC_LSFT,    KC_LCTRL,     LCTL(KC_Z),    KC_SPC
    ),
    [WIN_PS_2] = LAYOUT(
      MO(SETTING),  KC_ESC,     KC_G,         KC_R,          KC_ESC,
      _______,      LCTL(KC_D), KC_V,         LCTL(KC_T),    LCTL(KC_S),
                    KC_LALT,    KC_I,         C(S(KC_Z)),    KC_H
    ),
    // iOS
    // Clip Studio
    [IOS_CS_1] = LAYOUT(
      KC_TAB,       LGUI(KC_A), KC_E,         KC_P,          LGUI(KC_0),
      MO(IOS_CS_2), KC_M,       KC_BSPC,      KC_B,          LGUI(KC_LALT),
                    KC_LSFT,    KC_LGUI,      LGUI(KC_Z),    KC_SPC
    ),
    [IOS_CS_2] = LAYOUT(
      MO(SETTING),  KC_ESC,     KC_G,         KC_R,          LGUI(KC_EQL),
      _______,      LGUI(KC_D), KC_K,         KC_F,          LGUI(KC_S),
                    KC_LALT,    KC_I,         SGUI(KC_Z),    KC_H
    ),
    [SETTING] = LAYOUT(
      _______, IOS_CS, Win_CS, Mac_CS, KC_NO,
      _______, KC_NO,  Win_PS, Mac_PS, KC_NO,
               KC_NO,  KC_NO,  KC_NO,  KC_NO
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t currentDefault = get_highest_layer(default_layer_state);
  uint8_t currentLayer = get_highest_layer(layer_state);
  if (index == 0) { /* the upper encoder */
    switch (currentDefault) {
      case MAC_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // Zoom
          tap_code16(!clockwise ? G(KC_MINS) : G(KC_EQL));
        } else {
          // Fn Layer
          // rotate canvas
          tap_code(!clockwise ? KC_MINS : KC_QUOT);
        }
        break;
      case MAC_PS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // Zoom
          tap_code16(!clockwise ? G(KC_MINS) : G(KC_EQL));
        } else {
          // Fn Layer
          // undo / redo
          tap_code16(!clockwise ? G(KC_Z) : S(G(KC_Z)));
        }
        break;
      case WIN_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // Zoom
          tap_code16(!clockwise ? C(KC_MINS) : C(KC_EQL));
        } else {
          // Fn Layer
          // rotate canvas
          tap_code(!clockwise ? KC_MINS : KC_QUOT);
        }
        break;
      case WIN_PS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // Zoom
          tap_code16(!clockwise ? C(KC_MINS) : C(KC_SCLN));
        } else {
          // Fn Layer
          // undo / redo
          tap_code16(!clockwise ? C(KC_Z) : C(S(KC_Z)));
        }
        break;
      case IOS_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // Zoom
          tap_code16(!clockwise ? G(KC_MINS) : G(KC_SCLN));
        } else {
          // Fn Layer
          // rotate canvas
          tap_code(!clockwise ? KC_MINS : KC_EQL);
        }
        break;
      default:
        break;
    }
  } else if (index == 1) { /* the lower encoder */
    switch (currentDefault) {
      case MAC_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // size of brush
          tap_code(!clockwise ? KC_LBRC : KC_RBRC);
        } else {
          // Fn Layer
          // opacity of brush
          tap_code16(!clockwise ? G(KC_LBRC) : G(KC_RBRC));
        }
        break;
      case MAC_PS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // size of brush
          tap_code(!clockwise ? KC_LBRC : KC_RBRC);
        } else {
          // Fn Layer
          // opacity of brush
          tap_code16(!clockwise ? KC_LCBR : KC_RCBR);
        }
        break;
      case WIN_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // rotate canvas
          tap_code(!clockwise ? KC_LBRC : KC_RBRC);
        } else {
          // Fn Layer
          // opacity of brush
          tap_code16(!clockwise ? C(KC_LBRC) : C(KC_RBRC));
        }
        break;
      case WIN_PS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // rotate canvas
          tap_code(!clockwise ? KC_LBRC : KC_RBRC);
        } else {
          // Fn Layer
          // opacity of brush
          tap_code16(!clockwise ? KC_LCBR : KC_RCBR);
        }
        break;
      case IOS_CS_1:
        if (currentLayer % 2 == 0) {
          // default layer
          // size of brush
          tap_code(!clockwise ? KC_RBRC : KC_BSLS);
        } else {
          // Fn Layer
          // opacity of brush
          tap_code16(!clockwise ? G(KC_RBRC) : G(KC_BSLS));
        }
        break;
      default:
        break;
    }
  }
    return true;
}

// custom keycode
// switch default layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case Mac_CS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(MAC_CS_1);
      }
      return false;
      break;
    case Mac_PS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(MAC_PS_1);
      }
      return false;
      break;
    case Win_CS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(WIN_CS_1);
      }
      return false;
      break;
    case Win_PS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(WIN_PS_1);
      }
      return false;
      break;
    case IOS_CS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(IOS_CS_1);
      }
      return false;
      break;
  }
  return true;
}

// OLED Display
#ifdef OLED_ENABLE
bool oled_task_user(void) {
  // get layer Number
  uint8_t currentDefault = get_highest_layer(default_layer_state);
  uint8_t currentLayer = get_highest_layer(layer_state);
  // write OS mode / 1st line of the logo
  switch (currentDefault) {
    case MAC_CS_1:
    case MAC_PS_1:
      render_row(0, "Mac ");
      break;
    case WIN_CS_1:
    case WIN_PS_1:
      render_row(0, "Win ");
      break;
    case IOS_CS_1:
      render_row(0, "iOS ");
      break;
    default:
      render_row(0, "    ");
  }

  // write Application mode / 2nd line of the logo
  switch (currentDefault) {
    case MAC_CS_1:
    case WIN_CS_1:
    case IOS_CS_1:
      render_row(1, "A:CS");
      break;
    case MAC_PS_1:
    case WIN_PS_1:
      render_row(1, "A:Ps");
      break;
    default:
      render_row(1, "    ");
  }

  if (currentLayer == SETTING) {
    // 3rd & 4th line of the logo
    render_row(2, "****");
    render_row(3, "LSEL");
  } else {
    // Layer Status / 3rd line of the logo
    if (currentLayer % 2 == 0) {
      // default layer
      render_row(2, "L:DF");
    } else {
      // Fn Layer
      render_row(2, "L:Fn");
    }
    // pressed key / 4th line of the logo
    render_row(3, "    ");
  }
    return false;
}
#endif // #ifdef OLED_ENABLE
