#include "kyria.h"
#include "kyria/rev2/config.h"
#include "keymap_estonian.h"

enum layers {
    _QWERTY = 0,
    _COLEMAK_DH,
    _QWERTY_DOWN,
    _QWERTY_DOWN_RIGHT,
    _NAV,
    _SYM,
    _FUNCTION,
    _NUMS,
    _ADJUST,
    _LAYER_COUNT
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define NUMS     MO(_NUMS)
#define ADJUST   MO(_ADJUST)
#define QDOWN    MO(_QWERTY_DOWN)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

#define NUMS_ENT LT(NUMS, KC_ENT)
#define SYM_SPC  LT(SYM, KC_SPC)
#define NAV_SPC  LT(NAV, KC_SPC)
#define FKEY_TAB LT(FKEYS, KC_TAB)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //layout test:
    //shift+ctrl+enter
    //nav to end + semicolon
    //shift+f6
    //alt+f4
    //ctl+alt+k
    //ctl+alt+o
    //ctl+alt+l
    //ctl+nav
    //alt+ins
    //dot, comma & space on num layer

    [_COLEMAK_DH] = LAYOUT(
     KC_TAB , KC_Q, KC_W, KC_F   , KC_P    , KC_B    ,                                         KC_J    , KC_L   , KC_U   , KC_Y  , KC_SCLN, KC_BSPC ,
     KC_LCTL, KC_A, KC_R, KC_S   , KC_T    , KC_G    ,                                         KC_M    , KC_N   , KC_E   , KC_I  , KC_O   , KC_QUOT,
     KC_LSFT, KC_Z, KC_X, KC_C   , KC_D    , KC_V    , KC_LBRC, KC_CAPS,     FKEYS  , KC_RBRC, KC_K    , KC_H   , KC_COMM , KC_DOT, KC_SLSH, KC_RSFT ,
                          KC_LGUI, KC_LALT , NUMS_ENT, NAV_SPC, KC_ESC ,     KC_BSPC, SYM_SPC, FKEY_TAB, KC_RALT, KC_RGUI
    ),

    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q, KC_W, KC_E   , KC_R   , KC_T    ,                                         KC_Y    , KC_U   ,  KC_I   , KC_O  , KC_P   , KC_BSPC ,
     KC_LCTL, KC_A, KC_S, KC_D   , KC_F   , KC_G    ,                                         KC_H    , KC_J   ,  KC_K   , KC_L  , KC_SCLN, KC_QUOT,
     KC_LSFT, KC_Z, KC_X, KC_C   , KC_V   , KC_B    , KC_LBRC, KC_CAPS,     ADJUST , KC_RBRC, KC_N    , KC_M   , KC_COMM  , KC_DOT, KC_SLSH, KC_RSFT ,
                          KC_LGUI, KC_LALT, NUMS_ENT, NAV_SPC, KC_ESC ,     KC_BSPC, SYM_SPC, FKEY_TAB, KC_RALT, KC_RGUI
    ),

    [_NAV] = LAYOUT(
      KC_ESC , _______, LCTL(KC_B)           , LCA(KC_B), RSFT(KC_TAB), KC_TAB,                                          KC_PGUP  , KC_HOME, KC_UP  , KC_END , KC_DEL  , KC_BSPC,
      _______, KC_LGUI, KC_LALT           , KC_LCTRL , KC_LSHIFT   , _______,                                         KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RGHT, KC_RBRC , _______,
      _______, _______, LCTL(KC_KP_SLASH) , _______  , LALT(KC_ENT), _______, _______, KC_SLCK,     KC_NLCK, _______, KC_PAUSE , _______, KC_INS, _______ , KC_LBRC , KC_PSCR,
                                            _______  , _______     , _______, _______, _______,     _______, _______, _______  , _______, _______
    ),

    [_NUMS] = LAYOUT(
      KC_ESC , _______, _______, _______ , _______  , _______,                                         KC_COMM, KC_7   , KC_8   , KC_9, _______, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTRL, KC_LSHIFT, _______,                                         KC_DOT , KC_4   , KC_5   , KC_6, KC_SLSH, _______,
      _______, _______, _______, _______ , _______  , _______, _______, _______,     _______, _______, KC_0, KC_1   , KC_2   , KC_3, KC_DOT, _______,
                                 _______ , _______  , _______, _______, _______,     _______, _______, KC_0   , KC_COMM, _______
    ),

    [_SYM] = LAYOUT(
     _______     , RSFT(KC_5)   , RALT(KC_2), RSFT(KC_BSLS), RALT(KC_4), KC_NUBS   ,                                         RSFT(KC_NUBS), RSFT(KC_6)   , RSFT(KC_3)   , RSFT(KC_EQL), RALT(KC_QUOT), _______,
     RSFT(KC_GRV), RALT(KC_NUBS), RSFT(KC_2), RSFT(KC_SLSH), RSFT(KC_8), RALT(KC_7),                                         RALT(KC_0)   , RSFT(KC_9)   , RSFT(KC_0)   , KC_BSLS     , KC_MINS      , KC_SLSH,
     _______     , _______      , RSFT(KC_7), RALT(KC_MINS), RSFT(KC_1), RALT(KC_8), _______, _______,     _______, _______, RALT(KC_9)   , RSFT(KC_MINS), RSFT(KC_COMM), RSFT(KC_DOT), RSFT(KC_SLSH), _______,
                                              _______      , _______   , _______   , _______, _______,     _______, _______, _______      , _______      , _______
    ),

    [_FUNCTION] = LAYOUT(
      _______, KC_F9, KC_F10, KC_F11, KC_F12  , _______,                                         _______, _______  , _______ , _______, _______, _______,
      _______, KC_F5, KC_F6 , KC_F7 , KC_F8   , _______,                                         _______, KC_LSHIFT, KC_LCTRL, KC_LALT, KC_LGUI, _______,
      _______, KC_F1, KC_F2 , KC_F3 , KC_F4   , _______, _______, _______,     _______, _______, _______, _______  , _______ , _______, _______, _______,
                                      _______ , _______, _______, _______,     _______, _______, _______, _______  , _______ , _______
    ),

    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                        _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______ , _______, _______,                                       RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, _______, _______, _______,_______, _______,     _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______,     _______, _______, _______, _______, _______
    ),

    [_QWERTY_DOWN] = LAYOUT(
        _______, KC_1, KC_2, KC_3   , KC_4   , KC_5,                                            KC_Y   , KC_U   ,  KC_I  , KC_O   , KC_P   , _______,
        _______, KC_Q, KC_W, KC_E   , KC_R   , KC_T   ,                                         KC_H   , KC_J   ,  KC_K  , KC_L   , KC_SCLN, _______,
        _______, KC_A, KC_S, KC_D   , KC_F   , KC_G   , KC_LBRC, KC_LGUI,     FKEYS  , KC_RBRC, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                             _______, ALT_ENT, KC_SPC , KC_CAPS, KC_GRV,     _______, _______, _______, _______, _______
    ),

    [_QWERTY_DOWN_RIGHT] = LAYOUT(
        _______, KC_GRAVE, KC_1, KC_2     , KC_3   , KC_4    ,                                        _______ , KC_Y   ,  KC_U  , KC_I   , KC_O   , KC_P,
        KC_LSFT, KC_V    , KC_Q, KC_W     , KC_E   , KC_R    ,                                         KC_T   , KC_H   ,  KC_J  , KC_K   , KC_L, KC_SCLN,
        KC_LCTL, KC_G    , KC_A, KC_S     , KC_D   , KC_F    , KC_ESC, KC_LGUI,     FKEYS  , KC_RBRC, KC_G   , KC_N   , KC_M, KC_COMM , KC_DOT, KC_SLSH,
                                 KC_ESC   , KC_LALT, ALT_ENT , KC_SPC , KC_5,      _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void draw_my_default(void){

        oled_clear();

        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM scoro_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };
        // clang-format on

        oled_write_P(scoro_logo, false);
        oled_write_P(PSTR("Ver 21.12 "), false);

        // Write host Keyboard LED Status to OLED
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("Num ") : PSTR("    "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("Cps ") : PSTR("    "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("Scl ") : PSTR("    "), false);

        oled_write_P(PSTR("\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        static const char epd_bitmap_nav [] PROGMEM = {
            0x55, 0x00, 0xb9, 0x20, 0xa1, 0xa0, 0xb9, 0x02, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0xaa,
            0x01, 0x09, 0x09, 0x09, 0xc9, 0x39, 0x01, 0xff, 0x01, 0xf9, 0x89, 0x89, 0x89, 0xf9, 0x01, 0xff,
            0x01, 0xf9, 0x89, 0x89, 0x89, 0xf9, 0x01, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0x01, 0x7d, 0x15, 0xfd, 0xa1, 0xe1, 0x01, 0xff,
            0x01, 0x7d, 0x15, 0xfd, 0xa1, 0xe1, 0x01, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff,
            0x01, 0xd1, 0x11, 0x91, 0x11, 0xdd, 0x01, 0xff, 0x01, 0x01, 0x01, 0xf9, 0x01, 0x01, 0x01, 0xff,
            0x55, 0x80, 0x3b, 0xa2, 0x3b, 0xa0, 0x3b, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xaa,
            0x00, 0x80, 0x00, 0x9c, 0x03, 0x80, 0x00, 0xff, 0x80, 0x9f, 0x90, 0x90, 0x90, 0x9f, 0x80, 0xff,
            0x80, 0x90, 0x90, 0x90, 0x90, 0x9f, 0x80, 0xff, 0x80, 0x80, 0x9c, 0x9c, 0x9c, 0x80, 0x80, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x88, 0x90, 0xba, 0x92, 0x8b, 0x80, 0xff,
            0x80, 0xa0, 0x90, 0xba, 0x92, 0xa3, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x99, 0x95, 0x95, 0x95, 0x99, 0x80, 0xff, 0x80, 0x86, 0x88, 0x9f, 0x88, 0x86, 0x80, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x00, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0x00, 0xaa,
            0x00, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xff, 0x00, 0xfc, 0x04, 0x04, 0x04, 0x04, 0x00, 0xff,
            0x00, 0xfc, 0x04, 0x04, 0x04, 0x04, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x80, 0xc0, 0xa0, 0x80, 0x80, 0x00, 0xff, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x40, 0x20, 0xf0, 0x20, 0x40, 0x00, 0xff, 0x00, 0x80, 0x80, 0xa0, 0xc0, 0x80, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xaa, 0x80, 0x9f, 0x90, 0x90, 0x90, 0x9f, 0x80, 0xaa,
            0x80, 0x81, 0x81, 0x81, 0x81, 0x9f, 0x80, 0xff, 0x80, 0x91, 0x91, 0x91, 0x91, 0x9f, 0x80, 0xff,
            0x80, 0x9f, 0x91, 0x91, 0x91, 0x9f, 0x80, 0xff, 0x80, 0x80, 0x87, 0x87, 0x8f, 0x90, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x81, 0x82, 0x80, 0x80, 0x80, 0xff, 0x80, 0x81, 0x82, 0x87, 0x82, 0x81, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x87, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x82, 0x81, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x20, 0x10, 0x08, 0xfc, 0x00, 0xff, 0x00, 0x84, 0x84, 0x84, 0x84, 0xfc, 0x00, 0xff,
            0x00, 0x04, 0x84, 0x84, 0x84, 0xfc, 0x00, 0xff, 0x00, 0xe0, 0x70, 0x00, 0x38, 0x1c, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x4a, 0x4a, 0x4c, 0x6a, 0x00, 0xff,
            0x00, 0x00, 0x4a, 0x4a, 0x4c, 0x6a, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0xb8, 0x20, 0xb8, 0xa0, 0xb8, 0x00, 0xff, 0x00, 0x08, 0x1c, 0x2a, 0x08, 0x08, 0x00, 0xff,
            0x00, 0xb8, 0xa0, 0xb8, 0x88, 0xb8, 0x00, 0xff, 0x00, 0x08, 0x08, 0x2a, 0x1c, 0x08, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x9f, 0x80, 0xff, 0x80, 0x9f, 0x90, 0x90, 0x90, 0x90, 0x80, 0xff,
            0x80, 0x90, 0x90, 0x90, 0x90, 0x9f, 0x80, 0xff, 0x80, 0x9c, 0x8e, 0x80, 0x8e, 0x87, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0xb8, 0xa3, 0xba, 0x8a, 0xbb, 0x80, 0xff,
            0x80, 0xa2, 0xb2, 0xaa, 0xa6, 0xa2, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0xbb, 0xaa, 0xbb, 0xa0, 0xa3, 0x80, 0xff, 0x80, 0x84, 0x8e, 0x95, 0x84, 0x84, 0x80, 0xff,
            0x80, 0x94, 0x96, 0x96, 0x95, 0x94, 0x80, 0xff, 0x80, 0x84, 0x84, 0x95, 0x8e, 0x84, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xbe, 0x8a, 0x8e, 0x78, 0x08, 0x00, 0xff,
            0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff,
            0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0x80, 0x8b, 0x8a, 0xbe, 0xa4, 0xa4, 0x80, 0xff
        };


        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _COLEMAK_DH:
                draw_my_default();
                oled_write_P(PSTR("Kole-makk DH\n"), false);
                break;
            case _QWERTY:
                draw_my_default();
                oled_write_P(PSTR("KVERTI\n"), false);
                break;
            case _QWERTY_DOWN_RIGHT:
                draw_my_default();
                oled_write_P(PSTR("KVERTI DR\n"), false);
                break;
            case _NAV:
                oled_write_raw_P(epd_bitmap_nav, sizeof(epd_bitmap_nav));
                //oled_write_P(PSTR("Nav\n"), false);
                break;
            case _FUNCTION:
                draw_my_default();
                oled_write_P(PSTR("Function\n"), false);
                break;
            case _ADJUST:
                draw_my_default();
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _SYM:
                draw_my_default();
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case _QWERTY_DOWN:
                draw_my_default();
                oled_write_P(PSTR("KVERTI Down\n"), false);
                break;
            case _NUMS:
                draw_my_default();
                oled_write_P(PSTR("Numpad\n"), false);
                break;
            default:
                draw_my_default();
                oled_write_P(PSTR("Undefined\n"), false);
        }

    } else {
        static const char PROGMEM raw_logo[] = {
            130, 89, 18,164, 73,146, 36, 41, 66,172, 18, 84,193, 18,165,  0, 94,160, 10,161,  8, 34, 72, 18,164,  2, 72, 18, 66,148, 34,136, 34,  8, 34,248,174,216,178,196,188, 73,120,226,144,101,192,170,128,154,  0, 73, 16,164,  2,168,  2, 32,141, 32, 10, 80,130, 36,  0,173,  0, 42,  0,170,  0, 74, 16, 68,145, 36,  0, 68,153, 34,128, 42,160,  2, 36,138, 32,138, 16, 68,137, 80,  6, 32,202,144, 66, 82,164, 40, 81, 68, 58, 64,202, 18, 32, 77, 16, 34, 84,  0, 37,200, 10, 32, 74, 34,148, 32,133, 24, 66,138, 48,  2,213,  0,
            66,153, 98,  4,217, 36,171,  0,186,  1, 84,130, 44,193, 44,145, 34, 84,129, 52,133, 24,161,  2,168, 17,  2,196, 42,128, 36,  9, 34, 72,  0, 69, 30, 83, 62,245,175,185,183,170, 87,218,183,172,251, 37,222,235, 60,210,124,226,220,170,244, 93,246,156,118,205,170, 94,229,222, 58,218,118,205,254,138,127,146, 94,116,222, 84,190,212,165, 92,162, 88, 82, 72,181, 12,118,133, 43, 82,173, 16,199, 24,163,140, 49,133, 34, 68, 12, 81,  4,209,  4, 81,  2, 73,144, 34,  4,201, 18,168,  1, 72,146, 33, 20, 64, 21, 32,212,  1,
            4, 90, 65,188,129, 50,  5,208, 45, 66,168, 18, 36,194, 28, 33, 66, 76, 17, 34,196, 12, 81, 36,138, 32, 74, 16, 68,145, 36,145, 20, 33, 64,  5, 40, 66,148, 33,131, 28,247,154,117,222,210,189,101,255, 94,251,223,189,251,222,179,110,255,171,254,171, 95,250,181,247, 37,223,189,  3,126, 91,196,187, 98,221,171, 42,219, 36,203, 60,195, 60, 67,220, 35,212,181,  2, 90, 32,165,  8, 82,170, 64, 26, 64, 18, 68, 16,149, 32,  1, 82,132, 16, 37,192, 21,128, 42,128, 42,  0, 90,  0, 81,  4, 80,  5, 80,133, 40,  2,168,  2,
            84,165, 10, 80, 85,162,132, 57, 66, 68, 25,226,  4, 89, 66,153, 17, 68,145, 34, 68,201, 18, 36, 65, 44,145, 42,128,164,  8,162, 25, 64, 33,130, 12, 32, 74,  0, 42,192,249,187,235,254, 93,251,231,221,191,251, 38, 93,151, 14, 29,  3, 30, 34, 13, 91,106,165,254,195,190,233, 52,201,  2,125,138, 81,134, 42,  1, 74, 16,  5,  2, 20,  5,  2, 21,132, 27, 32, 13, 81,173, 18,172, 33, 94,160, 69,168,146,  1,164,  8,146, 64,  5,208,  2,164,  8,162,  8, 82,132,  8,211,  0, 74, 17,196, 17, 66,148, 32,197,  8,170, 16,
            66,200, 19, 84,161, 70,152, 34,201, 17, 84, 34, 68,153, 34, 65,172, 17,148, 32,  5, 88,  2, 73, 84, 33,132, 25, 34,200, 18,164,  1, 44, 65,170,  0,169,  2, 32,129, 94,235,190,255,218,183,111,250, 95,242, 95,244,149, 96,195,128, 72,128,160,128, 64,202, 32,213,126,213,255,237, 59,238, 65, 94,160,149, 36,201, 18, 64,129,  0,160,  0,128,128,  0, 32, 72, 65, 42, 89,162, 26,193, 53,138, 53, 74, 84,  1,  2,  2,  8,  1,  2, 16,  1,  2, 33,  0,  2,  1, 10,  0, 66,  0,  3,  0, 66,  1,  2,  2,  0,  2,  2, 66,  0,  3,
            0,146, 37, 72, 34,202, 18, 68,202, 25, 34, 33,196, 28, 65, 26, 64, 82,165,144,  5, 42, 64,165, 73,  2, 90,160, 20,161, 22, 96,133, 42,128, 76, 18,160,  4, 32,  2, 37,126,239,218,191,101,223,189,219, 53,223,178,111,171,222,123,214,234, 52,235,221,171,125,213,111,254, 93,123, 86,197, 29, 66,168, 18, 68, 19, 36,201, 20, 85, 66,218,  0,213, 34,133, 40,197, 26, 32, 84,  5,106,145, 38, 89,211,  4, 32,  1,  0,  0,  2,  0, 64,  0,  4, 32,129,  0,  0,  8,  0,  8,  0, 32,  0,  0,  1,  0, 64,132,  0,  0,  0, 34,  0,
            0,  0,  1,  0,  2,  0,  1,  2,  4,  9, 18,  2,  4, 41, 18, 36, 81,  4,208,  5, 42,200, 18, 36, 73,162,  8, 82, 10,208, 37, 72,149, 32, 74, 17, 64,132, 41,  0,132,  0,  1,255,165,255, 91,230, 61,235,173, 90,101,222,165, 91,127,226,191,213,175, 90,165, 31, 59,102, 29, 91, 18, 70,  8, 82,  0, 64,  9, 80,133, 32,  2, 69,  8, 82,130, 36, 43, 40, 66,164,  8,161, 12, 83,168, 18,101,138, 10,  0, 16,  1, 32,  0, 16,  0,  0,  0,136,  0,  0, 32,  0,  1,128,  4,  0, 32,  0,  1,  0, 16,  0,128,  0,  0,  2,  8,  0, 32,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  1,  2,  4,  1, 10,  1,  4, 42,133, 24, 66, 21, 40, 66,  8,212,  1,  0,128, 41,245, 78,251, 93,247, 61,231,190,235,191,218, 53,237,182,205,122,210,165, 91,178, 69,211, 38,219, 20,165, 26, 36, 84,146, 36,  0, 92,  0, 66, 76,145, 34,130, 40, 17, 66, 84, 34,232,  2,220, 42,209, 38,218, 37,106,136, 16,  0,  0,  0, 68,128,  0,  4,  0,  0,  8,  0, 64,  1,  8,128,  0,  0,  4,  0,  2,  8,  0, 32,  0,128,  0,130,  0,  4, 16,  0,
            0,
        };

        oled_write_raw_P(raw_logo, sizeof(raw_logo));
    }
    return false;
}


uint8_t selected_layer = 0;
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        // Rotate through layers
        if (!clockwise && selected_layer < _LAYER_COUNT - 1) {
            selected_layer ++;
        } else if (clockwise && selected_layer > 0){
            selected_layer --;
        }
        layer_move(selected_layer);
    }
    return false;
}
