#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
};

const uint16_t PROGMEM combo_btn1l[] = {KC_P, KC_T, COMBO_END};
const uint16_t PROGMEM combo_btn2l[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM combo_btn1r[] = {KC_L, KC_N, COMBO_END};
const uint16_t PROGMEM combo_btn2r[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM combo_play[] = {KC_MPRV, KC_MNXT, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_rctl[] = {KC_H, KC_COMMA, COMBO_END};
const uint16_t PROGMEM combo_semi[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_colon[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_backtick[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_dqt[] = {KC_X, KC_C, COMBO_END};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

combo_t key_combos[] = {
    COMBO(combo_btn1l, KC_BTN1),
    COMBO(combo_btn2l, KC_BTN2),
    COMBO(combo_btn1r, KC_BTN1),
    COMBO(combo_btn2r, KC_BTN2),
    COMBO(combo_play, KC_MPLY),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_rctl, OSM(MOD_LCTL)),
    COMBO(combo_dqt, KC_DQT),
};

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  DESKTOP_LEFT,
  DESKTOP_RIGHT,
  BUFFER_PREV,
  BUFFER_NEXT,
  ALT_TAB,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox_pretty(
  ALT_TAB,         KC_1,               KC_2,                 KC_3,                KC_4,                  KC_5,    KC_BACKSLASH,              LCTL(KC_H),     KC_6,                  KC_7,                  KC_8,                      KC_9,                 KC_0,                   LALT(KC_X),
  KC_TAB,          KC_Q,               KC_W,                 KC_F,                KC_P,                  KC_B,    KC_LBRC,                   KC_RBRC,        KC_J,                  KC_L,                  KC_U,                      KC_Y,                 KC_TRNS,                KC_BSPC,
  KC_ESC,          KC_A,               KC_R,                 KC_S,                KC_T,                  KC_G,                                               KC_M,                  KC_N,                  KC_E,                      KC_I,                 KC_O,                   KC_ENT,
  KC_LSFT,         KC_Z,               KC_X,                 KC_C,                KC_D,                  KC_V,    KC_QUOT,                   KC_SEMICOLON,   KC_K,                  KC_H,                  KC_COMMA,                  KC_DOT,               KC_MINUS,               KC_RSFT,
  KC_TRNS,         KC_TRNS,            KC_DELETE,            KC_BSPC,             MO(SYMB),                                                                                         KC_LGUI,               KC_TRNS,                   KC_TRNS,              KC_TRNS,                KC_TRNS,
                                                             KC_LT,               KC_GT,                                                    KC_VOLU,         KC_TRNS,
                                                                                  KC_PSCR,                                                  KC_VOLD,
                                                     KC_SPC, KC_ENT,              KC_SLASH,                                                 KC_GRAVE,        KC_LALT,               KC_LCTL
),

[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  VRSN,     KC_F1,      KC_F2,      KC_F3,   KC_F4,    KC_F5,   KC_TRNS,         KC_TRNS, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_QUOTE, KC_TRNS,    KC_PGUP,    KC_UP,   KC_PGDN,  KC_EQL,  KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
  KC_DQT,   KC_HOME,    KC_LEFT,    KC_DOWN, KC_RIGHT, KC_END,                   KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  LGUI(KC_E), LGUI(KC_D), KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  EE_CLR,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,
                                                      KC_TRNS,     KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
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

void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 400) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        default:
            break;
    }

    return state;
};
