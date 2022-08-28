// Copyright (C) 2019, 2020  Keyboard.io, Inc
//               2021  Antoine R. Dumont (@ardumont) <antoine.romain.dumont@gmail.com>
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _QW,
    _RS,
    _LW,
};

// tap: z    // hold: SHIFT
#define Z_SFT     SFT_T(KC_Z)
// tap: /    // hold: SHIFT
#define SLSH_SFT  SFT_T(KC_SLSH)

// tap: `    // hold: SHIFT
#define GRAVE_SFT SFT_T(KC_GRAVE)
// tap: [    // hold: SHIFT
#define RBRC_SFT  SFT_T(KC_RBRC)

// Layer movment
#define FN0 MO(_RS)  // move to layer 1 (L1)
#define FN1 TG(_LW)  // move to layer 2 (L2)
#define FN2 TO(_QW)  // move to layer 0 (L0)

  /*
   *  q     w     e     r   t      ||     y   u   i/tab o  p
   *  a     s     d     f   g      ||     h   j   k     l  ;
   *  z/sft x     c     v   b  `   || \   n   m   ,     .  //sft
   *  ctl   esc  super  alt L1 spc || spc L1  alt -     '  ctl
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,                      KC_Y,   KC_U,    KC_I,    KC_O,    KC_P    ,
    KC_A,    KC_S,   KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN ,
    Z_SFT,   KC_X,   KC_C,     KC_V,    KC_B,   KC_GRAVE, KC_BSLS, KC_N,   KC_M,    KC_COMM, KC_DOT,  SLSH_SFT,
    KC_LCTRL, KC_ESC, KC_LGUI,  KC_LALT, KC_SPC, FN0,      FN0,     KC_SPC, KC_LALT, KC_MINS, KC_QUOT, KC_LCTRL
  ),

  /*
   *  1     2      3     4   5       ||    6   7   8    9    0
   *  !     @      #     $   %       ||    ^   &   *    (    )
   *  `/sft ~      ?     ?   ?   ~   || |  +   -   /    [    ]/sft
   *  ctl   esc    super alt spc L2  || L2 spc alt =    esc  ctl
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,     KC_7,    KC_8,    KC_9,    KC_0    ,
    KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN ,
    GRAVE_SFT, KC_TILD, KC_NO,   KC_NO,   KC_NO,    _______, _______, KC_PLUS,  KC_MINS, KC_SLSH, KC_LBRC, RBRC_SFT,
    _______,   _______, _______, _______, _______, FN1,      FN1,     _______, _______, KC_EQL,   _______,  _______
  ),

  /*
   * F1  F2  F3    F4  F5          ||    F6  F7  F8  F9  F10
   * __  __  __    __  F11         ||    F12 __  __  __  __
   * __  __  __    dbg rst eep-rst || __ __  __  __  __  __
   * ctl esc super alt  __ L0      || L0 __ alt  __  esc ctl
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8, KC_F9,  KC_F10,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_F11,                    KC_F12,  KC_NO,   KC_NO, KC_NO,  KC_NO ,
    KC_NO,   KC_NO,   KC_NO,   DEBUG,   QK_BOOT, EEP_RST, _______, KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_NO ,
    _______, _______, _______, _______, _______, FN2,     FN2,     _______, _______, KC_NO, KC_ESC, _______
  )
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

bool substitute_keycode(uint16_t keycode, keyrecord_t *record, uint8_t mod_state, uint16_t substitute_keycode) {
    /* Substitute keycode if condition matches */
    // Initialize a boolean variable that keeps track
    // of the delete key status: registered or not?
    static bool key_registered;
    // ctrl activated?
    if ((mod_state & MOD_BIT(KC_LCTRL)) == MOD_BIT(KC_LCTRL)) {
        if (record->event.pressed) {
            // No need to register KC_LCTRL because it's already active.
            unregister_code(KC_LCTRL);
            // Send substitute code
            register_code(substitute_keycode);
            // Update the boolean variable to reflect the status of the register
            key_registered = true;
            // Reapplying modifier state so that the held shift key(s)
            // still work even after having tapped the Backspace/Delete key.
            set_mods(mod_state);
            // Do not let QMK process the keycode further
            return false;
        } else {
            // In case substitude_keycode is still even after release of the key
            if (key_registered) {
                unregister_code(substitute_keycode);
                key_registered = false;
                // Do not let QMK process the keycode further
                return false;
            }
        }
    } else { // ctrl got released
        // In case substitude_keycode is still sent after release of the ctrl key
        if (key_registered) {
            unregister_code(substitute_keycode);
            key_registered = false;
        }
    }
    // Else, let QMK process the keycode as usual
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
    case KC_I:
        return substitute_keycode(keycode, record, mod_state, KC_TAB);
    case KC_M:
        return substitute_keycode(keycode, record, mod_state, KC_ENTER);
    case KC_H:
        return substitute_keycode(keycode, record, mod_state, KC_BSPC);
    case KC_D:
        return substitute_keycode(keycode, record, mod_state, KC_DEL);
    case KC_N:
        return substitute_keycode(keycode, record, mod_state, KC_DOWN);
    case KC_P:
        return substitute_keycode(keycode, record, mod_state, KC_UP);
    }
    return true;
};
