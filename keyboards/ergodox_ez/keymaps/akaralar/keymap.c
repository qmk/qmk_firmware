#include QMK_KEYBOARD_H
#include "version.h"
#include "raw_hid.h"

enum layers {
    BASE,  // default layer
    NAVI,  // navigation layer
    MOUS,  // mouse layer
    MDIA,  // media keys layer
    NUMB,  // numbers layer
    CODE,  // code symbols layer
    FUNC,
    FUND,  // Fn keys layer
    BTTN,  // one handed usage layer
    WNDW,  // easy mac window and app navigation
};

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_MAC_REDO C_REDO
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)

enum C_keycodes {
#ifdef ORYX_CONFIGURATOR
    VRSN = EZ_SAFE_RANGE,
#else
    VRSN = SAFE_RANGE,
#endif
    RGB_SLD,
    BASE_LAYER,
    NAV_LAYER,
    MOUSE_LAYER,
    MEDIA_LAYER,
    NUM_LAYER,
    CODE_LAYER,
    FN_LAYER,
    BUTTON_LAYER,
    WINDOW_LAYER,
};

#define C_E MEH_T(KC_E)
#define C_R ALL_T(KC_R)

#define C_A MT(MOD_LCTL, KC_A)
#define C_S MT(MOD_LALT, KC_S)
#define C_D MT(MOD_LGUI, KC_D)
#define C_F MT(MOD_LSFT, KC_F)

#define C_U ALL_T(KC_U)
#define C_I MEH_T(KC_I)

#define C_QUOTE MT(MOD_RCTL, KC_QUOTE)
#define C_L MT(MOD_LALT, KC_L)
#define C_K MT(MOD_RGUI, KC_K)
#define C_J MT(MOD_RSFT, KC_J)

#define C_MOOM LALT(LCTL(LSFT(KC_GRAVE)))
#define C_ALFRED LGUI(KC_SPACE)
#define C_REDO LGUI(LSFT(KC_Z))

#define C_L1 LT(1, KC_SPACE)
#define C_L2 LT(2, KC_TAB)
#define C_L3 LT(3, KC_ESCAPE)
#define C_L4 LT(4, KC_BSPACE)
#define C_L5 LT(5, KC_ENTER)
#define C_L6 LT(6, KC_DELETE)
#define C_L9 LM(9, MOD_LGUI)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


    /*
     * ,--------------------------------------------------.    ,--------------------------------------------------.
     * |    0   |   1  |   2  |   3  |   4  |   5  |  6   |    |  38  |  39  |  40  |  41  |  42  |  43  |   44   |
     * |--------+------+------+------+------+------+------|    |------+------+------+------+------+------+--------|
     * |    7   |   8  |   9  |  10  |  11  |  12  |  13  |    |  45  |  46  |  47  |  48  |  49  |  50  |   51   |
     * |--------+------+------+------+------+------|      |    |      |------+------+------+------+------+--------|
     * |   14   |  15  |  16  |  17  |  18  |  19  |------|    |------|  52  |  53  |  54  |  55  |  56  |   57   |
     * |--------+------+------+------+------+------|  26  |    |  58  |------+------+------+------+------+--------|
     * |   20   |  21  |  22  |  23  |  24  |  25  |      |    |      |  59  |  60  |  61  |  62  |  63  |   64   |
     * `--------+------+------+------+------+-------------'    `-------------+------+------+------+------+--------'
     *   |  27  |  28  |  29  |  30  |  31  |                                |  65  |  66  |  67  |  68  |  69  |
     *   `----------------------------------'                                `----------------------------------'
     *                                       ,-------------.  ,-------------.
     *                                       |  32  |  33  |  |  70  |  71  |
     *                                ,------+------+------|  |------+------+------.
     *                                |      |      |  34  |  |  72  |      |      |
     *                                |  35  |  36  |------|  |------|  74  |  75  |
     *                                |      |      |  37  |  |  73  |      |      |
     *                                `--------------------'  `--------------------'
     */

[BASE] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______ , _______, _______ , _______,
_______, KC_Q   , KC_W   , C_E    , C_R    , KC_T   , _______,      _______, KC_Y   , C_U    , C_I     , KC_O   , KC_P    , _______,
_______, C_A    , C_S    , C_D    , C_F    , KC_G   ,                        KC_H   , C_J    , C_K     , C_L    , C_QUOTE , _______,
_______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,      _______, KC_N   , KC_M   , KC_COMMA, KC_DOT , KC_SLASH, _______,
_______, _______, _______, _______, C_L3   ,                                          C_L6   , _______ , _______, _______ , _______,

                                             TT(8)  , _______,      _______, _______,
                                                      _______,      _______,
                                    C_L1   , C_L2   , KC_F24 ,      C_L9   , C_L5   , C_L4
),

