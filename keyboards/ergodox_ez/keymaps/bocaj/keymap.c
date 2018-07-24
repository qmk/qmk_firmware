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

#ifdef UNICODEMAP_ENABLE
#include "bocaj_unicode.h"
#endif // UNICODEMAP_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Software Workman / QWERTY - http://www.keyboard-layout-editor.com/#/gists/b6c016a22a9d31381a276a603a42fe5f
            .---------------------------------------------.                                              .---------------------------------------------.
            |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                                              !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |  DEL  |  Q  |  W  |  E  |  R  |  T  |   (   |                                              !   )   |  Y  |  U  |  I  |  O  |  P  |   \   |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            | ADJST |  A  |  S  |  D  |  F  |  G  |-------!                                              !-------!  H  |  J  |  K  |  L  |  ;  |   '   |
            !-------+-----+-----+-----x-----x-----!  HYP  !                                              !  MEH  !-----x-----x-----+-----+-----+-------!
            | SHIFT |  Z  |  X  |  C  |  V  |  B  |   {   |                                              !   }   |  N  |  M  |  ,  |  .  |  /  | SHIFT |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             | GAME | NUM | VRS |  UP | LFT | .---------------.                                      .---------------. ! RGT | DWN | RSE | LWR | ADJ  |
             '------------------------------' |   APP | HOME  |                                      !  PGUP |  ESC  | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      ! SPACE !       |  END  |                                      !  PGDN |       ! ENTER !
                                      !   /   ! BSPCE !-------!                                      !-------!  TAB  !   /   !
                                      | LOWER |       | COPY  |                                      ! PASTE |       | RAISE |
                                      '-----------------------'                                      '-----------------------'
*/
  [_SWRKMN] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC, ______________________NUMBER_LEFT________________________, JJ_ARRW,    KC_MINUS, ______________________NUMBER_RIGHT_______________________, KC_EQUAL,
    KC_DEL, _______________________SWORKMAN_L1_______________________, KC_LPRN,    KC_RPRN,  _______________________SWORKMAN_R1_______________________, KC_BSLS,
    KC_ADJS,_______________________SWORKMAN_L2_______________________,                       _______________________SWORKMAN_R2_______________________, KC_QUOTE,
    KC_LSFT,_______________________SWORKMAN_L3_______________________, HYP_LBK,    MEH_RBK,  _______________________SWORKMAN_R3_______________________, KC_RSFT,
    ___________________ERGODOX_BOTTOM_LEFT___________________,                                         ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                      ______________________ERGODOX_THUMBS_____________________
  ),
/* Hardware Workman - http://www.keyboard-layout-editor.com/#/gists/7a07cb982ec3597ba3e3d947554225f1
            .---------------------------------------------.                                              .---------------------------------------------.
            |  ESC  |  1  |  2  |  3  |  4  |  5  |   ->  |                                              !   -   |  6  |  7  |  8  |  9  |  0  |   =   |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |  DEL  |  Q  |  D  |  R  |  W  |  B  |   (   |                                              !   )   |  J  |  F  |  U  |  P  |  ;  |   \   |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            | ADJST |  A  |  S  |  H  |  T  |  G  |-------!                                              !-------!  Y  |  N  |  E  |  O  |  I  |   '   |
            !-------+-----+-----+-----x-----x-----!  HYP  !                                              !  MEH  !-----x-----x-----+-----+-----+-------!
            | SHIFT |  Z  |  X  |  M  |  C  |  V  |   {   |                                              !   }   |  K  |  L  |  ,  |  .  |  /  | SHIFT |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             | GAME | NUM | VRS |  UP | LFT | .---------------.                                      .---------------. ! RGT | DWN | RSE | LWR | ADJ  |
             '------------------------------' |   APP | HOME  |                                      !  PGUP |  ESC  | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      ! SPACE !       |  END  |                                      !  PGDN |       ! ENTER !
                                      !   /   ! BSPCE !-------!                                      !-------!  TAB  !   /   !
                                      | LOWER |       | COPY  |                                      ! PASTE |       | RAISE |
                                      '-----------------------'                                      '-----------------------'
*/
  [_HWRKMN] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC, ______________________NUMBER_LEFT________________________, JJ_ARRW,    KC_MINUS, ______________________NUMBER_RIGHT_______________________, KC_EQUAL,
    KC_DEL, _______________________HWORKMAN_L1_______________________, KC_LPRN,    KC_RPRN,  _______________________HWORKMAN_R1_______________________, KC_BSLS,
    KC_ADJS,_______________________HWORKMAN_L2_______________________,                       _______________________HWORKMAN_R2_______________________, KC_QUOTE,
    KC_LSFT,_______________________HWORKMAN_L3_______________________, HYP_LBK,    MEH_RBK,  _______________________HWORKMAN_R3_______________________, KC_RSFT,
    ___________________ERGODOX_BOTTOM_LEFT___________________,                                         ___________________ERGODOX_BOTTOM_RIGHT__________________,
                                                      ______________________ERGODOX_THUMBS_____________________
  ),
