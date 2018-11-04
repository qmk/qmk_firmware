#include QMK_KEYBOARD_H
#include "drashna.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum crkbd_keycodes {
  RGBRST = NEW_SAFE_RANGE
};

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    KC_TAB,  K11,    K12,     K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29,  CTL_T(K2A), OS_RSFT, \
                           LT(_LOWER,KC_GRV), KC_SPC,  LALT_T(KC_BSPC),  KC_DEL,  KC_ENT,  RAISE                                    \
  )
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_crkbd_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_crkbd_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_crkbd_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_MODS] = LAYOUT_wrapper(
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      KC_LSFT, ___________________BLANK___________________,                  ___________________BLANK___________________, KC_RSFT,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_LOWER] = LAYOUT_wrapper(
    KC_TILD, _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, KC_BSPC,
    KC_F11,  _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, KC_PIPE,
    KC_F12,  _________________LOWER_L3__________________,                    _________________LOWER_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper( \
    KC_GRV,  _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, KC_BSPC,
    _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________,                    _________________RAISE_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    KC_MAKE, _________________ADJUST_L1_________________,                    _________________ADJUST_R1_________________, KC_RESET,
    VRSN,    _________________ADJUST_L2_________________,                    _________________ADJUST_R2_________________, EPRM,
    TG_MODS, _________________ADJUST_L3_________________,                    _________________ADJUST_R3_________________, KC_MPLY,
                                     _______, _______, _______,        _______, _______, _______
  )
};

int RGB_current_mode;

void matrix_init_keymap(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif

  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
char layer_state_str[24];
// const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);


const char* read_layer_state(void) {
  switch (layer_state) {
    case _QWERTY:
      switch (default_layer_state) {
        case _QWERTY:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
          break;
        case _COLEMAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Colemak");
          break;
        case _DVORAK:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Dvorak");
          break;
        case _WORKMAN:
          snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Workman");
          break;
      }
      break;
    case _RAISE:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
      break;
    case _LOWER:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
      break;
    case _ADJUST:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Adjust");
      break;
    default:
      snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

    return layer_state_str;
}

void matrix_scan_keymap(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    matrix_write_ln(matrix, read_host_led_state());
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

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }
  return true;
}

#endif
