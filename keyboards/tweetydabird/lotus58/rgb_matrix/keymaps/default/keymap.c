// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
	autoshift_disable();
}

enum layers {
    _QWERTY,
    _NUM,
    _FN,
    _SYS,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NUMERIC,
    KC_FUNCTION,
	KC_SYSTEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
//      											     				_______       _______
// .----------.----------.----------.----------.----------.----------. /       \     /       \ .----------.----------.----------.----------.----------.----------.
// |   Esc    |    1     |    2     |    3     |    4     |    5     |(  Media  )   (  Media  )|    6     |    7     |    8     |    9     |    0     |    -     |
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	   KC_4,     KC_5,  	KC_MPLY,      KC_MPLY,    KC_6,  	 KC_7,   	KC_8,       KC_9,      KC_0,    KC_MINS,
// |----------+----------+----------+----------+----------+----------| \_______/     \_______/ |----------+----------+----------+----------+----------+----------|
// |   Tab    |    Q     |    W     |    E     |    R     |    T     |                         |    Y     |    U     |    I     |    O     |    P     |   [ (Å)  |
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,       KC_P,    KC_LBRC,
// |----------+----------+----------+----------+----------+----------|                         |----------+----------+----------+----------+----------+----------|
// |  Capslk  |    A     |    S     |    D     |    F     |    G     |                         |    H     |    J     |    K     |    L     |  ; (Ö)   |   ' (Ä)  |
      KC_CAPS, 	 KC_A, 	    KC_S,       KC_D,      KC_F,    KC_G,                     			   KC_H, 	 KC_J,      KC_K,       KC_L,    KC_SCLN,   KC_QUOT,
// |----------+----------+----------+----------+----------+----------+-----------. .-----------+----------+----------+----------+----------+----------+----------|
// | <-  Ctrl |    Z     |    X     |    C     |    V     |    B     |   Down    | |    Up     |    N     |    M     |    ,     |    .     |    /     | Ctrl  -> |
LCTL_T(KC_LEFT), KC_Z, 	    KC_X,      KC_C,      KC_V,       KC_B,     KC_DOWN,       KC_UP,      KC_N,	KC_M,       KC_COMM,   KC_DOT,    KC_SLSH, RCTL_T(KC_RGHT),
// '----------'----------'----------+----------+----------+----------+-.---------' '---------.-+----------+----------+----------+----------'----------'----------'
//                                	|   Win    |   Lower  |   Alt    |/  Space  /   \  Enter  \|   AltGr  |  Raise   |   Bksp   |
//									|		   |	      |	         |  Shift  /     \  Shift  |          |          |          |
                                      KC_LGUI,   TG(_FN),   KC_LALT, LSFT_T(KC_SPC),RSFT_T(KC_ENT), KC_RALT, TG(_NUM), MT(MOD_RGUI,KC_BSPC)
//                                  '----------'----------'----------'--------'       '--------'----------'----------'----------'
),

//      											     				_______       _______
// .----------.----------.----------.----------.----------.----------. /       \     /       \ .----------.----------.----------.----------.----------.----------.
// |   Esc    |    1     |    2     |    3     |    4     |    5     |(  Media  )   (  Media  )|    6     |    7     |    8     |    9     |    0     |    -     |
// |----------+----------+----------+----------+----------+----------| \_______/     \_______/ |----------+----------+----------+----------+----------+----------|
// |   Tab    |    Q     |    W     |    E     |    R     |    T     |                         |    Y     |    U     |    I     |    O     |    P     |   [ (Å)  |
// |----------+----------+----------+----------+----------+----------|                         |----------+----------+----------+----------+----------+----------|
// |  Capslk  |    A     |    S     |    D     |    F     |    G     |                         |    H     |    J     |    K     |    L     |  ; (Ö)   |   ' (Ä)  |
// |----------+----------+----------+----------+----------+----------+-----------. .-----------+----------+----------+----------+----------+----------+----------|
// | <-  Ctrl |    Z     |    X     |    C     |    V     |    B     |   Down    | |    Up     |    N     |    M     |    ,     |    .     |    /     | Ctrl  -> |
// '----------'----------'----------+----------+----------+----------+-.---------' '---------.-+----------+----------+----------+----------'----------'----------'
//                                	|   Win    |   Lower  |   Alt    |/  Space  /   \  Enter  \|   AltGr  |  Raise   |   Bksp   |
//									|		   |	      |	         |  Shift  /     \  Shift  |          |          |          |
//                                  '----------'----------'----------'--------'       '--------'----------'----------'----------'


[_NUM] = LAYOUT(
  _______,   KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,  _______,      _______, KC_CIRC,    KC_KP_7,    KC_KP_8,    KC_KP_9, XXXXXXX, XXXXXXX,
  _______, XXXXXXX,   KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX,                         KC_HASH,    KC_KP_4,    KC_KP_5,    KC_KP_6, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_LBRC, KC_RBRC,                         KC_AMPR,    KC_KP_1,    KC_KP_2,    KC_KP_3, XXXXXXX, XXXXXXX,
  _______, XXXXXXX, KC_PAST,  KC_PPLS, KC_PSLS,  KC_EQL, _______,       _______,  KC_DLR,    KC_KP_0, KC_KP_DOT, KC_COLN, KC_PMNS, _______,
							  _______, _______, _______, _______,       _______, _______, _______, _______ 
),

