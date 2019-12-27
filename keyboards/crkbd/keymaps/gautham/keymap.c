#include QMK_KEYBOARD_H

#ifdef AUDIO_ENABLE
  #include "audio.h"
  extern audio_config_t audio_config;
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer                        = 0;
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
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_SFBS MT(MOD_LSFT, KC_BSPC)
#define KC_SFDL MT(MOD_LSFT, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_GRV,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_SFBS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, LT(_ADJUST, KC_BSLS),\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                    KC_LALT, LT(_LOWER, KC_SPC), LT(_RAISE, KC_EQL),  LT(_RAISE, KC_ENT), LT(_LOWER, KC_BSPC), KC_LGUI \
                                      //`--------------------------'  `--------------------------'
  ),
 
  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX,                      KC_PSCR, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_SFDL, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX,                      KC_PGUP, KC_LEFT, KC_DOWN,KC_RIGHT, KC_VOLD, KC_VOLU,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS,    KC_0,    KC_1,    KC_2,    KC_3, XXXXXXX,                    KC_PGDOWN, KC_HOME, XXXXXXX,  KC_END, XXXXXXX, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, LT(_LOWER, KC_DEL), KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_HASH,  KC_DLR, KC_LCBR, KC_RCBR, XXXXXXX,                      XXXXXXX, KC_AMPR, KC_EXLM, KC_ASTR, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_EXLM,   KC_AT, KC_LPRN, KC_RPRN, XXXXXXX,                      XXXXXXX, KC_UNDS,  KC_EQL, XXXXXXX, KC_PIPE, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, XXXXXXX,                      XXXXXXX, KC_MINS, KC_PLUS, XXXXXXX, KC_BSLS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  ),
 
  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,  AU_TOG,                      XXXXXXX,   KC_F12,  KC_F7,   KC_F8,   KC_F9, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RGB_MOD,                      XXXXXXX,   KC_F11,  KC_F4,   KC_F5,   KC_F6, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  RGBRST,                      XXXXXXX,   KC_F10,  KC_F1,   KC_F2,   KC_F3, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

#ifdef RGBLIGHT_ENABLE
  int RGB_current_mode;
#endif
#ifdef RGB_MATRIX_ENABLE
  rgb_config_t RGB_current_config;

  const char *get_effect_code(int effect) {
    switch (effect) {
      // case RGB_MATRIX_ALPHAS_MODS:
      //   return PSTR(" AMod");
      // case RGB_MATRIX_GRADIENT_UP_DOWN:
      //   return PSTR(" GrdV");
      // case RGB_MATRIX_BREATHING:
      //   return PSTR(" Brth");
      // case RGB_MATRIX_BAND_SAT:
      //   return PSTR(" BnSt");
      // case RGB_MATRIX_BAND_VAL:
      //   return PSTR(" BnVl");
      // case RGB_MATRIX_BAND_PINWHEEL_SAT:
      //   return PSTR(" PnSt");
      // case RGB_MATRIX_BAND_PINWHEEL_VAL:
      //   return PSTR(" PnVl");
      // case RGB_MATRIX_BAND_SPIRAL_SAT:
      //   return PSTR(" SpSt");
      // case RGB_MATRIX_BAND_SPIRAL_VAL:
      //   return PSTR(" SpVl");
      // case RGB_MATRIX_CYCLE_ALL:
      //   return PSTR(" CylA");
      // case RGB_MATRIX_CYCLE_LEFT_RIGHT:
      //   return PSTR(" CylH");
      // case RGB_MATRIX_CYCLE_UP_DOWN:
      //   return PSTR(" CylV");
      // case RGB_MATRIX_CYCLE_OUT_IN:
      //   return PSTR(" CyOI");
      // case RGB_MATRIX_CYCLE_OUT_IN_DUAL:
      //   return PSTR("CyOId");
      // case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:
      //   return PSTR(" Rb>>");
      // case RGB_MATRIX_DUAL_BEACON:
      //   return PSTR(" DlBc");
      // case RGB_MATRIX_CYCLE_PINWHEEL:
      //   return PSTR(" CyPn");
      // case RGB_MATRIX_CYCLE_SPIRAL:
      //   return PSTR("CySpr");
      // case RGB_MATRIX_RAINBOW_BEACON:
      //   return PSTR(" RbBc");
      // case RGB_MATRIX_RAINBOW_PINWHEELS:
      //   return PSTR(" RbPn");
      case RGB_MATRIX_RAINDROPS:
        return PSTR(" Rndr");
      // case RGB_MATRIX_JELLYBEAN_RAINDROPS:
      //   return PSTR(" JbRn");
      // case RGB_MATRIX_TYPING_HEATMAP:
      //   return PSTR(" HMap");
      // case RGB_MATRIX_DIGITAL_RAIN:
      //   return PSTR(" DgRn");
      case RGB_MATRIX_SOLID_REACTIVE:
        return PSTR(" SRct");
      // case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
      //   return PSTR(" SRSM");
      // case RGB_MATRIX_SOLID_REACTIVE_WIDE:
      //   return PSTR(" SRWd");
      // case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:
      //   return PSTR(" SRMW");
      // case RGB_MATRIX_SOLID_REACTIVE_CROSS:
      //   return PSTR(" SRCr");
      // case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:
      //   return PSTR(" SRMC");
      // case RGB_MATRIX_SOLID_REACTIVE_NEXUS:
      //   return PSTR(" SRNx");
      // case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:
      //   return PSTR(" SRMN");
      // case RGB_MATRIX_SPLASH:
      //   return PSTR("  Spl");
      // case RGB_MATRIX_MULTISPLASH:
      //   return PSTR(" SplM");
      // case RGB_MATRIX_SOLID_SPLASH:
      //   return PSTR(" SSpl");
      // case RGB_MATRIX_SOLID_MULTISPLASH:
      //   return PSTR("SMSpl");
      default:
        return PSTR(" Unkn");
    }
  }
