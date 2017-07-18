#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"

#define CMAKDH 0 // Colemak mod-dh Layer.
#define BASE 1 // default layer
#define SYMB 2 // symbols
#define MDIA 3 // media keys
#define TWITCH 4
#define TMOD 5

// Twitch emote macros.
#define POGCHAMP 1
#define HEYGUYS  2
#define KREYGASM 3
#define SEEMSGOOD 4
#define BLOODTRAIL 5
#define BLEEDPURPLE 6
#define NOTLIKETHIS 7
#define WUTFACE 8
#define FAILFISH 9
#define CMONBRUH 10
#define BABYRAGE 11
#define RESIDENTSLEEPER 12
#define DANSGAME 13
#define COOLCAT 14
#define FUTUREMAN 15
#define DATSHEFFY 16
#define SOONERLATER 17
#define BIBLETHUMP 18
#define GREETSTREAMER 19
#define PJSALT 26
#define PJSUGAR 27
#define RETURNWHISPER 28
#define HOWAREYOU 33
#define DOINGFINE 34

#define TIMEOUT 50
#define PURGE 51
#define STRIKE2 52
#define BAN 53
#define UNBAN 54



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // /* Keymap 0: Basic layer
  //  *
  //  * ,--------------------------------------------------.           ,--------------------------------------------------.
  //  * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
  //  * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
  //  * | Del    |   Q  |   W  |   F  |   P  |   B  | SYMB |           |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
  //  * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
  //  * | BkSp   |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |O / L2|   '    |
  //  * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
  //  * | LShift |Z/Ctrl|   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   .  |//Ctrl| RShift |
  //  * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  //  *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
  //  *   `----------------------------------'                                       `----------------------------------'
  //  *                                        ,-------------.       ,-------------.
  //  *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
  //  *                                 ,------|------|------|       |------+--------+------.
  //  *                                 |      |      | Home |       | PgUp |        |      |
  //  *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
  //  *                                 |      |ace   | End  |       | PgDn |        |      |
  //  *                                 `--------------------'       `----------------------'
  //  */
  // // If it accepts an argument (i.e, is a function), it doesn't need KC_.
  // // Otherwise, it needs KC_*
  [CMAKDH] = KEYMAP(  // layer 0 : Colemak-DH
    // left hand
    KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
    KC_DELT,        KC_Q,         KC_W,   KC_F,   KC_P,   KC_B,   TG(SYMB),
    KC_BSPC,        KC_A,         KC_R,   KC_S,   KC_T,   KC_G,
    KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_D,   KC_V,   ALL_T(KC_NO),
    LT(SYMB,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
    ALT_T(KC_INS),  KC_LGUI,
    KC_HOME,
    KC_SPC,KC_BSPC,KC_END,
    // right hand
    KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
    TG(BASE),    KC_J,   KC_L,   KC_U,   KC_Y,   KC_SCLN,          KC_BSLS,
    KC_M,   KC_N,   KC_E,   KC_I,   GUI_T(KC_O),   LT(MDIA, KC_QUOT),
    MEH_T(KC_NO),KC_K,   KC_H,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
    KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,
    KC_LALT,        CTL_T(KC_ESC),
    KC_PGUP,
    KC_PGDN, LT(TMOD, KC_TAB), LT(TWITCH, KC_ENT)
  ),
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,----------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc |
 *                                 ,------|------|------|       |------+---------+------.
 *                                 |      |      | Home |       | PgUp |         |      |
 *                                 | Space| Tab  |------|       |------|Backspace|Enter |
 *                                 |      |      | End  |       | PgDn |         |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 1 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   KC_LEFT,
        KC_DELT,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   TG(SYMB),
        KC_BSPC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   ALL_T(KC_NO),
        LT(SYMB,KC_GRV),KC_QUOT,      LALT(KC_LSFT),  KC_LEFT,KC_RGHT,
                                              ALT_T(KC_INS),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,             KC_MINS,
             TG(BASE),    KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_BSLS,
                          KC_H,   KC_J,   KC_K,   KC_L,   GUI_T(KC_SCLN),LT(MDIA, KC_QUOT),
             MEH_T(KC_NO),KC_N,   KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,          KC_FN1,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN, LT(TMOD, KC_TAB), LT(TWITCH, KC_ENT)
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
[SYMB] = KEYMAP(
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
       KC_TRNS, KC_UP,   KC_P7,   KC_P8,    KC_P9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_P4,   KC_P5,    KC_P6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_P1,   KC_P2,    KC_P3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_PDOT,  KC_P0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
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
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 2: Twitch emote layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
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
// Twitch emote layer
[TWITCH] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, M(DOINGFINE), M(HOWAREYOU),
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       M(GREETSTREAMER),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       M(PJSUGAR),  M(DANSGAME), M(COOLCAT), M(FUTUREMAN), M(DATSHEFFY), M(SOONERLATER), M(BIBLETHUMP),
                 M(HEYGUYS), M(POGCHAMP), M(SEEMSGOOD), M(KREYGASM), M(BLEEDPURPLE), M(BLOODTRAIL),
       M(PJSALT),  M(NOTLIKETHIS), M(WUTFACE), M(FAILFISH), M(CMONBRUH), M(BABYRAGE), M(RESIDENTSLEEPER),
                          M(RETURNWHISPER), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 5: Twitch mod layer.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
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
// MEDIA AND MOUSE
[TMOD] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 M(UNBAN), M(TIMEOUT), M(PURGE), M(STRIKE2), M(BAN), KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(BASE),
    [3] = ACTION_LAYER_TAP_KEY(TWITCH, KC_ENT),
    [4] = ACTION_LAYER_TAP_KEY(TMOD, KC_TAB),
    [5] = ACTION_LAYER_TAP_KEY(MDIA, KC_QUOT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case POGCHAMP:
        if (record->event.pressed) {
          // return MACRO(D(LSFT),T(P),U(LSFT),T(O),T(G),D(LSFT),T(C),U(LSFT),T(H),T(A),T(M),T(P),T(SPC),END);
          SEND_STRING("PogChamp ");
          break;
        }
        case HEYGUYS:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(H),U(LSFT),T(E),T(Y),D(LSFT),T(G),U(LSFT),T(U),T(Y),T(S),T(SPC),END);
          SEND_STRING("PogChamp ");
          break;
        }
        case KREYGASM:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(K),U(LSFT),T(R),T(E),T(Y),T(G),T(A),T(S),T(M),T(SPC),END);
        }
        case SEEMSGOOD:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(S),U(LSFT),T(E),T(E),T(M),T(S),D(LSFT),T(G),U(LSFT),T(O),T(O),T(D),T(SPC),END);
        }
        case BLOODTRAIL:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(B),U(LSFT),T(L),T(O),T(O),T(D),D(LSFT),T(T),U(LSFT),T(R),T(A),T(I),T(L),T(SPC),END);
        }
        case BLEEDPURPLE:
        if (record->event.pressed) {
          return MACRO(T(B),T(L),T(E),T(E),T(D),D(LSFT),T(P),U(LSFT),T(U),T(R),T(P),T(L),T(E),T(SPC),END);
        }
        case NOTLIKETHIS:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(N),U(LSFT),T(O),T(T),D(LSFT),T(L),U(LSFT),T(I),T(K),T(E),D(LSFT),T(T),U(LSFT),T(H),T(I),T(S),T(SPC),END);
        }
        case WUTFACE:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(W),U(LSFT),T(U),T(T),D(LSFT),T(F),U(LSFT),T(A),T(C),T(E),T(SPC),END);
        }
        case FAILFISH:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(F),U(LSFT),T(A),T(I),T(L),D(LSFT),T(F),U(LSFT),T(I),T(S),T(H),T(SPC),END);
        }
        case CMONBRUH:
        if (record->event.pressed) {
          return MACRO(T(C),T(M),T(O),T(N),D(LSFT),T(B),U(LSFT),T(R),T(U),T(H),T(SPC),END);
          }
        case BABYRAGE:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(B),U(LSFT),T(A),T(B),T(Y),D(LSFT),T(R),U(LSFT),T(A),T(G),T(E),T(SPC),END);
        }
        case RESIDENTSLEEPER:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(R),U(LSFT),T(E),T(S),T(I),T(D),T(E),T(N),T(T),D(LSFT),T(S),U(LSFT),T(L),T(E),T(E),T(P),T(E),T(R),T(SPC),END);
        }
        case DANSGAME:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(D),U(LSFT),T(A),T(N),T(S),D(LSFT),T(G),U(LSFT),T(A),T(M),T(E),T(SPC),END);
        }
        case COOLCAT:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(C),U(LSFT),T(O),T(O),T(L),D(LSFT),T(C),U(LSFT),T(A),T(T),T(SPC),END);
        }
        case FUTUREMAN:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(F),U(LSFT),T(U),T(T),T(U),T(R),T(E),D(LSFT),T(M),U(LSFT),T(A),T(N),T(SPC),END);
        }
        case DATSHEFFY:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(D),U(LSFT),T(A),T(T),D(LSFT),T(S),U(LSFT),T(H),T(E),T(F),T(F),T(Y),T(SPC),END);
        }
        case SOONERLATER:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(S),U(LSFT),T(O),T(O),T(N),T(E),T(R),D(LSFT),T(L),U(LSFT),T(A),T(T),T(E),T(R),T(SPC),END);
        }
        case BIBLETHUMP:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(B),U(LSFT),T(I),T(B),T(L),T(E),D(LSFT),T(T),U(LSFT),T(H),T(U),T(M),T(P),T(SPC),END);
        }
        case GREETSTREAMER:
        if (record->event.pressed) {
          // return MACRO(T(SLSH),T(M),T(E),T(SPC),T(Q),T(U),T(I),T(E),T(T),T(L),T(Y),T(SPC),T(S),T(N),T(E),T(A),T(K),T(S),T(SPC),T(I),T(N),T(SPC),T(A),T(N),T(D),T(SPC),T(T),T(A),T(K),T(E),T(S),T(SPC),T(A),T(SPC),T(S),T(E),T(A),T(T),T(SPC),T(I),T(N),T(SPC),T(T),T(H),T(E),T(SPC),T(G),T(R),T(A),T(S),T(S),T(DOT),W(255),W(255),T(ENT),T(TAB),T(SPC),D(LSFT),T(H),U(LSFT),T(E),T(Y),D(LSFT),T(G),U(LSFT),T(U),T(Y),T(S),T(SPC),D(LSFT),T(H),U(LSFT),T(O),T(W),T(SPC),T(A),T(R),T(E),T(SPC),T(Y),T(O),T(U),T(SPC),T(T),T(O),T(D),T(A),T(Y),D(LSFT),T(SLSH),U(LSFT),T(SPC),D(LSFT),T(C),U(LSFT),T(O),T(O),T(L),D(LSFT),T(C),U(LSFT),T(A),T(T),T(SPC),W(255),W(255),T(ENT),END);
          SEND_STRING("/me comes in and takes a seat.\n\t HeyGuys How are you doing today?");
          return MACRO(W(255),W(255),T(ENT),END);
          break;
        }
        case PJSALT:
        if (record->event.pressed) {
          // return MACRO(D(LSFT),T(P),U(LSFT),D(LSFT),T(J),U(LSFT),D(LSFT),T(S),U(LSFT),T(A),T(L),T(T),T(SPC),END);
          SEND_STRING("PJSalt ");
          break;
        }
        case PJSUGAR:
        if (record->event.pressed) {
          // return MACRO(D(LSFT),T(P),U(LSFT),D(LSFT),T(J),U(LSFT),D(LSFT),T(S),U(LSFT),T(U),T(G),T(A),T(R),T(SPC),END);
          SEND_STRING("PJSugar ");
          break;
        }
        case RETURNWHISPER:
        if (record->event.pressed) {
          return MACRO(T(SLSH),T(W),T(SPC),T(TAB),T(SPC),END);
        }
        case HOWAREYOU:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(H),U(LSFT),T(O),T(W),T(SPC),T(A),T(R),T(E),T(SPC),T(Y),T(O),T(U),T(SPC),T(T),T(O),T(D),T(A),T(Y),D(LSFT),T(SLSH),U(LSFT),T(SPC),END);
        }
        case DOINGFINE:
        if (record->event.pressed) {
          return MACRO(D(LSFT),T(I),U(LSFT),T(QUOT),T(M),T(SPC),T(D),T(O),T(I),T(N),T(G),T(SPC),T(F),T(I),T(N),T(E),T(COMM),T(SPC),T(T),T(H),T(A),T(N),T(K),T(S),T(SPC),T(F),T(O),T(R),T(SPC),T(A),T(S),T(K),T(I),T(N),T(G),T(DOT),END);
        }
        case TIMEOUT:
        if (record->event.pressed) {
          return MACRO(T(SLSH),T(T),T(I),T(M),T(E),T(O),T(U),T(T),T(SPC),END);
        }
        case PURGE:
        if (record->event.pressed) {
          return MACRO(T(1),T(ENT),END);
        }
        case STRIKE2:
        if (record->event.pressed) {
          return MACRO(T(3),T(0),T(0),T(ENT),END);
        }
        case BAN:
        if (record->event.pressed) {
          return MACRO(T(SLSH),T(B),T(A),T(N),T(SPC),END);
        }
        case UNBAN:
        if (record->event.pressed) {
          return MACRO(T(SLSH),T(U),T(N),T(B),T(A),T(N),T(SPC),END);
        }
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            // none
            break;
        case 2:
            ergodox_right_led_1_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            ergodox_right_led_2_on();
            break;
    }

};
