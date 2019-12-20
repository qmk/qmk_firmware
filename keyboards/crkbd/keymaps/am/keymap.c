#include QMK_KEYBOARD_H

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _TOUCHCURSOR 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// Tap-dance
enum {
    TD_GUI_ALT = 0
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Gui, twice for Alt
    [TD_GUI_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LALT)
};

#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RESET RESET
#define KC_VUP KC__VOLUP
#define KC_VDW KC__VOLDOWN
#define KC_LT_TC LT(_TOUCHCURSOR, KC_SPC) // L-ayer T-ap T-ouch C-ursor
#define KC_CT_ESC CTL_T(KC_ESC)
#define KC_SF_EN RSFT_T(KC_ENTER)
// GUI on tap/hold | ALT on double-tap/hold
#define KC_GUI_ALT TD(TD_GUI_ALT)
// GUI + ALT
#define KC_GUIAL OSM(MOD_LGUI | MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CT_ESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, SF_EN, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                GUI_ALT, LOWER, GUIAL,    LT_TC, RAISE, ENTER \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       TILD,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  TRNS, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       PIPE,    F1,    F2,    F3,    F4,    F5,                     F6,  MINS,  PLUS,  LCBR,  RCBR,   GRV, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       BSLS,    F7,    F8,    F9,   F10,   F11,                    F12,  UNDS,   EQL,  LBRC,  RBRC,  SLSH, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                GUI_ALT, LOWER, GUIAL,    LT_TC, RAISE, ENTER \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
          0,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  TRNS, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         NO,     4,     5,     6,    NO,    NO,                   PPLS,     4,     5,     6,    NO,   DLR, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         NO,     7,     8,     9,     0,    NO,                   PMNS,     1,     2,     3,    NO,  PENT, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                GUI_ALT, LOWER, GUIAL,    LT_TC, RAISE, ENTER \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      RESET, POWER,    NO,    NO,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,    NO, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         NO,    NO,    NO,    NO,    NO,    NO,                   MPRV,  MPLY,  MNXT,    NO,    NO,    NO, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
         NO,    NO,    NO,    NO,    NO,    NO,                  _MUTE,   VDW,   VUP,    NO,    NO,    NO, \
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                     NO,    NO,    NO,       NO,    NO,    NO \
                              //`--------------------'  `--------------------'
  ),

  [_TOUCHCURSOR] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       TRNS,    NO,    NO,    NO,    NO,    NO,                     NO,    NO,    NO,    NO,    NO,  TRNS, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,    NO,    NO,    NO,    NO,    NO,                   LEFT,  DOWN,    UP,  RGHT,    NO,  TRNS, \
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TRNS,    NO,    NO,    NO,    NO,    NO,                   MS_L,  MS_D,  MS_U,  MS_R,    NO,  TRNS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                GUI_ALT, LOWER, GUIAL,    LT_TC, RAISE, ENTER \
                              //`--------------------'  `--------------------'
  )
};

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
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
      break;
  }
  return true;
}
