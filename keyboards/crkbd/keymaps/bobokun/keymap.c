#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
#ifdef RGB_MATRIX_ENABLE
//Following line allows macro to read current RGB settings
extern rgb_config_t rgb_matrix_config;
#endif

extern uint8_t is_master;


#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer                        = 0;
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', 'I', 'H', 'U',  16, 'E', 'D',  26,  // 4x
     27,  31,  24, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '{', '}', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    'M',  30,  31,  26,  27,   7,  14, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'G', 'C', 'S', 'A', 'G', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode);
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _DJMAX 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

uint8_t prev = _QWERTY;
uint32_t desired;
uint32_t default_desired;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DJMAX,
  LOWER,
  RAISE,
  ADJUST
};

//Tap Dance Declarations
enum {
  ALT_GUI = 0,
  CTL_ALT,
  CTL_TAB
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Alt, twice for GUI
  [ALT_GUI]  = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
  //Tap once for Ctrl, twice for Alt
  [CTL_ALT]  = ACTION_TAP_DANCE_DOUBLE(KC_RCTL, KC_RALT),
  //Tap once for CTL, twice for TAB
  [CTL_TAB]  = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_TAB)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  TD(CTL_TAB),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	     KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    TD(ALT_GUI),   KC_SPC,  LOWER,      RAISE,  KC_ENT,  TD(CTL_ALT) \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MNXT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MPLY, KC_PGUP,  KC_HOME,  KC_UP,  KC_END, KC_PSCR,                      KC_MINS,  KC_EQL, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_MPRV, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS,                       KC_BSLS,  KC_GRV, KC_LBRC, KC_RBRC, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    TD(ALT_GUI),   KC_SPC,  LOWER,      RAISE,  KC_ENT,  TD(CTL_ALT) \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_VOLU,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_VOLD,  KC_F11,  KC_F12, RGB_VAD, RGB_TOG, RGB_VAI,                     RGB_RMOD, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    TD(ALT_GUI),   KC_SPC,  LOWER,      RAISE,  KC_ENT,  TD(CTL_ALT) \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,  EEP_RST, XXXXXXX,KC_NLCK, KC_CLCK, KC_SLCK,                       DJMAX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    TD(ALT_GUI),   KC_SPC,  LOWER,      RAISE,  KC_ENT,  TD(CTL_ALT) \
                                      //`--------------------------'  `--------------------------'
  ),
  
  [_DJMAX] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GESC,   KC_F1,  KC_F10,    KC_E,    KC_E,    KC_1,                         KC_2,    KC_I,    KC_I, XXXXXXX, KC_PGUP, QWERTY,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   KC_F9,    KC_S,    KC_D,    KC_F, XXXXXXX,                        KC_F5,    KC_J,    KC_K,    KC_L, KC_PGDN, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
	    KC_LSFT,   KC_F8, XXXXXXX, XXXXXXX, KC_LALT, XXXXXXX,                      XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_SPC, KC_LCTL,  LOWER,       RAISE, KC_RCTL , KC_ENT  \
                                      //`--------------------------'  `--------------------------'

  )
};

// clang-format on
void matrix_init_user(void) {
  desired = rgb_matrix_config.mode;
  default_desired = rgb_matrix_config.mode;
}


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;  // flips the display 270 degrees if master
    }
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

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
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
        case _DJMAX:
            oled_write_P(PSTR(" DJMX"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

void render_rgb_status(void) {
    oled_write_P(PSTR("RGB:"), false);
    static char temp[20] = {0};
    snprintf(temp, sizeof(temp) + 1, "M:%3dH:%3dS:%3dV:%3d", rgb_matrix_config.mode, rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
    oled_write_P(temp, false);
}



void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
// #    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
//     render_rgb_status();
// #    endif
    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_logo();  // Renders a static logo
    oled_scroll_left();  // Turns on scrolling
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



int RGB_current_mode;

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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        desired = default_desired;
        rgb_matrix_mode_noeeprom(desired);
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
    case DJMAX:
          if (record->event.pressed) {
            desired = RGB_MATRIX_TYPING_HEATMAP;
            persistent_default_layer_set(1UL<<_DJMAX);
            update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
          }
          return false;	
    case RGB_MOD:
          if (record->event.pressed) {
             uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                if (shifted) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                    rgblight_step_reverse();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_step_reverse();
#        endif
                } else {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                    rgblight_step();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_step();
#        endif
                }
            desired = rgb_matrix_config.mode;
            default_desired = desired;
          }
    case RGB_RMOD:
          if (record->event.pressed) {
             uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                if (shifted) {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                    rgblight_step();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_step();
#        endif
                } else {
#        if defined(RGBLIGHT_ENABLE) && !defined(RGBLIGHT_DISABLE_KEYCODES)
                    rgblight_step_reverse();
#        endif
#        if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_KEYCODES)
                    rgb_matrix_step_reverse();
#        endif
                }
            desired = rgb_matrix_config.mode;
            default_desired = desired;
          }
  }

  if (record->event.pressed) {
      #ifdef OLED_DRIVER_ENABLE
              oled_timer = timer_read32();
              add_keylog(keycode);
      #endif
      #ifndef SPLIT_KEYBOARD
              if (keycode == RESET && !is_master) {
                  return false;
              }
      #endif
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
	  switch (layer) {
        case _RAISE:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
            rgb_matrix_sethsv_noeeprom(128, 255, rgb_matrix_config.hsv.v);
            break;
        case _LOWER:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
            rgb_matrix_sethsv_noeeprom(28, 255, rgb_matrix_config.hsv.v);
            break;
        case _ADJUST:
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
            rgb_matrix_sethsv_noeeprom(0, 0, rgb_matrix_config.hsv.v);
            break;
        default: //  for any other layers, or the default layer
            rgb_matrix_mode_noeeprom(desired);
            break;
	  }
  return state;
}