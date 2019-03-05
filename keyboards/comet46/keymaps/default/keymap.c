// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum comet46_layers
{
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------+                    +-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Ctl  |   A  |   S  |   D  |   F  |   G  | Esc  |      | Del  |   H  |   J  |   K  |   L  |   ;  |   "  |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   {  |      |   }  |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             | GUI  | Lower| Space|      | Enter| Raise| Alt  |
   *                             +--------------------/      \--------------------+
   */
  [_QWERTY] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_ESC,         KC_DEL,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,        KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                        KC_LGUI, LOWER,   KC_SPC,         KC_ENT,  RAISE,   KC_LALT
  ),

  /* Colemak
   * ,-----------------------------------------+                    +-----------------------------------------.
   * | Tab  |   Q  |   W  |   F  |   P  |   G  |                    |   J  |   L  |   U  |   Y  |   ;  | Bksp |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Ctl  |   A  |   R  |   S  |   T  |   D  | Esc  |      | Del  |   H  |   N  |   E  |   I  |   O  |   "  |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   {  |      |   }  |   K  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             | GUI  | Lower| Space|      | Enter| Raise| Alt  |
   *                             +--------------------/      \--------------------+
   */
  [_COLEMAK] = LAYOUT(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                             KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_ESC,         KC_DEL,  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR,        KC_RCBR, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                        KC_LGUI, LOWER,   KC_SPC,         KC_ENT,  RAISE,   KC_LALT
  ),

  /* Dvorak
   * ,-----------------------------------------+                    +-----------------------------------------.
   * | Tab  |   "  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  | Bksp |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Ctl  |   A  |   O  |   E  |   U  |   I  | Esc  |      | Del  |   D  |   H  |   T  |   N  |   S  |  /   |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  |   {  |      |   }  |   B  |   M  |   W  |   V  |   Z  | Shift|
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             | GUI  | Lower| Space|      | Enter| Raise| Alt  |
   *                             +--------------------/      \--------------------+
   */
  [_DVORAK] = LAYOUT(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                             KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_ESC,         KC_DEL,  KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LCBR,        KC_RCBR, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
                                        KC_LGUI, LOWER,   KC_SPC,         KC_ENT,  RAISE,   KC_LALT
  ),

  /* Lower
   * ,-----------------------------------------+                    +-----------------------------------------.
   * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   `  |   \  |   -  |   =  |   [  |   ]  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   ~  |   |  |   _  |   +  |   {  |   }  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             |      |      |      |      |      |      |      |
   *                             +--------------------/      \--------------------+
   */
  [_LOWER] = LAYOUT(
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    _______, _______, _______, _______, _______, _______, _______,        KC_GRV,  KC_BSLS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,
    _______, _______, _______, _______, _______, _______, _______,        KC_TILD, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
                                        _______, _______, _______,        _______, _______, _______
  ),

  /* Raise
   * ,-----------------------------------------+                    +-----------------------------------------.
   * |      |   1  |   2  |   3  |   4  |   5  |                    |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      | Left | Down |  Up  |Right | End  |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      | Home |      | PgDn | PgUp |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             |      |      |      |      |      |      |      |
   *                             +--------------------/      \--------------------+
   */
  [_RAISE] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  _______,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,         KC_HOME, XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, _______,
                                        _______, _______, _______,        _______, _______, _______
  ),

  /* Adjust
   * ,-----------------------------------------+                    +-----------------------------------------.
   * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |Qwerty|      |Colemk|      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |Reset |      |Dvorak|      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+      +------+------+------+------+------+-------------|
   *                             |      |      |      |      |      |      |      |
   *                             +--------------------/      \--------------------+
   */
  [_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, QWERTY,         COLEMAK, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, RESET,          DVORAK,  _______, _______, _______, _______, _______, _______,
                                        _______, _______, _______,        _______, _______, _______
  )
};


uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
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
        case _COLEMAK:
          snprintf(layer_str, sizeof(layer_str), "Colemak");
          break;
        case _DVORAK:
          snprintf(layer_str, sizeof(layer_str), "Dvorak");
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
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      break;
  }
  return true;
}
