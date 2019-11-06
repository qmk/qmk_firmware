#include QMK_KEYBOARD_H
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#ifdef OLED_DRIVER_ENABLE
static uint32_t        oled_timer = 0;
static char     keylog_str[6]   = {};
static uint16_t log_timer       = 0;
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

void matrix_init_user(void) {
    if (!isLeftHand) {
        g_led_config = (led_config_t){ {
            {  51,  50,  45,  44,  37,  36 },
            {  52,  49,  46,  43,  38,  35 },
            {  53,  48,  47,  42,  39,  34 },
            { NO_LED, NO_LED, NO_LED,  41,  40,  33 },
            {  24,  23,  18,  17,  10,   9 },
            {  25,  22,  19,  16,  11,   8 },
            {  26,  21,  20,  15,  12,   7 },
            { NO_LED, NO_LED, NO_LED,  14,  13,   6 }
        }, {
            { 139,  16 }, { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 }, { 129,  63 },
            { 139,  39 }, { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 },
            { 164,  55 }, { 174,  35 }, { 174,  13 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 },
            { 208,  42 }, { 208,  24 }, { 208,   7 }, { 224,   7 }, { 224,  24 }, { 224,  41 }, {  85,  16 },
            {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 }, {  85,  39 },
            {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 }, {  80,  58 }, {  60,  55 },
            {  50,  35 }, {  50,  13 }, {  50,   0 }, {  33,   3 }, {  33,  20 }, {  33,  37 }, {  16,  42 },
            {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 }
        }, {
            2, 2, 2, 2, 2, 2, 1,
            4, 4, 4, 4, 4, 4, 1,
            1, 4, 4, 4, 4, 4, 4,
            4, 4, 4, 1, 1, 1, 2,
            2, 2, 2, 2, 2, 1, 4,
            4, 4, 4, 4, 4, 1, 1,
            4, 4, 4, 4, 4, 4, 4,
            4, 4, 1, 1, 1
        } };
    }
}


enum corne_layers {
    _QWERTY, 
    _NUM, 
    _NAV, 
    _FUNCT, 
    _GAME,
    _SYMBOL,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,\
      KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                           KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,\
      KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SFTENT,\
                            KC_LALT, MO(_NUM), LT(_NAV,KC_SPC),               LT(_NUM,KC_SPC), MO(_SYMBOL), LT(_FUNCT,KC_ESC)\
    ),

  [_NUM] = LAYOUT( \
      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,\
      KC_LSFT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                             KC_PPLS, KC_4, KC_5, KC_6, KC_MINS, KC_EQL,\
      KC_LCTL, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,                          KC_PSLS, KC_1, KC_2, KC_3, KC_SLSH, KC_RBRC,\
                                    KC_LGUI, KC_TRNS, KC_F5,                  KC_TRNS, KC_0, KC_PDOT\
    ),

  [_NAV] = LAYOUT( \
      KC_TAB, KC_EXLM, KC_HOME, KC_UP, KC_END, KC_PGUP,                       KC_NO, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_BSPC,\
      KC_TRNS, LCTL(KC_A), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_DEL,\
      KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL_T(KC_C), LCTL(KC_V), LCTL(KC_B),  KC_ESC, KC_NO, KC_NO, KC_NO, LCTL(KC_MINS), LCTL(LSFT(KC_MINS)),\
                                    KC_TRNS, KC_NO, KC_TRNS,                  KC_F5, KC_TRNS, LCTL(KC_F5)\
    ),

  [_FUNCT] = LAYOUT( \
      RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_CALC,                           KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,\
      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_MYCM,                   KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,\
      RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO,                    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_VAD, TG(_GAME),\
                                    KC_VOLD, KC_VOLU, KC_MUTE,                RGB_TOG, RGB_SAD, KC_TRNS\
    ),

  [_GAME] = LAYOUT( \
     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                    KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,\
     KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                                    KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,\
     KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                                   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,\
                                    KC_ESC, KC_LCTL, KC_SPC,                  KC_SPC, KC_NO, TG(_GAME)\
    ),

  [_SYMBOL] = LAYOUT( \
     KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_NO,\
     KC_LSFT, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                    KC_NO, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, KC_PLUS,\
     KC_LCTL, KC_PSLS, KC_PIPE, KC_BSLS, KC_LBRC, KC_RBRC,                      KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_QUES, KC_NO,\
                                    KC_NO, KC_LCBR, KC_RCBR,                      KC_NO, KC_TRNS, KC_NO\
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

 #ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
}

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 4; i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        //add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLGGR"), false);
    oled_write(keylog_str, false);
}


void render_layer_state(void) {
    oled_write_ln_P(PSTR("LAYER"), false);
    oled_write_ln_P(PSTR("NUM"), layer_state_is(_NUM));
    oled_write_ln_P(PSTR("NAV"), layer_state_is(_NAV));
    oled_write_ln_P(PSTR("FUNC"), layer_state_is(_FUNCT));
    oled_write_ln_P(PSTR("GAME"), layer_state_is(_GAME));
    oled_write_ln_P(PSTR("SYMBL"), layer_state_is(_SYMBOL));
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln_P(PSTR(" "), false);
}

//void render_bootmagic_status(void) {
//    /* Show Ctrl-Gui Swap options */
//    static const char PROGMEM logo[][2][3] = {
//        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//    };
//    oled_write_P(PSTR("BTMGK"), false);
//    oled_write_P(PSTR(" "), false);
//    oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
//    oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
//    oled_write_P(PSTR(" "), false);
//    oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
//    oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
//    oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
//}

void render_rj_logo(void) {
  static const char PROGMEM crkbd_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
  oled_write_P(crkbd_logo, false);
}

void render_status_main(void) {
    //layers first//
    render_layer_state();
    /* Show Keyboard Layout  */
    //  render_keylock_status(host_keyboard_leds());
    render_mod_status(get_mods()|get_oneshot_mods());
    render_keylogger_status();
}

void render_status_secondary(void) {
    //old layout
  //render_layer_state();
  //render_mod_status(get_mods()|get_oneshot_mods());
  //render_keylogger_status();
    render_rj_logo();
}


void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    update_log();
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void rgb_matrix_indicators_user(void) {
    if (rgb_matrix_config.enable 
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        && !g_suspend_state
#    endif
    ) {
        switch (biton32(layer_state)) {
            case _GAME:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _FUNCT:
                rgb_matrix_layer_helper(HSV_TURQUOISE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _NUM:
                rgb_matrix_layer_helper(HSV_MAGENTA, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _NAV:
                rgb_matrix_layer_helper(HSV_CYAN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _SYMBOL:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default:
                rgb_matrix_layer_helper(HSV_BLUE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            }
    }
}
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;
void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}
#endif