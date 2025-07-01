#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "keymap_uk.h"

enum layers {
    _BASE,
    _SYM,
    _NAV,
    _NUM,
    _MOUS,
    _MEDIA,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC,    UK_Q,    UK_W,    UK_F,    UK_P,    UK_B,                       UK_J,  UK_L,  UK_U,     UK_Y,   UK_QUOT,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTRL,     UK_A,    UK_R,    UK_S,    UK_T,    UK_G,                        UK_M,  UK_N,  UK_E,     UK_I,   UK_O,     KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,    UK_Z,    UK_X,    UK_C,    UK_D,    UK_V,                       UK_K,  UK_H,  UK_COMM,  UK_DOT, UK_SCLN,     KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_SPC, NAV, SHFT,            KC_SPC,  SYM, KC_NO
                                          
                                      //`--------------------------'  `--------------------------'

  ),


    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS,  KC_ESC, UK_LBRC,  UK_LCBR,  UK_LPRN,  TILDA,                      UK_CIRC, UK_RPRN, UK_RCBR, UK_RBRC, GRAVE, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  UK_MINS, UK_ASTR, UK_EQL, UK_UNDS, UK_DLR,                      MYHASH,   CMD,    SHFT,     ALT,    CTRL,   KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  UK_PLUS, PIPE, UK_DQUO, UK_SLSH, UK_PERC,                          KASHISH, KC_NUHS, UK_AMPR, UK_QUES, UK_EXLM, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'

  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_TAB,   KC_NO,  KC_NO,   KC_NO,  KC_NO,                        KC_NO,   KC_NO,   KC_UP,  KC_INS,  KC_DEL,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  CTRL,    ALT,   SHFT,      CMD,  C(KC_UP),                      SCRNSHOT,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSPC, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_UNDO, KC_CUT, KC_COPY,  QK_REP,  KC_PSTE,                      KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_ENT,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,      LAU, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'

  ),



    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS,  UK_7,   UK_5,    UK_3,  UK_1,   UK_9,                         UK_8,     UK_0,    UK_2,    UK_4,    UK_6,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  CTRL,   ALT,     SHFT,  CMD,  KC_F11,                          KC_F10,   CMD,    SHFT,      ALT,    CTRL,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,  KC_F7,  KC_F5,   KC_F3, KC_F1,    KC_F9,                      KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,  KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS,  KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [_MOUS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,                      KC_NO,   KC_WH_U, KC_MS_U, KC_NO,   KC_NO,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,   CTRL,    ALT,     SHFT,   CMD,   KC_NO,                          KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,  KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_UNDO,  KC_CUT, KC_COPY, KC_AGIN, KC_PSTE,                      KC_NO,   KC_WH_D, KC_NO,   KC_NO,   KC_WH_R,  KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_BTN1, KC_BTN2, KC_BTN3
                                      //`--------------------------'  `--------------------------'

  ),



    [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,  KC_NO,  KC_NO,     KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  CTRL,    ALT,     SHFT,   CMD,      KC_NO,                         KC_MRWD,  KC_VOLU, KC_VOLD, KC_MFFD, KC_NO, KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,  KC_NO,  KC_NO,     KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_MSTP, KC_MPLY , KC_MUTE
                                      //`--------------------------'  `--------------------------'

  ),
};


enum combo_events {
   // punctuation combos
   SHFT_COMBO,
   COMBO_LENGTH
 };



 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos
 const uint16_t PROGMEM shft_combo[] = {UK_G, UK_M, COMBO_END};


 combo_t key_combos[] = {
   [SHFT_COMBO] = COMBO(shft_combo, SHFT),
 };


 
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
    return true;
};
