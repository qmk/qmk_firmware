// Copyright 2023 Vinay Komaravolu
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _MISC,
};

#define L_RAISE MO(_RAISE)
#define L_LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Default keyboard settings
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   WHOM|    |   Mute|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGui | LAlt |Enter | /Space  /       \Enter \  |BackSP |RAlt | RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_WHOM,    KC_AUDIO_MUTE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                             KC_LALT, L_LOWER,KC_LGUI, KC_SPC,   KC_ENT, KC_BSPC,  L_RAISE, KC_RALT
  ),
  [_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   KC_F7  ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12,
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  KC_CAPS, KC_SCRL, KC_NUM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
  [_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
  [_MISC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};


#ifdef RGB_MATRIX_ENABLE
/* LED 
 *  {0,0}                                                                                             {224,0}
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  5   |   4  |   3  |   2  |   1  |   0  |                    |  28  |  29  |  30  |  31  |  32  |  33  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  11  |  10  |   9  |   8  |   7  |   6  |                    |  34  |  35  |  36  |  37  |  38  |  39  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  17  |  16  |  15  |  14  |  13  |  12  |-------.    ,-------|  40  |  41  |  42  |  43  |  44  |  45  |
 * |------+------+------+------+------+------| NO LED|    |NO LED |------+------+------+------+------+------|
 * |  23  |  22  |  21  |  20  |  19  |  18  |-------|    |-------|  46  |  47  |  48  |  49  |  50  |  51  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | 27   |26    |25   |  /24     /       \52    \  |53    |54     |55    |
 *                   |      |      |     | /       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'         
 *  {64,0}                                                                                           {224,64}      
 */
const is31fl3737_led_t PROGMEM g_is31fl3737_leds[IS31FL3737_LED_COUNT] = {
    // Left half
    {0, SW3_CS1, SW1_CS1, SW2_CS1 },
    {0, SW3_CS2, SW1_CS2, SW2_CS2 },
    {0, SW3_CS3, SW1_CS3, SW2_CS3 },
    {0, SW3_CS4, SW1_CS4, SW2_CS4 },
    {0, SW3_CS5, SW1_CS5, SW2_CS5 },
    {0, SW3_CS6, SW1_CS6, SW2_CS6 },
    {0, SW3_CS7, SW1_CS7, SW2_CS7 },
    {0, SW3_CS8, SW1_CS8, SW2_CS8 },
    {0, SW3_CS9, SW1_CS9, SW2_CS9 },

    {0, SW6_CS1, SW4_CS1, SW5_CS1 },
    {0, SW6_CS2, SW4_CS2, SW5_CS2 },
    {0, SW6_CS3, SW4_CS3, SW5_CS3 },
    {0, SW6_CS4, SW4_CS4, SW5_CS4 },
    {0, SW6_CS5, SW4_CS5, SW5_CS5 },
    {0, SW6_CS6, SW4_CS6, SW5_CS6 },
    {0, SW6_CS7, SW4_CS7, SW5_CS7 },
    {0, SW6_CS8, SW4_CS8, SW5_CS8 },
    {0, SW6_CS9, SW4_CS9, SW5_CS9 },

    {0, SW9_CS1, SW7_CS1, SW8_CS1 },
    {0, SW9_CS2, SW7_CS2, SW8_CS2 },
    {0, SW9_CS3, SW7_CS3, SW8_CS3 },
    {0, SW9_CS4, SW7_CS4, SW8_CS4 },
    {0, SW9_CS5, SW7_CS5, SW8_CS5 },
    {0, SW9_CS6, SW7_CS6, SW8_CS6 },
    {0, SW9_CS7, SW7_CS7, SW8_CS7 },
    {0, SW9_CS8, SW7_CS8, SW8_CS8 },
    {0, SW9_CS9, SW7_CS9, SW8_CS9 },
    {0, SW9_CS10, SW7_CS10, SW8_CS10 }, // 28 LED left
    

    // Right half (mirrored)
    {0, SW3_CS1, SW1_CS1, SW2_CS1 },
    {0, SW3_CS2, SW1_CS2, SW2_CS2 },
    {0, SW3_CS3, SW1_CS3, SW2_CS3 },
    {0, SW3_CS4, SW1_CS4, SW2_CS4 },
    {0, SW3_CS5, SW1_CS5, SW2_CS5 },
    {0, SW3_CS6, SW1_CS6, SW2_CS6 },
    {0, SW3_CS7, SW1_CS7, SW2_CS7 },
    {0, SW3_CS8, SW1_CS8, SW2_CS8 },
    {0, SW3_CS9, SW1_CS9, SW2_CS9 },

    {0, SW6_CS1, SW4_CS1, SW5_CS1 },
    {0, SW6_CS2, SW4_CS2, SW5_CS2 },
    {0, SW6_CS3, SW4_CS3, SW5_CS3 },
    {0, SW6_CS4, SW4_CS4, SW5_CS4 },
    {0, SW6_CS5, SW4_CS5, SW5_CS5 },
    {0, SW6_CS6, SW4_CS6, SW5_CS6 },
    {0, SW6_CS7, SW4_CS7, SW5_CS7 },
    {0, SW6_CS8, SW4_CS8, SW5_CS8 },
    {0, SW6_CS9, SW4_CS9, SW5_CS9 },

    {0, SW9_CS1, SW7_CS1, SW8_CS1 },
    {0, SW9_CS2, SW7_CS2, SW8_CS2 },
    {0, SW9_CS3, SW7_CS3, SW8_CS3 },
    {0, SW9_CS4, SW7_CS4, SW8_CS4 },
    {0, SW9_CS5, SW7_CS5, SW8_CS5 },
    {0, SW9_CS6, SW7_CS6, SW8_CS6 },
    {0, SW9_CS7, SW7_CS7, SW8_CS7 },
    {0, SW9_CS8, SW7_CS8, SW8_CS8 },
    {0, SW9_CS9, SW7_CS9, SW8_CS9 },
    {0, SW9_CS10, SW7_CS10, SW8_CS10 }, // 28 LED right
}; // 56 LED total

led_config_t g_led_config = {
    // Key Matrix to LED Index
    {// Left half
     {5, 4, 3, 2, 1, 0},
     {11, 10, 9, 8, 7, 6},
     {17, 16, 15, 14, 13, 12},
     {23, 22, 21, 20, 19, 18},
     {27, 26, 25, 24, NO_LED, NO_LED},
     // Right half
     {33, 32, 31, 30, 29, 28},
     {39, 38, 37, 36, 35, 34},
     {45, 44, 43, 42, 41, 40},
     {51, 50, 49, 48, 47, 46},
     {55, 54, 53, 52, NO_LED, NO_LED}
    },
    // LED Index to Physical Position
    {
      // Left half                                                                 
                  { 86,  0}, { 68,  0}, { 51,  0}, { 34,  0}, { 17,  0}, {  0,  0}, 
                  { 86, 16}, { 68, 16}, { 51, 16}, { 34, 16}, { 17, 16}, {  0, 16}, 
                  { 86, 32}, { 68, 32}, { 51, 32}, { 34, 32}, { 17, 32}, {  0, 32}, 
                  { 86, 48}, { 68, 48}, { 51, 48}, { 34, 48}, { 17, 48}, {  0, 48}, 
      {103, 64}, { 86, 64}, { 68, 64}, { 51, 64},

      // Right half
                  {137,  0}, {155,  0}, {172,  0}, {189,  0}, {206,  0}, {224,  0},
                  {137, 16}, {155, 16}, {172, 16}, {189, 16}, {206, 16}, {224, 16},
                  {137, 32}, {155, 32}, {172, 32}, {189, 32}, {206, 32}, {224, 32},
                  {137, 48}, {155, 48}, {172, 48}, {189, 48}, {206, 48}, {224, 48},
       {120, 64}, {137, 64}, {155, 64}, {172, 64}, 

    },
    // LED Index to Flag
    {
      // Left half
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,

      // Right half
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
      LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, 
    }};
bool rgb_matrix_indicators_user(void) {
  // Set all LEDs to teal color
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
    if (i == 33) {
      rgb_matrix_set_color(i, 255, 0, 0);
      } else if (i == 24) {
      rgb_matrix_set_color(i, 0, 0,255);
    } else {
      rgb_matrix_set_color(i, 255, 0, 255);
    }
  }
  return false;
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _MISC);
    return state;
}

