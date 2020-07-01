#include QMK_KEYBOARD_H

// Layer shorthand
#define _QW 0
#define _CM 1
#define _FN 2

typedef enum {
  NONE_NONE,
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state = NONE_NONE;
int cur_dance (qk_tap_dance_state_t *state);
void altlp_finished (qk_tap_dance_state_t *state, void *user_data);
void altlp_reset (qk_tap_dance_state_t *state, void *user_data);

// Four differend underglow states for 2 language layouts x 2 states of colemak layer
enum layer_states {
  S_ENGLISH,
  S_COLEMAK,
  S_CRUSSIAN,
  S_QRUSSIAN
} l_state = S_ENGLISH;

// CLMK to toggle colemak (active only with english qwerty, saves intent in russian but does nothing untill switched back to english)
// RNBW - rainbow underglow
// PING - ping pong underglow
// SP_UP/DW - underglow speed controls
enum custom_keycodes {
  STUB = SAFE_RANGE,
  CLMK,
  RNBW,
  PING,
  SP_UP,
  SP_DW
};

// Escape if taped, FN layer mod if held
enum tapdance_codes {
  LESC
};

bool sstate = false;
int rgb = 0;
int speed = 300;

void set_colors(int r, int g, int b) {
  for(int i = 0; i<6; i++) {
    sethsv(r, g, b, (LED_TYPE *)&led[i]);
  }
  rgblight_set();
}

void update_led_state_c(void) {
  if (rgb>0) return;
  if (td_state == SINGLE_HOLD) set_colors(HSV_BLUE);
  else {
    if (l_state == S_ENGLISH) set_colors(HSV_RED);
    if (l_state == S_QRUSSIAN) set_colors(HSV_GREEN);
    if (l_state == S_COLEMAK) set_colors(HSV_YELLOW);
    if (l_state == S_CRUSSIAN) set_colors(85, 100, 100);
  }
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted && state->pressed) { return SINGLE_HOLD; }
    else if (!state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; }
}

// Tapdance code stolen long time ago from one of the forum answers i found related to my problem, sadly can't provide link for the credits
void lesc_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      register_code16(KC_ESC);
      break;
    case SINGLE_HOLD:
      layer_on(_FN);
      update_led_state_c();
      sstate = false;
      break;
    case DOUBLE_SINGLE_TAP:
      break;
    case NONE_NONE:
      break;
  }
}

