#include QMK_KEYBOARD_H

// Implement Super-alt↯tab
// See https://docs.qmk.fm/#/feature_macros?id=super-alt↯tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Defining all the custom keycodes.
enum custom_keycodes {
  ALT_TAB = SAFE_RANGE
};

enum {
  CT_QW
};

const uint16_t PROGMEM lock_combo[] = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {COMBO(lock_combo, LGUI(KC_O))};

// Define the keycodes for one qwerty layer and one Fn layer.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: qwerty */
  [0] = LAYOUT_qwerty( \
    KC_GESC        , KC_1   , KC_2   , KC_3 , KC_4 , KC_5 , KC_6  , KC_7 , KC_8 , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,
    KC_TAB         , KC_Q   , KC_W   , KC_E , KC_R , KC_T , KC_Y  , KC_U , KC_I , KC_O   , KC_P   , KC_LBRC, KC_RBRC,
    MO(1)          , KC_A   , KC_S   , KC_D , KC_F , KC_G , KC_H  , KC_J , KC_K , KC_L   , KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT ,
    KC_LSPO        , KC_NUBS, KC_Z   , KC_X , KC_C , KC_V , KC_B  , KC_N , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC,
    KC_LCPO        , KC_LALT, ALT_TAB,                      KC_SPC,                        KC_LGUI, KC_RALT, KC_RCPC
  ),
  /* 1: second layer for media keys and many advanced features */
  [1] = LAYOUT_qwerty( \
    LALT(KC_F4), KC_F1     , KC_F2       , KC_F3       , KC_F4       , KC_F5  , KC_F6     , KC_F7  , KC_F8  , KC_F9   , KC_F10     , KC_F11    , KC_F12    , _______,
    _______    , _______   , _______     , KC_PSCR     , KC_BRIU     , KC_BRID, LCTL(KC_A), KC_HOME, KC_UP  , KC_END  , UC(0x203D) , UC(0x8593), UC(0x2E2E),
    _______    , _______   , LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), KC_DEL , KC_DEL    , KC_LEFT, KC_DOWN, KC_RIGHT, UC(0x8596) , UC(0x8595), UC(0x8594), _______,
    _______    , _______   , KC_MUTE     , KC_VOLD     , KC_VOLU     , _______, _______   , _______, _______, _______ , _______    , RESET     , _______   ,
    _______    , _______   , _______     ,                             _______,                                         _______    , _______   , _______
  )
};

// Set the unicode input mode for using UC.
void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
}

void q_w(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        register_code(KC_W);
    }    else {
        register_code(KC_Q);
    }
}

void q_w_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count > 1) {
    unregister_code(KC_W);
  } else {
    unregister_code(KC_Q);
  }
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [CT_QW] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, q_w, q_w_reset)
};

// Processing all the key pressed.
// Alt+tab.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Depending keycodes…
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {     // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
