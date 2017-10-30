// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include QMK_KEYBOARD_H
#include "action_layer.h"

enum keyboard_layers {
  QWERTY = 0, // default layer
  NUMS,     // numbers + symbols
  MOVE,     // vim-like movement
  AFK,
};

enum custom_keycodes {
  BF_AFK = SAFE_RANGE,
  BF_WAKE,
  BF_NUMS,
  BF_MOVE,
};

// Dashes (macOS)
#define KC_NDSH LALT(KC_MINS)
#define KC_MDSH S(LALT(KC_MINS))

#define VIM_B LALT(KC_LEFT)
#define VIM_W LALT(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |      |      |      |      |      |      |           | Power|      |      |      |      |      |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [   |           |   ]  |   Y  |   U  |   I  |   O  |   P  |   \    |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |Ctrl/Esc|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
  * |--------+------+------+------+------+------|  (   |           |   )  |------+------+------+------+------+--------|
  * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |Hyper |  F19 |AltShf|      | NUMS |                                       | NUMS |      |Ctrl/E|  F19 |  Meh |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |  V-  |  V+  |       | Next |Play/Pau|
  *                                 ,------|------|------|       |------+--------+------.
  *                                 |      |      |  Vx  |       | Prev |        |      |
  *                                 | Space| LGUI |------|       |------|  Bsp   | Enter|
  *                                 |      |      | LAlt |       | LAlt |        |      |
  *                                 `--------------------'       `----------------------'
  */
  // If it accepts an argument (i.e, is a function), it doesn't need KC_.
  // Otherwise, it needs KC_*
  [QWERTY] = KEYMAP(  // layer 0 : default
          // left hand
          KC_NO,        KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
          KC_TAB,       KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,
          CTL_T(KC_ESC),KC_A,  KC_S,   KC_D,   KC_F,   KC_G,
          KC_LSFT,      KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,   S(KC_9),
          ALL_T(KC_NO), KC_F19,KC_LALT,KC_NO,  BF_NUMS,
                                                        KC_VOLD,KC_VOLU,
                                                                KC_MUTE,
                                                 KC_SPC,KC_LGUI,KC_LALT,

          // right hand
          BF_AFK,      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,            KC_NO,
          KC_RBRC,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                       KC_H,   KC_J,   KC_K,   KC_L,   LT(MOVE, KC_SCLN),KC_QUOT,
          S(KC_0),     KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,
                               BF_NUMS,KC_NO,  CTL_T(KC_ESC),KC_F19,     MEH_T(KC_NO),
          KC_MNXT,KC_MPLY,
          KC_MPRV,
          KC_LALT,KC_BSPC,KC_ENT
      ),

  /* Keymap: Number Layer
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |   ⌘-`  |   `  |      |      |      |      |      |           |      |      |      |      |   -  |   =  |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |   1  |   2  |   3  |   4  |   5  |------|           |------|   6  |   7  |   8  |   9  |   0  |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        | F11  | F12  | F13  | F14  | F15  |      |           |      | F16  | F17  | F18  | F19  | F20  |        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |      |      |      |      |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |      |      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |      |      |------|       |------|      |      |
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  */
  [NUMS] = KEYMAP(
        // left hand
        KC_TRNS,     KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,   KC_TRNS,
        LGUI(KC_GRV),KC_GRV, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,
        KC_TRNS,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
        KC_TRNS,     KC_F11, KC_F12, KC_F13, KC_F14, KC_F15,  KC_TRNS,
        KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                                      KC_TRNS,KC_TRNS,
                                                              KC_TRNS,
                                              KC_TRNS,KC_TRNS,KC_TRNS,

        // right hand
        KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS, KC_MINS, KC_EQL,  KC_TRNS,
                 KC_6 ,   KC_7,   KC_8,    KC_9,    KC_0,    KC_TRNS,
        KC_TRNS, KC_F16,  KC_F17, KC_F18,  KC_F19,  KC_F20,  KC_TRNS,
                          KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
  ),

  /* Keymap 2: Movement Layer
  *
  * ,--------------------------------------------------.           ,--------------------------------------------------.
  * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  * |        |      |VIM W |      |      |      |      |           |      |  ⌘ ← |  ⌥ ← |  ⌥ → |  ⌘ → |      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      | HOME | PGUP | PGDW | END  |------|           |------|   ←  |   ↓  |   ↑  |   →  |      |        |
  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  * |        |      |      |      |      |VIM B |      |           |      |      |      |      |      |      |        |
  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  *   |      |      |      |      |      |                                       |      |      |      |      |      |
  *   `----------------------------------'                                       `----------------------------------'
  *                                        ,-------------.       ,-------------.
  *                                        |      |      |       |      |      |
  *                                 ,------|------|------|       |------+------+------.
  *                                 |      |      |      |       |      |      |      |
  *                                 |      |      |------|       |------|      |      |
  *                                 |      |      |      |       |      |      |      |
  *                                 `--------------------'       `--------------------'
  */
  [MOVE] = KEYMAP(
        // left hand
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,VIM_W,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_HOME,KC_PGUP,KC_PGDOWN,KC_END,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,VIM_B,  KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                        KC_TRNS,KC_TRNS,
                                                KC_TRNS,
                                KC_TRNS,KC_TRNS,KC_TRNS,

        // right hand
        KC_TRNS,KC_TRNS,      KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,KC_TRNS,
        KC_TRNS,LGUI(KC_LEFT),LALT(KC_LEFT),LALT(KC_RIGHT),LGUI(KC_RIGHT),KC_TRNS,KC_TRNS,
                KC_LEFT,      KC_DOWN,      KC_UP,         KC_RGHT,       KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,      KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,KC_TRNS,
                              KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,
        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS
  ),

  /* Keymap: AFK Layer
   * All keys wake
   */
  [AFK] = KEYMAP(
        // left hand
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                                                BF_WAKE,BF_WAKE,
                                                        BF_WAKE,
                                        BF_WAKE,BF_WAKE,BF_WAKE,

        // right hand
        KC_TRNS,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
                        BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,BF_WAKE,
        BF_WAKE,BF_WAKE,
        BF_WAKE,
        BF_WAKE,BF_WAKE,BF_WAKE
  ),
};

