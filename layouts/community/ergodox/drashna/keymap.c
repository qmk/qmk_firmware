#include "drashna.h"

#ifdef UNICODEMAP_ENABLE
#    include "drashna_unicode.h"
#endif  // UNICODEMAP_ENABLE
#ifndef UNICODE_ENABLE
#    define UC(x) KC_NO
#endif
#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

enum more_custom_keycodes { KC_SWAP_NUM = NEW_SAFE_RANGE };

// define layer change stuff for underglow indicator
bool skip_leds = false;

/*
 * The `LAYOUT_ergodox_pretty_base` macro is a template to allow the use of
 * identical modifiers for the default layouts (eg QWERTY, Colemak, Dvorak,
 * etc), so that there is no need to set them up for each layout, and modify
 * all of them if I want to change them.  This helps to keep consistency and
 * ease of use. K## is a placeholder to pass through the individual keycodes
 */
// clang-format off
#define LAYOUT_ergodox_pretty_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_ergodox_pretty_wrapper( \
      KC_ESC,  ________________NUMBER_LEFT________________, UC_FLIP,                 UC_TABL, ________________NUMBER_RIGHT_______________, KC_MINS, \
      LALT_T(KC_TAB), K01, K02, K03,      K04,     K05,     TG(_DIABLO),         TG(_DIABLO), K06,     K07,     K08,     K09,     K0A,     KC_BSLS, \
      KC_C1R3, K11,    K12,     K13,      K14,     K15,                                       K16,     K17,     K18,     K19,     K1A, RALT_T(KC_QUOT), \
      KC_MLSF, CTL_T(K21), K22, K23,      K24,     K25,     TG(_GAMEPAD),       TG(_GAMEPAD), K26,     K27,     K28,     K29,  RCTL_T(K2A), KC_MRSF, \
      KC_GRV,  OS_MEH, OS_HYPR, KC_LBRC, KC_RBRC,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, UC(0x2E2E),        \
                                                  OS_LALT, OS_LGUI,                 OS_RGUI, CTL_T(KC_ESCAPE),                                      \
                                                           KC_APP,                  KC_MENU,                                                        \
                              KC_SPC, LT(_LOWER, KC_BSPC), OS_LWR,                  OS_RSE, LT(_RAISE, KC_DEL), KC_ENT                              \
    )

#define LAYOUT_ergodox_pretty_base_wrapper(...)       LAYOUT_ergodox_pretty_base(__VA_ARGS__)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: QWERTY Layer
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   = +  |  1 ! | 2 @  | 3 #  | 4 $  | 5 %  | TG(4)|           | TG(4)| 6 ^  | 7 &  |  8 * | 9 (  |  0 ) |  - _   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |   Q  |   W  |   E  |   R  |   T  | TG(3)|           |TG(3) |   Y  |   U  |   I  |   O  |   P  |  \ |   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Bksp  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |  ' "   |
 * |--------+------+------+------+------+------| TG(2)|           | TG(2)|------+------+------+------+------+--------|
 * | Shift  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  , < |  . > |  ? / | Shift  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  MEH | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT | SYMB |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,--------------.       ,--------------.
 *                                        |Alt/Ap|  Win  |       | Alt  |Ctl/Esc|
 *                                 ,------|------|-------|       |------+-------+------.
 *                                 |      |      | Home  |       | PgUp |       |      |
 *                                 | Space| Bksp |-------|       |------|  DEL  |Enter |
 *                                 |      |      | End   |       | PgDn |       |      |
 *                                 `---------------------'       `---------------------'
 */
  [_QWERTY] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
    _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
    _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
  ),
