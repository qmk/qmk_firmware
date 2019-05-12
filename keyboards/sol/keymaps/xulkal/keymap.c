#include QMK_KEYBOARD_H
#include "xulkal.h"

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#ifdef OLED_DRIVER_ENABLE
  #include "oled_driver.h"
#endif

#define EXPAND_LAYOUT(...) LAYOUT(__VA_ARGS__)

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
   * | Sft[ |   Z  |   X  |   C  |  V   |  B   | RGB  |  |RGBRST|  N   |  M   |  ,   |  .   |  /   | Sft] |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctl- |  Win | LOWER| RAISE| Alt  | Space|RGBRMOD| |RGBMOD| Space| Left |  Up  | Down | Right| Ctl= |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = EXPAND_LAYOUT( \
    _________________QWERTY_L1_________________,  KC_MINS,  KC_EQL,   _________________QWERTY_R1_________________, \
    _________________QWERTY_L2_________________,  KC_LBRC,  KC_RBRC,  _________________QWERTY_R2_________________, \
    _________________QWERTY_L3_________________,  KC_GRV,   KC_QUOT,  _________________QWERTY_R3_________________, \
    _________________QWERTY_L4_________________,  RGB_TOG,  RGBRST,   _________________QWERTY_R4_________________, \
    _________________QWERTY_L5_________________,  RGB_RMOD, RGB_MOD,  _________________QWERTY_R5_________________, \
                                         KC_SPC,  KC_DEL,   KC_ENT,   KC_SPC \
  ),

#ifndef GAMELAYER_DISABLE
  [_GAME] = EXPAND_LAYOUT( \
    ___________________GAME_L1_________________,  KC_MINS,  KC_EQL,   ___________________GAME_R1_________________, \
    ___________________GAME_L2_________________,  KC_LBRC,  KC_RBRC,  ___________________GAME_R2_________________, \
    ___________________GAME_L3_________________,  KC_GRV,   KC_QUOT,  ___________________GAME_R3_________________, \
    ___________________GAME_L4_________________,  RGB_TOG,  RGBRST,   ___________________GAME_R4_________________, \
    ___________________GAME_L5_________________,  RGB_RMOD, RGB_MOD,  ___________________GAME_R5_________________, \
                                         KC_SPC,  KC_DEL,   KC_ENT,   KC_SPC \
  ),
#endif

  [_LOWER] =  EXPAND_LAYOUT( \
    __________________LOWER_L1_________________, KC_PMNS, KC_PPLS, __________________LOWER_R1_________________, \
    __________________LOWER_L2_________________, _______, _______, __________________LOWER_R2_________________, \
    __________________LOWER_L3_________________, _______, _______, __________________LOWER_R3_________________, \
    __________________LOWER_L4_________________, _______, _______, __________________LOWER_R4_________________, \
    __________________LOWER_L5_________________, _______, _______, __________________LOWER_R5_________________, \
                                        _______, _______, _______, _______ \
  ),

  [_RAISE] = EXPAND_LAYOUT( \
    __________________RAISE_L1_________________, _______, _______, __________________RAISE_R1_________________, \
    __________________RAISE_L2_________________, _______, _______, __________________RAISE_R2_________________, \
    __________________RAISE_L3_________________, _______, _______, __________________RAISE_R3_________________, \
    __________________RAISE_L4_________________, _______, _______, __________________RAISE_R4_________________, \
    __________________RAISE_L5_________________, _______, _______, __________________RAISE_R5_________________, \
                                        _______, _______, _______, _______ \
  ),

#ifdef TRILAYER_ENABLED
  [_RAISE] = EXPAND_LAYOUT( \
    _________________ADJUST_L1_________________, _______, _______, _________________ADJUST_R1_________________, \
    _________________ADJUST_L2_________________, _______, _______, _________________ADJUST_R2_________________, \
    _________________ADJUST_L3_________________, _______, _______, _________________ADJUST_R3_________________, \
    _________________ADJUST_L4_________________, _______, _______, _________________ADJUST_R4_________________, \
    _________________ADJUST_L5_________________, _______, _______, _________________ADJUST_R5_________________, \
                                        _______, _______, _______, _______ \
  ),
#endif
};

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(sol_logo, false);
}


static void render_status(void) {
  // Render to mode icon
  static const char PROGMEM mode_logo[2][3] = {
    {0x97,0x98,0},
    {0xb7,0xb8,0} };

    oled_write_P(mode_logo[0], false);

#if defined(RGB_MATRIX_ENABLE)
    static char buffer[20] = {0};
    snprintf(buffer, sizeof(buffer), "    h%3d s%3d v%3d\n", rgb_matrix_config.hue, rgb_matrix_config.sat, rgb_matrix_config.val);
    oled_write(buffer, false);
#endif

    oled_write_P(mode_logo[1], false);

#if defined(RGB_MATRIX_ENABLE)
    snprintf(buffer, sizeof(buffer), "         s%3d m%3d\n", rgb_matrix_config.speed, rgb_matrix_config.mode);
    oled_write(buffer, false);
#endif

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  oled_write_P(PSTR("Layer: "), false);
  switch (biton32(layer_state)) {
    case _QWERTY:
#ifndef GAMELAYER_DISABLE
      switch (biton32(default_layer_state)) {
        case _QWERTY:
          oled_write_P(PSTR("Default\n"), false);
          break;
        case _GAME:
          oled_write_P(PSTR("Game\n"), false);
          break;
        default:
          oled_write_P(PSTR("Undefined\n"), false);
          break;
      }
#else
      oled_write_P(PSTR("Default\n"), false);
#endif
      break;
    case _LOWER:
      oled_write_P(PSTR("Lower\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("Raise\n"), false);
      break;
#ifdef TRILAYER_ENABLED
    case _ADJUST:
      oled_write_P(PSTR("Adjust\n"), false);
      break;
#endif
    default:
      oled_write_P(PSTR("Undefined\n"), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif
