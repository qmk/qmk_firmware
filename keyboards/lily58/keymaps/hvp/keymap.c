#include QMK_KEYBOARD_H
#include "hvp.c"

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NAVI 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  NAVI,
  ADJUST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT( 
  LT(3,KC_ESC),   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
  LT(_NAVI,KC_TAB),   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, 
  KC_LSFT, KC_A,   KC_S,    KC_D,    LT(4,KC_F),    LT(3,KC_G),                     KC_H,    KC_J,    KC_K,    KC_L,     TD(TD1), TD(TD2),
  KC_LCTRL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, MT(MOD_LSFT,KC_BSPC),  MT(MOD_LSFT,KC_ENTER),  KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD3),  MT(MOD_RSFT,KC_ENT),
                             KC_LALT, KC_LGUI, LOWER,LT(1,KC_SPC),   LT(2,KC_SPC),   RAISE,   KC_RALT, KC_RGUI
),
[_RAISE] = LAYOUT( /* Right */
  _______, _______, _______,  _______,  _______,  _______,                   _______, _______, _______, _______, _______, _______,  
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
  KC_DEL, _______, _______, _______, _______, _______,                      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, MT(MOD_LCTL,KC_LBRC),            MT(MOD_LALT,KC_RBRC),  _______, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_PIPE, 
                             _______, _______, _______,  _______, _______,  _______, _______, _______ 
),

[_LOWER] = LAYOUT( /* Left */
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,
  KC_TILD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_BSPC,
  KC_DEL, _______, _______, _______, _______, _______,                      _______, KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
  _______, _______, _______, _______, _______, _______, MT(MOD_LCTL,KC_LCBR),         MT(MOD_LALT,KC_RCBR),  _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TILD, 
                             _______, _______, _______,  _______, _______,  _______, _______, _______
),

 [_NAVI] = LAYOUT( /* Tab */
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                     KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, 
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, 
  _______, _______, _______, D_NAVI, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,   _______, _______, 
  _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
                             _______, KC_VOLD, KC_MPRV, KC_MSTP, KC_MPLY,  KC_MNXT, KC_VOLU, _______ 
  ),

  [_ADJUST] = LAYOUT( /* Esc */
  _______,  RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______,                   _______, KC_7, KC_8, KC_9, KC_0, _______, 
  _______, RGB_M_P, RGB_HUD, RGB_HUI, _______, _______,                   _______, KC_4, KC_5, KC_6, _______, _______, 
  KC_PSCR, _______, RGB_SAD, RGB_SAI, _______, _______,                   KC_0, KC_1, KC_2, KC_3, _______, _______, 
  QK_BOOT, _______, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, KC_VOLD, KC_MPRV, KC_MSTP, KC_MPLY,  KC_MNXT, KC_VOLU, _______ 
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

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
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}