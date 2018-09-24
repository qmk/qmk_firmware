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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_wrapper(
    KC_ESC,  _________________QWERTY_L1_________________,                    _________________QWERTY_R1_________________, KC_BSPC,
    KC_TAB,  _________________QWERTY_L2_________________,                    _________________QWERTY_R2_________________, KC_QUOT,
    KC_MLSF, _________________QWERTY_L3_________________,                    _________________QWERTY_R3_________________, KC_MRSF,
                           LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_COLEMAK] = LAYOUT_wrapper(
    KC_ESC,  _________________QWERTY_L1_________________,                    _________________QWERTY_R1_________________, KC_BSPC,
    KC_TAB,  _________________QWERTY_L2_________________,                    _________________QWERTY_R2_________________, KC_QUOT,
    KC_MLSF, _________________QWERTY_L3_________________,                    _________________QWERTY_R3_________________, KC_MRSF,
                           LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_DVORAK] = LAYOUT_wrapper(
    KC_ESC,  _________________QWERTY_L1_________________,                    _________________QWERTY_R1_________________, KC_BSPC,
    KC_TAB,  _________________QWERTY_L2_________________,                    _________________QWERTY_R2_________________, KC_QUOT,
    KC_MLSF, _________________QWERTY_L3_________________,                    _________________QWERTY_R3_________________, KC_MRSF,
                           LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),
  [_WORKMAN] = LAYOUT_wrapper(
    KC_ESC,  _________________QWERTY_L1_________________,                    _________________QWERTY_R1_________________, KC_BSPC,
    KC_TAB,  _________________QWERTY_L2_________________,                    _________________QWERTY_R2_________________, KC_QUOT,
    KC_MLSF, _________________QWERTY_L3_________________,                    _________________QWERTY_R3_________________, KC_MRSF,
                           LT(_LOWER,KC_GRV), KC_SPC,  KC_BSPC,         KC_DEL,  KC_ENT,  RAISE
  ),

  [_MODS] = LAYOUT_wrapper(
      _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
      KC_LSFT, _______, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, KC_RSFT,
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
                                     _______, _______, _______,        _______, _______, _______                              //`--------------------'  `--------------------'
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

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

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

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }

  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode_noeeprom(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

#endif
