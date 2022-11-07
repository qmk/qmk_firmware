#include QMK_KEYBOARD_H

/*
Security Note: While it is possible to use macros to send passwords, credit card numbers,
and other sensitive information it is a supremely bad idea to do so. Anyone who gets a hold
of your keyboard will be able to access that information by opening a text editor.
*/
enum custom_keycodes
{
  PASS_A = SAFE_RANGE,
  PASS_B
};

#define ___ KC_NO

#define LAYOUT_melka(                                                           \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E,  \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,       \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,            \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E,  \
    K40, K41, K42, K43, K44, K45, K46, K47, K48)                                \
  {                                                                             \
    {K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D},     \
    {K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, ___},     \
    {K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K1D},     \
    {K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3E, K3D},     \
    {K40, K41, K42, ___, ___, K43, ___, K3C, K46, K0E, K44, K45, K47, K48}      \
  }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 0: Base Layer
    LAYOUT_melka(
      KC_NUBS,  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_DEL,     KC_BSPC,
      KC_TAB,   KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,    KC_ENT,
      KC_CAPS,  KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_BSLS,
      MT(KC_LSFT, KC_5),  KC_GRV,     KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    MT(KC_RSFT, KC_MINS),    KC_UP,      MO(1),
      KC_LCTL,  KC_LALT,    KC_LGUI,                                        KC_SPC,                                         KC_RGUI,    KC_RALT,    KC_LEFT,  KC_DOWN,      KC_RIGHT),

  // 1: Function Layer
  LAYOUT_melka(
      KC_ESC,   KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     _______,    _______,
      _______,  KC_WH_U,    KC_UP,      KC_WH_D,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
      _______,  KC_LEFT,    KC_DOWN,    KC_RIGHT,   _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGUP,    _______,
      TO(2),    TO(3),      _______,    KC_APP,     BL_STEP,    _______,    _______,    _______,    _______,    _______,    _______,    KC_END,     KC_PGDN,    KC_VOLU,    _______,
      _______,  _______,    _______,                                        _______,                                        _______,    _______,    _______,    KC_VOLD,    KC_MUTE),

  // 2: RGB Layer
  LAYOUT_melka(
      RGB_TOG,  RGB_M_P,    RGB_RMOD,   RGB_MOD,    RGB_M_B,    RGB_M_R,    RGB_M_SW,   RGB_M_SN,   RGB_M_K,    RGB_M_X,    RGB_M_G,    RGB_M_T,    _______,    _______,    QK_BOOT,
      _______,  RGB_HUD,    RGB_HUI,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
      _______,  RGB_SAD,    RGB_SAI,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
      TO(0),    _______,    RGB_VAD,    RGB_VAI,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    PASS_A,      PASS_B,    _______,    _______,
      _______,  _______,    _______,                                        _______,                                        _______,    _______,    _______,    _______,    _______),

  // 3: Keypad Layer
  LAYOUT_melka(
      KC_ESC,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    KC_PEQL,    KC_PSLS,    KC_PAST,    _______,    _______,
      _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_P7,      KC_P8,      KC_P9,      KC_PMNS,    _______,
      _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_P4,      KC_P5,      KC_P6,      KC_PPLS,
      TO(0),    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_P1,      KC_P2,      KC_P3,      KC_PENT,    TO(0),
      _______,  _______,    _______,                                        _______,                                        KC_P0,      KC_P0,      KC_PDOT,    KC_PENT,    _______)
};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM rgb_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {6, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM rgb_function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM rgb_backlight_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 2, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM rgb_keypad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {4, 4, HSV_RED}
);
// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_capslock_layer,
    rgb_function_layer,
    rgb_backlight_layer,    // Overrides caps lock layer
    rgb_keypad_layer     // Overrides other layers
);

layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}
// Loop
void matrix_scan_user(void) {
  // Empty
};

static bool control_disabled = false;
static bool delete_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (keycode == KC_BSPC)
  {
    if (record->event.pressed)
    {
      if (keyboard_report->mods & MOD_BIT(KC_LCTL))
      {
        delete_pressed = true;
        control_disabled = true;
        unregister_code(KC_LCTL);
        register_code(KC_DEL);
        return false;
      }
    }
    else if (delete_pressed)
    {
      delete_pressed = false;
      unregister_code(KC_DEL);

      if (control_disabled)
      {
        control_disabled = false;
        register_code(KC_LCTL);
      }
      return false;
    }
  }
  else if (keycode == KC_LCTL && !record->event.pressed && delete_pressed)
  {
    delete_pressed = false;
    control_disabled = false;
    unregister_code(KC_DEL);
    register_code(KC_BSPC);
    return false;
  }

  switch (keycode)
  {
  case PASS_A:
    if (record->event.pressed)
    {
      SEND_STRING(PASSWORD_A "\n");
    }
    break;
  case PASS_B:
    if (record->event.pressed)
    {
      SEND_STRING(PASSWORD_B "\n");
    }
    break;
  }
  return true;
}
