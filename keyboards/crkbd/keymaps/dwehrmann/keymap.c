#define SPLIT_USB_DETECT

#include QMK_KEYBOARD_H

#ifndef KEYMAP_GERMAN
#define KEYMAP_GERMAN

#include "keymap.h"

// normal characters
#define DE_Z KC_Y
#define DE_Y KC_Z

#define DE_A KC_A
#define DE_B KC_B
#define DE_C KC_C
#define DE_D KC_D
#define DE_E KC_E
#define DE_F KC_F
#define DE_G KC_G
#define DE_H KC_H
#define DE_I KC_I
#define DE_J KC_J
#define DE_K KC_K
#define DE_L KC_L
#define DE_M KC_M
#define DE_N KC_N
#define DE_O KC_O
#define DE_P KC_P
#define DE_Q KC_Q
#define DE_R KC_R
#define DE_S KC_S
#define DE_T KC_T
#define DE_U KC_U
#define DE_V KC_V
#define DE_W KC_W
#define DE_X KC_X

#define DE_0 KC_0
#define DE_1 KC_1
#define DE_2 KC_2
#define DE_3 KC_3
#define DE_4 KC_4
#define DE_5 KC_5
#define DE_6 KC_6
#define DE_7 KC_7
#define DE_8 KC_8
#define DE_9 KC_9

#define DE_DOT KC_DOT
#define DE_COMM KC_COMM

#define DE_SS KC_MINS
#define DE_AE KC_QUOT
#define DE_UE KC_LBRC
#define DE_OE KC_SCLN

#define DE_CIRC KC_GRAVE // accent circumflex ^ and ring °
#define DE_ACUT KC_EQL // accent acute ´ and grave `
#define DE_PLUS KC_RBRC // + and * and ~
#define DE_HASH KC_BSLS // # and '
#define DE_LESS KC_NUBS // < and > and |
#define DE_MINS KC_SLSH // - and _

// shifted characters
#define DE_RING LSFT(DE_CIRC) // °
#define DE_EXLM LSFT(KC_1) // !
#define DE_DQOT LSFT(KC_2) // "
#define DE_PARA LSFT(KC_3) // §
#define DE_DLR  LSFT(KC_4) // $
#define DE_PERC LSFT(KC_5) // %
#define DE_AMPR LSFT(KC_6) // &
#define DE_SLSH LSFT(KC_7) // /
#define DE_LPRN LSFT(KC_8) // (
#define DE_RPRN LSFT(KC_9) // )
#define DE_EQL  LSFT(KC_0) // =
#define DE_QST  LSFT(DE_SS) // ?
#define DE_GRV  LSFT(DE_ACUT) // `
#define DE_ASTR LSFT(DE_PLUS) // *
#define DE_QUOT LSFT(DE_HASH) // '
#define DE_MORE LSFT(DE_LESS) // >
#define DE_COLN LSFT(KC_DOT) // :
#define DE_SCLN LSFT(KC_COMM) // ;
#define DE_UNDS LSFT(DE_MINS) // _

// Alt Gr-ed characters
#define DE_SQ2 ALGR(KC_2) // ²
#define DE_SQ3 ALGR(KC_3) // ³
#define DE_LCBR ALGR(KC_7) // {
#define DE_LBRC ALGR(KC_8) // [
#define DE_RBRC ALGR(KC_9) // ]
#define DE_RCBR ALGR(KC_0) // }
#define DE_BSLS ALGR(DE_SS) // backslash
#define DE_AT  ALGR(KC_Q) // @
#define DE_EURO ALGR(KC_E) // €
#define DE_TILD ALGR(DE_PLUS) // ~
#define DE_PIPE ALGR(DE_LESS) // |

#endif


extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _CONTROL 3


//Tap Dance Declarations
enum {
  TD_AE = 0,
  TD_OE,
  TD_UE,
  TD_Q,
  TD_BR_O,
  TD_BR_C
};


void dance_brackets_o (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_NUBS);
        unregister_code (KC_NUBS);
    } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_8);
        unregister_code (KC_LSFT);
        unregister_code (KC_8);
    } else if (state->count == 3) {
        register_code (KC_ALGR);
        register_code (KC_5);
        unregister_code (KC_ALGR);
        unregister_code (KC_5);
    } else if (state->count == 4) {
        register_code (KC_ALGR);
        register_code (KC_8);
        unregister_code (KC_ALGR);
        unregister_code (KC_8);
    } else {
        reset_tap_dance (state);
    }
}

void dance_brackets_c (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
        register_code (KC_NUBS);
        unregister_code (KC_LSFT);
        unregister_code (KC_NUBS);
    } else if (state->count == 2) {
        register_code (KC_LSFT);
        register_code (KC_9);
        unregister_code (KC_LSFT);
        unregister_code (KC_9);
    } else if (state->count == 3) {
        register_code (KC_ALGR);
        register_code (KC_6);
        unregister_code (KC_ALGR);
        unregister_code (KC_6);
    } else if (state->count == 4) {
        register_code (KC_ALGR);
        register_code (KC_9);
        unregister_code (KC_ALGR);
        unregister_code (KC_9);
    } else {
        reset_tap_dance (state);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_AE]  = ACTION_TAP_DANCE_DOUBLE(KC_A, DE_AE),
  [TD_OE]  = ACTION_TAP_DANCE_DOUBLE(KC_O, DE_OE),
  [TD_UE]  = ACTION_TAP_DANCE_DOUBLE(KC_U, DE_UE),
  [TD_Q]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, LALT(KC_L)),
  [TD_BR_O] = ACTION_TAP_DANCE_FN(dance_brackets_o),
  [TD_BR_C] = ACTION_TAP_DANCE_FN(dance_brackets_c),
// Other declarations would go here, separated by commas, if you have them
};





enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  CONTROL,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    TD(TD_Q),    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    TD(TD_UE),    DE_Y,   DE_PLUS,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LSFT, KC_TAB),    TD(TD_AE),    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I, TD(TD_OE), DE_HASH,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DE_Z,    KC_X,    KC_C,    KC_V,    DE_COMM,                         DE_DOT,    KC_B, KC_K,  KC_M, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |-------+---------+--------+--------+--------+--------+--------|
                                          KC_LALT,   KC_LGUI,  KC_SPC,     KC_ENT,  LOWER,  RAISE \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_COPY,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PASTE,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      MT(MOD_LSFT, KC_TAB), LALT(KC_L), XXXXXXX, DE_SS, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD(TD_BR_O),                   TD(TD_BR_C), KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   KC_LGUI,  KC_SPC,     KC_ENT,   LOWER, RAISE \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_AMPR , KC_AMPR, KC_AMPR, KC_PIPE,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   KC_LGUI,  KC_SPC,     KC_ENT,   LOWER, RAISE \
                                      //`--------------------------'  `--------------------------'
  ),

  [_CONTROL] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  RGBRST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER,  KC_SPC,     KC_ENT,   RAISE, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting CONTROL layer RGB back to default
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
    //matrix_write_ln(matrix, read_keylogs());
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
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _CONTROL);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _CONTROL);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _CONTROL);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _CONTROL);
      }
      return false;
    case CONTROL:
        if (record->event.pressed) {
          layer_on(_CONTROL);
        } else {
          layer_off(_CONTROL);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
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