/* Keymap 0: COLEMAK layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   F  |   P  |   G  |  L1  |           |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |O / L2|   '    |
 * |--------+------+------+------+------+------| OVER |           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  MEH | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT | SYMB |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [_COLEMAK] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),
/* Keymap 0: DVORAK Layout
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   \    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   '  |   ,  |   .  |   P  |   Y  |  L1  |           |  L1  |   F  |   G  |   C  |   R  |   L  |   /    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   O  |   E  |   U  |   I  |------|           |------|   D  |   H  |   T  |   N  |S / L2|   -    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |:/Ctrl|   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |Z/Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  MEH | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT | SYMB |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [_DVORAK] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
    _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
    _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
  ),
/* Keymap 0: WORKMAN layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   D  |   R  |   W  |   B  |  L1  |           |  L1  |   J  |   F  |   U  |   P  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   H  |   T  |   D  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------| OVER |           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | `/SYM|  MEH | LGUI |  [ { | ] }  |                                       | LEFT | DOWN |  UP  |RIGHT | SYMB |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */

  [_WORKMAN] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
    _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
    _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
  ),

  [_NORMAN] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________NORMAN_L1_________________, _________________NORMAN_L1_________________,
    _________________NORMAN_L2_________________, _________________NORMAN_R2_________________,
    _________________NORMAN_L3_________________, _________________NORMAN_R3_________________
  ),

  [_MALTRON] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________MALTRON_L1________________, _________________MALTRON_R1________________,
    _________________MALTRON_L2________________, _________________MALTRON_R2________________,
    _________________MALTRON_L3________________, _________________MALTRON_R3________________
  ),

  [_EUCALYN] = LAYOUT_ergodox_pretty_base_wrapper(
    _________________EUCALYN_L1________________, _________________EUCALYN_R1________________,
    _________________EUCALYN_L2________________, _________________EUCALYN_R2________________,
    _________________EUCALYN_L3________________, _________________EUCALYN_R3________________
  ),

  [_CARPLAX] = LAYOUT_ergodox_pretty_base_wrapper(
    _____________CARPLAX_QFMLWY_L1_____________, _____________CARPLAX_QFMLWY_R1_____________,
    _____________CARPLAX_QFMLWY_L2_____________, _____________CARPLAX_QFMLWY_R2_____________,
    _____________CARPLAX_QFMLWY_L3_____________, _____________CARPLAX_QFMLWY_R3_____________
  ),


// Reverts OSM(Shift) to normal Shifts. However, may not need since we fixed the issue with RDP (LOCAL RESOURCES)
  [_MODS] = LAYOUT_ergodox_pretty_wrapper(
             _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,                                   _______, _______, _______, _______, _______, _______,
             KC_LSFT, _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, _______, _______, KC_RSFT,
             _______, _______, _______, _______, _______,                                                     _______, _______, _______, _______, _______,
                                                          _______, _______,                 _______, _______,
                                                                   _______,                 _______,
                                                 _______, _______, _______,                 _______, _______, _______
            ),


