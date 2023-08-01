#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Layer names
enum{
  // - Base layers:
  _COLEMAKDHMK,
  _COLEMAKDHMK_MAC,
  _QWERTY,
  _QWERTY_MAC,
  // - Symbols, numbers, functions and custom shifts:
  _SYMB,
  _NUMB,
  _FUNC,
  _RHSH, // Righ hand shifted keycodes
  _LHSH, // Left hand shifted keycodes
  // - Adjust layer:
  _ADJUST
};

// Custom keycodes
enum custom_keycodes {
  COLEMAKDHMK = SAFE_RANGE,
  COLEMAKDHMK_MAC,
  QWERTY,
  QWERTY_MAC,
  ASC_SAR,
  ASC_DAR,
  ASC_SQT,
  ASC_DQT,
  ASC_CIRC,
  ASC_TILD,
  ASC_HAP,
  ASC_SAD,
  ASC_BKT,
  ASC_CBRL,
  ASC_CBRR
};

// Tap dance keycodes
enum tap_dance{
  TD_SCLN, // ;; -> :
  TD_LBRC, // [[ -> {
  TD_RBRC, // ]] -> }
  TD_QMRK  // // -> ?
};

// Semicolon to Colon
void dance_scln_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_SCLN);
  } else {
    register_code (KC_RSFT);
    register_code (KC_SCLN);
  }
}
void dance_scln_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_SCLN);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_SCLN);
  }
}

// Square braket to curly bracket (left)
void dance_lbrc_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_LBRC);
  }
}
void dance_lbrc_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_LBRC);
  }
}

// Square braket to curly bracket (right)
void dance_rbrc_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_RSFT);
    register_code (KC_RBRC);
  }
}
void dance_rbrc_reset (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_RSFT);
    unregister_code (KC_RBRC);
  }
}


//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_SCLN]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_scln_finished, dance_scln_reset),
  [TD_LBRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lbrc_finished, dance_lbrc_reset),
  [TD_RBRC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rbrc_finished, dance_rbrc_reset)
};


// Shortcut to make keymap more readable

// - Adjustment Layer:
#define KC_ADEN LT(_ADJUST, KC_END)   // End / _ADJUST layer
#define KC_ADPU LT(_ADJUST, KC_PGUP)  // Page Up / _ADJUST layer

// - Custom layers:
#define KC_SYSP LT(_SYMB, KC_SPC)     // Space / _symbols
#define KC_NUES LT(_NUMB, KC_ESC)     // Esc / _numbers
#define KC_FUTA LT(_FUNC, KC_TAB)     // Tab / _functions
#define KC_N_SH LT(_LHSH, KC_N)       // Pressing N key, enable shifted keys on other half (the left one)
#define KC_T_SH LT(_RHSH, KC_T)       // Pressing T key, enable shifted keys on other half (the right one)

// - Custom keys/modifiers:
#define KC_ATAB RALT_T(KC_TAB)        // - Tab / Alt Gr
#define KC_CESC LCTL_T(KC_ESC)        // - Esc / Left Ctrl
#define KC_GSPC LGUI_T(KC_SPC)        // - Space / Left GUI
#define KC_CBSP LCTL_T(KC_BSPC)       // - Backspace / Left Ctrl

// -- Mac os mode:
#define KC_CSPC LCTL_T(KC_SPC)        // - Space / Left Ctrl
#define KC_GBSP LGUI_T(KC_BSPC)       // - Backspace / Left GUI


#define KC_AEQL LALT_T(KC_EQL)        // - Equals / Alt (left alt)
#define KC_CMIN RCTL_T(KC_MINUS)      // - Minus / Right Ctrl
#define KC_ADEL RALT_T(KC_DEL)        // - Del / Alt Gr
#define KC_RSEN RSFT_T(KC_ENT)        // - Enter / Right Shift (standard shift)
#define KC_LAEN LALT_T(KC_ENT)        // - Enter / Left Alt

// Home row mod tap keys:
// - Left hand
#define KC_CT_A CTL_T(KC_A)           // A / Left Ctrl
#define KC_AL_S ALT_T(KC_S)           // S / Left Alt
// - Right hand
#define KC_AL_E ALT_T(KC_E)           // E / Left Alt
#define KC_CT_O CTL_T(KC_O)           // O / Left Ctrl

// - Tap dance:
#define KC_TDSC TD(TD_SCLN)           // ;; -> :
#define KC_TDLB TD(TD_LBRC)           // [[ -> {
#define KC_TDRB TD(TD_RBRC)           // ]] -> }

// - Keyboard base maps:
#define LR1 COLEMAKDHMK
#define LR2 COLEMAKDHMK_MAC
#define LR3 QWERTY
#define LR4 QWERTY_MAC


