#include QMK_KEYBOARD_H

// readability
#define _______ KC_TRNS
#define XXXXXXX KC_NO

enum keymap_layout {
    VANILLA = 0,  // matches MF68 layout
    CS_GO,        // 0x08
    FUNC,         // 0x10
    SETTINGS,     // 0x20
};

enum {
    TD_ESC_FUNC = 0,
    TD_ESC_CTRL,
    TD_SPC_SPAM
};

bool spam_space = false;


  // {0x00000000, 0xFFFFFFFF, {0x0000, 0x0FFF, 0x0000}}, // base layer - green
  // {0x00000008, 0xFFFFFFF8, {0x07FF, 0x07FF, 0x0000}}, // CSGO layer - orange
  // {0x00000010, 0xFFFFFFF0, {0x0000, 0x0000, 0x0FFF}}, // function layer - blue
  // {0x00000020, 0xFFFFFFE0, {0x0FFF, 0x0000, 0x0FFF}}, // settings layer - magenta
  // {0xFFFFFFFF, 0xFFFFFFFF, {0x0FFF, 0x0FFF, 0x0FFF}}, // unknown layer - REQUIRED - white


// Colors of the layer indicator LED
// This list needs to define layer 0xFFFFFFFF, it is the end of the list, and the unknown layer
const Layer_Info layer_info[] = {
  // Layer     Mask           Red     Green   Blue
  {0x00000000, 0xFFFFFFFF, {0x0000, 0x0FFF, 0x0000}}, // base layer - green
  {0x00000002, 0xFFFFFFFE, {0x07FF, 0x07FF, 0x0000}}, // CSGO layer - orange
  {0x00000004, 0xFFFFFFFC, {0x0000, 0x0000, 0x0FFF}}, // function layer - blue
  {0x00000008, 0xFFFFFFE8, {0x0FFF, 0x0000, 0x0FFF}}, // settings layer - magenta
  {0xFFFFFFFF, 0xFFFFFFFF, {0x0FFF, 0x0FFF, 0x0FFF}}, // unknown layer - REQUIRED - white
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap BASE: (Base Layer) Default Layer
   * ,---------.  ,------------------------------------------------------------.  ,---------.
   * |Vol-|Vol+|  |Esc~| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backspa|  | Ins|PgUp|
   * |---------|  |------------------------------------------------------------|  |---------|
   * | F3 | F4 |  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|     \|  | Del|PgDn|
   * |---------|  |------------------------------------------------------------|  `---------'
   * | F5 | F6 |  |Control |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |---------|  |------------------------------------------------------------|  ,----.
   * | F7 | F8 |  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  Shift    |  | Up |
   * |---------|  |-------------------------------------------------------------------------.
   * | F9 | F10|  |Func|Alt |Cmd |      Space            |Cmd |Alt |Func |    |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'    `-------------'
   */
  [VANILLA] = LAYOUT_split_rshift(
    KC_VOLD, KC_VOLU, KC_GESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,       KC_BSPC,            LALT(KC_F5), KC_PGUP, \
    KC_F3,   KC_F4,   KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,      KC_BSLS,            KC_DEL,      KC_PGDN, \
    KC_F5,   KC_F6,   TD(TD_ESC_FUNC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,               KC_ENT,                                   \
    KC_F7,   KC_F8,   KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,      MO(CS_GO),          KC_UP,                \
    KC_F9,   KC_F10,  KC_LCTL,         KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RCTL, MO(FUNC),                KC_LEFT, KC_DOWN, KC_RGHT      \
  ),

  [CS_GO] = LAYOUT_split_rshift(
    _______, _______, KC_GESC,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            KC_FN0,      _______, \
    _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            _______,     _______, \
    _______, _______, KC_LCTL,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,                                  \
    _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                          _______,              \
    _______, _______, _______,         _______, _______,                            _______,                            _______, _______, _______,                 _______, _______, _______      \
  ),

  /* Keymap FUNCTION: Function Layer
   * ,---------.  ,-------------------------------------------------------------.  ,---------.
   * | V- | V+ |  | ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Delete   |  | Ins|Home|
   * |---------|  |-------------------------------------------------------------|  |---------|
   * |    |    |  |Tab  |   |PgU|   |   |   |   |   | Up|   |   |   |   |       |  | Del|End |
   * |---------|  |-------------------------------------------------------------|  `---------'
   * |    |    |  |Control|Hme|PgD|End|   |   |   |Lft|Dwn|Rgt|   |   |         |
   * |---------|  |-------------------------------------------------------------|  ,----.
   * |    |    |  |Shift   |   |Del|   |   |   |   |Mute|V- |V+ |  |TG(SETTINGS)|  | Up |
   * |---------|  |--------------------------------------------------------------------------.
   * |    | F10|  |Func|Win |Alt |        PgD           |Alt |Ctrl |Func |     |Lft| Dn |Rig |
   * `---------'  `------------------------------------------------------'     `-------------'
   */
  [FUNC] = LAYOUT_split_rshift(
    _______, _______, KC_GRV,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,       KC_DEL,             TO(CS_GO),   KC_HOME, \
    _______, _______, XXXXXXX,         KC_PGUP, KC_UP,   KC_PGDN, KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,            _______,     KC_END,  \
    _______, _______, _______,         KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,               XXXXXXX,                                  \
    _______, _______, _______,         XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,          TG(SETTINGS), XXXXXXX,            _______,              \
    _______, _______, _______,         _______, _______,                            KC_PGDN,                            _______, _______, _______,                 _______, _______, _______      \
  ),

  /* Keymap SETTINGS: Settings Layer
   * ,---------.  ,-----------------------------------------------------------.  ,-------------.
   * |    |    |  |FN0 |BL0|BL1|BL2|BL3|   |   |   |   |  |   |BL-|BL+|BL Togl|  |RGB Tog |Val+|
   * |---------|  |-----------------------------------------------------------|  |-------------|
   * |    |    |  |Debug|   |   |   |   |   |   |   |   |   |   |   |  |RGBTst|  |RGB Mode|Val-|
   * |---------|  |-----------------------------------------------------------|  `-------------'
   * |    |    |  |LayrClr|Hz+|MS+|   |   |   |   |   |   |   |   |   |  RST  |
   * |---------|  |-----------------------------------------------------------|  ,----.
   * |    |    |  |ClickTgl|Hz-|MS-|   |   |   |   |   |   |   |   |Layer Clr |  |Hue+|
   * |---------|  |------------------------------------------------------------------------.
   * |    |    |  |    |    |    |      Print Debug      |    |    |     |  |Sat-|Hue-|Sat+|
   * `---------'  `------------------------------------------------------'  `--------------'
   */
  [SETTINGS] = LAYOUT_split_rshift(
    XXXXXXX, XXXXXXX, KC_FN0,          KC_FN3,  KC_FN4,  KC_FN5,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BL_DEC,  BL_INC,       BL_TOGG,            RGB_TOG,     RGB_VAI, \
    XXXXXXX, XXXXXXX, DEBUG,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,            RGB_MOD,     RGB_VAD, \
    XXXXXXX, XXXXXXX, KC_FN0,          KC_FN6,  KC_FN8,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,               RESET,                                    \
    XXXXXXX, XXXXXXX, KC_FN10,         KC_FN7,  KC_FN9,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_FN0,       XXXXXXX,            RGB_HUI,              \
    XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX,                            KC_FN12,                            XXXXXXX, XXXXXXX, KC_FN0,                  RGB_SAD, RGB_HUD, RGB_SAI      \
  ),
};


void tap_space_spam_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(get_mods() & (MOD_BIT(KC_LGUI))){
      return;
    }
    if(state->pressed){
        spam_space = true;
    }
    register_code(KC_SPC);
    unregister_code(KC_SPC);
}

