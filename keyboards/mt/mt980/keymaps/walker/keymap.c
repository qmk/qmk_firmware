#include "mt980.h"

bool numlock_on = true;

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

enum {
  ALT_L1 = 0
};

int cur_dance (tap_dance_state_t *state);
void alt_finished (tap_dance_state_t *state, void *user_data);
void alt_reset (tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NO,              KC_INS,   KC_PSCR,  KC_PGUP,  KC_PGDN, 
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_BSPC,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                       KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,              KC_P1,    KC_P2,    KC_P3,    KC_PENT,
    KC_LCTL,  KC_LGUI,  TD(ALT_L1),                   KC_SPC,                                 KC_RALT,  MO(1),    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,            KC_P0,    KC_PDOT,  KC_PENT),

  [1] = LAYOUT(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_PAUSE, KC_SCRL,  KC_HOME,  KC_END,   
    KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   RGB_TOG,  QK_BOOT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_VAI,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   
    KC_TRNS,  KC_TRNS,  KC_TRNS,                      QK_BOOT,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_MOD,            KC_TRNS,  KC_TRNS,  KC_TRNS)  

};

int cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(1, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(1); break;
  }
}

void alt_reset (tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(1); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
  [ALT_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,alt_finished, alt_reset)
};

void led_set_keymap(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    numlock_on = true;
  }
  else {
    numlock_on = false;
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case QK_BOOT:
      /* Don't allow reset from oneshot layer state */
      if (record->event.pressed && is_oneshot_layer_active()) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        return false;
      }
      return true;
    case KC_PPLS:
      if (!numlock_on) {
        if (is_oneshot_layer_active() || layer_state & 0x2) {
          if (record->event.pressed)
            register_code(KC_HOME);
          else
            unregister_code(KC_HOME);
          clear_oneshot_layer_state(ONESHOT_START);
        }
        else {
          if (record->event.pressed)
            register_code(KC_PGUP);
          else
            unregister_code(KC_PGUP);
        }
        return false;
      }
      return true;
    case KC_PENT:
      if (!numlock_on) {
        if (is_oneshot_layer_active() || layer_state & 0x2) {
          if (record->event.pressed)
            register_code(KC_END);
          else
            unregister_code(KC_END);
          clear_oneshot_layer_state(ONESHOT_START);
        }
        else {
          if (record->event.pressed)
            register_code(KC_PGDN);
          else
            unregister_code(KC_PGDN);
        }
        return false;
      }
      return true;
    case KC_NUM:
      /* Shift + NumLock will be treated as shift-Insert */
      if ((keyboard_report->mods & MOD_BIT (KC_LSFT)) || (keyboard_report->mods & MOD_BIT (KC_RSFT))) {
        if (record->event.pressed) {
          register_code(KC_INS);
          unregister_code(KC_INS);
        }
        return false;
      }
      else
        return true;
    default:
      return true;
  }
  return true;
}
