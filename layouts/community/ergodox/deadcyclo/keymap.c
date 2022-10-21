#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys and navigation
#define UNI 3  // unicode 1
#define UNI2 4 // unicode 2

enum custom_keycodes {
  I3_RUN = SAFE_RANGE,
  VRSN,
  I3_GO_GROUP_1,
  I3_GO_GROUP_2,
  I3_GO_GROUP_3,
  I3_GO_GROUP_4,
  I3_GO_GROUP_5,
  I3_GO_GROUP_6,
  I3_GO_GROUP_7,
  I3_GO_GROUP_8,
  I3_GO_GROUP_9,
  I3_GO_GROUP_10,
  EMOJI_SHRUG,
  EMOJI_YAY,
  EMOJI_HUG,
  EMOJI_SMILE,
  EMOJI_SMILE2,
  EMOJI_HMM1,
  EMOJI_HMM2,
  EMOJI_BEAR1,
  EMOJI_BEAR2,
  EMOJI_FUU,
  EMOJI_EGGY1,
  EMOJI_EGGY2,
  EMOJI_FACE1,
  EMOJI_FACE2,
  EMOJI_UHU,
  EMOJI_SMRK1,
  EMOJI_SMRK2,
  EMOJI_LOVE
};

// TODO: Finish the macros for i3 (Macros should potentially be own function instead to make things easier? some of them at least, f. ex. the ones that use 1-0 keys so we can have a single switch)

// TODO: Do stuff with hyper and meh keys
// TODO: Add macros for lots of stuff. (Lastpass cli, pushbullet cli, other push service cli, linode cli, more?)
// TODO: Make macros for gnu screen and i3wm
// TODO: Need to change hotkeys for lastpass, and potentially make my own keys for them on one of my layers
// TODO: Look into using tap dance
// TODO: Use leader key for stuff. See https://github.com/qmk/qmk_firmware/wiki
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc/L3 |   1  |   2  |   3  |   4  |   5  |  6   |           |   6  |   7  |   8  |   9  |   0  |   -  |   =/L3 |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab/L1 |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |   \/L1 |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | ctrl/'|
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z / L4|X / L2|   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |. / L2|/ / L4| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  UNI |AltShf| Lalt | Ralt |                                       | Lalt | Ralt | LEAD |  UNI | ~/L1 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | Home |       | PgUp |  Ins   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | End  |       | PgDn |        |      |
 *                                 | Space|  TAB |------|       |------|  BSPC  |Enter |
 *                                 |      |      |   [  |       |  ]   |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
	LT(UNI,KC_ESC),         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_6,
        LT(SYMB,KC_TAB),        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_LCTL,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        LT(4, KC_Z),  LT(MDIA, KC_X),   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        LT(SYMB,KC_GRV),LCTL(LSFT(KC_U)),      LALT(KC_LSFT),  KC_RALT,KC_LALT,
                                              ALT_T(KC_APP),  KC_HOME,
                                                              KC_END,
                                               KC_SPC,KC_TAB,KC_LBRC,
        // right hand
		KC_6,     KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,             LT(UNI,KC_EQL),
	TG(MDIA),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             LT(SYMB, KC_BSLS),
	KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,CTL_T(KC_QUOT),
	MEH_T(KC_NO),KC_N,   KC_M,   KC_COMM,LT(MDIA, KC_DOT), LT(UNI2, KC_SLSH),   KC_RSFT,
		KC_LALT,  KC_RALT,QK_LEAD,LCTL(LSFT(KC_U)),          LT(SYMB,KC_TILD),
             KC_PGUP,        KC_INS,
             KC_PGDN,
             KC_RBRC,KC_BSPC, KC_ENT
    ),
