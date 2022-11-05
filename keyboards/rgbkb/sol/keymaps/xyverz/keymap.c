#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

enum layer_number {
    _DVORAK = 0,
    _DESTINY,
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  DESTINY,
  QWERTY,
  COLEMAK,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  RGB_MENU
};

// Aliases to make the keymap clearer.
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_END,   KC_PGDN, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,  XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    XXXXXXX,  XXXXXXX, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_LGUI,  KC_ENT,  KC_SPC \

  ),

  [_DESTINY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_END,   KC_PGDN, KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    XXXXXXX,  XXXXXXX, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    XXXXXXX,  XXXXXXX, KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_DEL,   KC_ENT,  KC_SPC \

  ),

  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_END,   KC_PGDN, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_SLSH, \
      KC_RCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX,  XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_LGUI,  KC_ENT,  KC_SPC \
  ),

  [_COLEMAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME,  KC_PGUP, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
      KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_END,   KC_PGDN, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_SLSH, \
      KC_RCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    XXXXXXX,  XXXXXXX, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    XXXXXXX,  XXXXXXX, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
      KC_GRV,  KC_LGUI, KC_LEFT, KC_RGHT, LOWER,   KC_LCTL, KC_LALT,  KC_RALT, KC_RCTL, RAISE,   KC_UP,   KC_DOWN, KC_RGUI, KC_RCTL, \
                                                   KC_BSPC, KC_LGUI,  KC_ENT,  KC_SPC \
  ),

  [_LOWER] =  LAYOUT( \
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, XXXXXXX, XXXXXXX, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
  ),

  [_RAISE] =  LAYOUT( \
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      KC_CAPS, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, XXXXXXX, XXXXXXX, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
  ),

  [_ADJUST] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_NLCK, _______, _______, \
      KC_CAPS, _______, QWERTY,  COLEMAK, DVORAK,  DESTINY, XXXXXXX, XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______, \
      _______, _______, _______, RGB_SPI, RGB_SPD, _______, XXXXXXX, XXXXXXX, _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                                   KC_DEL,  _______, _______, KC_INS \
      )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
   switch (keycode) {
    case DVORAK:
        set_single_persistent_default_layer(_DVORAK);
      return false;
    case DESTINY:
        set_single_persistent_default_layer(_DESTINY);
      return false;
    case QWERTY:
        set_single_persistent_default_layer(_QWERTY);
      return false;
    case COLEMAK:
        set_single_persistent_default_layer(_COLEMAK);
      return false;
    case RGBRST:
#if defined(RGBLIGHT_ENABLE)
        eeconfig_update_rgblight_default();
        rgblight_enable();
#elif defined(RGB_MATRIX_ENABLE)
        eeconfig_update_rgb_matrix_default();
#endif
      return false;
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_rgbkb_sol_rev2)
    case RGB_TOG:
      if (record->event.pressed) {
        rgb_matrix_increase_flags();
      }
      return false;
#endif
    case RGB_MENU:
#ifdef RGB_OLED_MENU
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          rgb_encoder_state = (rgb_encoder_state - 1);
          if (rgb_encoder_state > 5) {
            rgb_encoder_state = 5;
          }
        } else {
          rgb_encoder_state = (rgb_encoder_state + 1) % 6;
        }
      }
#endif
      return false;
    }
  }
  return true;
};

// For RGBRST Keycode
#if defined(RGB_MATRIX_ENABLE)
void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}

void rgb_matrix_decrease_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif

#ifdef RGB_OLED_MENU
uint8_t rgb_encoder_state = 4;

typedef void (*rgb_matrix_f)(void);

const rgb_matrix_f rgb_matrix_functions[6][2] = {
    { rgb_matrix_increase_hue, rgb_matrix_decrease_hue },
    { rgb_matrix_increase_sat, rgb_matrix_decrease_sat },
    { rgb_matrix_increase_val, rgb_matrix_decrease_val },
    { rgb_matrix_increase_speed, rgb_matrix_decrease_speed },
    { rgb_matrix_step, rgb_matrix_step_reverse },
    { rgb_matrix_increase_flags, rgb_matrix_decrease_flags }
};
#endif

#ifdef ENCODER_ENABLE

static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a)/sizeof(pin_t))

const uint16_t PROGMEM encoders[][NUMBER_OF_ENCODERS * 2][2]  = {
    [_QWERTY] = ENCODER_LAYOUT( \
        KC_VOLU, KC_VOLD,
        KC_VOLU, KC_VOLD
    ),
    [_COLEMAK] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    ),
    [_FN] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    ),
    [_ADJ] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (!is_keyboard_master())
    return;

#ifdef RGB_OLED_MENU
  if (index == RGB_OLED_MENU) {
    (*rgb_matrix_functions[rgb_encoder_state][clockwise])();
  } else
#endif
  {
    uint8_t layer = get_highest_layer(layer_state);
    uint16_t keycode = encoders[layer][index][clockwise];
    while (keycode == KC_TRANSPARENT && layer > 0)
    {
      layer--;
      if ((layer_state & (1 << layer)) != 0)
          keycode = encoders[layer][index][clockwise];
    }
    if (keycode != KC_TRANSPARENT)
      tap_code16(keycode);
  }
    return true;
}
#endif

// OLED Driver Logic
#ifdef OLED_ENABLE
 oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
  };
  oled_write_P(sol_logo, false);
}

static void render_status(void) {
  // Render to mode icon
  static const char PROGMEM sol_icon[] = {
    0x9b,0x9c,0x9d,0x9e,0x9f,
    0xbb,0xbc,0xbd,0xbe,0xbf,
    0xdb,0xdc,0xdd,0xde,0xdf,0
  };
  oled_write_P(sol_icon, false);

  // Define layers here
  oled_write_P(PSTR("     Layer-----"), false);
  uint8_t layer = layer_state ? get_highest_layer(layer_state) : get_highest_layer(default_layer_state);
  switch (layer) {
    case _DVORAK:
      oled_write_P(PSTR("DVRAK"), false);
      break;
    case _DESTINY:
      oled_write_P(PSTR("DSTNY"), false);
      break;
    case _QWERTY:
      oled_write_P(PSTR("QWRTY"), false);
      break;
    case _COLEMAK:
      oled_write_P(PSTR("COLMK"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("ADJST"), false);
      break;
    default:
      oled_write_P(PSTR("UNDEF"), false);
  }

  // Host Keyboard LED Status
    uint8_t led_state = host_keyboard_leds();
    oled_write_P(PSTR("-----"), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false);
    oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false);

#ifdef RGB_OLED_MENU
    static char buffer[31] = { 0 };
    snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d e%3d ", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_get_flags());
    buffer[4 + rgb_encoder_state * 5] = '<';

    oled_write_P(PSTR("-----"), false);
    oled_write(buffer, false);
#endif
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
    return false;
}

#endif
