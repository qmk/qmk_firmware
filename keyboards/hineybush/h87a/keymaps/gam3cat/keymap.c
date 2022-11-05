#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    _BL = 0,    // Base Layer
    _WL,        // Workman Layer
    _NL,        // Norman Layer
    _DL,        // Dvorak Layer
    _CL,        // Base Layer
    _FL,        // Function Layer
    _AL,        // Adjust Layer
};

enum custom_keycodes {
    QMK_REV = SAFE_RANGE,
    KC_WEB,
    KC_SP4,
    DYNAMIC_MACRO_RANGE
};

extern backlight_config_t backlight_config;

#include "dynamic_macro.h"
#define FN_CAPS LT(_FL, KC_CAPS)
#define KC_DMR1 DYN_REC_START1
#define KC_DMR2 DYN_REC_START2
#define KC_DMP1 DYN_MACRO_PLAY1
#define KC_DMP2 DYN_MACRO_PLAY2
#define KC_DMRS DYN_REC_STOP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*#### _BL: Base Layer - Standard TKL QWERTY layout.
    *    .-----------------------------------------------------------------------.
    *    |Esc|||||F1 |F2 |F3 |F4 |||F5 |F6 |F7 |F8 |||F9 |F10|F11|F12|PSc|SLk|Pau|
    *    |-----------------------------------------------------------|-----------|
    *    |~  |1  |2  |3  |4  |5  |6  |7  |8  |9  |0  |-  |=  |Backsp |Ins|Hom|PgU|
    *    |-----------------------------------------------------------|-----------|
    *    |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  |]  |\    |Del|End|PgD|
    *    |-----------------------------------------------------------|-----------|
    *    |Caps  |A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |Return  |           |
    *    |-----------------------------------------------------------|-----------|
    *    |Shift   |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |Shift |Fn |   | Up|   |
    *    |-----------------------------------------------------------|-----------|
    *    |Ctrl |Win|Alt  |      Space                |RAlt |Fn |Ctrl |Lft|Dwn|Rgt|
    *    *-----------------------------------------------------------------------*
    */
    [_BL] = LAYOUT_all( \
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT,                                      \
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FL),                   KC_UP,            \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RGUI, KC_RALT, MO(_FL), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    /*#### _WL: Workman Layer.
    *    .-----------------------------------------------------------------------.
    *    |   |||||   |   |   |   |||   |   |   |   |||   |   |   |   |   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |Q  |D  |R  |W  |B  |J  |F  |U  |P  |;  |[  |]  |\    |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |      |A  |S  |H  |T  |G  |Y  |N  |E  |O  |I  |'  |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |Z  |X  |M  |C  |V  |K  |L  |,  |.  |/  |      |   |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |                           |     |   |     |   |   |   |
    *    *-----------------------------------------------------------------------*
    */
    [_WL] = LAYOUT_all( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN, _______, _______, _______,          _______, _______, _______, \
        _______, KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , _______, _______, _______,                                     \
        _______, _______, KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH, _______, _______,                   _______,          \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______ \
    ),
    /*#### _NL: Norman Layer.
    *    .-----------------------------------------------------------------------.
    *    |   |||||   |   |   |   |||   |   |   |   |||   |   |   |   |   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |Q  |W  |D  |F  |K  |J  |U  |R  |L  |;  |[  |]  |\    |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |      |A  |S  |E  |T  |G  |Y  |N  |I  |O  |H  |'  |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |Z  |X  |C  |V  |B  |P  |M  |,  |.  |/  |      |   |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |                           |     |   |     |   |   |   |
    *    *-----------------------------------------------------------------------*
    */
    [_NL] = LAYOUT_all( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_Q   , KC_W   , KC_D   , KC_F   , KC_K   , KC_J   , KC_U   , KC_R   , KC_L   , KC_SCLN, _______, _______, _______,          _______, _______, _______, \
        _______, KC_A   , KC_S   , KC_E   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_I   , KC_O   , KC_H   , _______, _______, _______,                                     \
        _______, _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______, _______,                   _______,          \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______ \
    ),
    /*#### _DL: Dvorak Layer.
    *    .-----------------------------------------------------------------------.
    *    |   |||||   |   |   |   |||   |   |   |   |||   |   |   |   |   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |   |   |   |   |   |   |   |   |   |   |   |[  |]  |       |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |'  |,  |.  |P  |Y  |F  |G  |C  |R  |L  |/  |=  |\    |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |      |A  |O  |E  |U  |I  |D  |H  |T  |N  |S  |-  |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |;  |Q  |J  |K  |X  |B  |M  |W  |V  |Z  |      |   |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |                           |     |   |     |   |   |   |
    *    *-----------------------------------------------------------------------*
    */
    [_DL] = LAYOUT_all( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, \
        _______, KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_SLSH, KC_EQL , _______,          _______, _______, _______, \
        _______, KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_MINS, _______, _______,                                     \
        _______, _______, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , _______, _______,                   _______,          \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______ \
    ),
    /*#### _CL: Colmak Layer.
    *    .-----------------------------------------------------------------------.
    *    |   |||||   |   |   |   |||   |   |   |   |||   |   |   |   |   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |Q  |W  |F  |P  |G  |J  |L  |U  |Y  |;  |[  |]  |\    |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |      |A  |R  |S  |T  |D  |H  |N  |E  |I  |O  |'  |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |Z  |X  |C  |V  |B  |K  |M  |,  |.  |/  |      |   |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |                           |     |   |     |   |   |   |
    *    *-----------------------------------------------------------------------*
    */
    [_CL] = LAYOUT_all( \
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______, _______, _______,          _______, _______, _______, \
        _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______, _______, _______,                                     \
        _______, _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______, _______,                   _______,          \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______,          _______, _______, _______ \
    ),
    /*#### _FL: Function Layer.
    *    .-----------------------------------------------------------------------.
    *    |   |||||   |   |   |   |||   |   |   |   |||   |VlM|VlD|VlU|   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |Web|   |   |   |   |   |   |   |   |   |   |   |   |       |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |Fn_AL|   |   |   |   |   |   |   |   |   |   |   |   |     |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |      |   |   |   |   |   |   |Lft|Dwn|Up |Rgt|   |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |   |   |   |   |   |   |   |   |   |   |      |Fn |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |      SP4                  |     |Fn |     |WBk|   |WFw|
    *    *-----------------------------------------------------------------------*
    */
    [_FL] = LAYOUT_all( \
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,          XXXXXXX, XXXXXXX, XXXXXXX, \
        KC_WEB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        MO(_AL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                   XXXXXXX,          \
        XXXXXXX, XXXXXXX, KC_MENU,                            KC_SP4,                             XXXXXXX, _______, XXXXXXX, XXXXXXX,          KC_WBAK, XXXXXXX, KC_WFWD \
    ),
    /*#### _AL: Adjust Layer - Keymap select, LED backlight, and Dynamic Macro settings.
    *    .-----------------------------------------------------------------------.
    *    |Rst|||||   |   |   |   |||   |   |   |   |||   |   |   |   |   |   |   |
    *    .-----------------------------------------------------------|-----------|
    *    |Rev|Tog|Mod|H- |H+ |S- |S+ |V- |V+ |   |BLT|BL-|BL+|       |   |MR1|MP1|
    *    |-----------------------------------------------------------|-----------|
    *    |Fn_AL|_BL|_WL|   |   |   |   |   |   |   |   |   |   |     | MS|MR2|MP2|
    *    |-----------------------------------------------------------|-----------|
    *    |      |   |   |_DL|   |   |   |   |   |   |   |   |        |           |
    *    |-----------------------------------------------------------|-----------|
    *    |        |   |   |_CL|   |_BL|_NL|   |   |   |   |      |Fn |   |   |   |
    *    |-----------------------------------------------------------|-----------|
    *    |     |   |     |                           |     |Fn |     |   |   |   |
    *    *-----------------------------------------------------------------------*
    */
    [_AL] = LAYOUT_all( \
        RESET,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, \
        QMK_REV, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, BL_TOGG, BL_DEC,  BL_INC,  XXXXXXX, XXXXXXX, XXXXXXX, KC_DMR1, KC_DMP1, \
        _______, DF(_BL), DF(_WL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_DMRS, KC_DMR2, KC_DMP2, \
        XXXXXXX, XXXXXXX, XXXXXXX, DF(_DL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(_CL), XXXXXXX, DF(_BL), DF(_NL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                   XXXXXXX,          \
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, _______, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMK_REV:
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP "@" QMK_VERSION ":" QMK_BUILDDATE);
            }
            return false;
            break;
        case KC_WEB:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("r"));
                wait_ms(100);
                SEND_STRING("chrome.exe\n");
            }
            return false;
            break;
        case KC_SP4:
            if (record->event.pressed) {
                SEND_STRING ("    ");
            }
            return false;
            break;
    }
    // Dynamic Macros.
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }
    return true;
}

void custom_backlight_level(uint8_t level) {
    if (level > BACKLIGHT_LEVELS)
        level = BACKLIGHT_LEVELS;
    backlight_config.level = level;
    backlight_config.enable = !!backlight_config.level;
    backlight_set(backlight_config.level);
}

void matrix_init_user(void) {
    #ifdef BACKLIGHT_ENABLE
        custom_backlight_level(0);
    #endif
    #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
        rgblight_sethsv_noeeprom(180,100,100);
    #endif
}

void matrix_scan_user(void) {

}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BL:
            custom_backlight_level(0);
            rgblight_sethsv_noeeprom(180,100,255);
            break;
        case _WL:
        case _NL:
        case _DL:
        case _CL:
            custom_backlight_level(1);
            rgblight_sethsv_noeeprom(230,255,255);
            break;
        case _FL:
            custom_backlight_level(2);
            rgblight_sethsv_noeeprom(240,255,255);
            break;
        case _AL:
            custom_backlight_level(3);
            rgblight_sethsv_noeeprom(255,255,255);
            break;
        default:
            custom_backlight_level(0);
            rgblight_sethsv_noeeprom(180,100,100);
            break;
    }
    return state;
}

void led_init_ports(void) {
  DDRD |= (1<<5); // OUT
  DDRE |= (1<<6); // OUT
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    DDRD |= (1 << 5); PORTD &= ~(1 << 5);
  } else {
    DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
  }
  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    DDRE |= (1 << 6); PORTE &= ~(1 << 6);
  } else {
    DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);
  }
}