void tap_space_spam_reset(qk_tap_dance_state_t *state, void *user_data) {
    spam_space = false;
    unregister_code(KC_SPC);
}

void tap_esc_func_finished(qk_tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        layer_on(FUNC);
    }else{
        register_code(KC_ESC);
        unregister_code(KC_ESC);
    }
}

void tap_esc_func_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_off(FUNC);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESC_FUNC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_esc_func_finished, tap_esc_func_reset),
  [TD_SPC_SPAM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_space_spam_finished, tap_space_spam_reset),
};


const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(LFK_CLEAR),                               // FN0 - reset layers
    ACTION_FUNCTION(LFK_ESC_TILDE),                           // FN1 - esc+shift = ~, else escape
    ACTION_FUNCTION(LFK_LED_TEST),                            // FN2 - cycle through LEDs for testing
    ACTION_FUNCTION_OPT(LFK_SET_DEFAULT_LAYER, VANILLA),      // FN3 - set base layer to 0 and save
    ACTION_FUNCTION_OPT(LFK_SET_DEFAULT_LAYER, VANILLA),  // FN4 - set base layer to 1 and save
    ACTION_FUNCTION_OPT(LFK_SET_DEFAULT_LAYER, VANILLA),  // FN5 - set base layer to 2 and save
    ACTION_FUNCTION(LFK_CLICK_FREQ_HIGHER),                   // FN6 - Increase Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_FREQ_LOWER),                    // FN7 - Decrease Freq of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_LONGER),                   // FN8 - Increase length of audio click
    ACTION_FUNCTION(LFK_CLICK_TIME_SHORTER),                  // FN9 - Decrease length of audio click
    ACTION_FUNCTION(LFK_CLICK_TOGGLE),                        // FN10 - Toggle audio click
    ACTION_FUNCTION(LFK_LED_TEST),                            // FN11 - cycle through LEDs for testing
    ACTION_FUNCTION(LFK_DEBUG_SETTINGS),                      // FN12 - prints LED and click settings to HID
  };


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    if(spam_space && !(get_mods() & (MOD_BIT(KC_LGUI)))){
        register_code(KC_SPC);
        unregister_code(KC_SPC);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if((layer_state & (1 << CS_GO)) && (keycode == 44)){
    if(get_mods() & (MOD_BIT(KC_LGUI))){
      return false;
    }
  }
  return true;
}

void led_set_user(uint8_t usb_led) {

}
