#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSE,
  _TAB
};

#define MOUSE MO(_MOUSE)
#define LOWER_SPACE LT(_LOWER, KC_SPC)
#define RAISE_SPACE LT(_RAISE, KC_SPC)

// one shot keycodes
#define OS_GUI OSM(MOD_LGUI)
#define OS_CTL OSM(MOD_LCTL)
#define OS_ALT OSM(MOD_LALT)
#define OS_SFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty (base layer)
 * ,-----------------------------------------------------------------------------------.
 * | Tab¹ |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc³ |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '³  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps²|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter²|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Mouse | GUI  | Alt  | Lower Space | Raise Space | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 * ¹Hold to switch to Tab layer
 * ²Shift when held
 * ³Ctrl when held
 */
[_QWERTY] = LAYOUT_planck_grid(
    LT(_TAB, KC_TAB), KC_Q,  KC_W,    KC_E,    KC_R,        KC_T,        KC_Y,        KC_U,        KC_I,    KC_O,    KC_P,    KC_BSPC,
    LCTL_T(KC_ESC),   KC_A,  KC_S,    KC_D,    KC_F,        KC_G,        KC_H,        KC_J,        KC_K,    KC_L,    KC_SCLN, RCTL_T(KC_QUOT),
    LSFT_T(KC_CAPS),  KC_Z,  KC_X,    KC_C,    KC_V,        KC_B,        KC_N,        KC_M,        KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENTER),
    KC_LCTL,          MOUSE, KC_LGUI, KC_LALT, LOWER_SPACE, LOWER_SPACE, RAISE_SPACE, RAISE_SPACE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Ctrl¹| Alt¹ | GUI¹ | Prev | Play | Stop | Next |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             | Home | Vol- | Vol+ | End  |
 * `-----------------------------------------------------------------------------------'
 * ¹OneShot
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_DEL,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
    _______, _______, _______, _______, _______, OS_CTL,  OS_ALT,  OS_GUI,  KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_VOLD, KC_VOLU, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Ctrl¹| Alt¹ | GUI¹ |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 * ¹OneShot
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_TAB,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_DEL,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    _______, _______, _______, _______, _______, OS_CTL,  OS_ALT,  OS_GUI,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Tab Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    Space    |    Space    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_TAB] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENTER,
    _______, _______, _______, _______, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  _______, _______, _______, _______
),

/* Mouse (RGB & mouse control)
 *
 *        V---------- RGB CONTROL -----------V------ Mouse Control ------V
 * ,-----------------------------------------------------------------------------------.
 * |      | HUE+ | SAT+ |BRGTH+|------|------|------| Btn1 |  Up  | Btn2 |------|Reset |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | HUE- | SAT- |BRGTH-| RGB  |RGBMOD|WheelU| Left | Down | Right|------|Debug |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |------|------|------|------|------|WheelD| Btn3 | Btn4 | Btn5 |------|------|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |CPgUp | Bri- | Bri+ |CPgDn |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    _______, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_MS_U,    KC_BTN2, XXXXXXX, RESET,
    _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_TOG, RGB_MOD, KC_WH_U, KC_MS_L, KC_MS_D,    KC_MS_R, XXXXXXX, DEBUG,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_D, KC_BTN3, KC_BTN4,    KC_BTN5, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, C(KC_PGUP), KC_BRID, KC_BRIU, C(KC_PGDN)
),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER_SPACE:
	    return 150;
        case RAISE_SPACE:
	    return 150;
        default:
            return TAPPING_TERM;
    }
}