/*
 * Led Configuration
 */
extern rgblight_config_t rgblight_config;

typedef struct {
  uint16_t hue  :9;
  uint8_t  sat  :8;
  uint8_t  val  :8;
  uint8_t  mode :6;
} bf_rgb_data;

bf_rgb_data bf_rgb_config[] = {                                  // color   mode
  [QWERTY] = { .hue = 274, .sat = 255, .val = 36,  .mode = 3  }, // purple  breathing
  [MOVE]   = { .hue = 180, .sat = 255, .val = 75,  .mode = 1  }, // teal    solid
  [NUMS]   = { .hue = 120, .sat = 255, .val = 75,  .mode = 1  }, // green   solid
  [AFK]    = { .hue = 0,   .sat = 255, .val = 150, .mode = 22 }, // red     knight
};

static inline void bf_set_led(uint8_t layer) {
  bf_rgb_data cfg = bf_rgb_config[layer];

  if (rgblight_config.mode != cfg.mode) {
    rgblight_mode(cfg.mode);
  }

  rgblight_sethsv(cfg.hue, cfg.sat, cfg.val);
}

static inline void mod_layer_with_rgb(keyrecord_t *record, uint8_t layer) {
  if (record->event.pressed) {
    layer_on(layer);
    bf_set_led(layer);
  } else {
    layer_off(layer);
    uint8_t currentLayer = biton32(layer_state);
    bf_set_led(currentLayer);
  };
};

/*
 * Custom keycodes
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case BF_AFK:
      if (record->event.pressed) {
        layer_on(AFK);
        SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_POWER)SS_UP(X_LSHIFT)SS_UP(X_LCTRL));
      }
      return false; break;
    case BF_WAKE:
      if (record->event.pressed) {
        layer_off(AFK);
        SEND_STRING(" ");
      }
      return false; break;
    case BF_NUMS:
      mod_layer_with_rgb(record, NUMS);
      return false; break;
    case BF_MOVE:
      mod_layer_with_rgb(record, MOVE);
      return false; break;
  }

  return true;
};

/*
 * Active Routines
 */
void matrix_init_user(void) {
  bf_set_led(QWERTY);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
    case NUMS:
      ergodox_right_led_2_on();
    break;
    case MOVE:
      ergodox_right_led_3_on();
    break;
    case AFK:
      ergodox_right_led_1_on();
    break;
  }
};
