#include QMK_KEYBOARD_H

// Callum swapper
// https://github.com/callum-oakley/qmk_firmware/blob/master/users/callum
#include "oneshot.h"
#include "swapper.h"
#include "keycodes.h"
#include "layer_lock.h"
#include "keymap_uk.h"

enum layers {
    _CDH,
	_NUM,
	_NAV,
	_FUN,
};

enum keycodes {
	// Numword and switch app
	NUMWORD = SAFE_RANGE,
	OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

	LLOCK,
	SW_APP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Colemak Mod-DH layout
  [_CDH] = LAYOUT_split_3x5_2(
                              UK_Q, UK_W, UK_F, UK_P, UK_B,                UK_J, UK_L, UK_U,    UK_Y,   UK_QUOT,
                              UK_A, UK_R, UK_S, UK_T, UK_G,                UK_M, UK_N, UK_E,    UK_I,   UK_O,
                              UK_Z, UK_X, UK_C, UK_D, UK_V,                UK_K, UK_H, UK_COMM, UK_DOT, UK_SLSH,
                                                 NAV, SHFT,                KC_BSPC, NUM
                              ),


  [_NUM] = LAYOUT_split_3x5_2(
                           UK_LBRC,  UK_7, UK_8, UK_9, UK_RBRC,        KC_NO,   GBPD,    PMIN,    KC_NO,   KC_BSPC,
                           UK_SCLN,  UK_4, UK_5, UK_6, UK_EQL,         KC_NO,   OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
                           UK_GRV,   UK_1, UK_2, UK_3, UK_MINS,        KC_NO,   LLOCK,   UK_HASH,   UK_BSLS, UK_SLSH,
                                                 UK_DOT,  UK_0,        KC_SPC,  KC_TRNS
                              ),

  [_NAV] = LAYOUT_split_3x5_2(
                              SW_APP,  KC_NO,   TAB_L,  TAB_R,   KC_TAB,      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_BSPC,
                              OS_CTRL, OS_ALT,  OS_CMD, OS_SHFT, M_SAVE,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,
                              M_UNDO,  M_CUT,   M_COPY,  LLOCK,  M_PSTE,      WS_L,    W_L,     W_R,     WS_R,    KC_DEL,
                                                       KC_TRNS, KC_TRNS,      LAU, KC_TRNS
                              ),

  [_FUN] = LAYOUT_split_3x5_2(
                              KC_NO,   KC_VOLD,  KC_MUTE,  KC_VOLU,   KC_CAPS,      KC_F12,  KC_F7, KC_F8, KC_F9, KC_NO,
                              OS_CTRL, OS_ALT,   OS_CMD,   OS_SHFT,   KC_NO,        KC_F11,  KC_F4, KC_F5, KC_F6, KC_NO,
                              KC_NO,   KC_MPRV,  KC_MPLY,  KC_MNXT,   KC_NO,        KC_F10,  KC_F1, KC_F2, KC_F3, KC_NO,
                                                           KC_TRNS,   KC_TRNS,      KC_SPC, KC_TRNS
                              ),
};

enum combo_events {
   // punctuation combos
   MINS_COMBO, // C+D   -
   USCR_COMBO, // H+,,  _
   SCLN_COMBO, // .+/   ;
   // braces
   LCBR_COMBO, // F+S   {
   LPRN_COMBO, // P+T    (
   LBRC_COMBO, // B+G    [
   RCBR_COMBO, // U+E    }
   RPRN_COMBO, // L+N    )
   RBRC_COMBO, // J+M    ]
   PIPE_COMBO, // C+X    |
   TILDE_COMBO, // ,+.   ~
   SPACE_COMBO,   // NAV+SHIFT
   // Other combos...
   COMBO_LENGTH
 };


 
 uint16_t COMBO_LEN = COMBO_LENGTH;
// punctuation combos
 const uint16_t PROGMEM mins_combo[] = {UK_C, UK_D, COMBO_END};
 const uint16_t PROGMEM uscr_combo[] = {UK_H, UK_COMM, COMBO_END};
 const uint16_t PROGMEM scln_combo[] = {UK_DOT, UK_SLSH, COMBO_END};
 const uint16_t PROGMEM pipe_combo[] = {UK_X, UK_C, COMBO_END};
 const uint16_t PROGMEM tilde_combo[] = {UK_DOT, UK_COMM, COMBO_END};


 // braces - vertical combos
 const uint16_t PROGMEM lcbr_combo[] = {UK_F, UK_S, COMBO_END};
 const uint16_t PROGMEM lprn_combo[] = {UK_P, UK_T, COMBO_END};
 const uint16_t PROGMEM lbrc_combo[] = {UK_B, UK_G, COMBO_END};
 const uint16_t PROGMEM rbrc_combo[] = {UK_J, UK_M, COMBO_END};
 const uint16_t PROGMEM rprn_combo[] = {UK_L, UK_N, COMBO_END};
 const uint16_t PROGMEM rcbr_combo[] = {UK_U, UK_E, COMBO_END};

 // system keys on combos
 const uint16_t PROGMEM space_combo[] = {NAV, SHFT, COMBO_END};

 combo_t key_combos[] = {
   [MINS_COMBO] = COMBO(mins_combo, UK_MINS),
   [USCR_COMBO] = COMBO(uscr_combo, LSFT(UK_MINS)),
   [SCLN_COMBO] = COMBO(scln_combo, UK_SCLN),
   [LCBR_COMBO] = COMBO(lcbr_combo, UK_LCBR),
   [LPRN_COMBO] = COMBO(lprn_combo, UK_LPRN),
   [LBRC_COMBO] = COMBO(lbrc_combo, UK_LBRC),
   [RCBR_COMBO] = COMBO(rcbr_combo, UK_RCBR),
   [RPRN_COMBO] = COMBO(rprn_combo, UK_RPRN),
   [RBRC_COMBO] = COMBO(rbrc_combo, UK_RBRC),
   [PIPE_COMBO] = COMBO(pipe_combo, UK_BRKP),
   [TILDE_COMBO] = COMBO(tilde_combo, UK_TILD),
   [SPACE_COMBO] = COMBO(space_combo, KC_SPC),
 };

// caps word setup
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case UK_A ... UK_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case UK_1 ... UK_0:
        case KC_BSPC:
        case UK_MINS:
        case KC_DEL:
        case UK_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case NAV:
    case NUM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}


bool sw_app_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

  update_swapper(
                 &sw_app_active, KC_LGUI, KC_TAB, SW_APP,
                 keycode, record
                 );

  update_oneshot(
                 &os_shft_state, KC_LSFT, OS_SHFT,
                 keycode, record
                 );

  update_oneshot(
                 &os_ctrl_state, KC_LCTL, OS_CTRL,
                 keycode, record
                 );

  update_oneshot(
                 &os_alt_state, KC_LALT, OS_ALT,
                 keycode, record
                 );

  update_oneshot(
                 &os_cmd_state, KC_LCMD, OS_CMD,
                 keycode, record
                 );

  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _NAV, _FUN);
}