#endif

char rgb_enabled[24];

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
void save_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
  #ifdef RGB_MATRIX_ENABLE
    RGB_current_config.enable = rgb_matrix_config.enable;
    RGB_current_config.mode = rgb_matrix_config.mode;
    RGB_current_config.hsv = rgb_matrix_config.hsv;
    RGB_current_config.speed = rgb_matrix_config.speed;
  #endif
}

void restore_rgb_config(void) {
  #ifdef RGBLIGHT_ENABLE
    if (RGB_current_mode != rgblight_config.mode) rgblight_mode(RGB_current_mode);
  #endif
  #ifdef RGB_MATRIX_ENABLE
    if (rgb_matrix_config.mode != RGB_current_config.mode) rgb_matrix_config.mode = RGB_current_config.mode;
    if ((RGB_current_config.hsv.h != rgb_matrix_config.hsv.h) ||
      (RGB_current_config.hsv.s != rgb_matrix_config.hsv.s) ||
      (RGB_current_config.hsv.v != rgb_matrix_config.hsv.v)) {
      rgb_matrix_sethsv(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
    }
    rgb_matrix_config.speed = RGB_current_config.speed;
    // eeconfig_update_rgb_matrix();
    if (rgb_matrix_config.enable) {
      rgb_matrix_enable();
    } else {
      rgb_matrix_disable();
    }
  #endif
}

void rgb_by_layer(int layer) {
  rgblight_mode(RGB_MATRIX_SOLID_COLOR);
  switch (layer) {
    case _LOWER:
      rgb_matrix_sethsv_noeeprom(HSV_BLUE);
      break;
    case _RAISE:
      rgb_matrix_sethsv_noeeprom(HSV_GREEN);
      break;
    case _ADJUST:
      rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
      break;
    default:
      rgb_matrix_sethsv_noeeprom(HSV_RED);
      break;
  }
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {
    case _LOWER:
      save_rgb_config();
      rgb_by_layer(_LOWER);
      break;
    case _RAISE:
      save_rgb_config();
      rgb_by_layer(_RAISE);
      break;
    case _ADJUST:
      save_rgb_config();
      rgb_by_layer(_ADJUST);
      break;
    default:
      restore_rgb_config();
      break;
  }
  return state;
}
#endif

void matrix_init_user(void) {
    #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
      save_rgb_config(); // TODO: rgb_mat_mode rgb_mat_sethsv or rgb_matrix_set_color_all(20, 0, 0) sync both halves
    #endif
}

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

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        // add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("Log: "), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" Qrty"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("Layr:"), false);
    oled_write_P(PSTR("  Num"), layer_state_is(_LOWER));
    oled_write_P(PSTR("  Sym"), layer_state_is(_RAISE));
    oled_write_P(PSTR("   Fn"), layer_state_is(_ADJUST));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR("  Num"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR(" Caps"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_P(PSTR(" Scrl"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    oled_write_P(PSTR("BTMGK"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" "), false);
    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
}

// void render_user_status(void) {
//     oled_write_P(PSTR("USER:"), false);
//     oled_write_P(PSTR(" Anim"), userspace_config.rgb_matrix_idle_anim);
//     oled_write_P(PSTR(" Layr"), userspace_config.rgb_layer_change);
//     oled_write_P(PSTR(" Nuke"), userspace_config.nuke_switch);
// }

#ifdef RGB_MATRIX_ENABLE
void render_effect_status(void) {
    oled_write_P(PSTR("RGB: "), false);
    oled_write_P(get_effect_code(RGB_current_config.mode), false);
    oled_write_ln_P(PSTR(""), false);
}
#endif

#ifdef AUDIO_ENABLE
void render_audio_status(void) {
    oled_write_P(PSTR("Aud: "), false);
    if (audio_config.enable) {
      oled_write_P(PSTR("  Yes"), false);
    } else {
      oled_write_P(PSTR("   No"), false);
    }
    oled_write_ln_P(PSTR(""), false);
}
#endif

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    oled_write_ln_P(PSTR(""), false);

    render_layer_state();
    oled_write_ln_P(PSTR(""), false);
    // render_bootmagic_status();
    // render_user_status();
    #ifdef RGB_MATRIX_ENABLE
    render_effect_status();
    oled_write_ln_P(PSTR(""), false);
    #endif

    #ifdef AUDIO_ENABLE
    render_audio_status();
    oled_write_ln_P(PSTR(""), false);
    #endif

    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    oled_write_ln_P(PSTR(""), false);

    render_keylock_status(host_keyboard_leds());
    oled_write_ln_P(PSTR(""), false);

    render_mod_status(get_mods() | get_oneshot_mods());
    oled_write_ln_P(PSTR(""), false);

    render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif

    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
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
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    // TODO: restore_rgb_config fir rgb setting keys
    case RGB_MOD:
      #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        if (record->event.pressed) {
          restore_rgb_config();
          #ifdef RGBLIGHT_ENABLE
            rgblight_step();
          #endif
          #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_step();
          #endif
          save_rgb_config();
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
          save_rgb_config();
        }
      #endif
      break;
  }
  return true;
}
