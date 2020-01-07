#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
  extern rgblight_config_t rgblight_config;
  rgblight_config_t RGB_current_config;
#endif

#ifdef RGB_MATRIX_ENABLE
  rgb_config_t RGB_current_config;
#endif

#ifdef AUDIO_ENABLE
  extern audio_config_t audio_config;
#endif

#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode);
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  NOTEQL
};

#define KC________ KC_TRNS
#define KC____X___ KC_NO

#define KC_SFEQ MT(MOD_LSFT, KC_EQL)
#define KC_SFNE MT(MOD_LSFT, NOTEQL)

#define KC_LWSP LT(_LOWER, KC_SPC)
#define KC_RSEQ LT(_RAISE, KC_EQL)
#define KC_RSENT LT(_RAISE, KC_ENT)
#define KC_LWBSP LT(_LOWER, KC_BSPC)
#define KC_LWDEL LT(_RAISE, KC_DEL)
#define KC_ADBSL LT(_ADJUST, KC_BSLS)
#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)

#define KC_CK_RST CK_RST
#define KC_CK_DOWN CK_DOWN
#define KC_CK_UP CK_UP
#define KC_CK_TOGG CK_TOGG

#define KC_RGB_TOG RGB_TOG
#define KC_RGB_HUI RGB_HUI
#define KC_RGB_HUD RGB_HUD
#define KC_RGB_SAI RGB_SAI
#define KC_RGB_SAD RGB_SAD
#define KC_RGB_VAI RGB_VAI
#define KC_RGB_VAD RGB_VAD
#define KC_RGB_SPI RGB_SPI
#define KC_RGB_SPD RGB_SPD
#define KC_RGB_MOD RGB_MOD
#define KC_RGBRST RGBRST

#define KC_MU_TOG MU_TOG
#define KC_MU_MOD MU_MOD

#define KC_AU_TOG AU_TOG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          TAB,       Q,       W,       E,       R,       T,                            Y,       U,       I,       O,       P,     GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         SFEQ,       A,       S,       D,       F,       G,                            H,       J,       K,       L,    SCLN,    QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         LCTL,       Z,       X,       C,       V,       B,                            N,       M,    COMM,     DOT,    SLSH,   ADBSL,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             LALT,    LWSP,    RSEQ,      RSENT,   LWBSP,    LGUI\
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC, ___X___,       7,       8,       9, ___X___,                         PSCR, ___X___,      UP, ___X___, ___X___, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         SFNE,     DOT,       4,       5,       6, ___X___,                         PGUP,    LEFT,    DOWN,   RIGHT,    VOLD,    VOLU,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,       0,       1,       2,       3, ___X___,                       PGDOWN,    HOME, ___X___,     END, ___X___, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   LWDEL, _______\
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          ESC,    HASH,     DLR,    LCBR,    RCBR, ___X___,                      ___X___,    AMPR,    PIPE,    EXLM,    ASTR, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    EXLM,      AT,    LPRN,    RPRN, ___X___,                      ___X___,    UNDS,     EQL,    ANGL,    ANGR, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    PERC,    CIRC,    LBRC,    RBRC, ___X___,                      ___X___,    MINS,    PLUS, ___X___,    BSLS, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______\
                                      //`--------------------------'  `--------------------------'
  ),
 
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ___X___,  CK_RST, CK_DOWN,   CK_UP, CK_TOGG, RGB_TOG,                       MU_TOG,     F12,      F7,      F8,      F9, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ___X___, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                       MU_MOD,     F11,      F4,      F5,      F6, ___X___,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ___X___, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  RGBRST,                       AU_TOG,     F10,      F1,      F2,      F3, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______\
                                      //`--------------------------'  `--------------------------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
void save_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_config.enable = rgblight_config.enable;
    RGB_current_config.mode = rgblight_config.mode;
    RGB_current_config.speed  = rgblight_config.speed;
    RGB_current_config.hue = rgblight_config.hue;
    RGB_current_config.sat = rgblight_config.sat;
    RGB_current_config.val = rgblight_config.val;
  #elif RGB_MATRIX_ENABLE
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode = rgb_matrix_config.mode;
    RGB_current_config.speed  = rgb_matrix_config.speed;
    RGB_current_config.hsv.h = rgb_matrix_config.hsv.h;
    RGB_current_config.hsv.s = rgb_matrix_config.hsv.s;
    RGB_current_config.hsv.v = rgb_matrix_config.hsv.v;
  #endif
}

void restore_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_config.speed = RGB_current_config.speed;
    if (rgblight_config.mode != RGB_current_config.mode) {
      rgblight_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hue != rgblight_config.hue) ||
      (RGB_current_config.sat != rgblight_config.sat) ||
      (RGB_current_config.val != rgblight_config.val)) {
      rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
    }
    if (rgblight_config.enable) {
      rgblight_enable_noeeprom();
    } else {
      rgblight_disable_noeeprom();
    }
  #elif RGB_MATRIX_ENABLE
    rgb_matrix_config.speed = RGB_current_config.speed;
    if (rgb_matrix_config.mode != RGB_current_config.mode) {
      rgb_matrix_mode_noeeprom(RGB_current_config.mode);
    }
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) ||
      (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) ||
      (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
      rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    if (rgb_matrix_config.enable) {
      rgb_matrix_enable_noeeprom();
    } else {
      rgb_matrix_disable_noeeprom();
    }
  #endif
}

