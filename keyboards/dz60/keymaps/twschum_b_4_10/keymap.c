#include "dz60.h"
#include "twschum.h"

/* DZ60 layout using following options (from layouts diagram on KBDfans):
 *  - plate B (2.25u lshift)
 *  - opt 4 (1.75, 1, 1 on rshift)
 *  - opt 10 (2.75, 1.25, 2.25 on space, 5x1u bottom right keys)
 * http://www.keyboard-layout-editor.com/#/gists/225f0f4dcf6671405f744fabe314627c
 */

/* TODO: provide a standalone B_4_10 layout
 */

#undef KEYMAP
#define KEYMAP( \
        K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, \
        K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
        K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       \
        K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312, K313, K314, \
        K400, K401,       K403,       K404, K406,       K408,       K410, K411, K412, K413, K414  \
        ) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014 }, \
    { K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO }, \
    { K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, K312,  K313,  K314 }, \
    { K400,  K401,  KC_NO, K403,  K404,  KC_NO, K406,  KC_NO, K408,  KC_NO, K410,  K411,  K412,  K413,  K414 }  \
}

// Mac vs Linux/windows behaviour for media next/prev keys
#define IS_MAC 1
#ifdef IS_MAC
#define MEDIA_FWD KC_MFFD
#define MEDIA_RWD KC_MRWD
#elif
#define MEDIA_FWD KC_MNXT
#define MEDIA_RWD KC_MPRV
#define
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base 60% qwerty */
    KEYMAP(
       // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------||------2.0-------|
            KC_ESC,   KC_1,    KC_2,    KC_3,   KC_4,   KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS, KC_EQL,      KC_BSPC,
       // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------||----------------|
       //
       // |----1.5-----||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|----1.5-----|
             KC_TAB,      KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_LBRC, KC_RBRC,   KC_BSLS,
       // |------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------|
       //
       // |----1.75------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------2.25--------||
             KC_LCTL,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,     KC_ENT,
       // |--------------||--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|------------------||
       //
       // |------2.25--------|--------|--------|--------|--------|--------|--------|--------|--------|--------||----1.75------|--------|--------||
             KC_LSHIFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,  KC_COMM, KC_DOT,   SFT_T(KC_SLSH),  KC_UP, VIM_START,
       // |------------------|--------|--------|--------|--------|--------|--------|--------|--------|--------||--------------|--------|--------||
       //
       // |---1.25---|---1.25---||---1.25---||--------2.75----------||---1.25---|------2.25--------||--------|--------|--------|--------|--------|
            MO(L_Fn),  KC_LALT,    KC_LGUI,         KC_SPC,           TT(L_Nav),     MO(L_Fn),     TG(L_Num),TT(L_Cfg), KC_LEFT, KC_DOWN, KC_RGHT
       // |----------|----------||----------||----------------------||----------|------------------||--------|--------|--------|--------|--------|
          ),

    /* vim mode */
    KEYMAP(
            VIM_ESC,   _______, _______, _______, _______, _______, _______, _______, _______,   _______,    _______, _______, _______, _______,
            _______,   _______, VIM_W,   VIM_E,   KC_R,    _______, VIM_Y,   VIM_U,   VIM_I,     VIM_O,      VIM_P,   _______, _______, _______,
            _______,   VIM_A,   VIM_S,   VIM_D,   _______, VIM_G,   VIM_H,   VIM_J,   VIM_K,     VIM_L,      _______, _______, _______,
            VIM_SHIFT, _______, VIM_X,   VIM_C,   VIM_V,   VIM_B,   _______, _______, VIM_COMMA, VIM_PERIOD, _______, _______, VIM_ESC,
            _______,   _______, _______, _______, _______, _______, _______, _______, _______,   _______,    _______
          ),

    /* primary fn layer */
    KEYMAP(
            KC_GRV,   KC_F1,      KC_F2,          KC_F3,                KC_F4,            KC_F5,      KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_DEL,
            KC_TAB,   KC_NO,      KC_HOME,        KC_UP,                KC_END,           KC_NO,      KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,    LESS_PD,  KC_NO,    KC_NO,    KC_NO,
            KC_CAPS,  SALT_CMD,   KC_LEFT,        KC_DOWN,              KC_RIGHT,         KC_NO,      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  KC_NO,    KC_NO,    KC_ENT,
            KC_LSFT,  MEDIA_RWD,  KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,    KC_AUDIO_VOL_UP,  MEDIA_FWD,  KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_LOCK,  KC_PGUP,  KC_INS,
            KC_MEH,   KC_LALT,    KC_LGUI,        KC_MEDIA_PLAY_PAUSE,  _______,          _______,    _______,  _______,  KC_HOME,   KC_PGDN,    KC_END
          ),

    /* mouse navigation */
    KEYMAP(
            TO(L_Base), KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, KC_NO,       KC_NO,   KC_NO,         KC_NO,         KC_NO,       KC_NO,          KC_NO,  KC_NO,   KC_NO, KC_NO,
            KC_NO,      KC_NO,        KC_MS_BTN2,   KC_MS_UP,     KC_MS_BTN1,  KC_NO,   KC_NO,         KC_NO,         KC_PGDN,     KC_PGUP,        KC_NO,  KC_NO,   KC_NO, KC_NO,
            KC_LCTL,    KC_MS_BTN3,   KC_MS_LEFT,   KC_MS_DOWN,   KC_MS_RIGHT, KC_NO,   KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_NO,  KC_NO,   KC_NO,
            KC_LSHIFT,  KC_NO,        KC_NO,        KC_NO,        KC_NO,       KC_NO,   KC_NO,         KC_NO,         KC_NO,       KC_NO,          KC_NO,  _______, KC_NO,
            KC_NO,      KC_NO,        KC_NO,        KC_MS_BTN1,   _______,     _______, _______,       _______,       _______,     _______,        _______
          ),

    /* numpad layer */
    KEYMAP(
            _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,          KC_NO, KC_NO,  KC_BSPC,
            KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_KP_PLUS,     KC_NO, KC_NO,  KC_NO,
            KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_SLASH, KC_KP_ASTERISK, KC_NO, KC_ENT,
            KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT,   KC_KP_ENTER,    KC_NO, KC_NO,
            KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_KP_0, _______, _______, KC_NO,   KC_NO,       KC_NO
    ),


    /* RGB lighting controls and keyboard config, reset */
    KEYMAP(
            _______,            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    TG_L0_RGB,       KC_NO,             KC_NO,      TO(L_None),
            KC_NO,              KC_NO,  KC_NO,  KC_NO,  RESET,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,    KC_NO,           KC_NO,             KC_NO,      RGB_HUD,
            EN_CTRL_SHORTCUTS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,    TG_LAYER_RGB, RGB_MODE_PLAIN,  RGB_MODE_FORWARD,  KC_RSHIFT,
            KC_NO,              KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MAKE,  KC_NO,    KC_NO,    RGB_TOG,         RGB_VAI,           RGB_HUI,
            KC_NO,              KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  _______,  RGB_SAD,  RGB_VAD,  RGB_SAI
          ),

    /* soft "off" state where none of the keystroke register */
    KEYMAP(
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  TO(L_Base),
            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
          ),
};

uint8_t vim_cmd_layer(void) {
    return L_Vim;
}
