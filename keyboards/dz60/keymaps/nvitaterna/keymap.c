#include QMK_KEYBOARD_H
#include "rgblight.h"

#define DEFAULT_LAYER 0
#define FN_LAYER 1
#define TO_LAYER 2
#define LIGHTING_LAYER 3
#define ______ KC_TRNS
#define XXXXXX KC_NO
#define BACKLIGHT_TIMEOUT 1 // in minutes

static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;

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
    ______, XXXXXX, KC_UP, XXXXXX, XXXXXX, KC_MPLY, KC_MNXT, KC_VOLU, XXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, XXXXXX, \
    ______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXX, KC_MSTP, KC_MPRV, KC_VOLD, XXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, ______, \
    ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, KC_RSFT, KC_PGUP, KC_INS, \
    ______, ______, ______, ______, ______, ______, ______, ______, KC_HOME, KC_PGDN, KC_END \
  ),
	[2] = LAYOUT_60_b_ansi( \
    TO(DEFAULT_LAYER), TO(LIGHTING_LAYER), XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX \
  ),
	[3] = LAYOUT_60_b_ansi( \
    RGB_TOG, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, ______, \
    XXXXXX, XXXXXX, XXXXXX, XXXXXX, TO(2), XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX, XXXXXX \
  ),
};

uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case DEFAULT_LAYER:
      rgblight_setrgb(0x00, 0x00, 0xFF);
      break;
    case FN_LAYER:
      rgblight_setrgb(0x00, 0xA0, 0xFF);
      break;
    case LIGHTING_LAYER:
      rgblight_setrgb(0xFF, 0x00, 0x00);
      break;
    case TO_LAYER:
      rgblight_setrgb(0xFF, 0x20, 0x00);
      break;
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
