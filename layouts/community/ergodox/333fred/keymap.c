#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "333fred.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
};

enum custom_macros {
  // Windows macros
  DLEFT,
  DRIGHT,
  PSCREEN_APP,
  LSFT_TAB,

  // KeePass macros
  KEEPASS_OPEN,
  KEEPASS_TYPE,

  // Terminal Copy/Paste
  TERM_CP,
  TERM_PT
};

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
[CODEFLOW] = LAYOUT_ergodox(  // layer 1 : code
        // left hand
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                                             KC_TRNS, KC_TRNS,
                                                                                      KC_TRNS,
                                                                    KC_TRNS, KC_TRNS, KC_TRNS,
        // right han

            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                              KC_F7,   KC_F8,   KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS,
             KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS
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
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,                              KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_EXLM, KC_AT,   KC_LPRN, KC_RPRN, KC_PIPE, KC_TRNS,                              KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
       KC_TRNS, KC_HASH, KC_DLR,  KC_LCBR, KC_RCBR, KC_GRV,                                                 KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,                              KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                                                  KC_0,   KC_0,    KC_DOT,  KC_EQL,  KC_TRNS,
                                                             KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS,
                                                                      M(PSCREEN_APP),     KC_TRNS,
                                                    KC_TRNS, KC_TRNS, KC_PSCR,            KC_TRNS, KC_TRNS, KC_TRNS
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
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,                                                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                             BL_INC,  BL_DEC,      KC_VOLU, KC_TRNS,
                                                                      BL_TOGG,     KC_VOLD,
                                                    KC_TRNS, KC_TRNS, KC_TRNS,     KC_MPRV, KC_MPLY, KC_MNXT
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
       KC_TRNS, KC_TRNS,         KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
       KC_TRNS, M(KEEPASS_OPEN), M(KEEPASS_TYPE), TERM_CP, TERM_PT, KC_TRNS, KC_TRNS,                       KC_TRNS,  LCTL(KC_C), KC_TRNS, KC_TRNS, KC_TRNS,  LCTL(KC_V), KC_TRNS,
       KC_TRNS, M(DLEFT),        M(DRIGHT),       KC_LCTL, KC_LGUI, KC_TRNS,                                          KC_LEFT,    KC_DOWN, KC_UP,   KC_RIGHT, KC_TRNS,    KC_TRNS,
       KC_TRNS, M(LSFT_TAB),     KC_TAB,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS,         KC_TRNS,         KC_TRNS, KC_TRNS,                                                               KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,
                                                                             KC_TRNS, KC_TRNS,     KC_HOME, KC_END,
                                                                                      KC_TRNS,     KC_TRNS,
                                                                    KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
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
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_Z,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_ENT,  KC_TRNS, KC_TRNS, KC_LOCK, KC_BSPC,                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                              KC_F5,   KC_F6,         LCTL(KC_C), LCTL(KC_V),
                                                                       KC_TRNS,       KC_UP,
                                                     KC_LALT, KC_SPC,  OSM(SYMB),     KC_DOWN,    KC_TRNS, KC_TRNS
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
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS,                                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LSFT, KC_Z,    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_ENT,  KC_TRNS, KC_TRNS, KC_LOCK,  KC_BSPC,                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                               KC_F5,   KC_F6,         LCTL(KC_C), LCTL(KC_V),
                                                                        KC_TRNS,       KC_UP,
                                                      KC_LALT, KC_SPC,  OSM(SYMB),     KC_DOWN,    KC_TRNS, KC_TRNS
    )
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case DLEFT:
          if (record->event.pressed) { // Windows move desktop left
            return MACRO(D(LCTL), D(LGUI), T(LEFT), U(LGUI), U(LCTL), END);
          }
          break;
        case DRIGHT:
          if (record->event.pressed) { // Windows move desktop right
            return MACRO(D(LCTL), D(LGUI), T(RIGHT), U(LGUI), U(LCTL), END);
          }
          break;
        case PSCREEN_APP:
          if (record->event.pressed) {
            return MACRO(D(LALT), T(PSCR), U(LALT), END);
          }
          break;
        case LSFT_TAB:
          if (record->event.pressed) {
            return MACRO(D(LSFT), T(TAB), U(LSFT), END);
          }
        case KEEPASS_OPEN:
          if (record->event.pressed) { // Keepass open application
            return MACRO(D(LCTL), D(LALT), T(K), U(LALT), U(LCTL), END);
          }
          break;
        case KEEPASS_TYPE:
          if (record->event.pressed) { // Keepass autotype
            return MACRO(D(LCTL), D(LALT), T(A), U(LALT), U(LCTL), END);
          }
          break;
        case TERM_CP:
          if (record->event.pressed) { // Terminal Copy
            return MACRO(D(LCTL), T(INSERT), U(LCTL), END);
          }
          break;
        case TERM_PT:
          if (record->event.pressed) { // Terminal Paste
            return MACRO(D(LSFT), T(INSERT), U(LSFT), END);
          }
          break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_process_record(keycode);
  return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user_keyboard(void) {
    ergodox_board_led_on();
    ergodox_led_all_on();
}

