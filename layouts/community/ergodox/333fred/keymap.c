#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "333fred.h"

// NOTE: Cells marked with ACCESS must remain transparent, they're the keys that actually get to that layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  F5  |           |  F6  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  | GAME |           |GAMEA |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| SYMB |           |MEDIA |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |LCTRL |  F4  |  F5  | LGUI | LALT |                                       | Left | Down |  =   | Right| RGUI |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Copy | Paste|       | Copy | Paste  |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | PgUp |       |  Up  |        |      |
 *                                 | Bcksp|OSL(2)|------|       |------|  Ent   |Space |
 *                                 |      |  VIM | Del  |       | Down |        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox_pretty(  // layer 0 : default
        // left hand
        KC_GRV,        KC_1,        KC_2,  KC_3,    KC_4,    KC_5,    KC_F5,                                      KC_F6,          KC_6, KC_7,    KC_8,    KC_9,   KC_0,           KC_MINS,
        KC_TAB,        KC_Q,        KC_W,  KC_E,    KC_R,    KC_T,    TG(GAME),                                   TG(GAME_ARROW), KC_Y, KC_U,    KC_I,    KC_O,   KC_P,           KC_BSLS,
        KC_ESC,        KC_A,        KC_S,  KC_D,    KC_F,    KC_G,                                                                KC_H, KC_J,    KC_K,    KC_L,   KC_SCLN,        KC_QUOT,
        OSM(MOD_LSFT), CTL_T(KC_Z), KC_X,  KC_C,    KC_V,    KC_B,    TG(SYMB),                                   MO(MDIA),       KC_N, KC_M,    KC_COMM, KC_DOT, CTL_T(KC_SLSH), OSM(MOD_RSFT),
        OSM(MOD_LCTL), KC_F4,       KC_F5, KC_LGUI, KC_LALT,                                                                            KC_LEFT, KC_DOWN, KC_EQL, KC_RIGHT,       KC_RGUI,
                                                                      LCTL(KC_C),     LCTL(KC_V),     LCTL(KC_C), LCTL(KC_V),
                                                                                      KC_PGUP,        KC_UP,
                                                             KC_BSPC, TD(TD_SYM_VIM), KC_DEL,         KC_DOWN,    KC_ENT,         KC_SPC
    ),

/* Keymap 2: Codeflow Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  F7  |  F8  |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |ACCESS|       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[CODEFLOW] = LAYOUT_ergodox_pretty(  // layer 1 : code
        // left hand
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                      KC_F7,   KC_F8,   _______, _______, _______,
                                                     _______, _______,  _______, _______,
                                                              _______,  _______,
                                            _______, _______, _______,  _______, _______, _______
    ),
/* Keymap 3: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   (  |   )  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   {  |   }  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|ACCESS|           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |   0  |   0  |   .  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |APScr |       |      |      |      |
 *                                 |      |ACCESS|------|       |------|      |      |
 *                                 |      |      | PScr |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox_pretty(
       // left hand
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,                              _______, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE, _______,                              _______, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
       _______, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                                                 KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, _______,
       _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______,                              _______, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, _______,
       _______, _______, _______, _______, _______,                                                                  KC_0,   KC_0,    KC_DOT,  KC_EQL,  _______,
                                                             _______, _______,            _______, _______,
                                                                      PSCREEN_APP,     _______,
                                                    _______, _______, KC_PSCR,            _______, _______, _______
),
/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |ACCESS|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Back+| Back-|       | Vol+ |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |BackTg|       | Vol- |      |      |
 *                                 |      |      |------|       |------| PL/PS| Next |
 *                                 |      |      |      |       | Back |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox_pretty(
       _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_MS_U, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                                         _______, _______, _______, _______, _______, _______,
       _______, _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______, _______,
       _______, _______, _______, KC_BTN1, KC_BTN2,                                                           _______, _______, _______, _______, _______,
                                                             BL_INC,  BL_DEC,      KC_VOLU, _______,
                                                                      BL_TOGG,     KC_VOLD,
                                                    _______, _______, _______,     KC_MPRV, KC_MPLY, KC_MNXT
),
/* Keymap 4: Movement
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |KOpen |KType |TERMCP|TERMPT|      |      |           |      | Copy |      |      |      | Paste|        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |DLeft |DRight|LCTRL | LGUI |      |------|           |------| Left | Down |  Up  | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |SFT_TB| TAB  |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | Home | End  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |ACCESS|------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[VIM] = LAYOUT_ergodox_pretty(
       _______, _______, _______, _______, _______, _______, _______,     _______,  _______, _______, _______, _______,  _______, _______,
       _______, _______, _______, _______, _______, _______, _______,     _______,  _______, _______, _______, _______,  _______, _______,
       _______, DLEFT,   DRIGHT,  KC_LCTL, KC_LGUI, _______,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
       _______, _______, KC_TAB,  _______, _______, _______, _______,     _______,  _______, _______, _______, _______,  _______, _______,
       _______, _______, _______, _______, _______,                                          _______, _______, _______,  _______, _______,
                                                    _______, _______,     KC_HOME, KC_END,
                                                             _______,     _______,
                                           _______, _______, _______,     _______, _______, _______
),
/* Keymap 1: Game Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |ACCESS|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  CTRL  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | SHIFT  |  Z   |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |ENTER |      |      | LOCK | BSPC |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |  F5  |  F6  |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | ALT  | SPC  |------|       |------|        |      |
 *                                 |      |      | SYMB |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[GAME] = LAYOUT_ergodox_pretty(  // layer 1 : code
        // left hand
        KC_ESC,  _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
        KC_LSFT, KC_Z,    _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        KC_ENT,  _______, _______, KC_LOCK, KC_BSPC,                                                                _______, _______, _______, _______, _______,
                                                              KC_F5,   KC_F6,         LCTL(KC_C), LCTL(KC_V),
                                                                       _______,       KC_UP,
                                                     KC_LALT, KC_SPC,  OSM(SYMB),     KC_DOWN,    _______, _______
    ),
/* Keymap 1: Game Arrow Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ESC   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  Up  |      |      |      |      |           |ACCESS|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  CTRL  | Left | Down |Right |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | SHIFT  |  Z   |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |ENTER |      |      | LOCK | BSPC |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |  F5  |  F6  |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | ALT  | SPC  |------|       |------|        |      |
 *                                 |      |      | SYMB |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[GAME_ARROW] = LAYOUT_ergodox_pretty(  // layer 1 : code
        // left hand
        KC_ESC,  _______, _______, _______,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_UP,   _______,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,                                              _______, _______, _______, _______, _______, _______,
        KC_LSFT, KC_Z,    _______, _______,  _______, _______, _______,                            _______, _______, _______, _______, _______, _______, _______,
        KC_ENT,  _______, _______, KC_LOCK,  KC_BSPC,                                                                _______, _______, _______, _______, _______,
                                                               KC_F5,   KC_F6,         LCTL(KC_C), LCTL(KC_V),
                                                                        _______,       KC_UP,
                                                      KC_LALT, KC_SPC,  OSM(SYMB),     KC_DOWN,    _______, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_process_keycode(keycode);
  return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    ergodox_board_led_on();
    ergodox_led_all_on();
}