[_FN] = LAYOUT(
//      											     				_______       _______
// .----------.----------.----------.----------.----------.----------. /       \     /       \ .----------.----------.----------.----------.----------.----------.
// |   Esc    |    1     |    2     |    3     |    4     |    5     |(  Media  )   (  Media  )|    6     |    7     |    8     |    9     |    0     |    -     |
	  _______,   KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     _______,      _______,    KC_F6,    KC_F7,      KC_F8,     KC_F9,    KC_F10,    _______,
// |----------+----------+----------+----------+----------+----------| \_______/     \_______/ |----------+----------+----------+----------+----------+----------|
// |   Tab    |    Q     |    W     |    E     |    R     |    T     |                         |    Y     |    U     |    I     |    O     |    P     |   [ (Å)  |
     _______,   _______,   _______,   _______,   _______,   _______,                             _______,   _______,   _______,   _______,   _______,   _______,
// |----------+----------+----------+----------+----------+----------|                         |----------+----------+----------+----------+----------+----------|
// |  Capslk  |    A     |    S     |    D     |    F     |    G     |                         |    H     |    J     |    K     |    L     |  ; (Ö)   |   ' (Ä)  |
     _______,   _______,   _______,   _______,   _______,   _______,                             _______,   _______,   _______,   _______,   _______,   _______,
// |----------+----------+----------+----------+----------+----------+-----------. .-----------+----------+----------+----------+----------+----------+----------|
// | <-  Ctrl |    Z     |    X     |    C     |    V     |    B     |   Down    | |    Up     |    N     |    M     |    ,     |    .     |    /     | Ctrl  -> |
     _______,   _______,   _______,   _______,   _______,   _______,    _______,      _______,   _______,   _______,   _______,   _______,   _______,   _______,
// '----------'----------'----------+----------+----------+----------+-.---------' '---------.-+----------+----------+----------+----------'----------'----------'
//                                	|   Win    |   Lower  |   Alt    |/  Space  /   \  Enter  \|   AltGr  |  Raise   |   Bksp   |
//									|		   |	      |	         |  Shift  /     \  Shift  |          |          |          |
            					      _______,   _______,   _______,  _______,         _______,  _______,   _______,   _______
//                                  '----------'----------'----------'--------'       '--------'----------'----------'----------'
),

[_SYS] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX ,  XXXXXXX, XXXXXXX, XXXXXXX, _______,     _______, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_SAI, RGB_TOG,
  QK_BOOT, XXXXXXX, KC_QWERTY, XXXXXXX, XXXXXXX, KC_ASTG,                       XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD, RGB_SAD, RGB_M_P,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, KC_CAPS,                       XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUI, RGB_VAI, RGB_M_B,
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_VAD, RGB_M_R,
								_______, _______, _______, _______,     _______, _______, _______, _______  \
  )
};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };
    oled_write_P(qmk_logo, false);
}


static void print_status_narrow(void) {
	// Create OLED content
    oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
	oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case _SYS:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
	
	// Display autoshift
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);
	bool autoshift = get_autoshift_state();
	oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR("Auto-Shift"), autoshift);
	oled_write_P(PSTR("\n"), false);
	
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	// Rotate OLED to fit
    if (is_keyboard_left()) {
        return OLED_ROTATION_90;
	}
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
	// Render the OLED
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
	return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	// Set base layer
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	// Allow swithcing to the 'hidden' layer
   return update_tri_layer_state(state, _NUM, _FN, _SYS);
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
	// Encoders
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
        }
    return true;
}

#endif

#ifdef RGB_MATRIX_ENABLE

#define LED_MATRIX_CENTER {110, 21}

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 5,  4,  3,  2,  1,  0},
        { 6,  7,  8,  9, 10, 11},
        {17, 16, 15, 14, 13, 12},
        {18, 19, 20, 21, 22, 23},
    {NO_LED, 28, 27, 26, 25, 24},

                                        {34, 33, 32, 31, 30, 29},
                                        {35, 36, 37, 38, 39, 40},
                                        {46, 45, 44, 43, 42, 41},
                                        {47, 48, 49, 50, 51, 52},
                                {NO_LED, 57, 56, 55, 54, 53}
    }, {
        // LED Index to Physical Position
        // The default expected range of values for `{ x, y }` is the inclusive range `{ 0..224, 0..64 }`
        // 224 / (14 real cols + 6 cols as buffer) ~= 11 per col
        // 64 / (5 real rows + 1 row as buffer) ~= 10 per row

        // Left half
        { 55,  2}, { 44,  1}, { 33,  0}, { 22,  1}, { 11,  3}, {  0,  4},
        {  0, 14}, { 11, 13}, { 22, 11}, { 33, 10}, { 44, 11}, { 55, 12},
        { 55, 22}, { 44, 21}, { 33, 20}, { 22, 21}, { 11, 23}, {  0, 24},
        {  0, 34}, { 11, 33}, { 22, 31}, { 33, 30}, { 44, 31}, { 55, 32},
        { 70, 27}, { 66, 40}, { 50, 42}, { 39, 41} ,{ 28, 40}, // bottom row, right to left, far outer right key is first

        // Right half
        {165, 2}, {176, 1}, {187, 0}, {198, 1}, {209, 3}, {220, 4},
        {220, 14}, {209, 13}, {198, 11}, {187, 10}, {176, 11}, {165, 12},
        {165, 22}, {176, 21}, {187, 20}, {198, 21}, {209, 23}, {220, 24},
        {220, 34}, {209, 33}, {198, 31}, {187, 30}, {176, 31}, {165, 32},
        {150, 27}, {154, 40}, {170, 42}, {181, 41}, {192, 40}, // bottom row, left to right, far outer left key is first
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif