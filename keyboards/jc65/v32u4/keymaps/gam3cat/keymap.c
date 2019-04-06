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
    DYNAMIC_MACRO_RANGE = SAFE_RANGE,
    QMK_REV,
    KC_WEB,
    KC_SP4
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
    /*#### _BL: Base Layer - Mostly standard 65% QWERTY layout.
    *  .---------------------------------------------------------------.
    *  |GrE|1  |2  |3  |4  |5  |6  |7  |8  |9  |0  |-  |=  |Backsp |Ins|
    *  |---------------------------------------------------------------|
    *  |Tab  |Q  |W  |E  |R  |T  |Y  |U  |I  |O  |P  |[  |]  |\    |Del|
    *  |---------------------------------------------------------------|
    *  |FnCaps|A  |S  |D  |F  |G  |H  |J  |K  |L  |;  |'  |Return  |PgU|
    *  |---------------------------------------------------------------|
    *  |Shift   |Z  |X  |C  |V  |B  |N  |M  |,  |.  |/  |Shift |Up |PgD|
    *  |---------------------------------------------------------------|
    *  |Ctrl|Gui |Alt |      Space             |RAlt |Ctrl |Lft|Dwn|Rgt|
    *  *---------------------------------------------------------------*
    */
    [_BL] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_INS,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        FN_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_PGUP,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC,           KC_SPC,           KC_SPC,           KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*#### _WL: Workman Layer.
    *  .---------------------------------------------------------------.
    *  |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |
    *  |---------------------------------------------------------------|
    *  |     |Q  |D  |R  |W  |B  |J  |F  |U  |P  |;  |[  |]  |\    |   |
    *  |---------------------------------------------------------------|
    *  |      |A  |S  |H  |T  |G  |Y  |N  |E  |O  |I  |'  |        |   |
    *  |---------------------------------------------------------------|
    *  |        |Z  |X  |M  |C  |V  |K  |L  |,  |.  |/  |      |   |   |
    *  |---------------------------------------------------------------|
    *  |    |    |    |                        |     |     |   |   |   |
    *  *---------------------------------------------------------------*
    */
    [_WL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          KC_Q   , KC_D   , KC_R   , KC_W   , KC_B   , KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN, _______, _______, _______, _______,
        _______,          KC_A   , KC_S   , KC_H   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , _______, _______,          _______,
        _______, _______, KC_Z   , KC_X   , KC_M   , KC_C   , KC_V   , KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______, _______,
        _______, _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, _______
    ),
    /*#### _NL: Norman Layer.
    *  .---------------------------------------------------------------.
    *  |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |
    *  |---------------------------------------------------------------|
    *  |     |Q  |W  |D  |F  |K  |J  |U  |R  |L  |;  |[  |]  |\    |   |
    *  |---------------------------------------------------------------|
    *  |      |A  |S  |E  |T  |G  |Y  |N  |I  |O  |H  |'  |        |   |
    *  |---------------------------------------------------------------|
    *  |        |Z  |X  |C  |V  |B  |P  |M  |,  |.  |/  |      |   |   |
    *  |---------------------------------------------------------------|
    *  |    |    |    |                        |     |     |   |   |   |
    *  *---------------------------------------------------------------*
    */
    [_NL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          KC_Q   , KC_W   , KC_D   , KC_F   , KC_K   , KC_J   , KC_U   , KC_R   , KC_L   , KC_SCLN, _______, _______, _______, _______,
        _______,          KC_A   , KC_S   , KC_E   , KC_T   , KC_G   , KC_Y   , KC_N   , KC_I   , KC_O   , KC_H   , _______, _______,          _______,
        _______, _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_P   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______, _______,
        _______, _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, _______
    ),
    /*#### _DL: Dvorak Layer.
    *  .---------------------------------------------------------------.
    *  |   |   |   |   |   |   |   |   |   |   |   |[  |]  |       |   |
    *  |---------------------------------------------------------------|
    *  |     |'  |,  |.  |P  |Y  |F  |G  |C  |R  |L  |/  |=  |\    |   |
    *  |---------------------------------------------------------------|
    *  |      |A  |O  |E  |U  |I  |D  |H  |T  |N  |S  |-  |        |   |
    *  |---------------------------------------------------------------|
    *  |        |;  |Q  |J  |K  |X  |B  |M  |W  |V  |Z  |      |   |   |
    *  |---------------------------------------------------------------|
    *  |    |    |    |                        |     |     |   |   |   |
    *  *---------------------------------------------------------------*
    */
    [_DL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______,
        _______,          KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   , KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_SLSH, KC_EQL , _______, _______,
        _______,          KC_A   , KC_O   , KC_E   , KC_U   , KC_I   , KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_MINS, _______,          _______,
        _______, _______, KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   , KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   ,          _______, _______, _______,
        _______, _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, _______
    ),
    /*#### _CL: Colmak Layer.
    *  .---------------------------------------------------------------.
    *  |   |   |   |   |   |   |   |   |   |   |   |-  |=  |       |   |
    *  |---------------------------------------------------------------|
    *  |     |Q  |W  |F  |P  |G  |J  |L  |U  |Y  |;  |[  |]  |\    |   |
    *  |---------------------------------------------------------------|
    *  |      |A  |R  |S  |T  |D  |H  |N  |E  |I  |O  |'  |        |   |
    *  |---------------------------------------------------------------|
    *  |        |Z  |X  |C  |V  |B  |K  |M  |,  |.  |/  |      |   |   |
    *  |---------------------------------------------------------------|
    *  |    |    |    |                        |     |     |   |   |   |
    *  *---------------------------------------------------------------*
    */
    [_CL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   , KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______, _______, _______, _______,
        _______,          KC_A   , KC_R   , KC_S   , KC_T   , KC_D   , KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______, _______,          _______,
        _______, _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          _______, _______, _______,
        _______, _______,          _______, _______,          _______,          _______,          _______, _______, _______, _______, _______, _______
    ),
    /*#### _FL: Function Layer.
    *  .---------------------------------------------------------------.
    *  |Web|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|SLock  |PSc|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|   |   |   |   |   |   |   |   |   |   |   |   |     |Pau|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |   |   |   |Lft|Dwn|Up |Rgt|   |   |        |Hme|
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |VlMute|VlU|End|
    *  |---------------------------------------------------------------|
    *  |    |    |Menu|      SP4               |     |     |WBk|VlD|WFw|
    *  *---------------------------------------------------------------*
    */
    [_FL] = LAYOUT(
        KC_WEB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, KC_SLCK, KC_PSCR,
        MO(_AL),          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS,
        _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,          KC_HOME,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_MUTE, KC_VOLU, KC_END,
        XXXXXXX, XXXXXXX,          KC_MENU, KC_SP4,           KC_SP4,           KC_SP4,           XXXXXXX, XXXXXXX, XXXXXXX, KC_WBAK, KC_VOLD, KC_WFWD
    ),
    /*#### _AL: Adjust Layer - Keymap select, RGB Underglow, LED backlight, and Dynamic Macro settings.
    *  .---------------------------------------------------------------.
    *  |Rev|Tog|Mod|H- |H+ |S- |S+ |V- |V+ |   |BLT|BL-|BL+|       |MP1|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|_BL|_WL|   |   |   |   |   |   |   |   |   |   |     |MR1|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |_DL|   |   |   |   |   |   |   |   |        |MS |
    *  |---------------------------------------------------------------|
    *  |        |   |   |_CL|   |_BL|_NL|   |   |   |   |      |   |MR2|
    *  |---------------------------------------------------------------|
    *  |Rst |    |    |                        |     |     |   |   |MP2|
    *  *---------------------------------------------------------------*
    */
    [_AL] = LAYOUT(
        QMK_REV, RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, BL_TOGG, BL_DEC,  BL_INC,  XXXXXXX, XXXXXXX, KC_DMP1,
        _______,          DF(_BL), DF(_WL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DMR1,
        _______,          XXXXXXX, XXXXXXX, DF(_DL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          KC_DMRS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(_CL), XXXXXXX, DF(_BL), DF(_NL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, KC_DMR2,
        RESET,   XXXXXXX,          XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DMP2
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
                SEND_STRING("chrome.exe https://geekhack.org/index.php?topic=86756.new;topicseen#new\n");
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

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
       case _BL:
           custom_backlight_level(0);
           rgblight_sethsv_noeeprom(180,100,255);
           break;
       case _WL:
           custom_backlight_level(1);
           rgblight_sethsv_noeeprom(180,95,240);
           break;
       case _NL:
           custom_backlight_level(1);
           rgblight_sethsv_noeeprom(180,90,225);
           break;
       case _DL:
           custom_backlight_level(1);
           rgblight_sethsv_noeeprom(180,85,210);
           break;
       case _CL:
           custom_backlight_level(1);
           rgblight_sethsv_noeeprom(180,80,195);
           break;
       case _FL:
           custom_backlight_level(2);
           rgblight_sethsv_noeeprom(230,255,255);
           break;
       case _AL:
           custom_backlight_level(3);
           rgblight_sethsv_noeeprom(350,255,255);
           break;
       default:
           custom_backlight_level(0);
           rgblight_sethsv_noeeprom(180,100,100);
           break;
    }
    return state;
}

void led_set_user(uint8_t usb_led) {

}
