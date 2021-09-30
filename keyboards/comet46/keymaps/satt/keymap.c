// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"
#include "keymap_jp.h"
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PSEUDO_US,
  _PSEUDO_US_LOWER,
  _PSEUDO_US_RAISE,
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  PSEUDO_US,
  JIS2US,
};

// JIS keycodes
#define KC_JZHT JP_ZKHK  // hankaku/zenkaku|kanzi
#define KC_JCIR JP_CIRC  // ^, ~
#define KC_JAT  JP_AT    // @, `
#define KC_JLBR JP_LBRC  // [, {
#define KC_JCOL JP_COLN  // :, *
#define KC_JRBR JP_RBRC  // ], }
#define KC_JBSL JP_BSLS  // \, _
#define KC_JMHE JP_MHEN  // muhenkan
#define KC_JHEN JP_HENK  // henkan
#define KC_JKAN JP_KANA  // katakana/hiragana|ro-mazi
#define KC_JMKA JP_LANG1 //kana on MacOSX
#define KC_JMEI KC_LANG2 //eisu on MacOSX
#define KC_JAMP JP_AMPR  // &
#define KC_JQUO JP_QUOT  // '
#define KC_JLPR JP_LPRN  // (
#define KC_JRPR JP_RPRN  // )
#define KC_JEQL JP_EQL   // =
#define KC_JTIL JP_TILD  // ~
#define KC_JPIP JP_PIPE  // |
#define KC_JGRV JP_GRV   // `
#define KC_JLCB JP_LCBR  // {
#define KC_JPLU JP_PLUS  // +
#define KC_JAST JP_ASTR  // *
#define KC_JRCB JP_RCBR  // }
#define KC_JUND JP_UNDS  // _

// Layer related keycodes
#define KC_LWR  MO(_LOWER)
#define KC_RSE  MO(_RAISE)
#define KC_P_LW MO(_PSEUDO_US_LOWER)
#define KC_P_RS MO(_PSEUDO_US_RAISE)
#define KC_QWRT QWERTY
#define KC_P_US PSEUDO_US
#define KC_J2US JIS2US

// Special keycodes
#define KC_SPCT CTL_T(KC_SPC)
#define KC_ENSF SFT_T(KC_ENT)
#define KC_CAEC MT(MOD_LCTL | MOD_LALT, KC_ESC)
#define KC_CSTB C_S_T(KC_TAB)
#define KC_IMON ALT_T(KC_F13)
#define KC_IMOF GUI_T(KC_F14)
#define KC_CAD LCA(KC_DEL)
#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     KC_CAEC, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                 KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     KC_CSTB, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,KC_LPRN,      KC_RPRN, KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_LBRC,      KC_RBRC, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_QUOT,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         KC_IMOF,KC_LWR ,KC_SPCT,      KC_ENSF,KC_RSE ,KC_IMON
  //                    +----+----+---/       \---+----+----+
  ),

  [_LOWER] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     _______,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,      KC_GRV ,KC_BSLS,KC_MINS,KC_EQL ,KC_LBRC,KC_RBRC,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     _______, KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11, KC_F12,      KC_TILD,KC_PIPE,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         _______,_______,_______,      _______,_______,_______
  //                    +----+----+---/       \---+----+----+
  ),

  [_RAISE] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     _______, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                 KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,_______,      XXXXXXX,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,KC_END ,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,_______,      KC_HOME,XXXXXXX,KC_PGDN,KC_PGUP,XXXXXXX,XXXXXXX,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         _______,_______,_______,      _______,_______,_______
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     KC_CAEC, KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                 KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_DEL ,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     KC_CSTB, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,KC_JLPR,      KC_JRPR, KC_H  , KC_J  , KC_K  , KC_L  ,KC_J2US,KC_BSPC,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,KC_J2US,      KC_J2US, KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_J2US,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         KC_IMOF,KC_P_LW,KC_SPCT,      KC_ENSF,KC_P_RS,KC_IMON
  //                    +----+----+---/       \---+----+----+
  ),


  [_PSEUDO_US_LOWER] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     _______,KC_EXLM,KC_JAT ,KC_HASH,KC_DLR ,KC_PERC,                KC_JCIR,KC_JAMP,KC_JAST,KC_JLPR,KC_JRPR,_______,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     _______, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,      KC_JGRV,KC_JBSL,KC_MINS,KC_JEQL,KC_JLBR,KC_JRBR,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     _______, KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11, KC_F12,      KC_JTIL,KC_JPIP,KC_JUND,KC_JPLU,KC_JLCB,KC_JRCB,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         _______,_______,_______,      _______,_______,_______
  //                    +----+----+---/       \---+----+----+
  ),

  [_PSEUDO_US_RAISE] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     _______, KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                 KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,_______,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,KC_JZHT,      XXXXXXX,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,KC_END ,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,_______,      KC_HOME,XXXXXXX,KC_PGDN,KC_PGUP,XXXXXXX,XXXXXXX,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         _______,_______,_______,      _______,_______,_______
  //                    +----+----+---/       \---+----+----+
  ),

  [_ADJUST] = LAYOUT(
  //,----+----+----+----+----+----+               +----+----+----+----+----+----.
     _______,_______,_______,_______,_______,_______,                _______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----+----+     +----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,KC_CAD ,      KC_QWRT,_______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
     _______,_______,_______,_______,_______,_______,KC_RST ,      KC_P_US,_______,_______,_______,_______,_______,_______,
  //|----+----+----+----+----+----+----|     |----+----+----+----+----+----+----|
                         _______,_______,_______,      _______,_______,_______
  //                    +----+----+---/       \---+----+----+
  )

};

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (biton32(state)) {
    case _PSEUDO_US_LOWER:
    case _PSEUDO_US_RAISE:
      return update_tri_layer_state(state, _PSEUDO_US_RAISE, _PSEUDO_US_LOWER, _ADJUST);
      break;
    default:
      return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
      break;
  }
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// You need to add source files to SRC in rules.mk when using OLED display functions
void set_keylog(uint16_t keycode);
const char *read_keylog(void);
const char *read_modifier_state(void);
const char *read_host_led_state(void);