/* Keymap 1: Symbol Layer LCTL(LSFT(KC_U))
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |   F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Toggle|Animat|       | Hue+ | Hue- |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|Solid |       |      |      |      |
 *                                 |ness- |ness+ |------|       |------| DEL  |      |
 *                                 |      |      |      |       | EPRM |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_TOG,RGB_MOD,
       RGB_M_P,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_F6, KC_F7,   KC_F8,  KC_F9,   KC_F10,   KC_F11,  KC_F12,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_HUD, RGB_HUI,
       KC_TRNS,
       EE_CLR,  KC_DEL, KC_TRNS
),
/* Keymap 2: Media, mouse and navigation
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | gg(1)| gg(2)| gg(3)| gg(4)| gg(5)| gg(6)|           | gg(6)| gg(7)| gg(8)| gg(9)| gg(0)|      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp | RUN  |      |      |           |      |      |      |  Up  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Right|      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Prev | Next |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA , MOUSE and NAVIGATION
[MDIA] = LAYOUT_ergodox(
		KC_TRNS, I3_GO_GROUP_1, I3_GO_GROUP_2, I3_GO_GROUP_3, I3_GO_GROUP_4, I3_GO_GROUP_5, I3_GO_GROUP_6,
KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, I3_RUN, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
		I3_GO_GROUP_6, I3_GO_GROUP_7, I3_GO_GROUP_8, I3_GO_GROUP_9, I3_GO_GROUP_10, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,  KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS,  KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE,  KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: Unicode
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  ┌   |  ┐   |  └   |  ┘   |  │   |  ─   |           |  ╔   |  ╗   |  ╚   |  ╝   |  ║   |  ═   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | shrug| yay  | hug  | smile|smile2|      |           |      |  ■   |  λ   |  →   |  ➙   |  ▻   |  █     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | hmm1 | hmm2 | bear1| bear2| fuu  |------|           |------|  ☺   |  ☻   |  ☹   |  ♡   |  ♥   |  ░     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | eggy1| eggy2| face1| face2| uhu  |      |           |      |  ❤   |  ☐   |  ☑   |  ☒   |  ✓   |  ▄     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      | smrk1| smrk2| love | VER  |                                       |  ✔   |  ✗   |  ✘   |  ●   |  ▀   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |   ▒  |  ▓   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Unicode
[UNI] = LAYOUT_ergodox(
		KC_TRNS, UC(0x250c), UC(0x2510), UC(0x2514), UC(0x2518), UC(0x2502), UC(0x2500),
		KC_TRNS, EMOJI_SHRUG, EMOJI_YAY, EMOJI_HUG, EMOJI_SMILE, EMOJI_SMILE2, KC_TRNS,
		KC_TRNS, EMOJI_HMM1, EMOJI_HMM2, EMOJI_BEAR1, EMOJI_BEAR2, EMOJI_FUU,
		KC_TRNS, EMOJI_EGGY1, EMOJI_EGGY2, EMOJI_FACE1, EMOJI_FACE2, EMOJI_UHU, KC_TRNS,
		KC_TRNS, EMOJI_SMRK1, EMOJI_SMRK2, EMOJI_LOVE, VRSN,
		KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       UC(0x2554),  UC(0x2557), UC(0x255a), UC(0x255d), UC(0x2551), UC(0x2550), KC_TRNS,
       KC_TRNS,  UC(0x25a0), UC(0x03bb), UC(0x2192), UC(0x2799), UC(0x25bb), UC(0x2588),
                 UC(0x263a), UC(0x263b), UC(0x2639), UC(0x2661), UC(0x2665), UC(0x2591),
       KC_TRNS,  UC(0x2764), UC(0x2610), UC(0x2611), UC(0x2612), UC(0x2713), UC(0x2584),
       UC(0x2714), UC(0x2717), UC(0x2718), UC(0x25cf), UC(0x2580),
		UC(0x2592), UC(0x2593),
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 4: Unicode 2
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  ¹   |  ²   |  ³   |  ⁴   |  ⁵   |  ⁶   |           |  ⁶   |  ⁷   |  ⁸   |  ⁹   |  ⁰   |  ℃   |   ™    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  ₁   |  ₂   |  ₃   |  ₄   |  ₅   |  ₆   |           |  ₆   |  ₇   |  ₈   |  ₉   |  ₀   |  ⁄   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  ⅞   |  ⅝   |  ⅜   |  ⅛   |  ⅚   |------|           |------|  ⅓   |  ⅒   |  ⅑   |  ⅐   |  ¾   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  ⅗   |  ⅖   |  ⅕   |  ⅔   |           |  ¼   |  ⅙   |  ⅘   |  ½   |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Unicode 2
[UNI2] = LAYOUT_ergodox(
		KC_TRNS, UC(0x00b9), UC(0x00b2), UC(0x00b3), UC(0x2074), UC(0x2075), UC(0x2076),
		KC_TRNS, UC(0x2081), UC(0x2082), UC(0x2083), UC(0x2084), UC(0x2085), UC(0x2086),
		KC_TRNS, UC(0x215e), UC(0x215d), UC(0x215c), UC(0x215b), UC(0x215a),
		KC_TRNS, KC_TRNS, KC_TRNS, UC(0x2157), UC(0x2156), UC(0x2155), UC(0x2154),
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
		UC(0x2076),  UC(0x2077), UC(0x2078), UC(0x2079), UC(0x2070), UC(0x2103), UC(0x2122),
		UC(0x2086),  UC(0x2087), UC(0x2088), UC(0x2089), UC(0x2080), UC(0x2044), KC_TRNS,
		UC(0x2153), UC(0x2152), UC(0x2151), UC(0x2150), UC(0x00be), KC_TRNS,
		UC(0x00bc),  UC(0x2159), UC(0x2158), UC(0x00bd), KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,
		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case I3_RUN:
                tap_code16(C(KC_I));
                tap_code(KC_R);
                return false;
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            case I3_GO_GROUP_1 ... I3_GO_GROUP_10:
                tap_code16(C(KC_I));
                tap_code(KC_G);
                if (keycode == I3_GO_GROUP_10) {
                    tap_code(KC_0);
                } else {
                    tap_code(KC_1 + (keycode - I3_GO_GROUP_1));
                }
                return false;
            case EMOJI_SHRUG:
                send_unicode_string("¯\\_(ツ)_/¯");
                return false;
            case EMOJI_YAY:
                SEND_STRING("\\o/");
                return false;
            case EMOJI_HUG:
                send_unicode_string("༼ つ ◕_◕ ༽つ");
                return false;
            case EMOJI_SMILE:
                send_unicode_string("ʘ‿ʘ");
                return false;
            case EMOJI_SMILE2:
                send_unicode_string("(ʘ‿ʘ)");
                return false;
            case EMOJI_HMM1:
                send_unicode_string("ಠ_ಠ");
                return false;
            case EMOJI_HMM2:
                send_unicode_string("(ಠ_ಠ)");
                return false;
            case EMOJI_BEAR1:
                send_unicode_string("ʕ•ᴥ•ʔ");
                return false;
            case EMOJI_BEAR2:
                send_unicode_string("(ᵔᴥᵔ)");
                return false;
            case EMOJI_FUU:
                send_unicode_string("╭∩╮(-_-)╭∩╮");
                return false;
            case EMOJI_EGGY1:
                send_unicode_string("(╯°□°）╯");
                return false;
            case EMOJI_EGGY2:
                send_unicode_string("ノ( ゜-゜ノ)");
                return false;
            case EMOJI_FACE1:
                SEND_STRING("(-_-)");
                return false;
            case EMOJI_FACE2:
                send_unicode_string("(•_•)");
                return false;
            case EMOJI_UHU:
                send_unicode_string("⊙﹏⊙");
                return false;
            case EMOJI_SMRK1:
                send_unicode_string("^̮^");
                return false;
            case EMOJI_SMRK2:
                send_unicode_string("(^̮^)");
                return false;
            case EMOJI_LOVE:
                send_unicode_string("♥‿♥");
                return false;
        }
    }
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  set_unicode_input_mode(UC_LNX);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0xff,0x00,0x00);
      #endif
      break;
    case 2:
      ergodox_right_led_2_on();
      #ifdef RGBLIGHT_ENABLE
      rgblight_setrgb(0x00,0xff,0x00);
      #endif
      break;
    case 3:
      ergodox_right_led_3_on();
      #ifdef RGBLIGHT_ENABLE
       rgblight_setrgb(0x00,0x00,0xff);
      #endif
      break;
    case 4:
      ergodox_right_led_1_on();
      ergodox_right_led_3_on();
      #ifdef RGBLIGHT_ENABLE
       rgblight_setrgb(0xff,0x00,0xff);
      #endif
      break;
    default:
      // none
      break;
    }

};
