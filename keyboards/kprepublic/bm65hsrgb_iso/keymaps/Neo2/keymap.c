/* Copyright 2024 Tetraden
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY______ without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


/* Define layer numbers.
 * If you want to change the default to NEO1, exchange 0 and 1.
 */
#define QWERTZ  0
#define NEO_1   1
#define NEO_3   2
#define NEO_4   3
#define NEO_5   4
#define NEO_6   5
#define _FN   	6


// create custom keycodes for NEO shift functions
#define NO_1 KC_1    // 1
#define NO_2 KC_2    // 2
#define NO_3 KC_3    // 3
#define NO_4 KC_4    // 4
#define NO_5 KC_5    // 5
#define NO_6 KC_6    // 6
#define NO_7 KC_7    // 7
#define NO_8 KC_8    // 8
#define NO_9 KC_9    // 9
#define NO_0 KC_0    // 0
#define NO_MINS KC_SLSH // -

/* translate a few german keys for readability
 leaving out modifier symbols to not mess with custom keycodes and shift functions */
#define DE_CIRC KC_GRV  // ^ (dead)
#define DE_SS   KC_MINS // ß
#define DE_ACUT KC_EQL  // ´ (dead)
#define DE_UDIA KC_LBRC // Ü
#define DE_PLUS KC_RBRC // +
#define DE_ODIA KC_SCLN // Ö
#define DE_ADIA KC_QUOT // Ä
#define DE_HASH KC_NUHS // #
#define DE_LABK KC_NUBS // <
#define DE_MINS KC_SLSH // -

enum custom_keycodes {
        PLACEHOLDER = SAFE_RANGE,     // can always be here
        MC_CT_N,
        // custom neo related keycodes
        NO_UONE
    };


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Detect the activation of both Shifts
    if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) {
        // Toggle Caps_lock value
        tap_code(KC_CAPS);
        // Keep processing like normal, don't do anything to prevent that
        return true;
    }


    switch (keycode) {
    case MC_CT_N:
        if (record->event.pressed) {
            SEND_STRING(SS_RCTL("n"));
        } else {
        }
        break;

    // TODO: custom symbols
    case NO_UONE:
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_KP_0)SS_TAP(X_KP_1)SS_TAP(X_KP_8)SS_TAP(X_KP_5)));
        } else {
        }
        break;
    }
    return true;
};


// Use ______ to indicate a key that is transparent / falling through to a lower level
#define ______ KC_TRNS


/* TODO: NEO_2 characters


NEO_3 Characters
¹    ²    ³    ›    ‹    ¢    ¥    ‚    ‘    ’    x    °(dead)
185  AG2  AG3
… _ [ ] ^ ! < > = & ſ /(dead)
\ / { } * ? ( ) - : @
# $ | ~ ` + % " ' ;

TODO: ¹ ² ³ › ‹ ¢ ¥ ‚ ‘ ’ x °(dead)
TODO: … ſ /(dead)
TODO: `(non-dead)
*/

// NEO_4 Characters
#define NO_INV_EXLM                RSA(KC_1)                   // ¡
#define NO_INV_QUES                RSA(KC_MINS)                // ¿



// NEO_5 Characters
// ₁    ₂    ₃    ♀    ♂    ⚥    ϰ    ⟨    ⟩    ₀    ‑    ῾(dead)

