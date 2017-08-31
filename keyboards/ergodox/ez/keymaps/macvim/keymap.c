#include "ergodox.h"
#include "ez.h"
#include "config.h"
#include "quantum_keycodes.h"
#include "action_layer.h"
#include "version.h"
#include "vim.h"

#define VERSION_STRING QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
#define _______ KC_TRNS
#define KC_ATM LGUI(LSFT(KC_P))
#define KC_ATP LGUI(LCTL(KC_P))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Normal mode
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |  TAB   |      | WORD |  END |      |      |      |           |      | YANK | UNDO |      | OPEN |  PUT |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |    ⎋   |      |      |  DEL |      |      |------|           |------|  ←   |  ↓   |  ↑   |  →   |      |    ⎋   |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * | SHIFT  |      |      |      |VISUAL| BACK |      |           |      |      |      |      |      |      | SHIFT  |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |      |      |      |      |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |      |      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |SPACE |DELETE|------|       |------|ENTER |BACKSP|
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  */
  [NORMAL_MODE] = KEYMAP(
    // Layer 2 Left Hand
    _______,_______,_______,_______,_______,_______,_______,
    KC_TAB ,_______,VIM_W,  VIM_E  ,_______,_______,_______,
    KC_ESC ,VIM_A  ,VIM_S  ,VIM_D  ,_______,_______,
    KC_LSFT,_______,VIM_X  ,_______,VIM_V  ,VIM_B  ,_______,
    _______,_______,_______,_______,_______,

                                                                KC_LEFT,KC_DOWN,
                                                                        KC_HOME,
                                                GUI_T(KC_SPC),  KC_DEL, KC_END,

    // Layer 2 Right Hand
                              _______,_______,_______,_______,_______,_______,_______,
                              _______,VIM_Y  ,VIM_U  ,VIM_I  ,VIM_O  ,VIM_P  ,_______,
                                      VIM_H  ,VIM_J  ,VIM_K  ,VIM_L  ,_______,KC_ESC ,
                              _______,_______,_______,_______,_______,_______,KC_LSFT,
                                              _______,_______,_______,_______,_______,

    KC_UP,  KC_RGHT,
    KC_PGUP,
    KC_PGDN, KC_ENT, GUI_T(KC_BSPC)
  ),

  /* Insert mode
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * | NORMAL |   1  |   2  |   3  |   4  |   5  | ⇧⌘P  |           | PROJ |   6  |   7  |   8  |   9  |   0  |   -    |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |    ⇥   |   Q  |   W  |   E  |   R  |   T  |  `   |           |   -  |   Y  |   U  |   I  |   O  |   P  |   \    |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |    ⎋   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
  * |--------+------+------+------+------+------|   =  |           |   +  |------+------+------+------+------+--------|
  * |   L⇧   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |   R⇧   |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |  ⌃  |   ⌥  |  (   |  [   |   {  |                                       |  }   |  ]   |   )  |   ⌥   |   ⌃  |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        | HOME | END  |       | PGDN | PGUP |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |SPACE |      |      |       |      |      | BSPC |
  *                                 |      |NORMAL|------|       |------| ENTER|      |
  *                                 |   ⌘  |      |      |       |      |      |   ⌘  |
  *                                 `--------------------'       `--------------------'
  */
  [INSERT_MODE] = KEYMAP(
    // Left Hand
    NOR_MOD,KC_1,   KC_2,   KC_3,    KC_4,   KC_5, KC_ATM,
    KC_TAB ,KC_Q,   KC_W,   KC_E,    KC_R,   KC_T, KC_GRV,
    KC_ESC ,KC_A,   KC_S,   KC_D,    KC_F,   KC_G,
    KC_LSFT,KC_Z,   KC_X,   KC_C,    KC_V,   KC_B, KC_EQL,
    KC_LCTL,KC_LALT,KC_LPRN,KC_LBRC, KC_LCBR,

                                                                KC_HOME,KC_END,
                                                                        _______,
                                                GUI_T(KC_SPC),  NOR_MOD,_______,

    // Right Hand
                              KC_ATP , KC_6, KC_7,   KC_8,    KC_9,   KC_0,   KC_MINS,
                              KC_MINS, KC_Y, KC_U,   KC_I,    KC_O,   KC_P,   KC_BSLS,
                                       KC_H, KC_J,   KC_K,    KC_L,   KC_SCLN,KC_QUOT,
                              KC_PLUS, KC_N, KC_M,   KC_COMM, KC_DOT, KC_SLSH,KC_RSFT,
                                             KC_RCBR,KC_RBRC, KC_RPRN,KC_RALT,KC_RCTL,

    KC_PGDN, KC_PGUP,
    _______,
    _______, KC_ENT, GUI_T(KC_BSPC)
  ),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
    case 0:
        if (record->event.pressed) { SEND_STRING (VERSION_STRING); }
        break;
  }