// Send custom strings or change default base layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case ASC_SAR:
        SEND_STRING("->");
        return false;
      case ASC_DAR:
        SEND_STRING("=>");
        return false;
      case ASC_SQT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("'"));
        return false;
      case ASC_DQT:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("\"")));
        return false;
      case ASC_CIRC:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("^"));
        return false;
      case ASC_TILD:
        // SS_RALT(SS_LSFT()): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT(SS_LSFT("~")));
        return false;
      case ASC_HAP:
        SEND_STRING(":-) ");
        return false;
      case ASC_SAD:
        SEND_STRING(":-( ");
        return false;
      case ASC_BKT:
        // SS_RALT(): Avoid sending dead key on software intl layouts
        SEND_STRING(SS_RALT("`"));
        return false;
      case ASC_CBRL:
        SEND_STRING("{");
        return false;
      case ASC_CBRR:
        SEND_STRING("}");
        return false;
      case QWERTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
      case COLEMAKDHMK:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDHMK);
        }
        return false;
        break;
      case QWERTY_MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY_MAC);
        }
        return false;
        break;
      case COLEMAKDHMK_MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_COLEMAKDHMK_MAC);
        }
        return false;
        break;
    }
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Colemak DH-MK Mod
  [_COLEMAKDHMK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_ESC  ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ATAB ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,XXXXXXX ,                          XXXXXXX ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_TDSC ,KC_AEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CESC ,KC_A    ,KC_R    ,KC_AL_S ,KC_T_SH ,KC_G    ,KC_TDLB ,                          KC_TDRB ,KC_M    ,KC_N_SH ,KC_AL_E ,KC_I    ,KC_O    ,KC_CMIN ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       SC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       KC_GSPC ,KC_HYPR ,KC_MEH  ,XXXXXXX ,     KC_NUES ,    KC_CBSP ,KC_FUTA ,        KC_LAEN ,KC_SYSP ,    KC_ADEL ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Colemak DH-MK Mod, Mac version (CTRL and GUI are swapped)
  [_COLEMAKDHMK_MAC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_ESC  ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ATAB ,KC_Q    ,KC_W    ,KC_F    ,KC_P    ,KC_B    ,XXXXXXX ,                          XXXXXXX ,KC_J    ,KC_L    ,KC_U    ,KC_Y    ,KC_TDSC ,KC_AEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CESC ,KC_A    ,KC_R    ,KC_AL_S ,KC_T_SH ,KC_G    ,KC_TDLB ,                          KC_TDRB ,KC_M    ,KC_N_SH ,KC_AL_E ,KC_I    ,KC_O    ,KC_CMIN ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       SC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_D    ,KC_V    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_K    ,KC_H    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       KC_CSPC ,KC_HYPR ,KC_MEH  ,XXXXXXX ,     KC_NUES ,    KC_GBSP ,KC_FUTA ,        KC_LAEN ,KC_SYSP ,    KC_ADEL ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // QWERTY
  [_QWERTY] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_ESC  ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ATAB ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,XXXXXXX ,                          XXXXXXX ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_AEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CESC ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_TDLB ,                          KC_TDRB ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_TDSC ,KC_CMIN ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       SC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       KC_GSPC ,KC_HYPR ,KC_MEH  ,XXXXXXX ,     KC_NUES ,    KC_CBSP ,KC_FUTA ,        KC_LAEN ,KC_SYSP ,    KC_ADEL ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // QWERTY, Mac version (CTRL and GUI are swapped)
  [_QWERTY_MAC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_ESC  ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_ATAB ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,XXXXXXX ,                          XXXXXXX ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_AEQL ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_CESC ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_TDLB ,                          KC_TDRB ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_TDSC ,KC_CMIN ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       SC_LSPO ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,SC_RSPC ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       KC_CSPC ,KC_HYPR ,KC_MEH  ,XXXXXXX ,     KC_NUES ,    KC_GBSP ,KC_FUTA ,        KC_LAEN ,KC_SYSP ,    KC_ADEL ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Symbols, home row arrows, function keys and macros layer
  [_SYMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,_______ ,                          _______ ,ASC_CIRC,KC_AMPR ,KC_ASTR ,KC_PLUS ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_PIPE ,KC_PMNS ,ASC_SQT ,ASC_DQT ,KC_GRV  ,ASC_SAR ,                          ASC_DAR ,KC_QUOT ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_BSLS ,KC_UNDS ,KC_COLN ,ASC_TILD,KC_EQL  ,ASC_SAD ,ASC_HAP ,        _______ ,_______ ,ASC_BKT ,KC_PGUP ,KC_PGDN ,KC_HOME ,KC_END  ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Numeric keypad layer
  [_NUMB] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PAST ,KC_KP_7 ,KC_KP_8 ,KC_KP_9 ,KC_PPLS ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,XXXXXXX ,KC_KP_4 ,KC_KP_5 ,KC_KP_6 ,KC_PMNS ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,KC_KP_1 ,KC_KP_2 ,KC_KP_3 ,KC_PSLS ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    XXXXXXX ,     KC_KP_0 ,KC_PDOT ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Function layer and some extra keys on right hand
  [_FUNC] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F12  ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,KC_F4   ,KC_F5   ,KC_F6   ,KC_F11  ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,KC_PSCR ,KC_NUM  ,KC_INS  ,KC_CAPS ,KC_APP  ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F10  ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  // Left hand shifted keycodes
  [_LHSH] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,S(KC_Q) ,S(KC_W) ,S(KC_F) ,S(KC_P) ,S(KC_B) ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,S(KC_A) ,S(KC_R) ,S(KC_S) ,S(KC_T) ,S(KC_G) ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,S(KC_Z) ,S(KC_X) ,S(KC_C) ,S(KC_D) ,S(KC_V) ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_TAB  ,KC_BSPC ,    KC_ESC  ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Right hand shifted keycodes
  [_RHSH] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,S(KC_J) ,S(KC_L) ,S(KC_U) ,S(KC_Y) ,KC_COLN ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,S(KC_M) ,S(KC_N) ,S(KC_E) ,S(KC_I) ,S(KC_O) ,_______ ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,S(KC_K) ,S(KC_H) ,KC_LABK ,KC_RABK ,KC_QUES ,_______ ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       _______ ,_______ ,_______ ,_______ ,     KC_DEL  ,    KC_SPC  ,KC_ENT  ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  // Adjust layer (RGB, Reset and base layer switch)
  [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
       XXXXXXX ,LR1     ,LR2     ,LR3     ,LR4     ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,QK_BOOT,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,RGB_M_B ,RGB_M_R ,RGB_M_SW,RGB_M_SN,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,RGB_M_K ,RGB_M_X ,RGB_M_G ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
    //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
    //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )

};