void lesc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      unregister_code16(KC_ESC);
      break;
    case SINGLE_HOLD:
      layer_off(_FN);
      if (sstate == false) {
        register_code16(KC_ESC);
        unregister_code16(KC_ESC);
      }
      break;
    case DOUBLE_SINGLE_TAP:
      break;
    case NONE_NONE:
      break;
  }
  td_state = NONE_NONE;
  update_led_state_c();
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lesc_finished, lesc_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
KC_GRV,  KC_1,       KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, RNBW,    KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_BSPC,
KC_TAB,  KC_Q,       KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_QUOT,
KC_CAPS, KC_A,       KC_S,    KC_D,    KC_F,    KC_G,    CLMK,    KC_DEL,  SP_UP,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_ENT,
KC_LSFT, KC_Z,       KC_X,    KC_C,    KC_V,    KC_B,    _______, KC_UP,   SP_DW,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,
KC_LCTL, LSFT(KC_9), KC_LALT, KC_LGUI, TD(LESC),KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,  TD(LESC),KC_RGUI, KC_RALT, RSFT(KC_0),KC_RCTL
  ),
  [_CM] = LAYOUT_ortho_5x15( /* COLEMAK */
_______, _______, _______, _______, _______, _______, _______, PING,    _______, _______, _______, _______, _______, _______, _______,
_______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_Z,    _______, _______, _______, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_SLSH,
_______, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    _______, _______, _______, KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
_______, KC_X,    KC_V,    KC_C,    KC_D,    KC_B,    _______, _______, _______, KC_K,    KC_H,    KC_DOT,  KC_COMM, KC_QUOT, _______,
_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_P7,   KC_P8,   KC_P9,  KC_F7,   KC_F8,   KC_F9,   KC_F10,        KC_F11,        KC_F12,
RESET,   KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_WH_U, KC_P4,   KC_P5,   KC_P6,  _______, _______, _______, RSFT(KC_MINS), LSFT(KC_MINS), _______,
_______, KC_MS_L, KC_MS_D, KC_MS_R, KC_MINS, KC_WH_D, KC_P1,   KC_P2,   KC_P3,  _______, KC_PPLS, KC_ACL0, KC_ACL1,       KC_ACL2,       _______,
_______, KC_ACL0, KC_ACL1, KC_ACL2, KC_WH_L, KC_WH_R, KC_NLCK, KC_PGUP, KC_P0,  _______, _______, _______, _______,       _______,       _______,
RGB_TOG, _______, _______, _______, KC_BSPC, KC_BSPC, KC_HOME, KC_PGDN, KC_END, KC_BSPC, KC_BSPC, _______, _______,       _______,       _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(keycode != TD(LESC))
    sstate = true;
  switch (keycode) {
    case SP_UP:
      if (speed>25)
        speed -= 25;
      break;
    case SP_DW:
      if (speed < 1000)
        speed += 25;
      break;
    case RNBW:
      if(record->event.pressed) {
        rgb = rgb == 0 ? 1 : 0;
        update_led_state_c();
      }
      break;
    case PING:
      if(record->event.pressed) {
        rgb = rgb == 0 ? 2 : 0;
        update_led_state_c();
      }
      break;
    case CLMK:
      if(record->event.pressed) {
        if (l_state == S_COLEMAK) {
          layer_off(_CM);
          l_state = S_ENGLISH;
        }
        else if (l_state == S_ENGLISH) {
          layer_on(_CM);
          l_state = S_COLEMAK;
        }
        else if (l_state == S_CRUSSIAN) { l_state = S_QRUSSIAN; }
        else if (l_state == S_QRUSSIAN) { l_state = S_CRUSSIAN; }
      }
      update_led_state_c();
      break;
    case KC_CAPS:
      if(record->event.pressed) {
        if (l_state == S_ENGLISH) l_state = S_QRUSSIAN;
        else if (l_state == S_QRUSSIAN) l_state = S_ENGLISH;
        else if (l_state == S_COLEMAK) {
          layer_off(_CM);
          l_state = S_CRUSSIAN;
        }
        else if (l_state == S_CRUSSIAN) {
          layer_on(_CM);
          l_state = S_COLEMAK;
        }
        update_led_state_c();
      }
      break;
  }
  return true;
}

void matrix_init_user(void) { }

// Rainbow globals
int t = 0;
int rc = 0;
int col = 0;
bool right = false;

void matrix_scan_user(void) {
  if (rgb==0) return; // Do nothing each tick right away if neither of animations enabled
  if (rgb==1) {
    if (rc == 0) {
      rc = speed;
      for(int i = 0; i<6; i++) {
        sethsv(42*((t+i)%6), 255, 255, (LED_TYPE *)&led[i]);
      }
      rgblight_set();
      t++; t = t % 6;
    }
  } else if (rgb==2) {
    if (rc == 0) {
      rc = speed;
      col = (col + 1) % 36;
      for (int i = 0; i<6; i++) {
        if (i==t)
          sethsv(42*(((col-1)/6)%6), 255, 255, (LED_TYPE *)&led[(right ? t : 5-t)]);
        else
          sethsv(0, 0, 0, (LED_TYPE *)&led[right ? i : 5-i]);
      }
      rgblight_set();
      t++; t = t % 6;
      if (t == 0) right = !right;
    }
  }
  rc--;
}

void led_set_user(uint8_t usb_led) { }
