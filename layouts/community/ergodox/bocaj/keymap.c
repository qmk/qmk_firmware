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
  /* Hardware Workman - http://www.keyboard-layout-editor.com/#/gists/7a07cb982ec3597ba3e3d947554225f1
            .---------------------------------------------.                                              .---------------------------------------------.
            |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                                              !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |  DEL  |  Q  |  D  |  R  |  W  |  B  |   (   |                                              !   )   |  J  |  F  |  U  |  P  |  ;  |   \   |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |  NUMS |  A  |  S  |  H  |  T  |  G  |-------!                                              !-------!  Y  |  N  |  E  |  O  |  I  |   '   |
            !-------+-----+-----+-----x-----x-----!  HYP  !                                              !  MEH  !-----x-----x-----+-----+-----+-------!
            | SHIFT |  Z  |  X  |  M  |  C  |  V  |   [   |                                              !   ]   |  K  |  L  |  ,  |  .  |  /  | SHIFT |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             | GAME | NUM | LWR |  UP | LFT | .---------------.                                      .---------------. ! RGT | DWN |     |     | ADJ  |
             '------------------------------' |   APP | HOME  |                                      !  PGUP |  ESC  | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |  END  |                                      !  PGDN |       ! ENTER !
                                      ! SPACE ! BSPCE !-------!                                      !-------!  TAB  !   /   !
                                      |       |       | COPY  |                                      ! PASTE |       | LOWER |
                                      '-----------------------'                                      '-----------------------'
*/
  [_HWRKMN] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC, _______________________NUMBER_LEFT_______________________, JJ_ARRW,   KC_MINUS,_______________________NUMBER_RIGHT______________________, KC_EQUAL,
    KC_DEL, _______________________HWORKMAN_L1_______________________, KC_LPRN,   KC_RPRN, _______________________HWORKMAN_R1_______________________, KC_BSLS,
    KC_NUMS,_______________________HWORKMAN_L2_______________________,                     _______________________HWORKMAN_R2_______________________, KC_QUOTE,
    KC_LSFT,_______________________HWORKMAN_L3_______________________, HYP_LBK,   MEH_RBK, _______________________HWORKMAN_R3_______________________, KC_RSFT,
      ___________________ERGODOX_BOTTOM_LEFT___________________,                                  ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                   ______________________ERGODOX_THUMBS_____________________
  ),
