/*
Copyright 2018 Jacob Jerrell <jacob.jerrell@gmail.com> @JacobJerrell

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

#define LAYOUT_ergodox_pretty_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ergodox_pretty_wrapper( \
      KC_ESC,  __________________NUMBER_LEFT_______________, JJ_ARRW,                 KC_MINS,  __________________NUMBER_RIGHT______________, KC_EQUAL,  \
      KC_DEL,  K01,        K02,        K03,        K04, K05, KC_LPRN,                 KC_RPRN,  K06, K07,        K08,        K09,        K0A, KC_BSLASH, \
      KC_NUMS, K11, SFT_T(K12),        K13, ALT_T(K14), K15,                                    K16, ALT_T(K17), K18,     SFT_T(K19),    K1A, KC_QUOT,   \
      OS_LSFT, CTL_T(K21), K22,        K23,        K24, K25, HYP_LBK,                 MEH_RBK,  K26, K27,        K28,        K29, CTL_T(K2A), KC_RSFT,   \
       KC_GAME,KC_NUMS,    TT(_LOWER), KC_UP,  KC_LEFT,                                            KC_RIGHT,   KC_DOWN,    UC_DISA,KC_GAME, KC_ADJS,     \
                                                             KC_APP,KC_HOME,    KC_END,KC_ESC,           \
                                                                    UC_FLIP,    UC_TABL,                \
                                                 KC_SPACE,KC_BSPACE,KC_LEAD,    UC_SHRG,KC_TAB,KC_LWEN                          \
)

#define LAYOUT_ergodox_pretty_base_wrapper(...)       LAYOUT_ergodox_pretty_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Workman - http://www.keyboard-layout-editor.com/#/gists/7a07cb982ec3597ba3e3d947554225f1
                .---------------------------------------------.                                 .---------------------------------------------.
                |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                                 !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
                !-------+-----+-----+-----+-----+-------------!                                 !-------+-----+-----+-----+-----+-----+-------!
                |  DEL  |  Q  |  D  |  R  |  W  |  B  |   (   |                                 !   )   |  J  |  F  |  U  |  P  |  ;  |   \   |
                !-------+-----+-----+-----x-----x-----!       !                                 !       !-----x-----x-----+-----+-----+-------!
                |  NUMS |  A  |  S  |  H  |  T  |  G  |-------!                                 !-------!  Y  |  N  |  E  |  O  |  I  |   '   |
                !-------+-----+-----+-----x-----x-----!  HYP  !                                 !  MEH  !-----x-----x-----+-----+-----+-------!
                | SHIFT |  Z  |  X  |  M  |  C  |  V  |   [   |                                 !   ]   |  K  |  L  |  ,  |  .  |  /  | SHIFT |
                '-------+-----+-----+-----+-----+-------------'                                 '-------------+-----+-----+-----+-----+-------'
                 |      | NUM | LWR |  UP | LFT | .---------------.                         .---------------. ! RGT | DWN |     |GAME | ADJ  |
                 '------------------------------' |   APP | HOME  |                         !  PGUP |  ESC  | '------------------------------'
                                          .-------+-------+-------!                         !-------+-------+-------.
                                          !       !       |  END  |                         !  PGDN |       ! ENTER !
                                          ! SPACE ! BSPCE !-------!                         !-------!  TAB  !   /   !
                                          |       |       | COPY  |                         ! PASTE |       | LOWER |
                                          '-----------------------'                         '-----------------------'
*/
  [_WORKMAN] = LAYOUT_ergodox_pretty_base_wrapper(
                 _________________WORKMAN_L1_________________,         _________________WORKMAN_R1_________________,
                 _________________WORKMAN_L2_________________,         _________________WORKMAN_R2_________________,
                 _________________WORKMAN_L3_________________,         _________________WORKMAN_R3_________________
  ),
  [_WINWORKMAN] = LAYOUT_ergodox_pretty_base_wrapper(
                 _________________WORKMAN_L1_________________,         _________________WORKMAN_R1_________________,
                 ________________WWORKMAN_L2_________________,         ________________WWORKMAN_R2_________________,
                 _________________WORKMAN_L3_________________,         _________________WORKMAN_R3_________________
  ),
