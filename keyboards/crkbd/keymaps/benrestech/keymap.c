/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Ben Allen <@benrestech>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define KC_NP KC_NO // key is not present
#define KC_NA KC_NO // present but not available for use
#define KC_NU KC_NO // available but not used


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
    BASE,
    MEDR,
    NAVR,
    MOUR,
    NSSL,
    NSL,
    FUNL,
    GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
    TO(NSSL),  KC_Q,          KC_W,          KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,             KC_Y,            KC_QUOT,       TO(MOUR),
    TO(NSL),   LGUI_T(KC_A),  LALT_T(KC_R),  LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),     LALT_T(KC_I),    LGUI_T(KC_O),  TO(NAVR),
    TO(FUNL),  KC_Z,          ALGR_T(KC_X),  KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,          ALGR_T(KC_DOT),  KC_SLSH,       TO(MEDR),
                                             LT(MEDR, KC_ESC),  LT(NAVR, KC_SPC),  LT(MOUR, KC_TAB),  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL)
  ),
  [NAVR] = LAYOUT_split_3x6_3(
    TO(NSSL),  QK_BOOT,  KC_NA,    KC_NA,   KC_NA,   KC_NA,   KC_AGIN, KC_UNDO, KC_CUT,  KC_COPY, KC_PSTE,  TO(MOUR),
    TO(NSL),   KC_LGUI, KC_LALT,  KC_LCTL, KC_LSFT, KC_NA,   KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  TO(BASE),
    TO(FUNL),  KC_NA,   KC_ALGR,  KC_NA,   KC_NA,   KC_NA,   KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,   TO(MEDR),
                                  KC_NA,   KC_NA,   KC_NA,   KC_ENT,  KC_BSPC, KC_DEL
  ),
  [MOUR] = LAYOUT_split_3x6_3(
    TO(NSSL),  QK_BOOT,  KC_NA,    KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,    TO(BASE),
    TO(NSL),   KC_LGUI, KC_LALT,  KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,  TO(NAVR),
    TO(FUNL),  KC_NA,   KC_ALGR,  KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,  TO(MEDR),
                                  KC_NA,   KC_NA,   KC_NA,   KC_BTN1, KC_BTN3, KC_BTN2
  ),
  [MEDR] = LAYOUT_split_3x6_3(
    TO(NSSL),  QK_BOOT,  KC_NA,    KC_NA,   KC_NA,   KC_NA,   RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,   TO(MOUR),
    TO(NSL),   KC_LGUI, KC_LALT,  KC_LCTL, KC_LSFT, KC_NA,   KC_NU,   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  TO(NAVR),
    TO(FUNL),  KC_NA,   KC_ALGR,  KC_NA,   KC_NA,   KC_NA,   KC_NU,   KC_NU,   KC_NU,   KC_NU,   KC_NU,    TO(BASE),
                                  KC_NA,   KC_NA,   KC_NA,   KC_MSTP, KC_MPLY, KC_MUTE
  ),
  [FUNL] = LAYOUT_split_3x6_3(
    TO(NSSL),  KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, KC_NA,   KC_NA,   KC_NA,   KC_NA,    QK_BOOT,   TO(MOUR),
    TO(NSL),   KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK, KC_NA,   KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI,  TO(NAVR),
    TO(BASE),  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_NA,   KC_NA,   KC_NA,   KC_ALGR,  KC_NA,    TO(MEDR),
                                KC_APP,  KC_SPC,  KC_TAB,  KC_NA,   KC_NA,   KC_NA
  ),
  [NSL] = LAYOUT_split_3x6_3(
    TO(NSSL),  KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC, KC_NA,   KC_NA,   KC_NA,   KC_NA,    QK_BOOT,   TO(MOUR),
    TO(BASE),  KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL,  KC_NA,   KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI,  TO(NAVR),
    TO(FUNL),  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS, KC_NA,   KC_NA,   KC_NA,   KC_ALGR,  KC_NA,    TO(MEDR),
                                KC_DOT,  KC_0,    KC_MINS, TO(GAME),   KC_NA,   KC_NA
  ),
  [NSSL] = LAYOUT_split_3x6_3(
    TO(BASE),  KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, KC_NA,   KC_NA,   KC_NA,   KC_NA,    QK_BOOT,  TO(MOUR),
    TO(NSL),   KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS, KC_NA,   KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI, TO(NAVR),
    TO(FUNL),  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE, KC_NA,   KC_NA,   KC_NA,   KC_ALGR,  KC_NA,   TO(MEDR),
                                KC_GT,   KC_RPRN, KC_UNDS, KC_NA,   KC_NA,   KC_NA
  ),
  [GAME] = LAYOUT_split_3x6_3(
    KC_NA,  KC_Q,  KC_W,  KC_F,    KC_P,    KC_B,    KC_J,              KC_L,              KC_U,             KC_Y,            KC_QUOT,       TO(BASE),
    KC_NA,  KC_A,  KC_R,  KC_S,    KC_T,    KC_G,    KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),     LALT_T(KC_I),    LGUI_T(KC_O),  TO(BASE),
    KC_NA,  KC_Z,  KC_X,  KC_C,    KC_D,    KC_V,    KC_K,              KC_H,              KC_COMM,          ALGR_T(KC_DOT),  KC_SLSH,       TO(BASE),
                          KC_ESC,  KC_SPC,  KC_TAB,  LT(NSSL, KC_ENT),  LT(NSL, KC_BSPC),  LT(FUNL, KC_DEL)
  )
};

// Default (BASE) lighting layer is HSV_GREEN.
// MEDR lighting layer.
const rgblight_segment_t PROGMEM medr_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_PINK}       // Light all LEDs
);
// NAVR lighting layer.
const rgblight_segment_t PROGMEM navr_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_CYAN}       // Light all LEDs
);
// MOUR lighting layer.
const rgblight_segment_t PROGMEM mour_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_YELLOW}       // Light all LEDs
);
// NSSL lighting layer.
const rgblight_segment_t PROGMEM nssl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_SPRINGGREEN}       // Light all LEDs
);
// NSL lighting layer.
const rgblight_segment_t PROGMEM nsl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_BLUE}       // Light all LEDs
);
// FUNL lighting layer.
const rgblight_segment_t PROGMEM funl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_RED}       // Light all LEDs
);
// GAME lighting layer.
const rgblight_segment_t PROGMEM game_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 53, HSV_PURPLE}       // Light all LEDs
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    medr_layer,
    navr_layer,
    mour_layer,
    nssl_layer,
    nsl_layer, 
    funl_layer,
    game_layer 
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_sethsv(HSV_GREEN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, MEDR));
    rgblight_set_layer_state(1, layer_state_cmp(state, NAVR));
    rgblight_set_layer_state(2, layer_state_cmp(state, MOUR));
    rgblight_set_layer_state(3, layer_state_cmp(state, NSSL));
    rgblight_set_layer_state(4, layer_state_cmp(state, NSL));
    rgblight_set_layer_state(5, layer_state_cmp(state, FUNL));
    rgblight_set_layer_state(6, layer_state_cmp(state, GAME));
    return state;
}


