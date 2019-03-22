#include QMK_KEYBOARD_H
#include "rgblight.h"

#define DEFAULT_LAYER 0
#define FN_LAYER 1
#define NUM_LAYER 2
#define LIGHTING_LAYER 3
#define TO_LAYER 15
#define ______ KC_TRNS
#define XXXXXX KC_NO
#define BACKLIGHT_TIMEOUT 15 // in minutes

enum my_keycodes {
  L_BL = SAFE_RANGE,
  L_ID = SAFE_RANGE,
};

static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;
static bool layer_bl = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DEFAULT_LAYER] = LAYOUT_60_b_ansi( \
    KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, \
    KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, \
    LT(FN_LAYER,KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH), KC_UP, MO(TO_LAYER), \
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(FN_LAYER), KC_SPC, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT \
  ),
	[FN_LAYER] = LAYOUT_60_b_ansi( \
    KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_DEL, \
    ______, KC_MPLY, KC_MNXT, KC_VOLU, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, XXXXXX, \
    ______, KC_MSTP, KC_MPRV, KC_VOLD, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, ______, \
    ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_RSFT, KC_PGUP, KC_INS, \
    ______, ______, ______, ______, ______, ______, ______, ______, KC_HOME, KC_PGDN, KC_END \
  ),
	[NUM_LAYER] = LAYOUT_60_b_ansi( \
    ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, XXXXXX, ______, ______, \
    ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_P7, KC_P8, KC_P9, KC_PPLS, XXXXXX, XXXXXX, XXXXXX, \
    ______, ______, ______, ______, XXXXXX, XXXXXX, XXXXXX, KC_P4, KC_P5, KC_P6, KC_PPLS, XXXXXX, ______, \
    ______, ______, ______, ______, ______, XXXXXX, XXXXXX, KC_P1, KC_P2, KC_P3, KC_PENT, ______, ______, \
    ______, ______, ______, ______, ______, KC_P0, KC_PDOT, KC_PENT, ______, ______, ______ \
  ),
	[LIGHTING_LAYER] = LAYOUT_60_b_ansi( \
    RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, XXXXXX, XXXXXX, XXXXXX, XXXXXX, L_BL, L_BL, \
    XXXXXX, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX \
  ),
	[TO_LAYER] = LAYOUT_60_b_ansi( \
    TO(DEFAULT_LAYER), TO(NUM_LAYER), TO(LIGHTING_LAYER), XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX \
  ),
};

uint32_t layer_state_set_user(uint32_t state) {
  if (layer_bl) {
    switch (biton32(state)) {
      case DEFAULT_LAYER:
        rgblight_setrgb(0, 250, 255);
        break;
      case NUM_LAYER:
        rgblight_setrgb(0, 173, 20);
        break;
      case FN_LAYER:
        rgblight_setrgb(240, 255, 0);
        break;
      case LIGHTING_LAYER:
        rgblight_setrgb(255, 0, 229);
        break;
      case TO_LAYER:
        rgblight_setrgb(255, 136, 0);
        break;
    }
  }
  return state;
}

void keyboard_post_init_user(void) {
  rgblight_enable();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if (led_on == false) {
      rgblight_enable();
      idle_timer = timer_read();
      halfmin_counter = 0;
      led_on = true;
    }
  }
  switch (keycode) {
    case L_BL:
      if (record->event.pressed) {
        layer_bl = !layer_bl;
      }
      return false;
  }
  return true;
}

void matrix_scan_user() {
  if (idle_timer == 0) idle_timer = timer_read();
  if (led_on && timer_elapsed(idle_timer) > 30000) {
    halfmin_counter++;
    idle_timer = timer_read();
  }
  if (led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) {
    rgblight_disable();
    halfmin_counter = 0;
    led_on = false;
  }
}

void matrix_init_user(void) {
  DDRB |= (1 << 2);
  PORTB &= ~(1 << 2);
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    PORTB &= ~(1 << 2);
  } else {
    PORTB |= (1 << 2);
  }
}
