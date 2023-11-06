#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

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
  FN,
  ADJ,
  RGBRST
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* QWERTY
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | Bspc |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |  |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |  Esc |   A  |   S  |   D  |   F  |   G  |      |  |      |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |      |  |      |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Alt |  FN  | LGui |  RGB |  Spc |  Del |  | Bspc |  Spc |  Adj | LGui |  FN  |  Alt | Ctrl |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |  Spc |  Ent |  |  Ent |  Spc |
   *                                    `-------------'  `-------------'
   */
  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
          KC_GRV,       KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_MINS,          KC_EQL,          KC_6,       KC_7,       KC_8,       KC_9,       KC_0,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
          KC_TAB,       KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LBRC,         KC_RBRC,          KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,    KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
          KC_ESC,       KC_A,       KC_S,       KC_D,       KC_F,       KC_G,    _______,      _______,          KC_H,       KC_J,       KC_K,       KC_L,    KC_SCLN,    KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
         SC_LSPO,       KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,    _______,      _______,          KC_N,       KC_M,    KC_COMM,     KC_DOT,    KC_SLSH,    SC_RSPC,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
         KC_LCTL,    KC_LALT,      FN,    KC_LGUI, RGB_MOD,        KC_SPC,     KC_DEL,         KC_BSPC,        KC_SPC,     ADJ,    KC_LGUI,      FN,    KC_LALT,    KC_LCTL,
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
                                                          KC_SPC,     KC_ENT,          KC_ENT,        KC_SPC
  //                                                |--------+--------|    |--------+-----------+
      ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      |      |  Up  |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      |      | Left | Down | Right|      |      |  |      | Play | Next | Mute | V-Up |V-Down|      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
           KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,    _______,      _______,         KC_F7,      KC_F8,      KC_F9,     KC_F10,     KC_F11,     KC_F12,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______,      KC_UP, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______,    KC_LEFT,    KC_DOWN,    KC_RGHT, _______,    _______,      _______,       KC_MPLY,    KC_MNXT,    KC_MUTE,    KC_VOLD,    KC_VOLU, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,    _______, _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
                                                      _______, _______,      _______,    _______
  //                                                |--------+--------|    |--------+-----------+
      ),

  /* ADJ
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | Sat+ | Val+ | Hue+ |Speed+|Toggle|      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | Sat- | Val- | Hue- |Speed-|Reset |      |  |      |      |QWERTY| COLE |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */

  [_ADJ] =  LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--+--------+.   ,--------+--+--------+--------+--------+--------+--------+--------+
        QK_BOOT, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______,   QK_BOOT,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, RGB_SAI, RGB_VAI, RGB_HUI, RGB_SPI, RGB_TOG,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, RGB_SAD, RGB_VAD, RGB_HUD, RGB_SPD,  RGBRST,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,    _______,      _______,    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--+--------|    |--------+--+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______,    _______, _______,      _______, _______,    _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--+--------+--------|    |--------+--------+--+--------+--------+--------+--------+--------|
                                                      _______, _______,      _______, _______
  //                                                |--------+--------|    |--------+--------+
      )
};


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder*/
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
      } else {
        layer_off(_FN);
      }
      return false;
      break;
    case ADJ:
        if (record->event.pressed) {
          layer_on(_ADJ);
        } else {
          layer_off(_ADJ);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
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
}


// OLED Driver Logic
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flip 180 for offhand
  return rotation;
}

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
      oled_write_P(PSTR("Laser     \n"), false);
      break;
    case L_FN:
      oled_write_P(PSTR("Function  \n"), false);
      break;
    case L_ADJ:
    case L_ADJ_TRI:
      oled_write_P(PSTR("Adjustment\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined \n"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(led_state.num_lock ? PSTR("NUMLOCK ") : PSTR("        "), false);
  oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
  oled_write_P(led_state.scroll_lock ? PSTR("SCLK ") : PSTR("     "), false);
}

bool oled_task_user(void) {
  if (is_keyboard_master())
    render_status();
  else
    render_logo();

    return false;
}

#endif