// Remap the number row for shift
const key_override_t one_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, NO_1, S(KC_GRV), 1<<NEO_1, MOD_MASK_CA); // °
const key_override_t two_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, NO_2, S(KC_3), 1<<NEO_1, MOD_MASK_CA); // §
//TODO const key_override_t thee_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_3, DE_SECT, 1<<NEO_1, MOD_MASK_CA); // ℓ
//TODO const key_override_t four_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_4, NO_RAQUO, 1<<NEO_1, MOD_MASK_CA); // »
//TODO const key_override_t five_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_5, NO_LAQUO, 1<<NEO_1, MOD_MASK_CA); // «
const key_override_t six_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, NO_6, S(KC_4), 1<<NEO_1, MOD_MASK_CA); // $
const key_override_t seven_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, NO_7, ALGR(KC_E), 1<<NEO_1, MOD_MASK_CA); // €
//TODO const key_override_t eight_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_8, NO_LOWQUOT, 1<<NEO_1, MOD_MASK_CA); // „
//TODO const key_override_t nine_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_9, NO_LQUOT, 1<<NEO_1, MOD_MASK_CA); // “
//TODO const key_override_t zero_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_0, NO_RQUOT, 1<<NEO_1, MOD_MASK_CA); // ”
// TODO: NO_EM_DASH is underscore
//const key_override_t minus_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, NO_MINS, NO_EM_DASH, 1<<NEO_1, MOD_MASK_CA);