void rgb_by_layer(int layer) {
  #ifdef RGBLIGHT_ENABLE
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  #elif RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
  #endif

  switch (layer) {
    case _ADJUST:
      rgblight_sethsv_noeeprom(9, 255, 255);
      break;
    case _RAISE:
      rgblight_sethsv_noeeprom(HSV_CYAN);
      break;
    case _LOWER:
      rgblight_sethsv_noeeprom(HSV_MAGENTA);
      break;
    default:
      rgblight_sethsv_noeeprom(HSV_RED);
  }
}
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
uint32_t layer_state_set_user(uint32_t state) {
  if (state == default_layer_state) {
    restore_rgb_config();
  } else {
    uint8_t layer = biton32(state);
    if (layer_state == default_layer_state) save_rgb_config();
    rgb_by_layer(layer);
  }
  return state;
}
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
void matrix_init_user(void) {
  save_rgb_config();
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < (sizeof(code_to_name) / sizeof(char))) {
    keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
  }
}

void render_keylogger_status(void) {
  oled_write_P(PSTR("Log: "), false);
  oled_write(keylog_str, false);
}

// void render_default_layer_state(void) {
//   oled_write_P(PSTR("Lyout"), false);
//   switch (get_highest_layer(default_layer_state)) {
//     case _QWERTY:
//       oled_write_P(PSTR(" Qrty"), false);
//       break;
//   }
// }

void render_layer_state(void) {
  oled_write_P(PSTR("Layr:"), false);
  oled_write_P(PSTR("  Num"), layer_state_is(_LOWER));
  oled_write_P(PSTR("  Sym"), layer_state_is(_RAISE));
  oled_write_P(PSTR("   Fn"), layer_state_is(_ADJUST));
}

// void render_keylock_status(uint8_t led_usb_state) {
//   oled_write_P(PSTR("Lock:"), false);
//   oled_write_P(PSTR("  Num"), led_usb_state & (1 << USB_LED_NUM_LOCK));
//   oled_write_P(PSTR(" Caps"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
//   oled_write_P(PSTR(" Scrl"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
// }

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void render_effect_status(void) {
    oled_write_P(PSTR("RGB: "), false);
    #ifdef RGBLIGHT_ENABLE
      oled_write_P(rgblight_config.enable ? PSTR("  On") : PSTR("  Off"), false);
    #elif RGB_MATRIX_ENABLE
      oled_write_P(rgb_matrix_config.enable ? PSTR("  On") : PSTR("  Off"), false);
    #endif
    oled_write_ln_P(PSTR(""), false);
}
#endif

#ifdef AUDIO_ENABLE
void render_audio_status(void) {
    oled_write_P(PSTR("Aud: "), false);
    if (audio_config.enable) {
      oled_write_P(PSTR("   On"), false);
    } else {
      oled_write_P(PSTR("  Off"), false);
    }
    oled_write_ln_P(PSTR(""), false);
}
#endif

void render_status_main(void) {
    /* Show Keyboard Layout  */
    // render_default_layer_state();
    // oled_write_ln_P(PSTR(""), false);

    render_layer_state();
    oled_write_ln_P(PSTR(""), false);
    // render_bootmagic_status();
    // render_user_status();
    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    render_effect_status();
    oled_write_ln_P(PSTR(""), false);
    #endif

    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    // render_default_layer_state();
    // oled_write_ln_P(PSTR(""), false);

    render_layer_state();
    oled_write_ln_P(PSTR(""), false);

    // render_keylock_status(host_keyboard_leds());
    // oled_write_ln_P(PSTR(""), false);

    #ifdef NO_ACTION_ONESHOT
      render_mod_status(get_mods());
    #else
      render_mod_status(get_mods() | get_oneshot_mods());
    #endif
    
    oled_write_ln_P(PSTR(""), false);

    #ifdef AUDIO_ENABLE
    render_audio_status();
    // oled_write_ln_P(PSTR(""), false);
    #endif

    // render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
    #ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
    #endif

    if (is_master) {
        render_status_main();
    } else {
        render_status_secondary();
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
  #ifdef OLED_DRIVER_ENABLE
    oled_timer = timer_read32();
    add_keylog(keycode);
  #endif
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case NOTEQL:
        if (record->event.pressed) {
          SEND_STRING("!=");
        }
        break;
    #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    case RGB_MOD: case RGB_TOG:
    case RGB_HUI: case RGB_HUD:
    case RGB_SAI: case RGB_SAD:
    case RGB_VAI: case RGB_VAD:
    case RGB_SPI: case RGB_SPD:
      if (record->event.pressed) {
        restore_rgb_config();
        process_rgb(keycode, record);
        save_rgb_config();
      }
      return false;
    case RGBRST:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          eeconfig_update_rgblight_default();
          rgblight_enable();
        #elif RGB_MATRIX_ENABLE
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        #endif
        save_rgb_config();
      }
      return false;
    #endif
  }
  return true;
}
