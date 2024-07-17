#include QMK_KEYBOARD_H
#include "version.h"
#include "os_detection.h"

#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 4000  /* Time (in ms) before the one shot key is released */

enum layers {
    BASE,  // default layer
    SYMB,  // symbols
    QWERTY
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  VRSN = SAFE_RANGE,
  DESKTOP_LEFT,
  DESKTOP_RIGHT,
  BUFFER_PREV,
  BUFFER_NEXT,
  ALT_TAB,
  COPY,
  PASTE,
  H_PREV,
  H_NEXT,
};

combo_t key_combos[] = {};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox_pretty(
  KC_ESC,          KC_1,               KC_2,                 KC_3,                KC_4,                  KC_5,    KC_BACKSLASH,              ALT_TAB,        KC_6,                  KC_7,                  KC_8,                      KC_9,                 KC_0,                   KC_DEL,
  KC_TAB,          KC_Q,               KC_W,                 KC_E,                KC_R,                  KC_T,    KC_LBRC,                   KC_RBRC,        KC_Y,                  KC_U,                  KC_I,                      KC_O,                 KC_P,                   KC_BSPC,
  KC_LCTL,         KC_A,               KC_S,                 KC_D,                LT(SYMB, KC_F),        KC_G,                                               KC_H,                  LT(SYMB, KC_J),        KC_K,                   KC_L,                 KC_COLON,               KC_ENT,
  KC_LSFT,         KC_Z,               KC_X,                 KC_C,                KC_V,                  KC_B,    KC_QUOT,                   KC_SEMICOLON,   KC_N,                  KC_M,                  KC_COMMA,                  KC_DOT,               KC_MINUS,               KC_RSFT,
  KC_LCTL,         KC_LALT,            KC_LGUI,              KC_BTN1,             MO(SYMB),                                                                                         KC_LGUI,               KC_LSFT,                   KC_TRNS,              KC_TRNS,                TG(QWERTY),

                                                             KC_MPRV,             KC_MNXT,                                                  KC_VOLU,         KC_MPLY,
                                                                                  KC_PSCR,                                                  KC_VOLD,
                                                     KC_SPC, KC_LSFT,            KC_SLASH,                                                  KC_GRAVE,        KC_LALT,               KC_LCTL
),

[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  VRSN,     KC_F1,      KC_F2,      KC_F3,   KC_F4,    KC_F5,   KC_TRNS,         KC_TRNS, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_QUOTE, KC_TRNS,    KC_PGUP,    KC_UP,   KC_PGDN,  KC_EQL,  KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
  KC_DQT,   KC_HOME,    KC_LEFT,    KC_DOWN, KC_RIGHT, KC_END,                            KC_TRNS, H_PREV,   H_NEXT,  KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  LGUI(KC_E), KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  EE_CLR,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
                                             KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS,
                                                       KC_TRNS,     KC_TRNS,
                                    KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
),

[QWERTY] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESC,          KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_LEFT,              KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_MINS,
  KC_TAB,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    TG(SYMB),             TG(SYMB),     KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSPC,
  KC_LCTL,         KC_A,        KC_S,          KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
  KC_LSFT,         KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    ALL_T(KC_NO),                  MEH_T(KC_NO), KC_N,    KC_M,    KC_COMM, KC_DOT,           CTL_T(KC_SLSH), KC_RSFT,
  KC_LCTL,         KC_QUOT,     KC_BTN2, KC_BTN1,  MO(SYMB),                                            KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, TG(QWERTY),
                                                           ALT_T(KC_APP), KC_LGUI,                 TG(QWERTY), CTL_T(KC_ESC),
                                                                          KC_HOME,                 KC_PGUP,
                                                         KC_SPC, KC_BSPC, KC_END,                  KC_PGDN, KC_LALT, KC_LCTL
),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  os_variant_t os = detected_host_os();
  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case H_PREV:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
      }
      break;
    case H_NEXT:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_RIGHT)));
      }
      break;
    case COPY:
      if (record->event.pressed) {
        if (os == OS_MACOS) {
          SEND_STRING(SS_LGUI("c"));
        } else {
          SEND_STRING(SS_LCTL("c"));
        }
      }
      break;
    case PASTE:
      if (record->event.pressed) {
        if (os == OS_MACOS) {
          SEND_STRING(SS_LGUI("v"));
        } else {
          SEND_STRING(SS_LCTL("v"));
        }
      }
      break;
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          if (os == OS_MACOS) {
            register_code(KC_LGUI);
          } else {
            register_code(KC_LALT);
          }
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
  os_variant_t os = detected_host_os();
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 400) {
      if (os == OS_MACOS) {
        unregister_code(KC_LGUI);
      } else {
        unregister_code(KC_LALT);
      }
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
