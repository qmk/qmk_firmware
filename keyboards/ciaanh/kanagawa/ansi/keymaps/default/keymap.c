#include QMK_KEYBOARD_H

/* Keyboard layout
*   ,---------.   ,---------------------------------------.  ,---------------------------------------.  ,---------------------------------------.    ,---------.
*   |   ka0   |   |   ka1   |   ka2   |   ka3   |   ka4   |  |   ka5   |   ka6   |   ka7   |   ka8   |  |   ka9   |  ka10   |  ka11   |  ka12   |    |  sw99   |
*   `---------'   `---------+---------+---------+---------'  `---------+---------+---------+---------'  `---------+---------+---------+---------'    `---------'
*   ,-------------------------------------------------------------------------------------------------------------------------------------------.    ,---------.
*   |   kb0   |   kb1   |   kb2   |   kb3   |   kb4   |   kb5   |   kb6   |   kb7   |   kb8   |   kb9   |  kb10   |  kb11   |  kb12   |  kb13   |    |  kd13   |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|    |---------|
*   |   kc0   |   kc1   |   kc2   |   kc3   |   kc4   |   kc5   |   kc6   |   kc7   |   kc8   |   kc9   |  kc10   |  kc11   |  kc12   |  kc13   |    |  ke13   |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'    |---------|
*   |   kd0   |   kd1   |   kd2   |   kd3   |   kd4   |   kd5   |   kd6   |   kd7   |   kd8   |   kd9   |  kd10   |  kd11   |       kd12        |    |  kf13   |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'---------'    `---------'
*   |     ke0     | --- |   ke2   |   ke3   |   ke4   |   ke5   |   ke6   |   ke7   |   ke8   |   ke9   |  ke10   |  ke11   |  ke12   |  ,---------.
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'  |  kf12   |
*   |   kf0   |   kf1   |   kf2   |   kf3   |           ,---------.     ,---------.           |   kf6   |   kf7   |   kf8   |  ,---------|---------|---------.
*   `---------+---------+---------+---------+           |   kf4   |     |   kf5   |           +---------+---------+---------'  |   kf9   |  kf10   |  kf11   |
*                                                       `---------'     `---------'                                            `---------+---------+---------'
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap: BASE
*   ,---------.   ,---------------------------------------.  ,---------------------------------------.  ,---------------------------------------.    ,---------.
*   |   ESC   |   |   F1    |   F2    |   F3    |   F4    |  |   F5    |   F6    |   F7    |   F8    |  |   F9    |   F10   |   F11   |   F12   |    | ENCODER |
*   `---------'   `---------+---------+---------+---------'  `---------+---------+---------+---------'  `---------+---------+---------+---------'    `---------'
*   ,-------------------------------------------------------------------------------------------------------------------------------------------.    ,---------.
*   |    `    |    1    |    2    |    3    |    4    |    5    |    6    |    7    |    8    |    9    |    0    |    -    |    =    |Backspace|    |  Delete |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|    |---------|
*   |   Tab   |    Q    |    W    |    E    |    R    |    T    |    Y    |    U    |    I    |    O    |    P    |    [    |    ]    |    \    |    |   HOME  |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'    |---------|
*   |  CapsL  |    A    |    S    |    D    |    F    |    G    |    H    |    J    |    K    |    L    |    ;    |    '    |      ENTER        |    |   END   |
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'---------'    `---------'
*   |   LShift    | --- |    Z    |    X    |    C    |    V    |    B    |    N    |    M    |    ,    |    .    |    /    | RShift  |  ,---------.
*   |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'  |    UP   |
*   |  LCtrl  |   LGUI  |   LAlt  |  Func   |           ,---------.     ,---------.           |   RAlt  |   CODE  |  RCtrl  |  ,---------|---------|---------.
*   |---------+---------+---------+---------+           |  Space  |     |  Space  |           +---------+---------+---------'  |  LEFT   |   DOWN  |  RIGHT  |
*                                                       `---------'     `---------'                                            `---------+---------+---------'  
*/
    [_BASE] = LAYOUT_ansi( 
          KC_ESC,   KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,           KC_MPLY,  \
        
          KC_GRV,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSPC,   KC_DEL,  \
          KC_TAB,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS,  KC_HOME,  \
         KC_CAPS,    KC_A, LT(0,KC_S),       KC_D,       KC_F,       KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,            KC_END,  \
         KC_LSFT, XXXXXXX,       KC_Z, LT(0,KC_X), LT(0,KC_C), LT(0,KC_V),    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,    KC_UP,           \
         KC_LCTL, KC_LGUI,    KC_LALT,     L_CODE,        KC_SPC,        KC_SPC,             TO_FUNC, KC_RALT, KC_RCTL,           KC_LEFT, KC_DOWN, KC_RGHT   \
    ),

    [_CODE] = LAYOUT_ansi(
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,  \

       _SCRNSHOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,           \
         XXXXXXX, XXXXXXX, XXXXXXX, _______,         XXXXXXX,       XXXXXXX,              XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX   \
    ),


    [_FUNC] = LAYOUT_ansi(
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             RGB_TOG,  \

         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_VAI,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              RGB_VAD,  \
         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     RGB_HUI,           \
         XXXXXXX, XXXXXXX, XXXXXXX, _______,         XXXXXXX,       XXXXXXX,              TO_BASE, RGB_SPD, RGB_SPI,     RGB_SAD, RGB_HUD, RGB_SAI   \
    ),

};





/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

#ifdef OLED_ENABLE
    static void render_status(void) {
        // 21 characters per line
        // 16 cols / 4 rows

        oled_write_P(PSTR("    Kanagawa rev 2.1   "), false);
        //oled_write_ln("", false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_P(PSTR("_\n"), false);
                break;
            case _FUNC:
                oled_write_P(PSTR("[Fn]\n"), false);
                break;
            case _CODE:
                oled_write_P(PSTR("[Code]\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_ln(led_state.caps_lock ? "CAPLOCK" : "       ", false);
        // oled_write_P(PSTR("         "), false);
        
        // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

        oled_write_ln("", false);
        // oled_write_ln("", false);
        // oled_write_ln("", false);
        // oled_write_ln("", false);
        // oled_write_ln("", false);
    }

    // static void render_kanagawa_logo(void) {
    //     static const char PROGMEM kanagawa_logo[] = {
    //         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192, 64, 96, 96, 48, 24, 24,  8, 12, 12, 12,  4,  4,  6,134,134,195,194,194,210,250,250,254,254,254,188,124,252,232,248,216, 48,160,224,192,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    //         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192, 96, 48, 48, 24, 12,  4,  6,  3,  3,  0,192,192,208,248,248,252,255,255,127,254,158, 46,158,220, 63, 63, 63, 63, 63, 15,  7, 63, 63, 63,255,255,247,255,255,255,255,255,255,191,255,255,175, 28, 32,160,224,224,224,224,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
    //         0,  0,128,192, 96, 96, 48, 24, 12,  6,  3,  3,  0,128,128,192,192,192,  0,  0,  0,  0,  0,  0,143,153, 31, 63, 38,191,247,240,248,254,127,137,224,252,206,  7,192,240, 24, 60, 70,146,227,225,241,123,127,127, 55, 55,255,255,255,255,255,127,254,255,223, 63,255,255,255,255,255,158, 30, 56, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 56,
    //         56,248,249,241,248,248,224,240,240,252,254,255,255,239,231,239,255,255,253,252,248,216,254,254,252,255,255,255,255,254,254,253,251,247,255,254,255,255,255,255,255,255,253,249, 88,126,255,255, 15,  1,  0,  0,  0,  0,  0,  0,  3,  3,  1,  7,  1,  1,  1,  3, 31, 31, 27, 31, 31, 27,  3,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,
    //         62,124,208,240,185,135,135,195,255,255,255,255,199,159,255,255,255,255,255,255,255,255, 63,127, 63, 63,126,255,255,255,255,255,255,255,255,223,191,255,255,255,207,111,111,127,243,255,248,204,143,255,252,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,224, 48,  0,  0,  0,  0,  0,128,192,192,  0,  0, 10,
    //         31,255,255,223,135, 63,111,255, 95,127,191,255,127,127,255,215, 63, 63,127,127,254,252,253,249,255,255,255,255,252,253,124,127, 63, 31, 15,  7,  3,  1,  0,128,224,224,  0,  0,  1,  1,  1,  3,  7, 63,127,239,238,124,224,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,224,224,224,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192, 64, 96,176,152,200,204,195,227,193,192,224,248,176, 60, 63,191,255,116,  9,  0,  0,  0,  0,  1, 
    //         3,  0,  0,  0,  0,  3,  3,  2,  1, 11,204,207,  7, 12, 14, 13,  8, 96,244,247,227,225,225,193,  0,192,192,192,192,232,184,252,236,240,255,254,255,127,255,255,252,216,236,252,240,224,248,248,240,241,131,  7,142, 32,126,255,255,239,198,228,236,216,240,240,248,248,236,228,230,230,199, 71, 71, 71,199, 79,207,207,199,207, 79,238,238,108,236,232,184,240,240,208,216,248,232,236, 52,126,254,255,251,249,253,252,252,254,253,255,255,255,127,125,253,253,255,254,239,231, 31, 31, 63,  0, 96,  0,  0,  0,
    //         32,224,112,224,192,128,  0,  0,  0,  0,  0,224,224,  0,  0,  0,252,120, 14,126,127,103,255,255,127,127,239,240,241,249,241,225,241,247,255,255,253,252,252,252,252,255,255,255,251,241,143, 63,255,143, 63,239,143, 63,127,255,254, 56,113,243,246,229,235,239,255,243,163,231, 78,221,219,179,167,143,158, 31, 63, 55,127,126,112,193,192,212,191,188,167,  7, 95,126,254,254,255,120,124,127,127,127,255,255,255,247,231, 47, 47, 31, 31, 15,231,243, 51, 51,115,115,  3,  1,  1,  0,192,192,192,192,  0,
    //     };
    //     oled_write_raw_P(kanagawa_logo, sizeof(kanagawa_logo));
    // }
    
    // static void render_kanagawa_logo(void) {
    //     //oled_set_cursor(0, 5);

    //     static const char PROGMEM kanagawa_logo[] = {
    //         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    //         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    //         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    //     };

    //     oled_write_P(kanagawa_logo, false);
    // }

    bool oled_task_user(void) {
        // switch (get_highest_layer(layer_state)) {
        //     case _UPPER:
        //         render_kanagawa_logo();
        //         break;
        //     default:
        //         render_status();
        // }

        render_status();

        return false;
    }
#endif

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CUSTOMKEY:
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                tap_code16(G(A(KC_K)));
            } else {
                tap_code(KC_MPLY);
            }
        } 
        break; 
    case LT(0,KC_X):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-X
            return false;
        }
        return true;
    case LT(0,KC_C):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
            return false;
        }
        return true;
    case LT(0,KC_V):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
            return false;
        }
        return true;  
    case LT(0,KC_S):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(C(KC_S)); // Intercept hold function to send Ctrl-S
            return false;
        }
        return true;  
  }
  return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CODE] =  { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_FUNC] =   { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD) },
};
#endif

