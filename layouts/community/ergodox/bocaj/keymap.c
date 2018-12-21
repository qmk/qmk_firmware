/*
Copyright 2018 Jacob Jerrell jacob.jerrell@gmail.com @JacobJerrell

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
  [_OSXWRKMN] = LAYOUT_ergodox_pretty_osx_wrapper(
                 _______________________WORKMAN_L1________________________,         _______________________WORKMAN_R1________________________,
                 _______________________WORKMAN_L2________________________,         _______________________WORKMAN_R2________________________,
                 _______________________WORKMAN_L3________________________,         _______________________WORKMAN_R3________________________,
                 ___________________ERGODOX_BOTTOM_LEFT___________________,         ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                  ______________________ERGODOX_THUMBS_____________________
  ),
  [_WINWRKMN] = LAYOUT_ergodox_pretty_win_wrapper(
                 _______________________WORKMAN_L1________________________,         _______________________WORKMAN_R1________________________,
                 _______________________WORKMAN_L2________________________,         _______________________WORKMAN_R2________________________,
                 _______________________WORKMAN_L3________________________,         _______________________WORKMAN_R3________________________,
                 ___________________ERGODOX_BOTTOM_LEFT___________________,         ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                  ______________________ERGODOX_THUMBS_____________________
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
  [_OSXQWERTY] = LAYOUT_ergodox_pretty_osx_wrapper(
                 _______________________QWERTY_L1_________________________,         _______________________QWERTY_R1_________________________,
                 _______________________QWERTY_L2_________________________,         _______________________QWERTY_R2_________________________,
                 _______________________QWERTY_L3_________________________,         _______________________QWERTY_R3_________________________,
                 ___________________ERGODOX_BOTTOM_LEFT___________________,         ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                  ______________________ERGODOX_THUMBS_____________________
  ),
/* Lower - http://www.keyboard-layout-editor.com/#/gists/f1d745a88d1c48ab55e095efd9e7a43a
            .---------------------------------------------.                                              .---------------------------------------------.
            |  ESC  |     |     |     |     |     |   ->  |                                              !   -   |     |     |     |     |     |   =   |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |  DEL  |  !  |  @  |  #  |  $  |  %  |   (   |                                              !   )   |  ^  |  &  |  *  |  (  |  )  |   \   |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |   `   |  1  |  2  |  3  |  4  |  5  |-------!                                              !-------!   6 |  7  |  8  |  9  |  0  |   '   |
            !-------+-----+-----+-----x-----x-----!  HYP  !                                              !  MEH  !-----x-----x-----+-----+-----+-------!
            | SHIFT |     |     |     |     |     |   [   |                                              !   ]   |     |     |     |     |     | SHIFT |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             | GAME | NUM | LWR |  UP | LFT | .---------------.                                      .---------------. ! RGT | DWN |     |     | ADJ  |
             '------------------------------' |   APP | HOME  |                                      !  PGUP |  ESC  | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |  END  |                                      !  PGDN |       ! ENTER !
                                      ! SPACE ! BSPCE !-------!                                      !-------!  TAB  !   /   !
                                      |       |       | COPY  |                                      ! PASTE |       | LOWER |
                                      '-----------------------'                                      '-----------------------'
*/
  [_LOWER] = LAYOUT_ergodox_pretty_wrapper(
    _______,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, _______,    _______, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, _______,
    _______,_______________________SPECIAL_LEFT______________________, _______,    _______, _______________________SPECIAL_RIGHT_____________________, _______,
    KC_GRV ,_______________________NUMBER_LEFT_______________________,                      _______________________NUMBER_RIGHT______________________, _______,
    _______,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, _______,    _______, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, _______,
    _________________________________________________________,                                       _________________________________________________________,
                                                      ______________________ERGODOX_THUMBS_____________________
  ),
  /* Adjust - http://www.keyboard-layout-editor.com/#/gists/dedeae17b35a5d5f745a42aaea78f007
            .---------------------------------------------.                                              .---------------------------------------------.
            |       |     |     |     |     |     | EPRM  |                                              !  EPRM |     |     |     |     |     |       |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     |     |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       | 🔇  |  🔉  | 🔊  | LCK |     |-------!                                              !-------!     |     |     |     | WIN | QWRTY |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     | WIN | HWRKM |
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
    KC_MAKE,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX,  KC_RST,    KC_EPRM, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    XXXXXXX,KC__MUTE,  KC__VOLDOWN,   KC__VOLUP,   MC_LOCK,   XXXXXXX,                       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, KC_MQWR,
    _______,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     KC_WWRK, KC_MWRK,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                                             XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, _______,
                                                   ______________________ERGODOX_THUMBS_____________________
  ),
  [_NUMS] = LAYOUT_ergodox_pretty_osx_wrapper(
    XXXXXXX,    XXXXXXX,     KC_UP,      XXXXXXX,     XXXXXXX,         XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,     KC_PAST,
    XXXXXXX,    KC_LEFT,     KC_DOWN,    KC_RIGHT,    XXXXXXX,         XXXXXXX,    KC_KP_4,    KC_KP_5,    KC_KP_6,     KC_PPLS,
    _________________________________________________________,         XXXXXXX,    KC_KP_1,    KC_KP_2,    KC_KP_3,     KC_PMNS,
    XXXXXXX,    _______,     XXXXXXX,    XXXXXXX,     XXXXXXX,                     KC_KP_0,    KC_PDOT,    KC_COMM,     KC_PEQL, XXXXXXX,
                                     ______________________ERGODOX_THUMBS_____________________
  ),
// Diablo - http://www.keyboard-layout-editor.com/#/gists/28476e4237e77d4835ac8a9d7e5f9b2c
  [_DIABLO] = LAYOUT_ergodox_pretty_wrapper(
             KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,   KC_NO,                   KC_NO,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_NO,
             KC_TAB,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,    KC_ENTER,                KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,                                      KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,    KC_LOCK,                 KC_NO,   KC_N,    KC_M,     KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                         KC_NO,    KC_NO,   KC_NO,   KC_TRNS, KC_NO,
                                                             KC_L,    KC_J,                 KC_NO,   KC_NO,
                                                                      KC_F,                 KC_NO,
                                     SFT_T(KC_SPACE),  ALT_T(KC_Q),   KC_DCLR,              KC_PGDN, KC_DEL,  KC_ENT
  )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  // Keycodes using ErgoDox specific functions
  // MC_LOCK is here because default_layer is here
  uint8_t default_layer = 0;
  default_layer = eeconfig_read_default_layer();
  switch (keycode) {
    case KC_MWRK:
      if (!record->event.pressed) {
        layer_move(_OSXWRKMN);
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case KC_WWRK:
      if (!record->event.pressed) {
        layer_move(_WINWRKMN);
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case KC_MQWR:
      if (!record->event.pressed) {
        layer_move(_OSXQWERTY);
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case MC_LOCK:
      if (!record->event.pressed) {
        layer_move(default_layer);
        SEND_STRING(SS_LCTRL(SS_LGUI("q")));
      }
      return false;
      break;
    case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
      if (!record->event.pressed) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
        if (temp_mod & MODS_SHIFT_MASK) {
          #if defined(__ARM__)
            send_string_with_delay_P(PSTR(":dfu-util"), 10);
          #elif defined(BOOTLOADER_DFU)
            send_string_with_delay_P(PSTR(":dfu"), 10);
          #elif defined(BOOTLOADER_HALFKAY)
            send_string_with_delay_P(PSTR(":teensy"), 10);
          #elif defined(BOOTLOADER_CATERINA)
            send_string_with_delay_P(PSTR(":avrdude"), 10);
          #endif // bootloader options
        }
        #if defined(KEYBOARD_viterbi)
          send_string_with_delay_P(PSTR(":dfu"), 10);
        #endif
        if (temp_mod & MODS_CTRL_MASK) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10); }
        send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
        set_mods(temp_mod);
        layer_move(default_layer);
      }
      return false;
      break;
  }
  return true;
};

void matrix_init_keymap(void) {};

void matrix_scan_keymap(void) {
  uint8_t layer = biton32(layer_state);
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
  /*
    Lights are treated as binary here for easy identification.
    LED1 = 4; LED2 = 2; LED1 = 1
    This allows for up to 8 identified layers (default layers being no lights on)
    Which is way more than I should ever need
  */
    case _LOWER:
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10); // Default brightness is deadly in a dark room
      break;
    case _ADJUST:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      break;
    case _NUMS:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      ergodox_right_led_3_on();
      ergodox_right_led_3_set(10);
      break;
    case _DIABLO:
      ergodox_right_led_1_on();
      ergodox_right_led_1_set(10);
      break;
    default:
      // none
      break;
  }
  /* #ifdef TAP_DANCE_ENABLE
    run_diablo_macro_check();
  #endif */
};
