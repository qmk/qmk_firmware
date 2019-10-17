#include QMK_KEYBOARD_H
#include "drashna.h"

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
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

enum crkbd_keycodes { RGBRST = NEW_SAFE_RANGE };

// clang-format off
#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
    ALT_T(KC_TAB), K11,  K12, K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A, RALT_T(KC_QUOT), \
    OS_LSFT, CTL_T(K21), K22, K23,      K24,     K25,                        K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                                        KC_GRV,  KC_SPC,  BK_LWER, DL_RAIS,  KC_ENT,  OS_RGUI                                      \
  )
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_crkbd_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),

  [_COLEMAK] = LAYOUT_crkbd_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_DVORAK] = LAYOUT_crkbd_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),

  [_WORKMAN] = LAYOUT_crkbd_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_crkbd_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_MALTRON] = LAYOUT_crkbd_base_wrapper(
    _________________MALTRON_L1________________, _________________MALTRON_R1________________,
    _________________MALTRON_L2________________, _________________MALTRON_R2________________,
    _________________MALTRON_L3________________, _________________MALTRON_R3________________
  ),

  [_EUCALYN] = LAYOUT_crkbd_base_wrapper(
    _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
    _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
    _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
  ),

  [_CARPLAX] = LAYOUT_crkbd_base_wrapper(
    _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
    _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
    _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
  ),

  [_MODS] = LAYOUT_wrapper(
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      _______, ___________________BLANK___________________,                  ___________________BLANK___________________, _______,
      KC_LSFT, ___________________BLANK___________________,                  ___________________BLANK___________________, KC_RSFT,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_LOWER] = LAYOUT_wrapper(
    KC_F11,  _________________LOWER_L1__________________,                    _________________LOWER_R1__________________, KC_F11,
    KC_F12,  _________________LOWER_L2__________________,                    _________________LOWER_R2__________________, KC_PIPE,
    _______, _________________LOWER_L3__________________,                    _________________LOWER_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_RAISE] = LAYOUT_wrapper( \
    _______, _________________RAISE_L1__________________,                    _________________RAISE_R1__________________, _______,
    _______, _________________RAISE_L2__________________,                    _________________RAISE_R2__________________, KC_BSLS,
    _______, _________________RAISE_L3__________________,                    _________________RAISE_R3__________________, _______,
                                     _______, _______, _______,        _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_wrapper( \
    KC_MAKE, _________________ADJUST_L1_________________,                    _________________ADJUST_R1_________________, KC_RESET,
    VRSN,    _________________ADJUST_L2_________________,                    _________________ADJUST_R2_________________, EEP_RST,
    MG_NKRO, _________________ADJUST_L3_________________,                    _________________ADJUST_R3_________________, RGB_IDL,
                                     HPT_TOG, KC_NUKE, _______,        _______, TG_MODS, HPT_FBK
  )
};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
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
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

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
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR(" COLE"), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(" DVRK"), false);
            break;
        case _WORKMAN:
            oled_write_P(PSTR(" WKMN"), false);
            break;
        case _NORMAN:
            oled_write_P(PSTR(" NORM"), false);
            break;
        case _MALTRON:
            oled_write_P(PSTR(" MLTN"), false);
            break;
        case _EUCALYN:
            oled_write_P(PSTR(" ECLN"), false);
            break;
        case _CARPLAX:
            oled_write_P(PSTR(" CRPX"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
    oled_write_P(PSTR(" Mods"), layer_state_is(_MODS));
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

void render_user_status(void) {
    oled_write_P(PSTR("USER:"), false);
    oled_write_P(PSTR(" Anim"), userspace_config.rgb_matrix_idle_anim);
    oled_write_P(PSTR(" Layr"), userspace_config.rgb_layer_change);
    oled_write_P(PSTR(" Nuke"), userspace_config.nuke_switch);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_bootmagic_status();
    render_user_status();

    render_keylogger_status();
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods()|get_oneshot_mods());

    render_keylogger_status();
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

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case ALT_T(KC_A):
            return TAPPING_TERM + 100;
        default:
            return TAPPING_TERM;
    }
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
        case _DVORAK:
            rgb_matrix_layer_helper(HSV_SPRINGGREEN, mode, rgb_matrix_config.speed, type);
            break;
        case _WORKMAN:
            rgb_matrix_layer_helper(HSV_GOLDENROD, mode, rgb_matrix_config.speed, type);
            break;
        case _NORMAN:
            rgb_matrix_layer_helper(HSV_CORAL, mode, rgb_matrix_config.speed, type);
            break;
        case _MALTRON:
            rgb_matrix_layer_helper(HSV_YELLOW, mode, rgb_matrix_config.speed, type);
            break;
        case _EUCALYN:
            rgb_matrix_layer_helper(HSV_PINK, mode, rgb_matrix_config.speed, type);
            break;
        case _CARPLAX:
            rgb_matrix_layer_helper(HSV_BLUE, mode, rgb_matrix_config.speed, type);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (biton32(layer_state)) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(IS_LAYER_ON(_MODS), LED_FLAG_UNDERGLOW);
                break;
            }
        }
        check_default_layer(0, LED_FLAG_MODIFIER);
    }
}
#endif