/* Lower - http://www.keyboard-layout-editor.com/#/gists/f1d745a88d1c48ab55e095efd9e7a43a
            .---------------------------------------------.                                              .---------------------------------------------.
            |       | F1  | F2  | F3  | F4  | F5  |       |                                              !       |  F6 | F7  | F8  | F9  | F10 |       |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |   `   |  1  |  2  |  3  |  4  |  5  |       |                                              !       |   6 |  7  |  8  |  9  |  0  |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |-------!                                              !-------!     |     |     |     |     |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     |     |       |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             |      |     |     |     |     | .---------------.                                      .---------------. !     |     |     |     |      |
             '------------------------------' |       |       |                                      !       |       | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |       |                                      !       |       !       !
                                      !       !       !-------!                                      !-------!       !       !
                                      |       |       |       |                                      !       |       |       |
                                      '-----------------------'                                      '-----------------------'
*/
  [_LOWER] = LAYOUT_ergodox_pretty_wrapper(
    _______,_______________________FUNC_LEFT_________________________, _______,    _______, _______________________FUNC_RIGHT________________________, _______,
    KC_GRV ,______________________NUMBER_LEFT________________________, _______,    _______, ______________________NUMBER_RIGHT_______________________, _______,
    _______,_________________________________________________________,                      _________________________________________________________, _______,
    _______,_________________________________________________________, _______,    _______, _________________________________________________________, _______,
    _________________________________________________________,                                       _________________________________________________________,
                                                      ______________________ERGODOX_THUMBS_____________________
  ),
/* Raise - http://www.keyboard-layout-editor.com/#/gists/e0f591ec2ce9f24675a02d15c7048b25
            .---------------------------------------------.                                              .---------------------------------------------.
            |       | F1  | F2  | F3  | F4  | F5  |       |                                              !   _   |  F6 | F7  | F8  | F9  | F10 |       |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |   ~   |  !  |  @  |  #  |  $  |  %  |       |                                              !       |  ^  |  &  |  *  |  (  |  )  |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |-------!                                              !-------!     |     |     |     |     |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |     |     |     |     |       |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             |      |     |     |     |     | .---------------.                                      .---------------. !     |     |     |     |      |
             '------------------------------' |       |       |                                      !       |       | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |       |                                      !       |       !       !
                                      !       !       !-------!                                      !-------!       !       !
                                      |       |       |       |                                      !       |       |       |
                                      '-----------------------'                                      '-----------------------'
*/
  [_RAISE] = LAYOUT_ergodox_pretty_wrapper(
    _______,_______________________FUNC_LEFT_________________________, _______,    KC_UNDS, _______________________FUNC_RIGHT________________________, _______,
    KC_TILD,______________________SPECIAL_LEFT_______________________, _______,    _______, ______________________SPECIAL_RIGHT______________________, _______,
    _______,_________________________________________________________,                      _________________________________________________________, _______,
    _______,_________________________________________________________, _______,    _______, _________________________________________________________, _______,
    _________________________________________________________,                                       _________________________________________________________,
                                                     ______________________ERGODOX_THUMBS_____________________
  ),
  /* Adjust - http://www.keyboard-layout-editor.com/#/gists/dedeae17b35a5d5f745a42aaea78f007
            .---------------------------------------------.                                              .---------------------------------------------.
            |       |     |     |     |     |     | EPRM  |                                              !  EPRM |     |     |     |     |     |       |
            !-------+-----+-----+-----+-----+-------------!                                              !-------+-----+-----+-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |  7  |  8  |  9  |  *  |       |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       | 🔇  |  🔉  | 🔊  | LCK |     |-------!                                              !-------!     |  4  |  5  |  6  |  +  | SWRKM |
            !-------+-----+-----+-----x-----x-----!       !                                              !       !-----x-----x-----+-----+-----+-------!
            |       |     |     |     |     |     |       |                                              !       |     |  1  |  2  |  3  |  -  | HWRKM |
            '-------+-----+-----+-----+-----+-------------'                                              '-------------+-----+-----+-----+-----+-------'
             |      |     |     |     |     | .---------------.                                      .---------------. !  0  |  .  |  ,  |  =  |      |
             '------------------------------' |       |       |                                      !       |       | '------------------------------'
                                      .-------+-------+-------!                                      !-------+-------+-------.
                                      !       !       |       |                                      !       |       !       !
                                      !       !       !-------!                                      !-------!       !       !
                                      |       |       |       |                                      !       |       |       |
                                      '-----------------------'                                      '-----------------------'
*/
  [_ADJUST] = LAYOUT_ergodox_pretty_wrapper(
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, KC_EPRM,    KC_EPRM, XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,     KC_PAST, XXXXXXX,
    _______,KC__MUTE,  KC__VOLDOWN,   KC__VOLUP,   MC_LOCK,   XXXXXXX,                       XXXXXXX,    KC_KP_4,    KC_KP_5,    KC_KP_6,     KC_PPLS, KC_SWRK,
    XXXXXXX,XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX, XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_1,    KC_KP_2,    KC_KP_3,     KC_PMNS, KC_HWRK,
    XXXXXXX,_______,XXXXXXX,XXXXXXX,XXXXXXX,                                                              KC_KP_0,    KC_PDOT,    KC_COMM,     KC_PEQL, _______,
                                                     ______________________ERGODOX_THUMBS_____________________
  ),
