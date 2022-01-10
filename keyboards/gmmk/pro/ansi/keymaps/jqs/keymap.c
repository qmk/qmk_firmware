#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 End
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgUp
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       PgDn
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        RGB_TOG, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, DEBUG,            _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            NK_TOGG,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    )
};
uint8_t thisHue = 0;
uint8_t thisSat = 255;
uint8_t thisVal = 255;

void encoder_action_hsv_change(bool clockwise, uint8_t hueChange, uint8_t satChange, uint8_t valChange) {
    if (clockwise) {
        thisHue += hueChange;
        thisSat += satChange;
        thisVal += valChange;
    } else {
        thisHue -= hueChange;
        thisSat -= satChange;
        thisVal -= valChange;
    }            
}

// #ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
     uint8_t mods_state = get_mods();

    if (mods_state & MOD_BIT(KC_LCTL)) {
        encoder_action_hsv_change(clockwise, 2, 0, 0); // Hue change
    } else if (mods_state & MOD_BIT(KC_LSFT)) {
        encoder_action_hsv_change(clockwise, 0, 2, 0); // Saturation change
    } else if (mods_state & MOD_BIT(KC_LALT)) {  
        encoder_action_hsv_change(clockwise, 0, 0, 2); // Value/Brightness change
    } 
    else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }   
    return true;
}
// #endif // ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE

// RGB LED layout

// led index number, function of the key

//  67, Side led 01    0, ESC      6, F1       12, F2       18, F3       23, F4       28, F5       34, F6       39, F7       44, F8       50, F9       56, F10      61, F11      66, F12      69, Prt       Rotary(Mute)   68, Side led 12
//  70, Side led 02    1, ~        7, 1        13, 2        19, 3        24, 4        29, 5        35, 6        40, 7        45, 8        51, 9        57, 0        62, -_       78, (=+)     85, BackSpc   72, Del        71, Side led 13
//  73, Side led 03    2, Tab      8, Q        14, W        20. E        25, R        30, T        36, Y        41, U        46, I        52, O        58, P        63, [{       89, ]}       93, \|        75, PgUp       74, Side led 14
//  76, Side led 04    3, Caps     9, A        15, S        21, D        26, F        31, G        37, H        42, J        47, K        53, L        59, ;:       64, '"                    96, Enter     86, PgDn       77, Side led 15
//  80, Side led 05    4, Sh_L     10, Z       16, X        22, C        27, V        32, B        38, N        43, M        48, ,<       54, .<       60, /?                    90, Sh_R     94, Up        82, End        81, Side led 16
//  83, Side led 06    5, Ct_L     11,Win_L    17, Alt_L                              33, SPACE                              49, Alt_R    55, FN                    65, Ct_R     95, Left     97, Down      79, Right      84, Side led 17
//  87, Side led 07                                                                                                                                                                                                        88, Side led 18
//  91, Side led 08 
const int SIZE = 8;
int lockCaps[] = { 3, 70, 73 };
int scrollCaps[] = { 76, 80 };
int numCaps[] = { 83, 87 };
int leftAll[] = { 67, 70, 73, 76, 80, 83, 87, 91 };
int leftBorder[] = { 67, 91 };
int rightAll[] = { 68, 71, 74, 77, 81, 84, 88, 92 };

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color_all(RGB_WHITE);
    } else {
        HSV hsv = {thisHue, thisSat, thisVal};
        RGB rgb = hsv_to_rgb(hsv);
        for (int i = 0; i < SIZE; i++) {
            rgb_matrix_set_color(leftAll[i], rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(rightAll[i], rgb.r, rgb.g, rgb.b);
        }
    }
}


#endif // RGB_MATRIX_ENABLE