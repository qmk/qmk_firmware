#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_steno.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define STEN 2 // steno
#define MDIA 3 // media keys


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,---------------------------------------------------.           ,---------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4   |   5  | STEN |           | NONE  |   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+-------+-------------|           |-------+------+------+------+------+------+--------|
 * | Del    |   '  |   ,  |   .  |   P   |   Y  |  Esc |           | Caps  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+-------+------|      |           |       |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U   |   I  |------|           |-------|   D  |   H  |   T  |   N  |   S  |   -    |
 * |--------+------+------+------+-------+------|  Tab |           | Enter |------+------+------+------+------+--------|
 * | LShift |   ;  |   Q  |   J  |   K   |   X  |      |           |       |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `--------+------+------+------+-------+-------------'           `--------------+------+------+------+------+--------'
 *   |  L1  | NONE |  Grv | Left | Right |                                        |  Up  | Down |   [  |   ]  |  L1  |
 *   `-----------------------------------'                                        `----------------------------------'
 *                                        ,--------------.         ,---------------.
 *                                        |  PgUp | PgDn |         | Home  |  End  |
 *                                 ,------|-------|------|         |-------+-------+------.
 *                                 |      |       | NONE |         | AltGr |       |      |
 *                                 | Alt  | Enter |------|         |-------| Space | Ctrl |
 *                                 |      |       | Supr |         | ~MDIA |       |      |
 *                                 `---------------------'         `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TG(STEN),
        KC_DEL,         KC_QUOT,      KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_ESC,
        KC_BSPC,        KC_A,         KC_O,   KC_E,   KC_U,   KC_I,
        KC_LSFT,        KC_SCLN,      KC_Q,   KC_J,   KC_K,   KC_X,   KC_TAB,
        MO(SYMB),       KC_NO,        KC_GRV, KC_LEFT,KC_RGHT,
                                                      KC_PGUP,KC_PGDN,
                                                              KC_NO,
                                              KC_LALT,KC_ENT ,M(0),
        // right hand
             KC_NO,       KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_BSLS,
             KC_CAPS,     KC_F,   KC_G,   KC_C,   KC_R,   KC_L,    KC_SLSH,
                          KC_D,   KC_H,   KC_T,   KC_N,   KC_S,    KC_MINS,
             KC_ENT,      KC_B,   KC_M,   KC_W,   KC_V,   KC_Z   , KC_RSFT,
                                  KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC, MO(SYMB),
             KC_HOME, KC_END,
             KC_RALT,
             MO(MDIA),KC_SPC,KC_RCTL
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 2: Steno for Plover
 *
 * ,---------------------------------------------------.           ,---------------------------------------------------.
 * |        |      |   #  |   #  |   #   |   #  |      |           |       |   #  |   #  |   #  |   #  |   #  |        |
 * |--------+------+------+------+-------+-------------|           |-------+------+------+------+------+------+--------|
 * |        |      |   S  |   T  |   P   |   H  |   *  |           |   *   |   F  |   P  |   L  |   T  |   D  |        |
 * |--------+------+------+------+-------+------|      |           |       |------+------+------+------+------+--------|
 * |        |      |   S  |   K  |   W   |   R  |------|           |-------|   R  |   B  |   G  |   S  |   Z  |        |
 * |--------+------+------+------+-------+------|   *  |           |   *   |------+------+------+------+------+--------|
 * |        |      |      |      |       |      |      |           |       |      |      |      |      |      |        |
 * `--------+------+------+------+-------+-------------'           `--------------+------+------+------+------+--------'
 *   |  L1  |      |      | Left | Right |                                        |  Up  | Down |      |      |  L1  |
 *   `-----------------------------------'                                        `----------------------------------'
 *                                        ,--------------.         ,---------------.
 *                                        |       |      |         |       |       |
 *                                 ,------|-------|------|         |-------+-------+------.
 *                                 |      |       |      |         |       |       |      |
 *                                 |   A  |   O   |------|         |-------|   E   |   U  |
 *                                 |      |       |      |         |       |       |      |
 *                                 `---------------------'         `----------------------'
 */


[STEN] = LAYOUT_ergodox(  // layout: layer 2: Steno for Plover
        // left hand
        KC_NO,  STN_N1, STN_N2, STN_N3,  STN_N4, STN_N5,  KC_TRNS,
        KC_NO,  KC_NO,  STN_S1, STN_TL,  STN_PL, STN_HL,  STN_ST1,
        KC_NO,  KC_NO,  STN_S2, STN_KL,  STN_WL, STN_RL,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,   STN_ST2,
        KC_TRNS,KC_NO,  KC_NO,  KC_TRNS, KC_TRNS,
                                          KC_NO, KC_NO,
                                                 KC_NO,
                                 STN_A,  STN_O,  KC_TRNS,
        // right hand
          KC_NO,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,   KC_NO,
        STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,   KC_NO,
                  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,   KC_NO,
        STN_ST4,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_TRNS, KC_TRNS,   KC_NO,   KC_NO, KC_TRNS,
        KC_NO,  KC_NO,
        KC_NO,
        KC_TRNS, STN_E, STN_U
),

/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      | STEN |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      | Back |      | Frwd |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Lclk | Mclk | Rclk |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Prev | Play | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_WBAK, KC_TRNS, KC_WFWD, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_BTN1, KC_BTN3, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

// press `key`, but deactivate `layer` whilst it's held
void press_without(int pressed, int key, uint8_t layer)
{
  static bool was_on;
  if (pressed) {
    was_on = layer_state_is(layer);
    layer_off(layer);
    register_code(key);
  } else {
    if (was_on) layer_on(layer);
    unregister_code(key);
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
  case 0:
    press_without(record->event.pressed, KC_LGUI, STEN);
    break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_BOLT);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    __attribute__ ((unused))
    uint32_t layer0 = layer_state & (1UL << 0),
             layer1 = layer_state & (1UL << 1),
             layer2 = layer_state & (1UL << 2),
             layer3 = layer_state & (1UL << 3);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (layer1) ergodox_right_led_1_on();
    if (layer2) ergodox_right_led_2_on();
    if (layer3) ergodox_right_led_3_on();
};