/* QWERTY - http://www.keyboard-layout-editor.com/#/gists/b6c016a22a9d31381a276a603a42fe5f
                 .---------------------------------------------.                               .---------------------------------------------.
                 |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                               !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
                 !-------+-----+-----+-----+-----+-------------!                               !-------+-----+-----+-----+-----+-----+-------!
                 |  DEL  |  Q  |  W  |  E  |  R  |  T  |   (   |                               !   )   |  Y  |  U  |  I  |  O  |  P  |   \   |
                 !-------+-----+-----+-----x-----x-----!       !                               !       !-----x-----x-----+-----+-----+-------!
                 |  NUMS |  A  |  S  |  D  |  F  |  G  |-------!                               !-------!  H  |  J  |  K  |  L  |  ;  |   '   |
                 !-------+-----+-----+-----x-----x-----!  HYP  !                               !  MEH  !-----x-----x-----+-----+-----+-------!
                 | SHIFT |  Z  |  X  |  C  |  V  |  B  |   [   |                               !   ]   |  N  |  M  |  ,  |  .  |  /  | SHIFT |
                 '-------+-----+-----+-----+-----+-------------'                               '-------------+-----+-----+-----+-----+-------'
                  | GAME | NUM | LWR |  UP | LFT | .---------------.                       .---------------. ! RGT | DWN |     |     | ADJ  |
                  '------------------------------' |   APP | HOME  |                       !  PGUP |  ESC  | '------------------------------'
                                           .-------+-------+-------!                       !-------+-------+-------.
                                           !       !       |  END  |                       !  PGDN |       ! ENTER !
                                           ! SPACE ! BSPCE !-------!                       !-------!  TAB  !   /   !
                                           |       |       | COPY  |                       ! PASTE |       | LOWER |
                                           '-----------------------'                       '-----------------------'
*/
  [_QWERTY] = LAYOUT_ergodox_pretty_base_wrapper(
                 _________________QWERTY_L1__________________,         _________________QWERTY_R1__________________,
                 _________________QWERTY_L2__________________,         _________________QWERTY_R2__________________,
                 _________________QWERTY_L3__________________,         _________________QWERTY_R3__________________
  ),
  [_LOWER] = LAYOUT_ergodox_pretty_wrapper(
    KC_F11 ,__________________FUNCTION_LEFT_____________, _______,    _______, __________________FUNCTION_RIGHT____________,  KC_F12,
    _______, _______, _______,  KC_UP, _______,  _______, _______,    _______, _______,   KC_7,    KC_8,    KC_9,   KC_PAST, _______,
   LM_GRAVE, _______, KC_LEFT, KC_DOWN,KC_RIGHT, _______,                      _______,   KC_4,    KC_5,    KC_6,   KC_PPLS, _______,
    OS_LSFT,____________________BLANK___________________, _______,    _______, _______,   KC_1,    KC_2,    KC_3,   KC_PMNS, _______,
      ____________________BLANK___________________,                                       KC_0,    KC_PDOT, KC_COMM,KC_PEQL, _______,
                                                _______, _______,      _______, _______,
                                                         _______,      _______,
                                       _______, _______, _______,      _______, _______, _______
  ),
/* Adjust - http://www.keyboard-layout-editor.com/#/gists/dedeae17b35a5d5f745a42aaea78f007
            .---------------------------------------------.                                              .---------------------------------------------.
            | MAKE  |     |     |     |     |     | RESET |                                              !  EPRM |     |     |     |     |     |       |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     |     |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       | 🔇  |  🔉  | 🔊  | LCK |     |-------!                                              !-------!     |     |     |     |     | QWRTY |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     | WIN | WRKMN |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             |      |     |     |     |     | .---------------.                                      .---------------. !     |     |     |     |      |
             '------------------------------' |       |       |                                      !       |       | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |       |                                      !       |       !       !
                                      !       !       !-------!                                      !-------!       !       !
                                      |       |       |       |                                      !       |       |       |
                                      '-----------------------'                                      '-----------------------'
*/
  [_ADJUST] = LAYOUT_ergodox_pretty_wrapper(
    KC_MAKE,  ____________________BLANK___________________,  KC_RST,    KC_EPRM, ____________________BLANK___________________, XXXXXXX,
    _______,  ____________________BLANK___________________, _______,    _______, ____________________BLANK___________________, XXXXXXX,
    _______,KC__MUTE,KC__VOLDOWN,KC__VOLUP,MC_LOCK,_______,                      ____________________BLANK___________________, KC_MQWR,
    _______,  ____________________BLANK___________________, _______,    _______, _______, _______, _______, _______,  KC_WWRK, KC_MWRK,
      ____________________BLANK___________________,                                     ____________________BLANK___________________,
                                                  _______, _______,      _______, _______,
                                                           _______,      _______,
                                         _______, _______, _______,      _______, _______, _______
  ),
  [_DIABLO] = LAYOUT_ergodox_pretty_wrapper(
             KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,   KC_NO,                   KC_NO,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_NO,
             KC_TAB,  KC_S,    KC_F,    KC_I,    KC_M,    KC_T,    KC_ENTER,                KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_P,                                      KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,    KC_LOCK,                 KC_NO,   KC_N,    KC_M,     KC_NO,   KC_NO,   KC_NO,   KC_NO,
             _______, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         KC_NO,    KC_NO,   KC_NO,   KC_TRNS, KC_NO,
                                                             KC_L,    KC_J,                 KC_NO,   KC_NO,
                                                                      KC_F,                 KC_NO,
                                     SFT_T(KC_SPACE),  ALT_T(KC_Q),   KC_DCLR,              KC_PGDN, KC_DEL,  KC_ENT
  )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void matrix_init_keymap(void) {};

void matrix_scan_keymap(void) {
  uint8_t modifiers = get_mods();
  uint8_t led_usb_state = host_keyboard_leds();
  uint8_t one_shot = get_oneshot_mods();
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
    case _WORKMAN:
    case _QWERTY:
    case _WINWORKMAN:
      if (modifiers & MODS_SHIFT_MASK || led_usb_state & (1<<USB_LED_CAPS_LOCK) || one_shot & MODS_SHIFT_MASK) {
        ergodox_right_led_1_on();
        ergodox_right_led_1_set( 25 );
      }
      if (modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK || modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK) {
        if ((modifiers & MODS_CTRL_MASK || one_shot & MODS_CTRL_MASK) && (modifiers & MODS_GUI_MASK || one_shot & MODS_GUI_MASK)) {
          ergodox_right_led_2_on();
          ergodox_right_led_2_set( 50 );
        } else {
          ergodox_right_led_2_on();
          ergodox_right_led_2_set( 10 );
        }
      }
      if (modifiers & MODS_ALT_MASK || one_shot & MODS_ALT_MASK) {
        ergodox_right_led_3_on();
        ergodox_right_led_3_set( 10 );
      }
      break;
    case _LOWER:
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10); // Default brightness is deadly in a dark room
      break;
    case _ADJUST:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      break;
    case _DIABLO:
      ergodox_right_led_1_on();
      ergodox_right_led_1_set(10);
      break;
    default:
      // none
      break;
  }
};