return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool SHIFTED = (keyboard_report->mods & MOD_BIT(KC_LSFT)) |
                 (keyboard_report->mods & MOD_BIT(KC_RSFT));

  switch (keycode) {

    case NORMAL_MODE:

      // START switch(vim_queue)
      switch (vim_queue) {

        case KC_NO: print("⍉");

          // START switch(is_vim_leader(keycode))
          switch (is_vim_leader(keycode)) {

            case true:
              switch (SHIFTED) {
                case true:
                  // START switch keycode when leader and shifted
                  switch (keycode) {

                    case VIM_D:
                      if (record->event.pressed) { VIM_COMMAND_SHIFT_D(); }
                      return false;

                    case VIM_C:
                      if (record->event.pressed) { VIM_COMMAND_SHIFT_C(); }
                      return false;

                  }
                  // END switch keycode when leader and shifted
                case false: print("☞");
                  if (record->event.pressed) { ENQUEUE_VIM_LEADER(keycode); }
                  return false;
              }

            case false:

              // START switch(keycode) when no vim leader
              switch (keycode) {
                case VIM_A:
                  if (record->event.pressed) { SHIFTED ? VIM_COMMAND_SHIFT_A() : VIM_COMMAND_A(); }
                  return false;

                case VIM_B:
                  if (record->event.pressed) { VIM_COMMAND_B(); }
                  return false;

                case VIM_E:
                  if (record->event.pressed) { VIM_COMMAND_E(); }
                  return false;

                case VIM_H:
                  if (record->event.pressed) { VIM_LEFT(); }
                  return false;

                case VIM_J:
                  if (record->event.pressed) { SHIFTED ? VIM_JOIN() : VIM_DOWN(); }
                  return false;

                case VIM_K:
                  if (record->event.pressed) { VIM_UP(); }
                  return false;

                case VIM_L:
                  if (record->event.pressed) { VIM_RIGHT(); }
                  return false;

                case VIM_O:
                  if (record->event.pressed) { SHIFTED ? VIM_COMMAND_SHIFT_O() : VIM_COMMAND_O(); }
                  return false;

                case VIM_P:
                  if (record->event.pressed) { VIM_COMMAND_P(); }
                  return false;

                case VIM_S:
                  if (record->event.pressed) { SHIFTED ? VIM_COMMAND_SHIFT_S() : VIM_COMMAND_S(); }
                  return false;

                case VIM_U:
                  if (record->event.pressed) { VIM_COMMAND_U(); }
                  return false;

                case VIM_W:
                  if (record->event.pressed) { VIM_COMMAND_W(); }
                  return false;

                case VIM_Y:
                  if (record->event.pressed) { VIM_COMMAND_Y(); }
                  return false;

              }
              // END switch(keycode) when no vim leader
            }
            // END switch(is_vim_leader(keycode))

            case VIM_D: print("|vim D|");
                if (record->event.pressed) { VIM_COMMAND_SHIFT_D(); }
                return false;

        case VIM_D:
          // START switch(keycode) for case vim_queue != VIM_QUEUE_D
          switch (keycode) {

            case VIM_D:
                if (record->event.pressed) { VIM_COMMAND_DD(); }
                return false;

            case VIM_W:
                if (record->event.pressed) { VIM_COMMAND_DW(); }
                return false;

            case VIM_B:
                if (record->event.pressed) { VIM_COMMAND_DB(); }
                return false;

            default:
              return true;
          }
          // END switch(keycode) for case vim_queue != VIM_QUEUE_D

        case VIM_V:
          // START switch(keycode) for vim_queue == VIM_QUEUE_V
          switch (keycode) {

            case VIM_W:
                if (record->event.pressed) { VIM_COMMAND_VW(); }
                return false;

            case VIM_B:
                if (record->event.pressed) { VIM_COMMAND_VB(); }
                return false;

          }
          // END switch(keycode) for vim_queue == VIM_QUEUE_V

        case VIM_C:
            ENQUEUE_VIM_LEADER(KC_NO);
            return true; // placeholder until VIM_C queue is implemented

    case VIM_B:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: VIM_BACK(); break;
          case VIM_C: VIM_CHANGE_BACK(); break;
          case VIM_D: VIM_DELETE_BACK(); break;
          case VIM_V: VIM_VISUAL_BACK(); break;
        }
      }
      return false;

    case VIM_C:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_CHANGE_LINE() : VIM_LEADER(VIM_C); break;
          case VIM_C: VIM_CHANGE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_D:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_DELETE_LINE() : VIM_LEADER(VIM_D); break;
          case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_E:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_END(); break;
          case VIM_C: VIM_CHANGE_END(); break;
          case VIM_D: VIM_DELETE_END(); break;
          case VIM_V: VIM_VISUAL_END(); break;
        }
      }
      return false;

    case VIM_H:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_LEFT(); break;
          case VIM_C: VIM_CHANGE_LEFT(); break;
          case VIM_D: VIM_DELETE_LEFT(); break;
          case VIM_V: VIM_VISUAL_LEFT(); break;
        }
      }
      return false;

    case VIM_I:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: layer_on(INSERT_MODE); break;
          case VIM_C: VIM_LEADER(VIM_CI); break;
          case VIM_D: VIM_LEADER(VIM_DI); break;
          case VIM_V: VIM_LEADER(VIM_VI); break;
        }
      }
      return false;

    case VIM_J:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: SHIFTED ? VIM_JOIN() : VIM_DOWN(); break;
          case VIM_C: VIM_CHANGE_DOWN(); break;
          case VIM_D: VIM_DELETE_DOWN(); break;
          case VIM_V: VIM_VISUAL_DOWN(); break;
        }
      }
      return false;

    case VIM_K:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_UP(); break;
          case VIM_C: VIM_CHANGE_UP(); break;
          case VIM_D: VIM_DELETE_UP(); break;
          case VIM_V: VIM_VISUAL_UP(); break;
        }
      }
      return false;

    case VIM_L:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_RIGHT(); break;
          case VIM_C: VIM_CHANGE_RIGHT(); break;
          case VIM_D: VIM_DELETE_RIGHT(); break;
          case VIM_V: VIM_VISUAL_RIGHT(); break;
        }
      }
      return false;

    case VIM_O:
      if (record->event.pressed) { SHIFTED ? VIM_OPEN_ABOVE() : VIM_OPEN(); }
      return false;

    case VIM_P:
      if (record->event.pressed) { SHIFTED ? VIM_PUT_BEFORE() : VIM_PUT(); }
      return false;

    case VIM_S:
      if (record->event.pressed) { SHIFTED ? VIM_CHANGE_WHOLE_LINE() : VIM_SUBSTITUTE(); }
      return false;

    case VIM_U:
      if (record->event.pressed) { VIM_UNDO(); }
      return false;

    case VIM_V:
      if (record->event.pressed) { VIM_LEADER(VIM_V); }
      return false;

    case VIM_W:
      if (record->event.pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_WORD(); break;
          case VIM_C: VIM_CHANGE_WORD(); break;
          case VIM_CI: VIM_CHANGE_INNER_WORD(); break;
          case VIM_D: VIM_DELETE_WORD(); break;
          case VIM_DI: VIM_DELETE_INNER_WORD(); break;
          case VIM_V: VIM_VISUAL_WORD(); break;
          case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
        }
      }
      return false;

    case VIM_X:
      if (record->event.pressed) { VIM_CUT(); }
      return false;

    case VIM_Y:
      if (record->event.pressed) { SHIFTED ? VIM_YANK_LINE() : VIM_YANK(); }
      return false;

    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) { eeconfig_init(); }
      return false;
    case VRSN:
      if (record->event.pressed) { SEND_STRING(VERSION_STRING); }
      return false;
    case RGB_SLD:
      if (record->event.pressed) { rgblight_mode(1); }
      return false;
  }

  // End by clearing the queue unless keycode is a
  // if ((record->event.pressed) &&
  //     (keycode != VIM_I ||
  //     keycode != VIM_C ||
  //     keycode != VIM_D ||
  //     keycode != VIM_V)) {
  //   VIM_LEADER(KC_NO);
  // }

  return true;
};

void matrix_init_user(void) {
  debug_enable = true;
  VIM_LEADER(KC_NO);
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