/* Keymap 4: Customized Overwatch Layout
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |      |      |      |      |      |      |           |      |  F9  | F10  | F11  |  F12 |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   F1   |  K   |  Q   |  W   |  E   |  R   |  T   |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   TAB  |  G   |  A   |  S   |  D   |  F   |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  LCTR  | LSHFT|  Z   |  X   |  C   |  V   |      |           |      |   N  |  M   |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |   J  |  U   |  I   |  Y   |  T   |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  O   |  P   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LGUI |       |      |      |      |
 *                                 |  V   | SPACE|------        |------|      | Enter|
 *                                 |      |      |  H   |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [_GAMEPAD] = LAYOUT_ergodox_pretty_wrapper(
             KC_ESC,  KC_NO,   KC_1,    KC_2,    KC_3, HYPR(KC_Q), HYPR(KC_GRV),            KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NO,   KC_NO,
             KC_F1,   KC_K,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    UC_SHRG, UC_DISA, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_TAB,  KC_G,    KC_A,    KC_S,    KC_D,    KC_F,                                      KC_I,    KC_O,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_TRNS,            TG(_GAMEPAD), KC_N,    KC_M,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_GRV,  KC_U,    KC_I,    KC_Y,    KC_T,                                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,
                                                          KC_O,    KC_P,                    MAGIC_TOGGLE_NKRO, LALT(KC_PSCR),
                                                                   KC_LGUI,                 KC_HYPR,
                                                 KC_V,    KC_SPC,  KC_H,                    KC_NO, KC_NO,  KC_SWAP_NUM
            ),

/* Keymap 3:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   ESC  |  V   |  D   | ALT  |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   TAB  |  S   |  I   |  F   |  M   |  T   |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |    Q   |  1   |  2   |  3   |  4   |  G   |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | NUMLOCK| NUM1 | NUM2 | NUM3 | NUM4 |  Z   |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTL | MAC1 | MAC2 | MAC3 | MAC4 |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   L  |  J   |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  G   |       |      |      |      |
 *                                 | SPACE|  Q   |------        |------|      |      |
 *                                 | SHIFT| ALT  | 0MAC |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [_DIABLO] = LAYOUT_ergodox_pretty_wrapper(
             KC_ESC,  KC_V,    KC_D,    KC_LALT, KC_NO,   KC_NO,   KC_NO,                   KC_TRNS, KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_NO,
             KC_TAB,  KC_S,    KC_I,    KC_F,    KC_M,    KC_T,    KC_TRNS,                 KC_TRNS, KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_Q,    KC_1,    KC_2,    KC_3,    KC_4,    KC_G,                                      KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_LCTL, KC_D3_1, KC_D3_2, KC_D3_3, KC_D3_4, KC_Z,    KC_NO,                   KC_NO,   KC_N,    KC_M,     KC_NO,   KC_NO,   KC_NO,   KC_NO,
             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                                       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                                             KC_L,    KC_J,                 KC_NO,   KC_NO,
                                                                      KC_F,                 KC_NO,
                          SFT_T(KC_SPACE),  ALT_T(KC_Q),   KC_DIABLO_CLEAR,                 KC_PGDN, KC_DEL,  KC_ENT
            ),

  [_LOWER] = LAYOUT_ergodox_pretty_wrapper(
             KC_F12,  _________________FUNC_LEFT_________________, _______,                 _______, _________________FUNC_RIGHT________________, KC_F11,
             KC_TILD, _________________LOWER_L1__________________, _______,                 _______, _________________LOWER_R1__________________, KC_PIPE,
             _______, ___________________BLANK___________________,                                   _________________LOWER_R2__________________, KC_DQUO,
             _______, ___________________BLANK___________________, _______,                 _______, _________________LOWER_R3__________________, KC_PSCR,
             _______, _______, _______, _______, _______,                                                     _______, _______, _______, _______, KC_PAUS,
                                                          _______, _______,                 _______, _______,
                                                                   _______,                 _______,
                                                 _______, _______, _______,                 _______, _______, _______
            ),

  [_RAISE] = LAYOUT_ergodox_pretty_wrapper(
             KC_F12,  _________________FUNC_LEFT_________________, _______,                 _______, _________________FUNC_RIGHT________________, KC_F11,
             KC_GRV,  _________________RAISE_L1__________________, _______,                 _______, _________________RAISE_R1__________________, KC_BSLS,
             _______, _________________RAISE_L2__________________,                                   _________________RAISE_R2__________________, KC_QUOT,
             _______, _________________RAISE_L3__________________, _______,                 _______, _________________RAISE_R3__________________, KC_PSCR,
             _______, _______, _______, _______, _______,                                                     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_SLCK,
                                                          _______, _______,                 _______, _______,
                                                                   _______,                 _______,
                                                 _______, _______, _______,                 _______, _______, _______
            ),

  [_ADJUST] = LAYOUT_ergodox_pretty_wrapper(
             KC_MAKE, _______, _______, _______, _______, _______, _______,                 KC_NUKE, _________________ADJUST_R1_________________, KC_RST,
             VRSN,    _________________ADJUST_L1_________________, _______,                 _______, _______, _______, _______, _______, _______, EEP_RST,
             _______, _________________ADJUST_L2_________________,                                   _________________ADJUST_R2_________________, RGB_IDL,
             _______, _________________ADJUST_L3_________________, _______,                 _______, _________________ADJUST_R3_________________, TG(_MODS),
             _______, _______, _______, _______, _______,                                                     _______, _______, _______, _______, _______,
                                                          _______, _______,                 _______, _______,
                                                                   _______,                 _______,
                                                 _______, _______, _______,                 _______, _______, _______
            ),

};
// clang-format on

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_1:
            if (IS_LAYER_ON(_GAMEPAD) && userspace_config.swapped_numbers) {
                if (record->event.pressed) {
                    register_code(KC_2);
                } else {
                    unregister_code(KC_2);
                }
                return false;
            }
            break;
        case KC_2:
            if (IS_LAYER_ON(_GAMEPAD) && userspace_config.swapped_numbers) {
                if (record->event.pressed) {
                    register_code(KC_1);
                } else {
                    unregister_code(KC_1);
                }
                return false;
            }
            break;
        case KC_SWAP_NUM:
            if (record->event.pressed) {
                userspace_config.swapped_numbers ^= 1;
                eeconfig_update_user(userspace_config.raw);
            }
            break;
    }
    // switch (keycode) {
    //  case KC_P00:
    //    if (!record->event.pressed) {
    //      register_code(KC_KP_0);
    //      unregister_code(KC_KP_0);
    //      register_code(KC_KP_0);
    //      unregister_code(KC_KP_0);
    //    }
    //    return false;
    //    break;
    //}
    return true;
}

void matrix_scan_keymap(void) {  // runs frequently to update info
    uint8_t modifiers     = get_mods();
    uint8_t led_usb_state = host_keyboard_leds();
    uint8_t one_shot      = get_oneshot_mods();

    if (!skip_leds) {
        ergodox_board_led_off();
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();

        // Since we're not using the LEDs here for layer indication anymore,
        // then lets use them for modifier indicators.  Shame we don't have 4...
        // Also, no "else", since we want to know each, independently.
        if ((modifiers | one_shot) & MOD_MASK_SHIFT || led_usb_state & (1 << USB_LED_CAPS_LOCK)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set(50);
        }
        if ((modifiers | one_shot) & MOD_MASK_CTRL) {
            ergodox_right_led_1_on();
            ergodox_right_led_1_set(10);
        }
        if ((modifiers | one_shot) & MOD_MASK_ALT) {
            ergodox_right_led_3_on();
            ergodox_right_led_3_set(10);
        }
    }
}

bool indicator_is_this_led_used_keyboard(uint8_t index) {
    switch (index) {
        case 13 ... 14:
            return true;
            break;
        default:
            return false;
    }
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change &&
#    ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
        !g_suspend_state &&
#    endif
#    if defined(RGBLIGHT_ENABLE)
        (!rgblight_config.enable && rgb_matrix_config.enable)
#    else
        rgb_matrix_config.enable
#    endif
    ) {
        switch (get_highest_layer(layer_state)) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                rgb_matrix_set_color(32, 0x00, 0xFF, 0x00);  // Q
                rgb_matrix_set_color(31, 0x00, 0xFF, 0xFF);  // W
                rgb_matrix_set_color(30, 0xFF, 0x00, 0x00);  // E
                rgb_matrix_set_color(29, 0xFF, 0x80, 0x00);  // R
                rgb_matrix_set_color(37, 0x00, 0xFF, 0xFF);  // A
                rgb_matrix_set_color(36, 0x00, 0xFF, 0xFF);  // S
                rgb_matrix_set_color(35, 0x00, 0xFF, 0xFF);  // D
                rgb_matrix_set_color(34, 0x7A, 0x00, 0xFF);  // F

                rgb_matrix_set_color(userspace_config.swapped_numbers ? 27 : 26, 0xFF, 0xFF, 0xFF);  // 1
                rgb_matrix_set_color(userspace_config.swapped_numbers ? 26 : 27, 0x00, 0xFF, 0x00);  // 2
                rgb_matrix_set_color(25, 0x7A, 0x00, 0xFF);                                          // 3
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed * 8, LED_FLAG_MODIFIER);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                break;
            default: {
                bool mods_enabled = IS_LAYER_ON(_MODS);
                switch (get_highest_layer(default_layer_state)) {
                    case _QWERTY:
                        rgb_matrix_layer_helper(HSV_CYAN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _COLEMAK:
                        rgb_matrix_layer_helper(HSV_MAGENTA, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _DVORAK:
                        rgb_matrix_layer_helper(HSV_SPRINGGREEN, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _WORKMAN:
                        rgb_matrix_layer_helper(HSV_GOLDENROD, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _NORMAN:
                        rgb_matrix_layer_helper(HSV_CORAL, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _MALTRON:
                        rgb_matrix_layer_helper(HSV_YELLOW, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _EUCALYN:
                        rgb_matrix_layer_helper(HSV_PINK, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                    case _CARPLAX:
                        rgb_matrix_layer_helper(HSV_BLUE, mods_enabled, rgb_matrix_config.speed, LED_FLAG_MODIFIER);
                        break;
                }
                break;
            }
        }
    }
}

#endif  // RGB_MATRIX_INIT

uint16_t get_tapping_term(uint16_t keycode) {
    if (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) {
        if (mod_config(keycode & 0xf) & MOD_MASK_ALT) {
            return (2 * TAPPING_TERM);
        }
    }
    return TAPPING_TERM;
}