#ifdef OLED_ENABLE
static const char PROGMEM varys_logo[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 
0x38, 0x18, 0x38, 0x78, 0xf8, 0x70, 0x70, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xff, 0xff, 0xef, 0x1f, 0x3f, 0x7f, 
0xff, 0xfe, 0xfe, 0xff, 0xc6, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xfc, 0xff, 0x0f, 0xf7, 0xfb, 0xfd, 0x66, 0x37, 0xdf, 0xee, 
0xe4, 0x71, 0xb3, 0xc7, 0xff, 0x7f, 0xfe, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xc1, 0xfe, 0xff, 0x03, 0xff, 0xff, 0x00, 0xff, 0xff, 0x01, 
0xfe, 0xff, 0xc3, 0x99, 0x3c, 0x76, 0xef, 0x9f, 0xbf, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x7f, 0x0f, 0x07, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x80, 
0x7f, 0xff, 0xfd, 0xfb, 0x03, 0xfc, 0xff, 0xff, 0xff, 0x0f, 0x7f, 0x7e, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x7f, 0xfc, 0xf9, 0xf3, 0xe7, 0xcc, 0x99, 0x73, 
0x67, 0xee, 0xed, 0xf1, 0xfc, 0xff, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x03, 0x07, 0x07, 0x04, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x06, 0x07, 0x07, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  oled_set_cursor(0, 1);
  // Draw Logo 32x96
  oled_write_raw_P(varys_logo, sizeof(varys_logo));
  oled_set_cursor(0, 14);
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("VARYS"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE"), false);
      break;
    case _MISC:
      oled_write_P(PSTR("MISC "), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undefined"), false);
  }
  led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 9);
  oled_write_P(led_state.num_lock ? PSTR(" NUM ") : PSTR(" NUM "), false);
  oled_set_cursor(0, 10);
  oled_write_P(led_state.caps_lock ? PSTR(" CAP ") : PSTR(" CAP "), false);
  oled_set_cursor(0, 11);
  oled_write_P(led_state.scroll_lock ? PSTR(" SCR ") : PSTR(" SCR "), false);
  return false;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP),
                 ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE] = {ENCODER_CCW_CW(_______, _______),
                ENCODER_CCW_CW(_______, _______)},
    [_LOWER] = {ENCODER_CCW_CW(_______, _______),
                ENCODER_CCW_CW(_______, _______)},
    [_MISC] = {ENCODER_CCW_CW(_______, _______),
               ENCODER_CCW_CW(_______, _______)}};
#endif