const key_override_t **key_overrides = (const key_override_t *[]){
    &one_override,
    &two_override,
//    &three_override,
//    &four_override,
//    &five_override,
    &six_override,
    &seven_override,
//    &eight_override,
//    &nine_override,
//    &zero_override,
//    &minus_override,
//    &acut_override,
//    &gravis_override,
    NULL
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [QWERTZ] = LAYOUT_65_iso_blocker(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,     KC_BSPC,    KC_DEL,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                KC_PPLS,
        KC_CAPS,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_NUHS,    KC_ENT,     KC_PMNS,
        KC_LSFT,    KC_NUBS,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,    KC_UP,      ______,
        KC_LCTL,    KC_LGUI,    KC_LALT,                                        KC_SPC,                                         KC_RALT,    MO(_FN),    KC_LEFT,    KC_DOWN,    KC_RGHT
    ),

    [NEO_1] = LAYOUT_65_iso_blocker(
        KC_ESC,     NO_1,       NO_2,       NO_3,       NO_4,       NO_5,       NO_6,       NO_7,       NO_8,       NO_9,       NO_0,       NO_MINS,    S(KC_EQL),  KC_BSPC,    KC_DEL,
        KC_TAB,     KC_X,       KC_V,       KC_L,       KC_C,       KC_W,       KC_K,       KC_H,       KC_G,       KC_F,       KC_Q,       KC_MINS,    KC_EQL,                 KC_PPLS,
        MO(NEO_3),  KC_U,       KC_I,       KC_A,       KC_E,       KC_O,       KC_S,       KC_N,       KC_R,       KC_T,       KC_D,       KC_Z,       MO(NEO_3),  KC_ENT,     KC_PMNS,
        KC_LSFT,    MO(NEO_4),  KC_LBRC,    KC_SCLN,    KC_QUOT,    KC_P,       KC_Y,       KC_B,       KC_M,       KC_COMM,    KC_DOT,     KC_J,       KC_RSFT,    KC_UP,      ______,
        KC_LCTL,    KC_LGUI,    KC_LALT,                                        KC_SPC,                                         MO(NEO_4),  MO(_FN),    KC_LEFT,    KC_DOWN,    KC_RGHT
    ),


    // Symbol layer
    [NEO_3] = LAYOUT_65_iso_blocker(
        //Esc       ¹           ²           ³           ›           ‹           ¢           ¥           ‚           ‘           ’           empty       ° (dead)
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Tab       …           _           [           ]           ^           !           <           >           =           &           ſ           / (dead)
        ______,     ______,     S(KC_SLSH), ALGR(KC_8), ALGR(KC_9), KC_GRV,     S(KC_1),    KC_NUBS,    S(KC_NUBS), S(KC_0),    S(KC_6),    ______,     ______,                 ______,
        //Caps      \           /           {           }           *           ?           (           )           -           :           @           Mod3
        ______,     ALGR(KC_MINS),S(KC_7),  ALGR(KC_7), ALGR(KC_0), S(KC_RBRC), S(KC_MINS), S(KC_8),    S(KC_9),    KC_SLSH,    S(KC_DOT),  ALGR(KC_Q), ______,     ______,     ______,
        //Shift     Mod4        #           $           |           ~           `           +           %           "           '           ;           Mod5
        ______,     ______,     KC_NUHS,    S(KC_4),  ALGR(KC_NUBS),ALGR(KC_RBRC),S(KC_EQL),KC_RBRC,    S(KC_5),    S(KC_2),    S(KC_NUHS), S(KC_COMM), MO(NEO_5),  ______,     ______,
        //Ctrl      GUI         Alt                                             Space                                           Mod4        Fn          Left        Down        Right
        ______,     ______,     ______,                                         KC_SPC,                                         ______,     ______,     ______,     ______,     ______
    ),

    // Cursor & Numpad
    [NEO_4] = LAYOUT_65_iso_blocker(
        //˙(dead)   ª           º           №           empty       ·           £           ¤           Tab         /           *           -           "(dead)
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     KC_TAB,     KC_SLSH,    S(KC_RBRC), KC_MINS,    ______,     ______,     ______,
        //Tab       pgup        bspc        up          del         pgdn        ¡           7           8           9           +           −           ˝(dead)
        ______,     KC_PGUP,    KC_BSPC,    KC_UP,      KC_DELETE,  KC_PGDN,    NO_INV_EXLM,KC_7,       KC_8,       KC_9,       KC_RBRC,    ______,     ______,                 ______,
        // row complete
        ______,     KC_HOME,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,     NO_INV_QUES,KC_4,       KC_5,       KC_6,       KC_COMM,    KC_DOT,     ______,     ______,     ______,
        //shift     Mod4        Esc         Tab         insert      enter       Ctrl+Z      :           1           2           3           ;
        ______,     ______,     KC_ESCAPE,  KC_TAB,     KC_INSERT,  KC_PENT,    ______,     S(KC_DOT),  KC_1,       KC_2,       KC_3,       S(KC_COMM), ______,     ______,     ______,
        //Ctrl      GUI         Alt                                             Space                                           Mod4        Fn          Left        Down        Right
        KC_RCTL,    ______,     KC_RALT,                                        KC_0,                                           ______,     ______,     ______,     ______,     ______
    ),

    // TODO: Greek
    [NEO_5] = LAYOUT_65_iso_blocker(
        //(dead)    ₁           ₂           ₃           ♀           ♂           ⚥           ϰ           ⟨           ⟩            ₀
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Tab        ξ          empty       λ           χ           ω           κ           ψ           γ           φ           ϕ           ς           ᾿(dead)
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,                 ______,
        //Caps      empty       ι           α           ε           ο           σ           ν           ρ           τ           δ           υ           Mod3
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Shift     Mod4        empty       ϵ           η           π           ζ           β           μ           ϱ           ϑ           θ           Shift
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Ctrl      GUI         Alt                                             Space                                           Mod4        Fn          Left        Down        Right
        ______,     ______,     ______,                                         ______,                                         ______,     ______,     ______,     ______,     ______
    ),

    // TODO: Math
    [NEO_6] = LAYOUT_65_iso_blocker(
        //Esc                                                                                                                                                       Backspace
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Tab
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,                 ______,
        //Caps                                                                                                                                          Mod3        Enter
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Shift     Mod4                                                                                                                                Shift       Up
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,
        //Ctrl      GUI         Alt                                             Space                                           Mod4        Fn          Left        Down        Right
        ______,     ______,     ______,                                         ______,                                         ______,     ______,     ______,     ______,     ______
    ),

    [_FN] = LAYOUT_65_iso_blocker(
        KC_GRV,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     ______,     ______,
        ______,     RGB_TOG,    RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,    ______,     ______,     ______,     ______,     ______,     ______,                 TO(NEO_1),
        ______,     ______,     RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,    MC_CT_N,    ______,     ______,     ______,     ______,     ______,     ______,     TO(QWERTZ),
        ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     ______,     KC_PGUP,    ______,
        ______,     QK_BOOT,    ______,                                         ______,                                         ______,     ______,     KC_HOME,    KC_PGDN,    KC_END
    ),

};