[NAVI] = LAYOUT_ergodox_pretty(
_______, _______    , _______   , _______    , _______     , _______ , _______,      _______, _______  , _______     , _______    , _______   , _______    , _______,
_______, XXXXXXX    , XXXXXXX   , KC_MEH     , KC_HYPR     , C_MOOM  , _______,      _______, KC_PGUP  , KC_HOME     , KC_UP      , KC_END    , KC_INSERT  , _______,
_______, KC_LCTRL   , KC_LALT   , KC_LGUI    , KC_LSHIFT   , C_ALFRED,                        KC_PGDOWN, KC_LEFT     , KC_DOWN    , KC_RIGHT  , KC_CAPSLOCK, _______,
_______, KC_MAC_UNDO, KC_MAC_CUT, KC_MAC_COPY, KC_MAC_PASTE, C_REDO  , _______,      _______, C_REDO   , KC_MAC_PASTE, KC_MAC_COPY, KC_MAC_CUT, KC_MAC_UNDO, _______,
_______, _______    , _______   , _______    , XXXXXXX     ,                                             KC_DELETE   , _______    , _______   , _______    , _______,

                                                             XXXXXXX , XXXXXXX,      _______, _______  ,
                                                                       _______,      _______,
                                               _______     , XXXXXXX , XXXXXXX,      _______, KC_ENTER , KC_BSPACE
),

[MOUS] = LAYOUT_ergodox_pretty(
_______, _______ , _______, _______, _______  , _______, _______,      _______, _______      , _______      , _______    , _______       , _______    , _______,
_______, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, KC_MS_WH_UP  , KC_MS_WH_LEFT, KC_MS_UP   , KC_MS_WH_RIGHT, XXXXXXX    , _______,
_______, KC_LCTRL, KC_LALT, KC_LGUI, KC_LSHIFT, XXXXXXX,                        KC_MS_WH_DOWN, KC_MS_LEFT   , KC_MS_DOWN , KC_MS_RIGHT   , XXXXXXX    , _______,
_______, XXXXXXX , XXXXXXX, XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, C_REDO       , KC_MAC_PASTE , KC_MAC_COPY, KC_MAC_CUT    , KC_MAC_UNDO, _______,
_______, _______ , _______, _______, _______  ,                                                KC_MS_BTN2   , _______    , _______       , _______    , _______,

                                                XXXXXXX, XXXXXXX,      _______, _______      ,
                                                         _______,      _______,
                                     XXXXXXX  , _______, XXXXXXX,      _______, KC_MS_BTN1   , KC_MS_BTN3
),

[MDIA] = LAYOUT_ergodox_pretty(
_______, _______ , _______    , _______, _______  , _______, _______,      _______, _______           , _______            , _______          , _______        , _______            , _______,
_______, RESET   , WEBUSB_PAIR, XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, RGB_TOG           , RGB_MOD            , RGB_HUI          , RGB_SAI        , RGB_VAI            , _______,
_______, KC_LCTRL, KC_LALT    , KC_LGUI, KC_LSHIFT, XXXXXXX,                        XXXXXXX           , KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK, _______,
_______, XXXXXXX , XXXXXXX    , XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP   , RGB_HUD          , RGB_SAD        , RGB_VAD            , _______,
_______, _______ , _______    , _______, _______  ,                                                     KC_AUDIO_MUTE      , _______          , _______        , _______            , _______,

                                                    XXXXXXX, XXXXXXX,      _______, _______           ,
                                                             _______,      _______,
                                         XXXXXXX  , XXXXXXX, XXXXXXX,      _______, KC_MEDIA_STOP     , KC_MEDIA_PLAY_PAUSE
),

[NUMB] = LAYOUT_ergodox_pretty(
_______, _______    , _______, _______, _______, _______    , _______,      _______, _______, _______  , _______, _______, _______ , _______,
_______, KC_LBRACKET, KC_7   , KC_8   , KC_9   , KC_RBRACKET, _______,      _______, XXXXXXX, KC_HYPR  , KC_MEH , XXXXXXX, XXXXXXX , _______,
_______, KC_SCOLON  , KC_4   , KC_5   , KC_6   , KC_EQUAL   ,                        XXXXXXX, KC_RSHIFT, KC_RGUI, KC_RALT, KC_RCTRL, _______,
_______, KC_GRAVE   , KC_1   , KC_2   , KC_3   , KC_BSLASH  , _______,      _______, XXXXXXX, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX , _______,
_______, _______    , _______, _______, KC_DOT ,                                              XXXXXXX  , _______, _______, _______ , _______,

                                                 XXXXXXX    , XXXXXXX,      _______, _______,
                                                              _______,      _______,
                                        KC_0   , KC_MINUS   , XXXXXXX,      _______, XXXXXXX, _______
),

[CODE] = LAYOUT_ergodox_pretty(
_______, _______ , _______  , _______, _______ , _______ , _______,      _______, _______ , _______    , _______    , _______  , _______ , _______,
_______, KC_TILD , KC_PIPE  , KC_LABK, KC_RABK , KC_PLUS , _______,      _______, KC_ASTR , KC_LCBR    , KC_RCBR    , KC_COLN  , KC_DQUO , _______,
_______, KC_GRAVE, KC_BSLASH, KC_LPRN, KC_RPRN , KC_MINUS,                        KC_SLASH, KC_LBRACKET, KC_RBRACKET, KC_SCOLON, KC_QUOTE, _______,
_______, KC_EXLM , KC_AT    , KC_HASH, KC_DLR  , KC_PERC , _______,      _______, KC_CIRC , KC_AMPR    , KC_COMMA   , KC_DOT   , KC_QUES , _______,
_______, _______ , _______  , _______, KC_UNDS ,                                            XXXXXXX    , _______    , _______  , _______ , _______,

                                                 XXXXXXX , XXXXXXX,      _______, _______ ,
                                                           _______,      _______,
                                       KC_SPACE, KC_EQUAL, XXXXXXX,      _______, _______ , XXXXXXX
),

[FUNC] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______  , _______, _______,      _______, _______, _______  , _______, _______, _______ , _______,
_______, KC_F12 , KC_F7  , KC_F8  , KC_F9    , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX , _______,
_______, KC_F11 , KC_F4  , KC_F5  , KC_F6    , XXXXXXX,                        XXXXXXX, KC_RSHIFT, KC_RGUI, KC_RALT, KC_RCTRL, _______,
_______, KC_F10 , KC_F1  , KC_F2  , KC_F3    , XXXXXXX, _______,      _______, XXXXXXX, OSL(7)   , XXXXXXX, XXXXXXX, XXXXXXX , _______,
_______, _______, _______, _______, KC_ESCAPE,                                          _______  , _______, _______, _______ , _______,

                                               XXXXXXX, XXXXXXX,      _______, _______,
                                                        _______,      _______,
                                    KC_SPACE , KC_TAB , XXXXXXX,      _______, XXXXXXX, XXXXXXX
),

[FUND] = LAYOUT_ergodox_pretty(
_______, _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, KC_F24 , KC_F19 , KC_F20 , KC_F21 , _______, _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, KC_F23 , KC_F16 , KC_F17 , KC_F18 , _______,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, KC_F22 , KC_F13 , KC_F14 , KC_F15 , _______, _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, _______, _______, _______, _______,                                          _______, _______, _______, _______, _______,

                                             _______, _______,      _______, _______,
                                                      _______,      _______,
                                    _______, _______, _______,      _______, XXXXXXX, XXXXXXX
),

[BTTN] = LAYOUT_ergodox_pretty(
_______, _______     , _______        , _______       , _______        , _______       , _______,      _______, _______   , _______     , _______    , _______   , _______    , _______,
_______, KC_MAC_UNDO , KC_MAC_CUT     , KC_MAC_COPY   , KC_MAC_PASTE   , C_REDO        , _______,      _______, C_REDO    , KC_MAC_PASTE, KC_MAC_COPY, KC_MAC_CUT, KC_MAC_UNDO, _______,
_______, KC_LCTRL    , KC_LALT        , KC_LGUI       , KC_LSHIFT      , XXXXXXX       ,                        XXXXXXX   , KC_RSHIFT   , KC_RGUI    , KC_RALT   , KC_RCTRL   , _______,
_______, DYN_REC_STOP, DYN_MACRO_PLAY2, DYN_REC_START2, DYN_MACRO_PLAY1, DYN_REC_START1, _______,      _______, C_REDO    , KC_MAC_PASTE, KC_MAC_COPY, KC_MAC_CUT, KC_MAC_UNDO, _______,
_______, _______     , _______        , _______       , KC_MS_BTN1     ,                                                    _______     , _______    , _______   , _______    , _______,

                                                                         _______       , XXXXXXX,      _______, _______   ,
                                                                                         _______,      _______,
                                                        KC_MS_BTN3     , KC_MS_BTN2    , XXXXXXX,      _______, KC_MS_BTN1, KC_MS_BTN3
),

[WNDW] = LAYOUT_ergodox_pretty(
_______, _______, _______ , _______, _______  , _______, _______,      _______, _______, _______, _______, _______, _______, _______,
_______, KC_Q   , KC_GRAVE, KC_TAB , XXXXXXX  , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, XXXXXXX, XXXXXXX , XXXXXXX, KC_LSHIFT, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, XXXXXXX, XXXXXXX , XXXXXXX, XXXXXXX  , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
_______, _______, _______ , _______, XXXXXXX  ,                                          XXXXXXX, _______, _______, _______, _______,

                                                XXXXXXX, XXXXXXX,      _______, _______,
                                                         _______,      _______,
                                     XXXXXXX  , XXXXXXX, _______,      _______, XXXXXXX, XXXXXXX
)
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
}

void matrix_scan_user() {
    led_t led_state = host_keyboard_led_state();
    if (led_state.caps_lock) {
        ergodox_right_led_3_on();
    }
    else {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer != 3) {
            ergodox_right_led_3_off();
        }
    }

    if (is_caps_word_on()) {
        ergodox_right_led_2_on();
    }
    else {
        uint8_t layer = get_highest_layer(layer_state);
        if (layer != 2) {
            ergodox_right_led_2_off();
        }        
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        case 8:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_8
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_8);
#endif
            break;
        default:
            break;
    }

    return state;
};
