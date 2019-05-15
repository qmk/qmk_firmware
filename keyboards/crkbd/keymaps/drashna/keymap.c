#include QMK_KEYBOARD_H
#include "drashna.h"

extern keymap_config_t keymap_config;
extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum crkbd_keycodes {
    RGBRST = NEW_SAFE_RANGE
};

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,  K01,    K02,     K03,      K04,     K05,                        K06,     K07,     K08,     K09,     K0A,     KC_MINS, \
    KC_TAB, ALT_T(K11),  K12, K13,      K14,     K15,                        K16,     K17,     K18,     K19,     K1A,     KC_QUOT, \
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
    _______, _________________ADJUST_L3_________________,                    _________________ADJUST_R3_________________, KC_MPLY,
                                     _______, KC_NUKE, _______,        _______, TG_MODS, _______
  )
};

void matrix_init_keymap(void) {
#ifndef CONVERT_TO_PROTON_C
    setPinOutput(D5);
    writePinHigh(D5);

    setPinOutput(B0);
    writePinHigh(B0);
#endif
}


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

#define KEYLOG_LEN (int)(32 / OLED_FONT_WIDTH)
char keylog_str[KEYLOG_LEN] = {};
uint8_t keylogs_str_idx = 0;
uint16_t log_timer = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {  add_keylog(keycode); }
    return true;
}

void render_status(void) {

    oled_write_P(PSTR("Layer"), false);
    switch (biton32(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_P(PSTR("Unkn "), false);
            break;
    }
    oled_write_P(PSTR("Lyout"), false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWRTY"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("COLMK"), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR("DVRAK"), false);
            break;
        case _WORKMAN:
            oled_write_P(PSTR("WRKMN"), false);
            break;
        case _NORMAN:
            oled_write_P(PSTR("NORMN"), false);
            break;
        case _MALTRON:
            oled_write_P(PSTR("MLTRN"), false);
            break;
        case _EUCALYN:
            oled_write_P(PSTR("ECLYN"), false);
            break;
        case _CARPLAX:
            oled_write_P(PSTR("CRPLX"), false);
            break;
    }

    uint8_t modifiers = get_mods();
    uint8_t one_shot = get_oneshot_mods();

    oled_write_P(PSTR("Mods:"), false);
    oled_write_P( (modifiers & MOD_MASK_SHIFT || one_shot & MOD_MASK_SHIFT) ? PSTR(" SFT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_CTRL  || one_shot & MOD_MASK_CTRL ) ? PSTR(" CTL ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_ALT   || one_shot & MOD_MASK_ALT  ) ? PSTR(" ALT ") : PSTR("     "), false);
    oled_write_P( (modifiers & MOD_MASK_GUI   || one_shot & MOD_MASK_GUI  ) ? PSTR(" GUI ") : PSTR("     "), false);


    oled_write_P(PSTR("BTMGK"), false);

    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(PSTR(" Mac "), false);
    } else {
        oled_write_P(PSTR(" Win "), false);
    }

    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK)    ? PSTR(" NUM ") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK)   ? PSTR(" CAPS") : PSTR("     "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR(" SCRL") : PSTR("     "), false);

    oled_write(keylog_str, false);
}


void oled_task_user(void) {
    if (is_master) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_crkbd_logo();
        oled_scroll_left();  // Turns on scrolling
    }
}

void matrix_scan_keymap(void) { update_log(); }
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

void rgb_matrix_indicators_user(void) {
    if ( userspace_config.rgb_layer_change &&
#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#endif
#if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#else
        rgb_matrix_config.enable
#endif
    ) {
        switch (biton32(layer_state)) {
            case _MODS:
                rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, LED_FLAG_UNDERGLOW); break;
            case _GAMEPAD:
                rgb_matrix_layer_helper(0xFF, 0x80, 0x00, LED_FLAG_UNDERGLOW); break;
            case _DIABLO:
                rgb_matrix_layer_helper(0xFF, 0x00, 0x00, LED_FLAG_UNDERGLOW); break;
            case _RAISE:
                rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, LED_FLAG_UNDERGLOW); break;
            case _LOWER:
                rgb_matrix_layer_helper(0x00, 0xFF, 0x00, LED_FLAG_UNDERGLOW); break;
            case _ADJUST:
                rgb_matrix_layer_helper(0xFF, 0x00, 0x00, LED_FLAG_UNDERGLOW); break;
            default:
                switch (biton32(default_layer_state)) {
                    case _QWERTY:
                        rgb_matrix_layer_helper(0x00, 0xFF, 0xFF, LED_FLAG_UNDERGLOW); break;
                    case _COLEMAK:
                        rgb_matrix_layer_helper(0xFF, 0x00, 0xFF, LED_FLAG_UNDERGLOW); break;
                    case _DVORAK:
                        rgb_matrix_layer_helper(0x00, 0xFF, 0x00, LED_FLAG_UNDERGLOW); break;
                    case _WORKMAN:
                        rgb_matrix_layer_helper(0xD9, 0xA5, 0x21, LED_FLAG_UNDERGLOW); break;
                    case _NORMAN:
                        rgb_matrix_layer_helper(0xFF, 0x7C, 0x4D, LED_FLAG_UNDERGLOW); break;
                    case _MALTRON:
                        rgb_matrix_layer_helper(0xFF, 0xFF, 0x00, LED_FLAG_UNDERGLOW); break;
                    case _EUCALYN:
                        rgb_matrix_layer_helper(0xFF, 0x80, 0xBF, LED_FLAG_UNDERGLOW); break;
                    case _CARPLAX:
                        rgb_matrix_layer_helper(0x00, 0x00, 0xFF, LED_FLAG_UNDERGLOW); break;
                }
        }
    }
}
#endif