/* Software Workman / QWERTY - http://www.keyboard-layout-editor.com/#/gists/b6c016a22a9d31381a276a603a42fe5f
            .---------------------------------------------.                                              .---------------------------------------------.
            |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                                              !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |  DEL  |  Q  |  W  |  E  |  R  |  T  |   (   |                                              !   )   |  Y  |  U  |  I  |  O  |  P  |   \   |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |  NUMS |  A  |  S  |  D  |  F  |  G  |-------!                                              !-------!  H  |  J  |  K  |  L  |  ;  |   '   |
            !-------+-----+-----+-----x-----x-----!  HYP  !                                              !  MEH  !-----x-----x-----+-----+-----+-------!
            | SHIFT |  Z  |  X  |  C  |  V  |  B  |   [   |                                              !   ]   |  N  |  M  |  ,  |  .  |  /  | SHIFT |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             | GAME | NUM | LWR |  UP | LFT | .---------------.                                      .---------------. ! RGT | DWN |     |     | ADJ  |
             '------------------------------' |   APP | HOME  |                                      !  PGUP |  ESC  | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |  END  |                                      !  PGDN |       ! ENTER !
                                      ! SPACE ! BSPCE !-------!                                      !-------!  TAB  !   /   !
                                      |       |       | COPY  |                                      ! PASTE |       | LOWER |
                                      '-----------------------'                                      '-----------------------'
*/
  [_SWRKMN] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC, _______________________NUMBER_LEFT_______________________, JJ_ARRW,   KC_MINUS,_______________________NUMBER_RIGHT______________________, KC_EQUAL,
    KC_DEL, _______________________SWORKMAN_L1_______________________, KC_LPRN,   KC_RPRN, _______________________SWORKMAN_R1_______________________, KC_BSLS,
    KC_NUMS,_______________________SWORKMAN_L2_______________________,                     _______________________SWORKMAN_R2_______________________, KC_QUOTE,
    KC_LSFT,_______________________SWORKMAN_L3_______________________, HYP_LBK,   MEH_RBK, _______________________SWORKMAN_R3_______________________, KC_RSFT,
      ___________________ERGODOX_BOTTOM_LEFT___________________,                                  ___________________ERGODOX_BOTTOM_RIGHT__________________,
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
            |       | 🔇  |  🔉  | 🔊  | LCK |     |-------!                                              !-------!     |     |     |     |     | SWRKM |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     |     | HWRKM |
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
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, KC_EPRM,    KC_EPRM, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    XXXXXXX,KC__MUTE,  KC__VOLDOWN,   KC__VOLUP,   MC_LOCK,   XXXXXXX,                       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, KC_SWRK,
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, KC_HWRK,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                                             XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, _______,
                                                     ______________________ERGODOX_THUMBS_____________________
  ),
  [_NUMS] = LAYOUT_ergodox_pretty_wrapper(
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,
    XXXXXXX,XXXXXXX,  XXXXXXX,   KC_UP,     XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,     KC_PAST, XXXXXXX,
    _______,XXXXXXX,  KC_LEFT,   KC_DOWN,   KC_RIGHT,   XXXXXXX,                             XXXXXXX,    KC_KP_4,    KC_KP_5,    KC_KP_6,     KC_PPLS, XXXXXXX,
    LM_SHFT,XXXXXXX,  XXXXXXX,   XXXXXXX,   JJ_COPY,   JJ_PSTE,        XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_1,    KC_KP_2,    KC_KP_3,     KC_PMNS, XXXXXXX,
    XXXXXXX,_______,XXXXXXX,XXXXXXX,XXXXXXX,                                                             KC_KP_0,    KC_PDOT,    KC_COMM,     KC_PEQL, XXXXXXX,
                                                              _______, _______,    _______,_______,
                                                                       _______,    _______,
                                                       KC_LALT,KC_LGUI,_______,    _______,_______,_______
  ),
  [_NMOD] = LAYOUT_ergodox_pretty_wrapper(
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,
    XXXXXXX,XXXXXXX,  XXXXXXX,   _______,   XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,  XXXXXXX,    _______,    _______,    _______,     _______, XXXXXXX,
    XXXXXXX,XXXXXXX,  _______,   _______,   _______,    XXXXXXX,                             XXXXXXX,    _______,    _______,    _______,     _______, XXXXXXX,
    LM_SHFT,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    _______,    _______,    _______,     _______, XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                                                             _______,    _______,    _______,     _______, XXXXXXX,
                                                              XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX,
                                                                       XXXXXXX,    XXXXXXX,
                                                       KC_LALT,KC_LGUI,XXXXXXX,    XXXXXXX,XXXXXXX,XXXXXXX
  ),
// Diablo - http://www.keyboard-layout-editor.com/#/gists/28476e4237e77d4835ac8a9d7e5f9b2c
  [_DIABLO] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC , XXXXXXX  , XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_TAB , KC_Q     ,ALT_T(KC_S), KC_I     , KC_F     , KC_J     ,KC_MINS,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_LOCK, KC_1     , KC_2      , KC_3     , KC_4     ,KC_DCLR   ,                      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_LSFT, KC_D3_1  , KC_D3_2   , KC_D3_3  , KC_D3_4  , KC_T     ,KC_MINS,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    _______, XXXXXXX  , XXXXXXX   , XXXXXXX  , KC_M     ,                                             XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
                                                              XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX,
                                                                       XXXXXXX,    XXXXXXX,
                                                      KC_BTN1,KC_BTN2,KC_ENTER,    XXXXXXX,XXXXXXX,XXXXXXX
  )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  uint8_t default_layer = 0;
  default_layer = eeconfig_read_default_layer();
  switch (keycode) {
    case KC_SWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_SWRKMN);
        layer_move(default_layer);
        ergodox_blink_all_leds();
        ergodox_blink_all_leds();
      }
      return false;
      break;
    case KC_HWRK:
      if (!record->event.pressed) {
        set_single_persistent_default_layer(_HWRKMN);
        layer_move(default_layer);
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
    case MC_LOCK:
      if (!record->event.pressed) {
        layer_move(default_layer);
        SEND_STRING(SS_LCTRL(SS_LGUI("q")));
      }
      return false;
      break;
  }
  return true;
}

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
    case _NMOD:
      ergodox_right_led_1_on();
      ergodox_right_led_1_set(10);
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
