/* Copyright 2021 @Ciutadellla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


 #include QMK_KEYBOARD_H

 enum layer_names {
     _BASE,
     _LOWER,
     _RAISE,
     _MOVE,
     _ADJUST
 };

 //UNICODES
 #include "process_unicode.h"

 enum unicode_names {
     CKC_EUR,
     N_TILDE,
     COMB_ACUTE_ACCENT,
     GRINNING_FACE, // 😃
     BEAMING_FACE, // 😁
     GRINNING_FACE_WITH_SWEAT, // 😅
     ROLLING_LAUGHING, // 🤣
     FACE_TEARS_JOY, // 😂
     WINKING_FACE, // 😉
     SMILING_FACE_HALO, // 😇
     SMILING_FACE_HEARTS, // 🥰
     SMILING_FACE_HEART_EYES, // 😍
     FACE_BLOWING_KISS, // 😘
     FACE_SAVORING_FOOD, // 😋
     ZANY_FACE, // 🤪
     HUGGING_FACE, // 🤗
     SHUSHING_FACE, // 🤫
     THINKING_FACE, // 🤔
     FACE_RAISED_EYEBROW, // 🤨
     NEUTRAL_FACE, // 😐
     SMIRKING_FACE, // 😏
     FACE_ROLLING_EYES, // 🙄
     PENSIVE_FACE, // 😔
     FACE_VOMITING, // 🤮
     WOOZY_FACE, // 🥴
     PLEADING_FACE, // 🥺
     LOUDLY_CRYING_FACE, // 😭
     DISAPPOINTED_FACE, // 😞
     FACE_SYMBOLS_MOUTH, // 🤬
     SMILING_FACE_HORNS, // 😈
     SKULL, // 💀
     PILE_POO, // 💩
     GHOST, // 👻
     ALIEN_MONSTER, // 👾
     RED_HEART, // ❤
     BOMB, // 💣
     WAVING_HAND, // 👋
     OK_HAND, // 👌
     CLAPPING_HANDS, // 👏
     EYES, // 👀
     MAN_FACEPALMING, // 🤦
     TURTLE, // 🐢
     SNAKE, // 🐍
     SPOUTING_WHALE, // 🐳
     DRAGON, // 🐉
     TREX, // 🦖
     THUMBSDOWN, // 👍
     THUMBSUP, // 👎
 };

 //https://unicode-table.com/en/#00F1
 const uint32_t PROGMEM unicode_map[] = {
     [CKC_EUR] = 0x20AC, //€
     [N_TILDE] = 0x00F1,  // ñ
     [COMB_ACUTE_ACCENT] = 0x0301,  // ´
     [GRINNING_FACE] = 0x1F603,
     [BEAMING_FACE] = 0x1F601,
     [GRINNING_FACE_WITH_SWEAT] = 0x1F605,
     [ROLLING_LAUGHING] = 0x1F923,
     [FACE_TEARS_JOY] = 0x1F602,
     [WINKING_FACE] = 0x1F609,
     [SMILING_FACE_HALO] = 0x1F607,
     [SMILING_FACE_HEARTS] = 0x1F970,
     [SMILING_FACE_HEART_EYES] = 0x1F60D,
     [FACE_BLOWING_KISS] = 0x1F618,
     [FACE_SAVORING_FOOD] = 0x1F60B,
     [ZANY_FACE] = 0x1F92A,
     [HUGGING_FACE] = 0x1F917,
     [SHUSHING_FACE] = 0x1F92B,
     [THINKING_FACE] = 0x1F914,
     [FACE_RAISED_EYEBROW] = 0x1F928,
     [NEUTRAL_FACE] = 0x1F610,
     [SMIRKING_FACE] = 0x1F60F,
     [FACE_ROLLING_EYES] = 0x1F644,
     [PENSIVE_FACE] = 0x1F614,
     [FACE_VOMITING] = 0x1F92E,
     [WOOZY_FACE] = 0x1F974,
     [PLEADING_FACE] = 0x1F97A,
     [LOUDLY_CRYING_FACE] = 0x1F62D,
     [DISAPPOINTED_FACE] = 0x1F61E,
     [FACE_SYMBOLS_MOUTH] = 0x1F92C,
     [SMILING_FACE_HORNS] = 0x1F608,
     [SKULL] = 0x1F480,
     [PILE_POO] = 0x1F4A9,
     [GHOST] = 0x1F47B,
     [ALIEN_MONSTER] = 0x1F47E,
     [RED_HEART] = 0x2764,
     [BOMB] = 0x1F4A3,
     [WAVING_HAND] = 0x1F44B,
     [OK_HAND] = 0x1F44C,
     [CLAPPING_HANDS] = 0x1F44F,
     [EYES] = 0x1F440,
     [MAN_FACEPALMING] = 0x1F926,
     [TURTLE] = 0x1F422,
     [SNAKE] = 0x1F40D,
     [SPOUTING_WHALE] = 0x1F433,
     [DRAGON] = 0x1F409,
     [TREX] = 0x1F996,
     [THUMBSDOWN] = 0x1F44E,
     [THUMBSUP] = 0x1F44D,
 };


 void matrix_init_user(){
     set_unicode_input_mode(UC_MAC);
 }


 // Shortcut to make keymap more readable
 #define KC_OSX_EJECT 0x66
 #define LOCK_OSX LSFT(LCTL(KC_OSX_EJECT))
 #define SLEEP_OSX LALT(LGUI(KC_OSX_EJECT))
 #define KC_C_LF  RCTL(KC_LEFT)     // control + left
 #define KC_C_RT  RCTL(KC_RGHT)     // control + right

 // tap dance declarations
 enum {
     _TD_TAB_ESC = 0,
     _TD_BSPC_WDEL,
     _TD_SFT_CAPS,
     _TD_SPC_ENT,
     _TD_N_NTILDE,
     _TD_CTRL_LANG,
     _TD_SCLN_NTILDE
 };

 #define TD_TAB_ESC TD(_TD_TAB_ESC)
 #define TD_BSPC_WDEL TD(_TD_BSPC_WDEL)
 #define TD_SFT_CAPS TD(_TD_SFT_CAPS)
 #define TD_SPC_ENT TD(_TD_SPC_ENT)
 #define TD_N_NTILDE TD(_TD_N_NTILDE)
 #define TD_CTRL_LANG TD(_TD_CTRL_LANG)
 #define TD_SCLN_NTILDE TD(_TD_SCLN_NTILDE) //TP with costum keycodes has to be a funtion

 void td_scln_ntilde(qk_tap_dance_state_t *state, void *user_data) {
      if (state->count == 1) {
         register_code(KC_SCLN);
         unregister_code(KC_SCLN);
      } else {
         send_unicode_string("ñ");
      }
      reset_tap_dance(state);
 }

 // Tap Dance Definitions
 qk_tap_dance_action_t tap_dance_actions[] = {
     [_TD_TAB_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_ESC),
     [_TD_BSPC_WDEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, LALT(KC_BSPC)),
     [_TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
     [_TD_SPC_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_ENT),
     [_TD_CTRL_LANG] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, LCTL(LSFT(KC_SPACE))),
     [_TD_SCLN_NTILDE] = ACTION_TAP_DANCE_FN(td_scln_ntilde),
 };


 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


     /* Qwerty 0
    * ,-----------------------------------------+         +-----------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |         |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |CtlLNG|   A  |   S  |   D  |   F  |   G  |         |   H  |   J  |   K  |   L  |   ;  |   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |         |   N  |   M  |   ,  |   .  |   /  | Shift|
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             | GUI  | Lower|  Space  | Raise| Alt  |
    *                             +-------------/         \--------------+
    */
     [_BASE] =  LAYOUT_reviung41(TD_TAB_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD_BSPC_WDEL, TD_CTRL_LANG, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, TD_SCLN_NTILDE, KC_QUOT, TD_SFT_CAPS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT), KC_LGUI, MO(1), TD_SPC_ENT, MO(2), LT(4,KC_NO)),


     /* LOWER 1
    * ,-----------------------------------------+         +-----------------------------------------.
    * | Tab  |   !  |  @   |   #  |   $  |   %  |         |   ^  |   &  |   *  |  ()  |   )  |  Del |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Ctl  |   _  |  +   |  {}  |   }  |   |  |         | LEFT | DOWN |  UP  | RIGHT|  ´   |   "  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * | Shift| Esc  |  Gui |  Alt |  =   |  ""  |         | HOME | END  | PGUP | PDOWN|   /  | Shft |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             | GUI  | Lower|  Space  | Raise| Alt  |
    *                             +-------------/         \--------------+
    */
         [_LOWER] = LAYOUT_reviung41(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC, KC_LGUI, KC_LALT, KC_LCTL, KC_TRNS, KC_HOME, KC_END, KC_PGUP, KC_PGDN, KC_PSCR, MT(MOD_LSFT | MOD_RSFT,KC_SPC), KC_TRNS, KC_TRNS, KC_ENT, MO(3), KC_TRNS),

   /* Raise 2
    * ,-----------------------------------------+         +-----------------------------------------.
    * |      |   1  |   2  |   3  |   4  |   5  |         |   6  |   7  |   8  |   9  |   0  | DEL  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      | MINS |  EQL | LBRC | RBRC | BSLS |         |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    * |      |      |      |      |      | QUOT |         |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------+         +------+------+------+------+------+------|
    *                             | ____ | MO(3)|   BSPC  | ____  | ____ |
    *                             +-------------/         \--------------+
    */

            // [_RAISE] = LAYOUT_reviung41(
     //     KC_TRNS, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5,                 KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_DEL,
     //     KC_TRNS, KC_LPRN, KC_RPRN, KC_LT, KC_GT, KC_AMPR,           KC_PMNS, KC_PPLS, KC_HASH, KC_PERC, KC_COLN, KC_PEQL,
     //     KC_TRNS, KC_LCBR, KC_RCBR, KC_SLSH, KC_RO, KC_PIPE,         KC_PSLS, KC_PAST, KC_PCMM, KC_PDOT, KC_HASH, KC_PENT,
     //                                     KC_TRNS, MO(3), KC_BSPC, KC_TRNS, KC_TRNS
     // ),

     [_RAISE] = LAYOUT_reviung41(
         KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_P7, KC_P8, KC_P9, KC_P0, KC_PPLS, KC_PMNS,
         KC_COLN, KC_DQUO, KC_LCBR, KC_RCBR, KC_LT, KC_GT, KC_P4, KC_P5, KC_P6, KC_PERC, KC_PAST, KC_PSLS,
         KC_AMPR, KC_PIPE, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_P1, KC_P2, KC_P3, KC_PCMM, KC_PDOT, KC_PEQL,
         KC_TRNS, MO(3), KC_PENT, KC_TRNS, KC_TRNS
         ),


   /* _MOVE 3
    * ,---------------------------------------------------+     +------------------------------------------.
    * |       |       |       |         |       |         |     |      | WHD  |  WHU |      |      |  LOCK |
    * |-------+-------+-------+---------+-------+---------+     +------+------+------+------+------+-------|
    * |       |       |       |         |       |         |     | M_L  | M_D  | M_I  | M_R  |      | SLEEP |
    * |-------+-------+-------+---------+-------+---------+     +------+------+------+------+------+-------|
    * |       |       |       |         | SCRLFT| SCRRGHT |     | M_B1 |  M_B2|  M0  |  M2  |      | QK_BOOT |
    * |-------+-------+-------+---------+-------+---------+     +------+------+------+------+------+-------|
    *                                   | ____ | ____ |    BSPC   | ____  | ____ |
    *                                   +-------------/            \--------------+
    */
     [_MOVE] = LAYOUT_reviung41(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2, LOCK_OSX, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL0, SLEEP_OSX, KC_F13, KC_F14, KC_F15, KC_F16, KC_C_LF, KC_C_RT, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
     /* _ADJUST 4
    * ,----------------------------------------+         +---------------------------------------------------.
    * |  😃  |   😅 |  🤣  |  😉  |  😇  |  🥰  |          | RGBUP | HUEUP  | RGB_MOD |  BRIU  | PLAY  | VOLU |
    * |------+-----+------+------+------+------+         +-------+--------+----------+-------+-------+------|
    * |  😍  |  😘  |  🙄  |  😔  |  😭  |  💩  |          | RGBDWN| HUEDWN | RGB_TOG |  BRID  | STOP  | VOLD |
    * |------+-----+------+------+------+------+         +-------+--------+----------+--------+------+------|
    * |  👍  |  👎  |  👏  |  👀  |  🤦  |  👻  |          | RGB_TG|        |         |        |       | MUTE |
    * |------+------+------+------+------+------+        +-------+--------+----------+--------+------+------|
    *                             | GUI  | Lower|  BSPC   | Raise| Alt  |
    *                             +-------------/         \--------------+
    */

     [_ADJUST] = LAYOUT_reviung41(X(GRINNING_FACE), X(GRINNING_FACE_WITH_SWEAT), X(ROLLING_LAUGHING), X(WINKING_FACE), X(SMILING_FACE_HALO), X(SMILING_FACE_HEARTS), RGB_VAI, RGB_HUI, RGB_MOD, KC_BRIU, KC_MPLY, KC_VOLU, X(SMILING_FACE_HEART_EYES), X(FACE_BLOWING_KISS), X(FACE_ROLLING_EYES), X(PENSIVE_FACE), X(LOUDLY_CRYING_FACE), X(PILE_POO), RGB_VAD, RGB_HUD, RGB_RMOD, KC_BRID, KC_MSTP, KC_VOLD, X(THUMBSUP), X(THUMBSDOWN), X(CLAPPING_HANDS), X(EYES), X(MAN_FACEPALMING), X(GHOST), RGB_TOG, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

 };



 #ifdef RGBLIGHT_ENABLE
 // RGB LED Indicators
 const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_RED}    // Light 1 LED, starting with LED 0
 );

 // RGB LED Indicators
 const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_CYAN}    // Light 1 LED, starting with LED 0
 );

 const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_GREEN}  // Light 1 LED, starting with LED 1
 );

 // RGB LED Indicators
 const rgblight_segment_t PROGMEM my_rise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_MAGENTA}    // Light 1 LED, starting with LED 0
 );

 // RGB LED Indicators
 const rgblight_segment_t PROGMEM my_MOVE_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_YELLOW}    // Light 1 LED, starting with LED 0
 );


 // RGB LED Indicators
 const rgblight_segment_t PROGMEM my_ADJUST_layer[] = RGBLIGHT_LAYER_SEGMENTS(
     {0, 11, HSV_AZURE}    // Light 1 LED, starting with LED 0
 );

 // Now define the array of layers. Later layers take precedence
 const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
     my_base_layer,          // 0
     my_lower_layer,         // 1
     my_rise_layer,          // 2
     my_MOVE_layer,        // 3
     my_ADJUST_layer,   // 4
     my_capslock_layer       // 5
 );

 // Enable the LED layers
 void keyboard_post_init_user(void) {
     rgblight_layers = my_rgb_layers;
 }

 layer_state_t layer_state_set_user(layer_state_t state) {
     rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
     rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
     rgblight_set_layer_state(3, layer_state_cmp(state, _MOVE));
     rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));
     return state;
 }

 bool led_update_user(led_t led_state) {
     rgblight_set_layer_state(5, led_state.caps_lock);
     return true;
 }
 #endif