void matrix_init_user(void) {
  iota_gfx_init(false);   // turns on the display
}

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void render_status(struct CharacterMatrix *matrix) {
  // Layer state
  char layer_str[22];
  matrix_write(matrix, "Layer: ");
  uint8_t layer = biton32(layer_state);
  uint8_t default_layer = biton32(eeconfig_read_default_layer());
    switch (layer) {
      case _QWERTY:
        switch (default_layer) {
          case _QWERTY:
            snprintf(layer_str, sizeof(layer_str), "Qwerty");
            break;
          case _PSEUDO_US:
            snprintf(layer_str, sizeof(layer_str), "Psuedo_US");
            break;
          default:
            snprintf(layer_str, sizeof(layer_str), "Undef-%d", default_layer);
            break;
        }
        break;
      case _RAISE:
        snprintf(layer_str, sizeof(layer_str), "Raise");
        break;
      case _LOWER:
        snprintf(layer_str, sizeof(layer_str), "Lower");
        break;
      case _PSEUDO_US_RAISE:
        snprintf(layer_str, sizeof(layer_str), "P_US_Raise");
        break;
      case _PSEUDO_US_LOWER:
        snprintf(layer_str, sizeof(layer_str), "P_US_Lower");
        break;
      case _ADJUST:
        snprintf(layer_str, sizeof(layer_str), "Adjust");
        break;
      default:
        snprintf(layer_str, sizeof(layer_str), "Undef-%d", layer);
    }
  matrix_write_ln(matrix, layer_str);
  // Last entered keycode
  matrix_write_ln(matrix, read_keylog());
  // Modifier state
  matrix_write_ln(matrix, read_modifier_state());
  // Host Keyboard LED Status
  matrix_write(matrix, read_host_led_state());
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  render_status(&matrix);
  matrix_update(&display, &matrix);
}

#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef SSD1306OLED
    if (record->event.pressed) {
      set_keylog(keycode);
    }
  #endif
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      break;
    case PSEUDO_US:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PSEUDO_US);
      }
      break;
    case JIS2US:
      action_pseudo_lut(record, _QWERTY, keymap_jis2us);
      break;
  }
  return true;
}
