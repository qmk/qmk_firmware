#include QMK_KEYBOARD_H


enum keyboard_layers {
  QWERTY = 0,      // Base Layer
  WORKMAN = 1,     // Alternate Base
  FN,              // Function Layer
  NAV              // Navigation Layer
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,
    KC_KEEB,
    KC_TMRK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY] = LAYOUT_infinity(
      KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
      KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, TG(WORKMAN),
      KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                                     MO(FN),  KC_RALT, KC_RGUI, KC_RCTL
  ),

/*
 * Base Layer: WORKMAN
 *
 *  --------+------+------+------+------+------+------+------+------+------+------+-------+-------+------+--------        
 * |  ESC   |  1   |   2  |   3  |   4  |   5  |  6   |   7  |   8  |   9  |   0  |  - _  |  = +  |  | \ |  ` ~   |
 * |--------+------+------+------+------+------+------+------+------+------+------+-------+-------+------+--------|
 * |  TAB   |  Q   |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  | ;  : |  [ {  |  ] }  |    Bk Spc     |
 * |--------+------+------+------+------+------+------+------+------+------+------+-------+-------+------+--------|
 * |     Bk Spc    |   A  |   S  |  H   |   T  |   G  |   Y  |   N  |   E  |   O  |   I   |  ' "  |    ENTER      |
 * |--------+------+------+------+------+------+------+------+------+------+------+-------+-------+---------------|
 * |      LCTL     |   Z  |   X  |   M  |   C  |   V  |   K  |   L  |  , < |  . > |  /  ? |     RCTL      | QWERTY|
 * |--------+------+------+------+------+------+------+------+------+------+------+-------+-------+-------+-------|
 * |  CCCV  | MENU |  ALT |                       SPACE FN                        |  ALT  |  MENU |   FN  |  LEAD |
 *  --------+------+------+-------------------------------------------------------+-------+-------+-------+-------'
 *
 */

  [WORKMAN] = LAYOUT_infinity(
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,   KC_F,    KC_U,    KC_P,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSPC,
      KC_BSPC, KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,   KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT, KC_ENT,
      KC_LCTL, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,   KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL, TG(QWERTY),
      KC_CCCV, KC_LGUI, KC_LALT,                   LT(NAV,KC_SPC),                             MO(FN),  KC_RALT, KC_RGUI, KC_LEAD
  ),

  [FN] = LAYOUT_infinity(
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, _______,  _______,
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      KC_ASON,  KC_ASUP, KC_ASRP, _______, KC_VOLU, KC_MPLY, _______, KC_KEEB, KC_TMRK, _______, _______, _______, _______,
      KC_ASOFF, KC_ASDN, _______, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______, _______,                   _______,                                     _______, _______, _______, _______
  ),

  [NAV] = LAYOUT_infinity(
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_PGDN, _______, _______,  _______, _______, _______,
      _______, _______, _______,                   _______,                                     _______,  _______, _______, _______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold to copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap to paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_N) { // Undo closed browser window
            SEND_STRING(SS_LCTL(SS_LALT("n")));
        }
        SEQ_ONE_KEY(KC_P) { // New private browser window
            SEND_STRING(SS_LCTL(SS_LSFT("p")));
        }
        SEQ_ONE_KEY(KC_R) { // Toggle browser reader mode
            SEND_STRING(SS_LCTL(SS_LSFT("r")));
        }
        SEQ_ONE_KEY(KC_T) { // Undo closed browser tab
            SEND_STRING(SS_LCTL(SS_LSFT("t")));
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
case KEEB:
    if (record->event.pressed) {
        send_string_hex_string("2328") 
    }
        return false; 
        break;
case TMRK:
    if (record->event.pressed) {
        send_string_hex_string("2122") 
    }
        return false; 
        break;
 }
return true;
}

