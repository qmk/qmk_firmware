#include QMK_KEYBOARD_H
#include "drashna.h"

extern keymap_config_t keymap_config;
extern uint8_t         is_master;

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
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
// clang-format on

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }
uint16_t        oled_timer;

char     keylog_str[5]   = {};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer       = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = 4; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[5] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
        oled_timer = timer_read();
    }
    return true;
}

void render_rgb_status(void) {
    oled_write_ln("RGB:", false);
    static char temp[20] = {0};
    snprintf(temp, sizeof(temp) + 1, "M:%3dH:%3dS:%3dV:%3d", rgb_matrix_config.mode, rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v);
    oled_write(temp, false);
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    oled_write("Lyout", false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write(" QRTY", false);
            break;
        case _COLEMAK:
            oled_write(" COLE", false);
            break;
        case _DVORAK:
            oled_write(" DVRK", false);
            break;
        case _WORKMAN:
            oled_write(" WKMN", false);
            break;
        case _NORMAN:
            oled_write(" NORM", false);
            break;
        case _MALTRON:
            oled_write(" MLTN", false);
            break;
        case _EUCALYN:
            oled_write(" ECLN", false);
            break;
        case _CARPLAX:
            oled_write(" CRPX", false);
            break;
    }

    /* Show Lock Status (only work on master side) */
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write("Lock:", false);
    oled_write(" ", false);
    oled_write_ln("NUM", led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write(" ", false);
    oled_write("CAPS", led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write(" ", false);
    oled_write("SCRL", led_usb_state & (1 << USB_LED_SCROLL_LOCK));

    /* Show Alt-Gui Swap options */
    oled_write("BTMGK", false);
    oled_write(" ", false);
    oled_write_ln("Win", !keymap_config.swap_lalt_lgui);
    oled_write(" ", false);
    oled_write_ln("Mac", keymap_config.swap_lalt_lgui);

#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    /* Show RGB Options */
    render_rgb_status();
#    endif

    oled_write(keylog_str, false);
}

void render_status_secondary(void) {
    /* Show Keyboard Layout  */
    oled_write("Lyout", false);
    switch (biton32(default_layer_state)) {
        case _QWERTY:
            oled_write(" QRTY", false);
            break;
        case _COLEMAK:
            oled_write(" COLE", false);
            break;
        case _DVORAK:
            oled_write(" DVRK", false);
            break;
        case _WORKMAN:
            oled_write(" WKMN", false);
            break;
        case _NORMAN:
            oled_write(" NORM", false);
            break;
        case _MALTRON:
            oled_write(" MLTN", false);
            break;
        case _EUCALYN:
            oled_write(" ECLN", false);
            break;
        case _CARPLAX:
            oled_write(" CRPX", false);
            break;
    }

    /* Show Activate layer */
    oled_write("Layer", false);
    switch (biton32(layer_state)) {
        case _RAISE:
            oled_write("Raise", false);
            break;
        case _LOWER:
            oled_write("Lower", false);
            break;
        case _ADJUST:
            oled_write("Adjst", false);
            break;
        default:
            oled_write("Dflt ", false);
            break;
    }

    /* Show Mod  */
    uint8_t modifiers = get_mods() | get_oneshot_mods();

    oled_write("Mods:", false);
    oled_write(" ", false);
    oled_write_ln("SFT", (modifiers & MOD_MASK_SHIFT));
    oled_write(" ", false);
    oled_write_ln("CTL", (modifiers & MOD_MASK_CTRL));
    oled_write(" ", false);
    oled_write_ln("ALT", (modifiers & MOD_MASK_ALT));
    oled_write(" ", false);
    oled_write_ln("GUI", (modifiers & MOD_MASK_GUI));

#    if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    render_rgb_status();
#    endif

    /* Show logged Keys */
    oled_write(keylog_str, false);
}

void oled_task_user(void) {
    if (timer_elapsed(oled_timer) > 60000) {
        oled_off();
        return;
    }
    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
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

static bool is_suspended;
static bool rgb_matrix_enabled;

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
    if (!is_suspended) {
        is_suspended = true;
        rgb_matrix_enabled = (bool)rgb_matrix_config.enable;
        rgb_matrix_disable_noeeprom();
    }
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
    is_suspended = false;
    if (rgb_matrix_enabled) {
        rgb_matrix_enable_noeeprom();
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
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                bool mods_enabled = IS_LAYER_ON(_MODS);
                switch (biton32(default_layer_state)) {
                    case _QWERTY:
                        rgb_matrix_layer_helper(HSV_CYAN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _COLEMAK:
                        rgb_matrix_layer_helper(HSV_MAGENTA, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _DVORAK:
                        rgb_matrix_layer_helper(HSV_SPRINGGREEN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _WORKMAN:
                        rgb_matrix_layer_helper(HSV_GOLDENROD, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _NORMAN:
                        rgb_matrix_layer_helper(HSV_CORAL, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _MALTRON:
                        rgb_matrix_layer_helper(HSV_YELLOW, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _EUCALYN:
                        rgb_matrix_layer_helper(HSV_PINK, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                    case _CARPLAX:
                        rgb_matrix_layer_helper(HSV_BLUE, mods_enabled, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                        break;
                }
                break;
            }
        }
    }
}
#endif
