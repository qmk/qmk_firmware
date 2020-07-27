#include "kopesh.h"
#include QMK_KEYBOARD_H
#include <string.h>
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif


enum custom_keycodes {KC_PASTA = SAFE_RANGE};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
  KC_GESC,        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_NO,           KC_BSPACE, KC_Y, KC_U, KC_I, KC_O, KC_P,                           KC_BSPACE, KC_DELETE, KC_MPLY, \
  CTL_T(KC_TAB),  KC_A, KC_S, KC_D, KC_F, KC_G, KC_G,            KC_QUOT,   KC_H, KC_J, KC_K, KC_L, LT(3, KC_ENT),                  KC_ENT,  KC_UP,   KC_PIPE,   \
  KC_LSFT,    KC_Z, KC_X, KC_C, KC_V, KC_B, LT(2, KC_SPC),   LT(1, KC_SPC), KC_N, KC_M, ALT_T(KC_COMM), GUI_T(KC_DOT), KC_RSFT, KC_LEFT, KC_DOWN, KC_RIGHT   \
),
  [1] = LAYOUT(
  KC_GRV,         KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO,                      KC_TRNS, KC_6, KC_7, KC_8, KC_9, KC_0,                  KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_MINS, KC_EQL, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_SCLN, KC_UP,   KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS  \
),

  [2] = LAYOUT(
  KC_TRNS,        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_UNDS, KC_PLUS, KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS,      KC_COLN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUES, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS  \
),

  [3] = LAYOUT(
  RESET,          KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO,                  KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,             KC_F12,  KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS  \
)

};


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(false);   // turns on the display
    #endif
}


// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (true) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}


void led_set_user(uint8_t usb_led) {

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_COMPOSE)) {
    
  } else {
    
  }

  if (usb_led & (1 << USB_LED_KANA)) {
    
  } else {
    
  }

}