// Diablo - http://www.keyboard-layout-editor.com/#/gists/28476e4237e77d4835ac8a9d7e5f9b2c
  [_DIABLO] = LAYOUT_ergodox_pretty_wrapper(
    KC_ESC , KC_V        , KC_D      ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
    KC_TAB , KC_S        , KC_I      , KC_F     , KC_T     , KC_J     ,XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_7,    KC_KP_8,    KC_KP_9,     XXXXXXX, XXXXXXX,
    KC_Q   , KC_1        , KC_2      , KC_3     , KC_4     , KC_M     ,                      XXXXXXX,    KC_KP_4,    KC_KP_5,    KC_KP_6,     XXXXXXX, XXXXXXX,
    KC_LSFT,KC_D3_1      ,KC_D3_2    ,KC_D3_3   ,KC_D3_4   ,XXXXXXX   ,XXXXXXX,    XXXXXXX,  XXXXXXX,    KC_KP_1,    KC_KP_2,    KC_KP_3,     XXXXXXX, XXXXXXX,
    _______,ALT_T(KC_Z)  ,KC_G       ,KC_Y      ,XXXXXXX   ,                                             KC_KP_0,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,
                                                              XXXXXXX, XXXXXXX,    XXXXXXX,XXXXXXX,
                                                                       XXXXXXX,    XXXXXXX,
                                               KC_BTN1,KC_BTN2,KC_DIABLO_CLEAR,    XXXXXXX,XXXXXXX,XXXXXXX
  )
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
        SEND_STRING("->");
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
    case MC_LOCK:
      if (!record->event.pressed) {
        layer_move(_HWRKMN);
        SEND_STRING(SS_LCTRL(SS_LGUI("q")));
      }
      return false;
      break;
    case KC_DIABLO_CLEAR:
#ifdef TAP_DANCE_ENABLE
      if (record->event.pressed) {
        uint8_t dtime;
        for (dtime = 0; dtime < 4; dtime++) {
          diablo_key_time[dtime] = diablo_times[0];
        }
      }
#endif // TAP_DANCE_ENABLE
      return false;
      break;
  }
  return true;
}

void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };

// Diablo III Fun stuff
//define diablo macro timer variables
uint16_t diablo_timer[4];
uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
uint8_t diablo_key_time[4];

// has the correct number of seconds elapsed (as defined by diablo_times)
bool check_dtimer(uint8_t dtimer) { return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true; };

// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
  if (state->count >= 7) {
    diablo_key_time[diablo_key] = diablo_times[0];
    reset_tap_dance(state);
  }  else {
    diablo_key_time[diablo_key] = diablo_times[state->count - 1];
  }
}

// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 0); }
void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 1); }
void diablo_tapdance3(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 2); }
void diablo_tapdance4(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 3); }

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once to disable, and more to enable timed micros
  [TD_D3_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
  [TD_D3_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
  [TD_D3_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
  [TD_D3_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),
};

// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke(uint8_t diablo_key) {
  if (biton32(layer_state) == _DIABLO) {
    switch (diablo_key) {
      case 0:
        tap(KC_1); break;
      case 1:
        tap(KC_2); break;
      case 2:
        tap(KC_3); break;
      case 3:
        tap(KC_4); break;
    }
  }
}

// Checks each of the 4 timers/keys to see if enough time has elapsed
// Runs the "send string" command if enough time has passed, and resets the timer.
void run_diablo_macro_check(void) {
  uint8_t dtime;
  for (dtime = 0; dtime < 4; dtime++) {
    if (check_dtimer(dtime) && diablo_key_time[dtime]) {
      diablo_timer[dtime] = timer_read();
      send_diablo_keystroke(dtime);
    }
  }
}

void matrix_scan_user(void) {
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
    case _RAISE:
      ergodox_right_led_2_on();
      ergodox_right_led_2_set(10);
      break;
    case _ADJUST:
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
  #ifdef TAP_DANCE_ENABLE
    run_diablo_macro_check();
  #endif
};
