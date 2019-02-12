#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef OLED_ENABLE
#include "common/ssd1306.h"
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
enum layer_number {
    _QWERTY = 0,
    _FN,
    _ADJ
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RGBRST
};

#define FN_CAPS  LT(_FN, KC_CAPS)
#define FN       MO(_FN)
#define ADJ      MO(_ADJ)

// Define your non-alpha grouping in this define's LAYOUT, and all your BASE_LAYERS will share the same mod/macro columns

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty Layout
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |  3   |  4   |  5   |   -  |  |   =  |  6   |  7   |  8   |  9   |  0   | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |  E   |  R   |  T   |   [  |  |   ]  |  Y   |  U   |  I   |  O   |  P   |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |  F   |  G   |   `  |  |   '  |  H   |  J   |  K   |  L   |  ;   | Enter|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |  V   |  B   | RGB  |  |      |  N   |  M   |  ,   |  .   |  /   | Shift|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  ADJ |  FN  | Alt  | Space|RGBRMOD| |RGBMOD|Space|Left |  Up  | Down | Right| Ctrl |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,  KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSLS, \
      FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_GRV,   KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_ENT, \
      KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    RGB_TOG,  _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSPC, \
      KC_LCTL, KC_LGUI, ADJ,     FN,      KC_LALT, KC_SPC,  RGB_RMOD, RGB_MOD, KC_SPC,  KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, KC_RCTL, \
                        KC_VOLU, KC_VOLD,          KC_SPC,  KC_DEL,   KC_ENT,  KC_SPC,           KC_VOLU, KC_VOLD \
      ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |  | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      | INS  | HOME | PGUP | PRINT|      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | DEL  | END  | PGDN |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      | PLAY |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      | PREV | VOL- | VOL+ | NEXT |      |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
      _______, KC_PGDN, KC_UP,   KC_PGUP, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, KC_PSCR, _______, \
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, \
                        KC_VOLU, KC_VOLD,          _______, _______, _______, _______,          KC_VOLU, KC_VOLD \
      ),

  /* ADJ
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |      |      |      |      |      |      |   -  |  |   +  |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | SAI  | VAI  | SAI  | RESET|      |      |  |      |  1   |  2   |  3   |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | SAD  | VAD  | HUI  |RGBRST|      |      |  |      |  4   |  5   |  6   |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |  7   |  8   |  9   |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |  0   |  .   |      |      |      |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */

  [_ADJ] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______, KC_PMNS, KC_PPLS, _______, _______, _______, _______, _______, _______, \
      _______, RGB_SAI, RGB_VAI, RGB_HUI, RESET,   _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, \
      _______, RGB_SAD, RGB_VAD, RGB_HUD, RGBRST,  _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_PDOT, _______, _______, _______, \
                        KC_VOLU, KC_VOLD,          _______, _______, _______, _______,          KC_VOLU, KC_VOLD \
      )
};


// define variables for reactive RGB
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef OLED_ENABLE
    // Wake up oled if user is at the keyboard
    if (record->event.pressed)
      oled_on();
  #endif

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
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

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  RGB_current_mode = rgblight_config.mode;
#endif
//SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_ENABLE
  oled_init(!has_usb());   // turns on the display
#endif
}


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_ENABLE

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(sol_logo, false);
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_FN (1<<_FN)
#define L_ADJ (1<<_ADJ)
#define L_ADJ_TRI (L_ADJ|L_FN)

static void render_status(void) {
  // Render to mode icon
  static const char PROGMEM mode_logo[4][4] = {
    {0x95,0x96,0x0a,0},
    {0xb5,0xb6,0x0a,0},
    {0x97,0x98,0x0a,0},
    {0xb7,0xb8,0x0a,0} };

  if (keymap_config.swap_lalt_lgui != false) {
    oled_write_P(mode_logo[0], false);
    oled_write_P(mode_logo[1], false);
  } else {
    oled_write_P(mode_logo[2], false);
    oled_write_P(mode_logo[3], false);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  oled_write_P(PSTR("Layer: "), false);
  switch (layer_state) {
    case L_BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case L_FN:
      oled_write_P(PSTR("FN     \n"), false);
      break;
    case L_ADJ:
    case L_ADJ_TRI:
      oled_write_P(PSTR("ADJ    \n"), false);
      break;
    default:
      oled_write_P(PSTR("UNDEF  \n"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUM ") : PSTR("    "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAP ") : PSTR("    "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCR ") : PSTR("    "), false);
}

void matrix_scan_user(void) {
  if (!oled_ready())
    return;

  oled_set_cursor(0, 0);
  if (is_master)
    render_status();
  else
    render_logo();
  oled_render();
}

#endif