#include QMK_KEYBOARD_H

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    FUNC,         // 0x02
    SETTINGS,     // 0x04
};

// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
  // Layer     Mask           Red     Green   Blue
  {0x00000000, 0xFFFFFFFF, {0x0000, 0x0FFF, 0x0000}}, // base layer - green
  {0x00000002, 0xFFFFFFFE, {0x0000, 0x0000, 0x0FFF}}, // function layer - blue
  {0x00000004, 0xFFFFFFFC, {0x0FFF, 0x0000, 0x0FFF}}, // settings layer - magenta
  {0xFFFFFFFF, 0xFFFFFFFF, {0x0FFF, 0x0FFF, 0x0FFF}}, // unknown layer - REQUIRED - white
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap VANILLA: (Base Layer) Default Layer
   * ,---------.  ,------------------------------------------------------------.  ,---------.
   * | F1 | F2 |  |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa|  | Ins|PgUp|
   * |---------|  |------------------------------------------------------------|  |---------|
   * | F3 | F4 |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|  | Del|PgDn|
   * |---------|  |------------------------------------------------------------|  `---------'
   * | F5 | F6 |  |CAPS    |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |---------|  |------------------------------------------------------------|  ,----.
   * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift      |  | Up |
   * |---------|  |-------------------------------------------------------------------------.
   * | F9 | F10|  |Ctrl|Win |Alt |      Space            |Alt |Ctrl|Func |    |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'    `-------------'
   */
  [VANILLA] = LAYOUT(
    KC_F1,   KC_F2,   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,          KC_INS,  KC_PGUP, \
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,          KC_DEL,  KC_PGDN, \
    KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,                             \
    KC_F7,   KC_F8,   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,          KC_UP,            \
    KC_F9,   KC_F10,  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RCTL, MO(FUNC),          KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  /* Keymap FUNCTION: Function Layer
   * ,---------.  ,-------------------------------------------------------------.  ,---------.
   * |    |    |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  | Ins|Home|
   * |---------|  |-------------------------------------------------------------|  |---------|
   * |    |    |  |Tab  |Hom| Up|End|PgU|   |   |   |   |   |   |   |   |       |  | Del|End |
   * |---------|  |-------------------------------------------------------------|  `---------'
   * |    |    |  |MO(FUNC)|Lft|Dn |Rig|PgD|   |Lft|Dwn| Up|Rgt|   |   |        |
   * |---------|  |-------------------------------------------------------------|  ,----.
   * |    |    |  |Shift   |   |   |   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|  | Up |
   * |---------|  |--------------------------------------------------------------------------.
   * |    |    |  |Ctrl|Win |Alt |        Enter         |Alt |Func |CTRL |     |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'     `-------------'
   */
  [FUNC] = LAYOUT(
    _______, _______, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,                _______, KC_HOME, \
    _______, _______, XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               _______, KC_END,  \
    _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,          XXXXXXX,                                 \
    _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,                   TG(SETTINGS),          _______,          \
    _______, _______, _______, _______, _______,                            KC_ENT,                             _______, _______, _______,               _______, _______, _______  \
  ),

  /* Keymap SETTINGS: Settings Layer
   * ,---------.  ,-------------------------------------------------------------.  ,-------------.
   * |    |    |  |LayClr|   |   |   |   |   |   |   |   |  |   |BL-|BL+|BL Togl|  |RGB Tog |Val+|
   * |---------|  |-------------------------------------------------------------|  |-------------|
   * |    |    |  |MuMode |   |   |   |   |   |   |   |   |   |   |   |  |LEDTst|  |RGB Mode|Val-|
   * |---------|  |-------------------------------------------------------------|  `-------------'
   * |    |    |  |AudTgl   |Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
   * |---------|  |-------------------------------------------------------------|  ,----.
   * |    |    |  |ClickTgl  |Hz-|MS-|   |   |   |   |MuTgl|  |  |   |Layer Clr |  |Hue+|
   * |---------|  |-------------------------------------------------------------------------.
   * |    |    |  |    |    |    |                         |    |    |     |  |Sat-|Hue-|Sat+|
   * `---------'  `--------------------------------------------------------'  `--------------'
   */
  [SETTINGS] = LAYOUT(
    XXXXXXX, XXXXXXX, KC_FN0,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_INC,  BL_TOGG,          RGB_TOG, RGB_VAI, \
    XXXXXXX, XXXXXXX, MU_MOD,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_MOD, RGB_VAD, \
    XXXXXXX, XXXXXXX, AU_TOG,  KC_FN1,  KC_FN3,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RESET,                              \
    XXXXXXX, XXXXXXX, KC_FN5,  KC_FN2,  KC_FN4,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOG,  XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,          RGB_HUI,          \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX,          RGB_SAD, RGB_HUD, RGB_SAI  \
  ),
};

const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),                   // FN1 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),                    // FN2 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),                   // FN3 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),                  // FN4 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),                        // FN5 - Toggle audio click
  };

void matrix_init_user(void) {
    // This keymap only has a single base layer, so reset the default if needed
    if(eeconfig_read_default_layer() > 1){
        eeconfig_update_default_layer(1);
        default_layer_set(1);
    }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {
}
