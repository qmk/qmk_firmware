#include "ok60.h"

// defining layer names
#define _BL 0
#define _EXCEL 1
#define _DOTA 2
#define _FN 3
#define _MEDIA 4

// defining keys
#define _______ KC_TRNS

// bool has_layer_changed = false;
// static uint8_t current_layer = _BL;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty (KEYMAP_ANSI)
    ---------------------------------------------------------------------------
    |GESC| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  | 10 | -  | =  | BSPC   |
    ---------------------------------------------------------------------------
    | TAB  | Q  | W  | E  | R  | T  | Y  | U  | I  | O  | P  | [  | ]  | \    |
    ---------------------------------------------------------------------------
    |  CAPS  | A  | S  | D  | F  | G  | H  | J  | K  | L  | ;  | '  |   ENT   |
    ---------------------------------------------------------------------------
    |   LSFT    | Z  | X  | C  | V  | B  | N  | M  | ,  | .  | /  |   RSFT    |
    ---------------------------------------------------------------------------
    | LCTL| LGUI| LALT|               SPC             | RALT| RGUI| APP | RCTL|

    NOTE: ESC cannot be used as a layer toggle! Not sure why, and not sure if the docs will talk about this
    */

    [_BL] = KEYMAP_ANSI(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        LT(_FN, KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LT(_MEDIA, KC_ENT),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RGUI, MO(_SFX), KC_APP, KC_RCTL

    /* 1: FN2 EXCEL (KEYMAP_ANSI)
    This layer changes the right modifiers to arrow keys to work spreadsheets and stuff */
    [_EXCEL] = KEYMAP_ANSI(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,
        _______, KC_LGUI, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT),

    /* 2: FN3 DOTA (KEYMAP_ANSI)  */
    [_DOTA] = KEYMAP_ANSI(
        _______, KC_F1, _______, _______, _______, _______, _______, _______, _______, KC_F9, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,
        _______, KC_NO, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT),

    /* 3: FN1, activated by CAPS (KEYMAP_ANSI)
    ---------------------------------------------------------------------------
    |ESC | F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10| F11| F12|  DEL   |
    ---------------------------------------------------------------------------
    |      |    | UP |    |    |    |    |    | UP |PSCR|SLCK|PAUS|    |      |
    ---------------------------------------------------------------------------
    |        |LEFT|DOWN|RGHT|    |    |    |LEFT|DOWN|RGHT|PGUP|    |         |
    --------------------------------------------------------------------------- 
    |           |    |HOME| END|    |    |    |    |HOME| END|PGDN|           |
    ---------------------------------------------------------------------------
    |     |     |     |                               |     |     |     |     |
    */

    [_FN] = KEYMAP_ANSI(
        _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        _______, KC_PGUP, KC_UP, KC_PGDN, LALT(KC_F4), _______, _______, _______, KC_UP, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______, _______,
        _______, _______, KC_HOME, KC_END, _______, _______, _______, _______, KC_HOME, KC_END, KC_PGDN, _______,
        _______, _______, _______, _______, _______, _______, _______, _______),

    /* 4: FN4 MEDIA KEYS, activated by TAB (KEYMAP_ANSI)  */
    [_MEDIA] = KEYMAP_ANSI(
        _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,
        _______, RGB_TOG, RGB_MOD, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, TO(_BL), TO(_EXCEL), TO(_DOTA), _______),


    /* 5: NUMPAD KEYS, unassigned
    [_NUMPAD] = KEYMAP_ANSI(
        _______, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______, _______, _______,
        _______, _______, KC_UP, _______, _______, _______, KC_PMNS, KC_P4, KC_P5, KC_P6, , KC_PAST, _______, KC_PENT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_PPLS, KC_P1, KC_P2, KC_P3, KC_PSLS, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P0, KC_PCMM, KC_PDOT, KC_PEQL, _______,
        _______, _______, _______, KC_SPC, _______, _______, _______, _______), */
};

// uint8_t prev = _BL;
// bool change_bl = false;
// uint32_t check;
// uint8_t bl_hue = 0;
// uint8_t bl_sat = 0;
// uint8_t bl_hue_old = 255;
// uint8_t bl_sat_old = 255;
// uint8_t rgb_val = 255;


// void matrix_init_user() {
//     rgblight_sethsv(0, 0, 255);
//     rgblight_mode(1);
// }

// // RGB Modes
// // 1 = Static
// // 2-5 = Breathing
// // 6-8 = Rainbow
// // 9-14 = Swirl
// // 15-20 = Snake
// // 21-24 = Nightrider
// // 25 = Christmas
// // 26-30 = Static Gradient

// uint32_t layer_state_set_user(uint32_t state) {
//     uint8_t layer = biton32(state);
//     if (prev != layer) {
//         rgb_val = rgblight_get_val();
//         switch (layer) {
//             case _BL:
//                 if (change_bl) {
//                     rgblight_sethsv(bl_hue_old, bl_sat_old, rgb_val);
//                 } else {
//                     bl_hue = rgblight_get_hue();
//                     bl_sat = rgblight_get_sat();
//                     rgblight_sethsv(bl_hue, bl_sat, rgb_val);
//                 }
//                 rgblight_mode(1);
//                 break;

//             case _DOTA:
//                 rgblight_sethsv(16, 165, rgb_val);
//                 rgblight_mode(1);
//                 break;

//             case _EXCEL:
//                 rgblight_sethsv(150, 165, rgb_val);
//                 rgblight_mode(1);
//                 break;

//             case _MEDIA:
//                 // rgblight_mode(15);
//                 if (prev == _BL) {
//                     change_bl = false;
//                     rgblight_mode(15);
//                     bl_hue_old = rgblight_get_hue();
//                     bl_sat_old = rgblight_get_sat();
//                 } else {
//                     change_bl = true;
//                     rgblight_mode(15);
//                 }
//                 break;

//             default:
//                 break;
//         }
//     }
//     prev = layer;
//     return state;
// }

    // /* x: empty keymap  */
    // [_X] = KEYMAP_ANSI(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______), 


// uint8_t layer_state_set_user(uint8_t layer_state) {
//     switch (biton32(layer_state)) {
//         case _FN:
//             rgblight_setrgb (0, 0, 255);
//             break;
//         case _EXCEL:
//             rgblight_setrgb (0, 255, 0);
//             break;
//         case _DOTA:
//             rgblight_setrgb (255, 0, 0);
//             break;
//         case _MEDIA:
//             rgblight_setrgb (0, 255, 255);
//             break;
//         default: //  for any other layers, or the default layer
//             rgblight_setrgb (255, 255, 255);
//             break;
//     }
//     return layer_state;
// };

// rudimentary thing. there's something in docs about layer change
// void matrix_scan_user(void) {
//     static uint8_t current_layer = _BL;
//     uint8_t layer = biton32(layer_state);
//     if (current_layer != layer) {
//         if (layer == _EXCEL) {
//             rgblight_setrgb (0, 128, 0);
//         } else if (layer == _DOTA) {
//             rgblight_setrgb (128, 0, 0);
//         } else if (layer == _MEDIA) {
//             rgblight_setrgb (0, 56, 56);
//         } else if (layer == _BL) {
//             rgblight_setrgb (0, 0, 0);
//         }
//         current_layer = layer; 
//     }       
// };