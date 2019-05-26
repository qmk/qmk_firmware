#include QMK_KEYBOARD_H
#include "bootloader.h"
#include "keymap_french_osx.h"
#include "keymap_bepo.h"
#include "sendstring_bepo.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO  0
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define _______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_ZI    ZI
#define KC_ZO    ZO
#define COPY     RGUI(BP_C)
#define PASTE    RGUI(BP_V)
#define SAVE     RGUI(BP_S)
#define CTAB     RGUI(BP_TAB)
#define ALTSFT   RALT(KC_LSFT)
#define BP_TAB   KC_TAB
#define BP_RCTL  KC_RCTL
#define BP_RGUI  KC_RGUI
#define BP_LOWR  KC_LOWR
#define BSPC     KC_BSPC
#define BP_ENT   KC_ENT
#define BP_RASE  KC_RAISE
#define BP_SPC   KC_SPC
#define BP_RALT  KC_RALT
#define BP_SPC   KC_SPC
#define BP_WSH   MT(MOD_LSFT, BP_W)
#define BP_SPSFT MT(MOD_RSFT, BP_SPC)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.    ,-------+--------+---------+--------+--------+---------.
    BP_TAB , BP_B   , BP_ECUT, BP_P   , BP_O   , BP_EGRV,     BP_DCRC, BP_V   , BP_D    , BP_L   , BP_J   , BP_Z ,
  //,------+--------+--------+--------+--------+--------.    ,-------+--------+---------+--------+--------+---------.
    BP_W   , BP_A   , BP_U   , BP_I   , BP_E   , BP_COMM,     BP_C   , BP_T   , BP_S    , BP_R   , BP_N   , BP_M,
  //,------+--------+--------+--------+--------+--------+    ,-------+--------+---------+--------+--------+---------.
    KC_LSFT,BP_AGRV, BP_Y  , BP_X   , BP_DOT    , BP_K   ,     BP_APOS, BP_Q   , BP_G    , BP_H   , BP_F   , BP_CCED,
  //,------+--------+--------+--------+--------+--------+    ,-------+--------+---------+--------+--------+---------.
                               BP_RALT, BP_RGUI, BP_RASE ,   BP_SPSFT, BP_ENT , BSPC
  ),

  [_RAISE] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.   ,-------+--------+---------+--------+--------+---------.
    BP_DLR , BP_DQOT, BP_LGIL, BP_RGIL, BP_LPRN, BP_RPRN,    BP_AT  , BP_PLUS, BP_MINUS, BP_SLSH, BP_ASTR, BP_EQUAL,
  //,------+--------+--------+--------+--------+--------.   ,-------+--------+---------+--------+--------+---------.
    _______, _______ ,_______ , _______, KC_UP , BP_SPC ,    _______, _______ , _______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+   ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT,    KC_ESC , _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+   ,-------+--------+---------+--------+--------+---------.
                               BP_RALT, BP_RGUI, _______,    KC_RCTRL,BP_ENT , BSPC
  ),

  [_LOWER] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,    _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------.    ,-------+--------+---------+--------+--------+---------.
    _______, _______, SAVE   , COPY   , PASTE  , CTAB   ,    _______, _______, _______  , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+    ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, BP_RALT, ALTSFT,     _______, _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+    ,-------+--------+---------+--------+--------+---------.
                               _______, _______, _______,    _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
  //,------+--------+--------+--------+--------+--------.   ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,   _______, _______, _______  , _______, _______ ,  KC_RST,
  //,------+--------+--------+--------+--------+--------.   ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,    _______, _______, _______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+   ,-------+--------+---------+--------+--------+---------.
    _______, _______, _______, _______, _______, _______,    _______, _______ ,_______ , _______, _______ , _______,
  //,------+--------+--------+--------+--------+--------+   ,-------+--------+---------+--------+--------+---------.
                               _______, _______, _______,    _______, _______, _______
  )

};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
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

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }

  switch (keycode) {
    case BEPO:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_BEPO);
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
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
  }
  return true;
}

#endif
