/*
Copyright 2018 Jacob Jerrell <jacob.jerrell@gmail.com>
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
#include "bocaj.h"
#include "version.h"
#include "action_layer.h"
#include "secrets.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_HWRKMN] = LAYOUT_ergodox_pretty_wrapper(
     _____________________ERGODOX_TOP_LEFT__________________, _____________________ERGODOX_TOP_RIGHT_________________,
     KC_DEL,______________HWORKMAN_L1______________,KC_LPRN,  KC_RPRN,______________HWORKMAN_R1______________,KC_BSLS,
TT(_NUMPAD),______________HWORKMAN_L2______________,                  ______________HWORKMAN_R2______________,LT(_TOOLS, KC_QUOTE),
    KC_LSFT,______________HWORKMAN_L3______________,HYP_LBK,  MEH_RBK,______________HWORKMAN_R3______________,KC_RSFT,
    _____________________ERGODOX_BOTTOM_LEFT_______________,  _____________________ERGODOX_BOTTOM_RIGHT______________,
                                         _____________ERGODOX_THUMBS____________
  ),
  [_SWRKMN] = LAYOUT_ergodox_pretty_wrapper(
     _____________________ERGODOX_TOP_LEFT__________________, _____________________ERGODOX_TOP_RIGHT_________________,
     KC_DEL,______________SWORKMAN_L1______________,KC_LPRN,  KC_RPRN,______________SWORKMAN_R1______________,KC_BSLS,
TT(_NUMPAD),______________SWORKMAN_L2______________,                  ______________SWORKMAN_R2______________,LT(_TOOLS, KC_QUOTE),
    KC_LSFT,______________SWORKMAN_L3______________,HYP_LBK,  MEH_RBK,______________SWORKMAN_R3______________,KC_RSFT,
    _____________________ERGODOX_BOTTOM_LEFT_______________,  _____________________ERGODOX_BOTTOM_RIGHT______________,
                                         _____________ERGODOX_THUMBS____________
  ),
  [_NUMPAD] = LAYOUT_ergodox_pretty_wrapper(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,  XXXXXXX,XXXXXXX,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX, KC_UP ,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,KC_KP_7,KC_KP_8,KC_KP_9,KC_PPLS,XXXXXXX,
    _______,XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,                  XXXXXXX,KC_KP_4,KC_KP_5,KC_KP_6,KC_PEQL,XXXXXXX,
    KC_LSFT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,KC_KP_1,KC_KP_2,KC_KP_3,KC_PENT,XXXXXXX,
    XXXXXXX,_______,XXXXXXX,KC_LALT,KC_LGUI,                                  KC_KP_0,KC_PDOT,KC_COMM,KC_PENT,XXXXXXX,
                                         _____________ERGODOX_THUMBS____________
  ),
  [_MOUSE] = LAYOUT_ergodox_pretty_wrapper(
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,KC_MS_U,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,KC_WH_L,KC_WH_U,KC_WH_R,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,XXXXXXX,                  XXXXXXX,KC_ACL0,KC_ACL1,KC_ACL2,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,KC_WH_D,XXXXXXX,XXXXXXX,XXXXXXX,
    _______,XXXXXXX,XXXXXXX,XXXXXXX,KC_BTN1,                                  KC_BTN2,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                                         _____________ERGODOX_THUMBS____________
  ),
  [_TOOLS] = LAYOUT_ergodox_pretty_wrapper(
           XXXXXXX,KC_SEC1,KC_SEC2,KC_SEC3,KC_SEC4,KC_SEC5,KC_EPRM,  KC_EPRM,KC_SEC6,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
           XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,HYPR(KC_LEFT),HYPR(KC_RGHT),HYPR(KC_F),XXXXXXX,XXXXXXX,  XXXXXXX,MEH(KC_UP),MEH(KC_DOWN),MEH(KC_LEFT),MEH(KC_RGHT),_______,
           XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
           XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                  XXXXXXX,XXXXXXX,KC_HWRK,KC_SWRK,_______,
                                         _____________ERGODOX_THUMBS____________
  )
};

const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{0,13}, {1,13}, {2,13}, {3,13}, {4,13}, {5,13}},
    {{0,12}, {1,12}, {2,12}, {3,12}, {4,12}, {5,12}},
    {{0,11}, {1,11}, {2,11}, {3,11}, {4,11}, {5,11}},
    {{0,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}},
    {{0,9}, {1,9}, {2,9}, {3,9}, {4,9}, {5,9}},
    {{0,8}, {1,8}, {2,8}, {3,8}, {4,8}, {5,8}},
    {{0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}},
    /* Right hand, matrix positions */
    {{0,6}, {1,6}, {2,6}, {3,6}, {4,6}, {5,6}},
    {{0,5}, {1,5}, {2,5}, {3,5}, {4,5}, {5,5}},
    {{0,4}, {1,4}, {2,4}, {3,4}, {4,4}, {5,4}},
    {{0,3}, {1,3}, {2,3}, {3,3}, {4,3}, {5,3}},
    {{0,2}, {1,2}, {2,2}, {3,2}, {4,2}, {5,2}},
    {{0,1}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}},
    {{0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}},
};

void matrix_init_keymap(void) { // Runs boot tasks for keyboard
};

// Defines actions for my custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // KC_COPY and KC_PASTE have problems with different hardware/software mappings
    // e.g. If the mappings conflict, KC_COPY will send Cmd+M which minimizes the 
    // window and is very annoying. JJ_COPY and JJ_PASTE fix this by sending the
    // raw character rather than the KC_* code
    case JJ_COPY:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
      }
      return false;
      break;
    case JJ_PASTE:
      if (!record->event.pressed) {
        SEND_STRING(SS_LGUI("v"));
      }
      return false;
      break;
    case JJ_ARRW:
      if (!record->event.pressed) {
        SEND_STRING(" -> ");
      }
      return false;
      break;
    case KC_SWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_SWRKMN);
        layer_move(_SWRKMN);
        ergodox_blink_all_leds();
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case KC_HWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_HWRKMN);
        layer_move(_HWRKMN);
        ergodox_blink_all_leds();
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case KC_EPRM:
      if (!record->event.pressed) {
        ergodox_blink_all_leds();
        eeconfig_init();
      }
      return false;
      break;
    case KC_VRSN:
      if (!record->event.pressed) {
        SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
      }
      return false;
      break;
    case KC_SECRET_1 ... KC_SECRET_6: // Secrets!  Externally defined strings, not stored in repo
      if (!record->event.pressed) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        send_string_P(secret[keycode - KC_SECRET_1]);
      }
      return false;
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case _NUMPAD:
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10);
      break;
    case _MOUSE:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      break;
    case _TOOLS:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10);
    default:
      // none
      break;
  }
};
