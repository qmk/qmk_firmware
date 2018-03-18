#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keymap.h"
#include "keymap_german.h"

#define UC_ASYMPTOTICALLY_EQUAL_TO 0
#define UC_DIVISION_SIGN 1
#define UC_DOWNWARDS_ARROW 2
#define UC_ELEMENT_OF 3
#define UC_EMPTY_SET 4
#define UC_FOR_ALL 5
#define UC_GREEK_CAPITAL_LETTER_ALPHA 6
#define UC_GREEK_CAPITAL_LETTER_BETA 7
#define UC_GREEK_CAPITAL_LETTER_CHI 8
#define UC_GREEK_CAPITAL_LETTER_DELTA 9
#define UC_GREEK_CAPITAL_LETTER_EPSILON 10
#define UC_GREEK_CAPITAL_LETTER_ETA 11
#define UC_GREEK_CAPITAL_LETTER_GAMMA 12
#define UC_GREEK_CAPITAL_LETTER_IOTA 13
#define UC_GREEK_CAPITAL_LETTER_KAPPA 14
#define UC_GREEK_CAPITAL_LETTER_LAMDA 15
#define UC_GREEK_CAPITAL_LETTER_MU 16
#define UC_GREEK_CAPITAL_LETTER_NU 17
#define UC_GREEK_CAPITAL_LETTER_OMEGA 18
#define UC_GREEK_CAPITAL_LETTER_OMICRON 19
#define UC_GREEK_CAPITAL_LETTER_PHI 20
#define UC_GREEK_CAPITAL_LETTER_PI 21
#define UC_GREEK_CAPITAL_LETTER_PSI 22
#define UC_GREEK_CAPITAL_LETTER_RHO 23
#define UC_GREEK_CAPITAL_LETTER_SIGMA 24
#define UC_GREEK_CAPITAL_LETTER_TAU 25
#define UC_GREEK_CAPITAL_LETTER_THETA 26
#define UC_GREEK_CAPITAL_LETTER_UPSILON 27
#define UC_GREEK_CAPITAL_LETTER_XI 28
#define UC_GREEK_CAPITAL_LETTER_ZETA 29
#define UC_GREEK_SMALL_LETTER_ALPHA 30
#define UC_GREEK_SMALL_LETTER_BETA 31
#define UC_GREEK_SMALL_LETTER_CHI 32
#define UC_GREEK_SMALL_LETTER_DELTA 33
#define UC_GREEK_SMALL_LETTER_EPSILON 34
#define UC_GREEK_SMALL_LETTER_ETA 35
#define UC_GREEK_SMALL_LETTER_FINAL_SIGMA 36
#define UC_GREEK_SMALL_LETTER_GAMMA 37
#define UC_GREEK_SMALL_LETTER_IOTA 38
#define UC_GREEK_SMALL_LETTER_KAPPA 39
#define UC_GREEK_SMALL_LETTER_LAMDA 40
#define UC_GREEK_SMALL_LETTER_MU 41
#define UC_GREEK_SMALL_LETTER_NU 42
#define UC_GREEK_SMALL_LETTER_OMEGA 43
#define UC_GREEK_SMALL_LETTER_OMICRON 44
#define UC_GREEK_SMALL_LETTER_PHI 45
#define UC_GREEK_SMALL_LETTER_PI 46
#define UC_GREEK_SMALL_LETTER_PSI 47
#define UC_GREEK_SMALL_LETTER_RHO 48
#define UC_GREEK_SMALL_LETTER_SIGMA 49
#define UC_GREEK_SMALL_LETTER_TAU 50
#define UC_GREEK_SMALL_LETTER_THETA 51
#define UC_GREEK_SMALL_LETTER_UPSILON 52
#define UC_GREEK_SMALL_LETTER_XI 53
#define UC_GREEK_SMALL_LETTER_ZETA 54
#define UC_INFINITY 55
#define UC_LEFTWARDS_ARROW 56
#define UC_MULTIPLICATION_SIGN 57
#define UC_NOT_AN_ELEMENT_OF 58
#define UC_NOT_EQUAL_TO 59
#define UC_PLUS_MINUS_SIGN 60
#define UC_RIGHTWARDS_ARROW 61
#define UC_SUBSCRIPT_EIGHT 62
#define UC_SUBSCRIPT_FIVE 63
#define UC_SUBSCRIPT_FOUR 64
#define UC_SUBSCRIPT_NINE 65
#define UC_SUBSCRIPT_ONE 66
#define UC_SUBSCRIPT_SEVEN 67
#define UC_SUBSCRIPT_SIX 68
#define UC_SUBSCRIPT_THREE 69
#define UC_SUBSCRIPT_TWO 70
#define UC_SUBSCRIPT_ZERO 71
#define UC_SUPERSCRIPT_EIGHT 72
#define UC_SUPERSCRIPT_FIVE 73
#define UC_SUPERSCRIPT_FOUR 74
#define UC_SUPERSCRIPT_LATIN_SMALL_LETTER_N 75
#define UC_SUPERSCRIPT_NINE 76
#define UC_SUPERSCRIPT_ONE 77
#define UC_SUPERSCRIPT_SEVEN 78
#define UC_SUPERSCRIPT_SIX 79
#define UC_SUPERSCRIPT_THREE 80
#define UC_SUPERSCRIPT_TWO 81
#define UC_SUPERSCRIPT_ZERO 82
#define UC_THERE_DOES_NOT_EXIST 83
#define UC_THERE_EXISTS 84
#define UC_UPWARDS_ARROW 85
#define UC_VULGAR_FRACTION_ONE_EIGHTH 86
#define UC_VULGAR_FRACTION_ONE_FIFTH 87
#define UC_VULGAR_FRACTION_ONE_HALF 88
#define UC_VULGAR_FRACTION_ONE_QUARTER 89
#define UC_VULGAR_FRACTION_ONE_SIXTH 90
#define UC_VULGAR_FRACTION_ONE_THIRD 91
#define UC_VULGAR_FRACTION_THREE_QUARTERS 92
#define UC_VULGAR_FRACTION_TWO_THIRDS 93
#define UM 94

#define L0   0      // layer_0
#define L1   1      // layer_1
#define L2   2      // layer_2
#define L3   3      // layer_3
#define L4   4      // layer_4
#define L5   5      // layer_5
#define L6   6      // layer_6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * .------------------------------------.------------------------------------.
 * |MO(5)| 1  | 2  | 3  | 4  | 5  |ACUT | GRV | 6  | 7  | 8  | 9  | 0  |CIRC |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |MO(4)| X  | P  | F  | W  | G  |HOME |TG(2)| H  | J  | K  | L  | Q  |  Z  |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |MO(1)| U  | I  | A  | E  | O  |-----!-----! S  | N  | R  | T  | D  | SS  |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |MO(3)| UE | OE | AE | C  | V  |END  | TAB | B  | M  |COMM| DOT| UP |  Y  |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |LGUI|LALT|LCTL|                     !RCTL|RALT|LEFT|DOWN|RGHT|
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |INS  |TG(2)| !M(UM)|DELT |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     | APP | ! PGUP|     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |BSPC |LSFT | ESC | ! PGDN|ENTER|SPACE|
 *                   '-----------------' '-----------------'
 */
[L0] = LAYOUT_ergodox(
 MO(5),   DE_1,     DE_2,     DE_3,    DE_4,    DE_5,    DE_ACUT,
 MO(4),   DE_X,     DE_P,     DE_F,    DE_W,    DE_G,    KC_HOME,
 MO(1),   DE_U,     DE_I,     DE_A,    DE_E,    DE_O,
 MO(3),   DE_UE,    DE_OE,    DE_AE,   DE_C,    DE_V,    KC_END,
 KC_TRNS, KC_TRNS,  KC_LGUI,  KC_LALT, KC_LCTL,
 /*-*/    /*-*/     /*-*/     /*-*/    /*-*/    KC_INS,  TG(2),
 /*-*/    /*-*/     /*-*/     /*-*/    /*-*/    /*-*/    KC_APP,
 /*-*/    /*-*/     /*-*/     /*-*/    KC_BSPC, KC_LSFT, KC_ESC,
 DE_GRV,  DE_6,     DE_7,     DE_8,    DE_9,    DE_0,    DE_CIRC,
 TG(2),   DE_H,     DE_J,     DE_K,    DE_L,    DE_Q,    DE_Z,
 /*-*/    DE_S,     DE_N,     DE_R,    DE_T,    DE_D,    DE_SS,
 KC_TAB,  DE_B,     DE_M,     DE_COMM, DE_DOT,  KC_UP,   DE_Y,
 /*-*/    /*-*/     KC_RCTL,  KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT,
 M(UM),   KC_DELT,
 KC_PGUP,
 KC_PGDN, KC_ENTER, KC_SPACE
),
/*
 * .------------------------------------.------------------------------------.
 * |     |EXLM|DQOT|PARA|    |    |     |     |    |    |    |    |RING|     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |ASTR|PIPE|SLSH|LCBR|RCBR|     |     |HASH|LESS|MORE|    |DQOT|     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |UNDS|MINS|AMPR|LBRC|RBRC|-----!-----!DLR |LPRN|RPRN|TILD|QUOT| QST |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |PLUS|EQL |    |    |     |     |BSLS|PERC|SCLN|COLN| ↑  |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    | ←  | ↓  | →  |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L1] = LAYOUT_ergodox(
 KC_TRNS, DE_EXLM, DE_DQOT, DE_PARA, KC_TRNS,               KC_TRNS,               KC_TRNS,
 KC_TRNS, DE_ASTR, DE_PIPE, DE_SLSH, DE_LCBR,               DE_RCBR,               KC_TRNS,
 KC_TRNS, DE_UNDS, DE_MINS, DE_AMPR, DE_LBRC,               DE_RBRC,
 KC_TRNS, KC_TRNS, DE_PLUS, DE_EQL,  KC_TRNS,               KC_TRNS,               KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/                  KC_TRNS,               KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/                  /*-*/                  KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,               KC_TRNS,               KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               DE_RING,               KC_TRNS,
 KC_TRNS, DE_HASH, DE_LESS, DE_MORE, KC_TRNS,               DE_DQOT,               KC_TRNS,
 /*-*/    DE_DLR,  DE_LPRN, DE_RPRN, DE_TILD,               DE_QUOT,               DE_QST,
 KC_TRNS, DE_BSLS, DE_PERC, DE_SCLN, DE_COLN,               M(UC_UPWARDS_ARROW),   KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, M(UC_LEFTWARDS_ARROW), M(UC_DOWNWARDS_ARROW), M(UC_RIGHTWARDS_ARROW),
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     | F1 | F2 | F3 | F4 | F5 | F11 | F12 | F6 | F7 | F8 | F9 |F10 |PEQL |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    | P7 | P8 | P9 |PAST|PSLS |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |-----!-----!    | P4 | P5 | P6 |PMNS|PMNS |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |     | NLCK|    | P1 | P2 | P3 |PPLS|PPLS |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     ! P0 |PCMM|PDOT|PENT|PENT|
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L2] = LAYOUT_ergodox(
 KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PEQL,
 KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_PSLS,
 /*-*/    KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_PMNS,
 KC_NLCK, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, KC_PPLS,
 /*-*/    /*-*/    KC_P0,   KC_PCMM, KC_PDOT, KC_PENT, KC_PENT,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     | ¹  | ²  | ³  | ⁴  | ⁵  |  ∀  |     | ⁶  | ⁷  | ⁸  | ⁹  |  ⁰ |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     | ×  | ½  | ÷  | ¼  |  ⅕ |     |     | ⅙  |    | ⅛  |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    | ±  | AT |EURO| ∅  |-----!-----! ∞  | ⁿ  | ∃  | ∈  |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     | ⅓  | ≠  | ⅔  | ¾  | ≃  |     |     |EXLM|    | ∄  | ∉  |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L3] = LAYOUT_ergodox(
 KC_TRNS, M(UC_SUPERSCRIPT_ONE),           M(UC_SUPERSCRIPT_TWO),                  M(UC_SUPERSCRIPT_THREE),          M(UC_SUPERSCRIPT_FOUR),               M(UC_SUPERSCRIPT_FIVE),          M(UC_FOR_ALL),
 KC_TRNS, M(UC_MULTIPLICATION_SIGN),       M(UC_VULGAR_FRACTION_ONE_HALF),         M(UC_DIVISION_SIGN),              M(UC_VULGAR_FRACTION_ONE_QUARTER),    M(UC_VULGAR_FRACTION_ONE_FIFTH), KC_TRNS,
 KC_TRNS, KC_TRNS,                         M(UC_PLUS_MINUS_SIGN),                  DE_AT,                            DE_EURO,                              M(UC_EMPTY_SET),
 KC_TRNS, M(UC_VULGAR_FRACTION_ONE_THIRD), M(UC_NOT_EQUAL_TO),                     M(UC_VULGAR_FRACTION_TWO_THIRDS), M(UC_VULGAR_FRACTION_THREE_QUARTERS), M(UC_ASYMPTOTICALLY_EQUAL_TO),   KC_TRNS,
 KC_TRNS, KC_TRNS,                         KC_TRNS,                                KC_TRNS,                          KC_TRNS,
 /*-*/    /*-*/                            /*-*/                                   /*-*/                             /*-*/                                 KC_TRNS,                         KC_TRNS,
 /*-*/    /*-*/                            /*-*/                                   /*-*/                             /*-*/                                 /*-*/                            KC_TRNS,
 /*-*/    /*-*/                            /*-*/                                   /*-*/                             KC_TRNS,                              KC_TRNS,                         KC_TRNS,
 KC_TRNS, M(UC_SUPERSCRIPT_SIX),           M(UC_SUPERSCRIPT_SEVEN),                M(UC_SUPERSCRIPT_EIGHT),          M(UC_SUPERSCRIPT_NINE),               M(UC_SUPERSCRIPT_ZERO),          KC_TRNS,
 KC_TRNS, M(UC_VULGAR_FRACTION_ONE_SIXTH), KC_TRNS,                                M(UC_VULGAR_FRACTION_ONE_EIGHTH), KC_TRNS,                              KC_TRNS,                         KC_TRNS,
 /*-*/    M(UC_INFINITY),                  M(UC_SUPERSCRIPT_LATIN_SMALL_LETTER_N), M(UC_THERE_EXISTS),               M(UC_ELEMENT_OF),                     KC_TRNS,                         KC_TRNS,
 KC_TRNS, DE_EXLM,                         KC_TRNS,                                M(UC_THERE_DOES_NOT_EXIST),       M(UC_NOT_AN_ELEMENT_OF),              KC_TRNS,                         KC_TRNS,
 /*-*/    /*-*/                            KC_TRNS,                                KC_TRNS,                          KC_TRNS,                              KC_TRNS,                         KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS,                         KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     | ₁  | ₂  | ₃  | ₄  | ₅  |     |     | ₆  | ₇  | ₈  | ₉  | ₀  |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     | χ  | π  | φ  | ω  | γ  |     |     | η  | ξ  | κ  | λ  |    |  ζ  |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     | υ  | ι  | α  | ε  | ο  |-----!-----! σ  | ν  | ρ  | τ  | δ  |  ς  |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    | θ  |    |    |    |     |     | β  | μ  |    |    |    |  ψ  |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L4] = LAYOUT_ergodox(
 KC_TRNS, M(UC_SUBSCRIPT_ONE),              M(UC_SUBSCRIPT_TWO),            M(UC_SUBSCRIPT_THREE),          M(UC_SUBSCRIPT_FOUR),             M(UC_SUBSCRIPT_FIVE),             KC_TRNS,
 KC_TRNS, M(UC_GREEK_SMALL_LETTER_CHI),     M(UC_GREEK_SMALL_LETTER_PI),    M(UC_GREEK_SMALL_LETTER_PHI),   M(UC_GREEK_SMALL_LETTER_OMEGA),   M(UC_GREEK_SMALL_LETTER_GAMMA),   KC_TRNS,
 KC_TRNS, M(UC_GREEK_SMALL_LETTER_UPSILON), M(UC_GREEK_SMALL_LETTER_IOTA),  M(UC_GREEK_SMALL_LETTER_ALPHA), M(UC_GREEK_SMALL_LETTER_EPSILON), M(UC_GREEK_SMALL_LETTER_OMICRON),
 KC_TRNS, KC_TRNS,                          M(UC_GREEK_SMALL_LETTER_THETA), KC_TRNS,                        KC_TRNS,                          KC_TRNS,                          KC_TRNS,
 KC_TRNS, KC_TRNS,                          KC_TRNS,                        KC_TRNS,                        KC_TRNS,
 /*-*/    /*-*/                             /*-*/                           /*-*/                           /*-*/                             KC_TRNS,                          KC_TRNS,
 /*-*/    /*-*/                             /*-*/                           /*-*/                           /*-*/                             /*-*/                             KC_TRNS,
 /*-*/    /*-*/                             /*-*/                           /*-*/                           KC_TRNS,                          KC_TRNS,                          KC_TRNS,
 KC_TRNS, M(UC_SUBSCRIPT_SIX),              M(UC_SUBSCRIPT_SEVEN),          M(UC_SUBSCRIPT_EIGHT),          M(UC_SUBSCRIPT_NINE),             M(UC_SUBSCRIPT_ZERO),             KC_TRNS,
 KC_TRNS, M(UC_GREEK_SMALL_LETTER_ETA),     M(UC_GREEK_SMALL_LETTER_XI),    M(UC_GREEK_SMALL_LETTER_KAPPA), M(UC_GREEK_SMALL_LETTER_LAMDA),   KC_TRNS,                          M(UC_GREEK_SMALL_LETTER_ZETA),
 /*-*/    M(UC_GREEK_SMALL_LETTER_SIGMA),   M(UC_GREEK_SMALL_LETTER_NU),    M(UC_GREEK_SMALL_LETTER_RHO),   M(UC_GREEK_SMALL_LETTER_TAU),     M(UC_GREEK_SMALL_LETTER_DELTA),   M(UC_GREEK_SMALL_LETTER_FINAL_SIGMA),
 KC_TRNS, M(UC_GREEK_SMALL_LETTER_BETA),    M(UC_GREEK_SMALL_LETTER_MU),    KC_TRNS,                        KC_TRNS,                          KC_TRNS,                          M(UC_GREEK_SMALL_LETTER_PSI),
 /*-*/    /*-*/                             KC_TRNS,                        KC_TRNS,                        KC_TRNS,                          KC_TRNS,                          KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS,                          KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     | Χ  | Π  | Φ  | Ω  | Γ  |     |     | Η  | Ξ  | Κ  | Λ  |    |  Ζ  |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     | Υ  | Ι  | Α  | Ε  | Ο  |-----!-----! Σ  | Ν  | Ρ  | Τ  | Δ  |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    | Θ  |    |    |    |     |     | Β  | Μ  |    |    |    |  Ψ  |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L5] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS,                            KC_TRNS,                          KC_TRNS,                          KC_TRNS,                            KC_TRNS,                            KC_TRNS,
 KC_TRNS, M(UC_GREEK_CAPITAL_LETTER_CHI),     M(UC_GREEK_CAPITAL_LETTER_PI),    M(UC_GREEK_CAPITAL_LETTER_PHI),   M(UC_GREEK_CAPITAL_LETTER_OMEGA),   M(UC_GREEK_CAPITAL_LETTER_GAMMA),   KC_TRNS,
 KC_TRNS, M(UC_GREEK_CAPITAL_LETTER_UPSILON), M(UC_GREEK_CAPITAL_LETTER_IOTA),  M(UC_GREEK_CAPITAL_LETTER_ALPHA), M(UC_GREEK_CAPITAL_LETTER_EPSILON), M(UC_GREEK_CAPITAL_LETTER_OMICRON),
 KC_TRNS, KC_TRNS,                            M(UC_GREEK_CAPITAL_LETTER_THETA), KC_TRNS,                          KC_TRNS,                            KC_TRNS,                            KC_TRNS,
 KC_TRNS, KC_TRNS,                            KC_TRNS,                          KC_TRNS,                          KC_TRNS,
 /*-*/    /*-*/                               /*-*/                             /*-*/                             /*-*/                               KC_TRNS,                            KC_TRNS,
 /*-*/    /*-*/                               /*-*/                             /*-*/                             /*-*/                               /*-*/                               KC_TRNS,
 /*-*/    /*-*/                               /*-*/                             /*-*/                             KC_TRNS,                            KC_TRNS,                            KC_TRNS,
 KC_TRNS, KC_TRNS,                            KC_TRNS,                          KC_TRNS,                          KC_TRNS,                            KC_TRNS,                            KC_TRNS,
 KC_TRNS, M(UC_GREEK_CAPITAL_LETTER_ETA),     M(UC_GREEK_CAPITAL_LETTER_XI),    M(UC_GREEK_CAPITAL_LETTER_KAPPA), M(UC_GREEK_CAPITAL_LETTER_LAMDA),   KC_TRNS,                            M(UC_GREEK_CAPITAL_LETTER_ZETA),
 /*-*/    M(UC_GREEK_CAPITAL_LETTER_SIGMA),   M(UC_GREEK_CAPITAL_LETTER_NU),    M(UC_GREEK_CAPITAL_LETTER_RHO),   M(UC_GREEK_CAPITAL_LETTER_TAU),     M(UC_GREEK_CAPITAL_LETTER_DELTA),   KC_TRNS,
 KC_TRNS, M(UC_GREEK_CAPITAL_LETTER_BETA),    M(UC_GREEK_CAPITAL_LETTER_MU),    KC_TRNS,                          KC_TRNS,                            KC_TRNS,                            M(UC_GREEK_CAPITAL_LETTER_PSI),
 /*-*/    /*-*/                               KC_TRNS,                          KC_TRNS,                          KC_TRNS,                            KC_TRNS,                            KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS,                            KC_TRNS
),
/*
 * .------------------------------------.------------------------------------.
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----+----+----------!-----+----+----+----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |-----!-----!    |    |    |    |    |     |
 * !-----+----+----+----x----x----!     !     !----x----x----+----+----+-----!
 * |     |    |    |    |    |    |     |     |    |    |    |    |    |     |
 * '-----+----+----+----+----+----------'----------+----+----+----+----+-----'
 *  |    |    |    |    |    |                     !    |    |    |    |    |
 *  '------------------------'                     '------------------------'
 *                         .-----------. .-----------.
 *                         |     |     | !     |     |
 *                   .-----+-----+-----! !-----+-----+-----.
 *                   !     !     |     | !     |     !     !
 *                   !     !     !-----! !-----!     !     !
 *                   |     |     |     | !     |     |     |
 *                   '-----------------' '-----------------'
 */
[L6] = LAYOUT_ergodox(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS,
 /*-*/    /*-*/    /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 /*-*/    /*-*/    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS,
 KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {};

#define UC_MODE_WIN 0
#define UC_MODE_LINUX 1
#define UC_MODE_OSX 2

// TODO: allow default mode to be configured
static uint16_t unicode_mode = UC_MODE_WIN;

uint16_t hextokeycode(uint8_t hex) {
    if (hex == 0x0) {
        return KC_P0;
    }
    if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    }
    return KC_A + (hex - 0xA);
}

void unicode_action_function(uint16_t hi, uint16_t lo) {
    switch (unicode_mode) {
    case UC_MODE_WIN:
        register_code(KC_LALT);

        register_code(KC_PPLS);
        unregister_code(KC_PPLS);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LALT);
        break;
    case UC_MODE_LINUX:
        register_code(KC_LCTL);
        register_code(KC_LSFT);

        register_code(KC_U);
        unregister_code(KC_U);

        register_code(hextokeycode((hi & 0xF0) >> 4));
        unregister_code(hextokeycode((hi & 0xF0) >> 4));
        register_code(hextokeycode((hi & 0x0F)));
        unregister_code(hextokeycode((hi & 0x0F)));
        register_code(hextokeycode((lo & 0xF0) >> 4));
        unregister_code(hextokeycode((lo & 0xF0) >> 4));
        register_code(hextokeycode((lo & 0x0F)));
        unregister_code(hextokeycode((lo & 0x0F)));

        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    case UC_MODE_OSX:
        break;
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (!record->event.pressed) {
        return MACRO_NONE;
    }
    // MACRODOWN only works in this function
    switch(id) {
        case UM:
            unicode_mode = (unicode_mode + 1) % 2;
            break;

case UC_GREEK_SMALL_LETTER_OMICRON:
    unicode_action_function(0x03, 0xbf);
    break;
case UC_LEFTWARDS_ARROW:
    unicode_action_function(0x21, 0x90);
    break;
case UC_GREEK_CAPITAL_LETTER_RHO:
    unicode_action_function(0x03, 0xa1);
    break;
case UC_SUBSCRIPT_THREE:
    unicode_action_function(0x20, 0x83);
    break;
case UC_VULGAR_FRACTION_ONE_EIGHTH:
    unicode_action_function(0x21, 0x5b);
    break;
case UC_GREEK_SMALL_LETTER_LAMDA:
    unicode_action_function(0x03, 0xbb);
    break;
case UC_VULGAR_FRACTION_ONE_THIRD:
    unicode_action_function(0x21, 0x53);
    break;
case UC_GREEK_SMALL_LETTER_XI:
    unicode_action_function(0x03, 0xbe);
    break;
case UC_THERE_DOES_NOT_EXIST:
    unicode_action_function(0x22, 0x04);
    break;
case UC_SUPERSCRIPT_ONE:
    unicode_action_function(0x00, 0xb9);
    break;
case UC_GREEK_SMALL_LETTER_BETA:
    unicode_action_function(0x03, 0xb2);
    break;
case UC_SUBSCRIPT_FIVE:
    unicode_action_function(0x20, 0x85);
    break;
case UC_GREEK_CAPITAL_LETTER_IOTA:
    unicode_action_function(0x03, 0x99);
    break;
case UC_VULGAR_FRACTION_ONE_FIFTH:
    unicode_action_function(0x21, 0x55);
    break;
case UC_GREEK_SMALL_LETTER_PSI:
    unicode_action_function(0x03, 0xc8);
    break;
case UC_SUBSCRIPT_NINE:
    unicode_action_function(0x20, 0x89);
    break;
case UC_SUPERSCRIPT_FOUR:
    unicode_action_function(0x20, 0x74);
    break;
case UC_RIGHTWARDS_ARROW:
    unicode_action_function(0x21, 0x92);
    break;
case UC_SUPERSCRIPT_SIX:
    unicode_action_function(0x20, 0x76);
    break;
case UC_DOWNWARDS_ARROW:
    unicode_action_function(0x21, 0x93);
    break;
case UC_GREEK_SMALL_LETTER_PI:
    unicode_action_function(0x03, 0xc0);
    break;
case UC_SUPERSCRIPT_TWO:
    unicode_action_function(0x00, 0xb2);
    break;
case UC_GREEK_CAPITAL_LETTER_OMEGA:
    unicode_action_function(0x03, 0xa9);
    break;
case UC_GREEK_CAPITAL_LETTER_PSI:
    unicode_action_function(0x03, 0xa8);
    break;
case UC_SUBSCRIPT_FOUR:
    unicode_action_function(0x20, 0x84);
    break;
case UC_GREEK_CAPITAL_LETTER_NU:
    unicode_action_function(0x03, 0x9d);
    break;
case UC_DIVISION_SIGN:
    unicode_action_function(0x00, 0xf7);
    break;
case UC_GREEK_SMALL_LETTER_SIGMA:
    unicode_action_function(0x03, 0xc3);
    break;
case UC_GREEK_SMALL_LETTER_RHO:
    unicode_action_function(0x03, 0xc1);
    break;
case UC_VULGAR_FRACTION_ONE_SIXTH:
    unicode_action_function(0x21, 0x59);
    break;
case UC_GREEK_SMALL_LETTER_GAMMA:
    unicode_action_function(0x03, 0xb3);
    break;
case UC_VULGAR_FRACTION_TWO_THIRDS:
    unicode_action_function(0x21, 0x54);
    break;
case UC_GREEK_SMALL_LETTER_NU:
    unicode_action_function(0x03, 0xbd);
    break;
case UC_GREEK_SMALL_LETTER_ZETA:
    unicode_action_function(0x03, 0xb6);
    break;
case UC_GREEK_SMALL_LETTER_EPSILON:
    unicode_action_function(0x03, 0xb5);
    break;
case UC_GREEK_SMALL_LETTER_KAPPA:
    unicode_action_function(0x03, 0xba);
    break;
case UC_SUPERSCRIPT_SEVEN:
    unicode_action_function(0x20, 0x77);
    break;
case UC_GREEK_CAPITAL_LETTER_PI:
    unicode_action_function(0x03, 0xa0);
    break;
case UC_GREEK_SMALL_LETTER_FINAL_SIGMA:
    unicode_action_function(0x03, 0xc2);
    break;
case UC_GREEK_CAPITAL_LETTER_XI:
    unicode_action_function(0x03, 0x9e);
    break;
case UC_GREEK_SMALL_LETTER_THETA:
    unicode_action_function(0x03, 0xb8);
    break;
case UC_GREEK_SMALL_LETTER_ETA:
    unicode_action_function(0x03, 0xb7);
    break;
case UC_SUBSCRIPT_TWO:
    unicode_action_function(0x20, 0x82);
    break;
case UC_ASYMPTOTICALLY_EQUAL_TO:
    unicode_action_function(0x22, 0x43);
    break;
case UC_GREEK_SMALL_LETTER_ALPHA:
    unicode_action_function(0x03, 0xb1);
    break;
case UC_GREEK_CAPITAL_LETTER_PHI:
    unicode_action_function(0x03, 0xa6);
    break;
case UC_GREEK_SMALL_LETTER_PHI:
    unicode_action_function(0x03, 0xc6);
    break;
case UC_INFINITY:
    unicode_action_function(0x22, 0x1e);
    break;
case UC_GREEK_CAPITAL_LETTER_OMICRON:
    unicode_action_function(0x03, 0x9f);
    break;
case UC_ELEMENT_OF:
    unicode_action_function(0x22, 0x08);
    break;
case UC_MULTIPLICATION_SIGN:
    unicode_action_function(0x00, 0xd7);
    break;
case UC_SUBSCRIPT_ZERO:
    unicode_action_function(0x20, 0x80);
    break;
case UC_GREEK_CAPITAL_LETTER_SIGMA:
    unicode_action_function(0x03, 0xa3);
    break;
case UC_GREEK_SMALL_LETTER_OMEGA:
    unicode_action_function(0x03, 0xc9);
    break;
case UC_SUBSCRIPT_ONE:
    unicode_action_function(0x20, 0x81);
    break;
case UC_GREEK_CAPITAL_LETTER_ZETA:
    unicode_action_function(0x03, 0x96);
    break;
case UC_GREEK_SMALL_LETTER_TAU:
    unicode_action_function(0x03, 0xc4);
    break;
case UC_SUPERSCRIPT_FIVE:
    unicode_action_function(0x20, 0x75);
    break;
case UC_THERE_EXISTS:
    unicode_action_function(0x22, 0x03);
    break;
case UC_PLUS_MINUS_SIGN:
    unicode_action_function(0x00, 0xb1);
    break;
case UC_VULGAR_FRACTION_THREE_QUARTERS:
    unicode_action_function(0x00, 0xbe);
    break;
case UC_SUPERSCRIPT_THREE:
    unicode_action_function(0x00, 0xb3);
    break;
case UC_EMPTY_SET:
    unicode_action_function(0x22, 0x05);
    break;
case UC_UPWARDS_ARROW:
    unicode_action_function(0x21, 0x91);
    break;
case UC_SUPERSCRIPT_NINE:
    unicode_action_function(0x20, 0x79);
    break;
case UC_GREEK_SMALL_LETTER_DELTA:
    unicode_action_function(0x03, 0xb4);
    break;
case UC_GREEK_SMALL_LETTER_MU:
    unicode_action_function(0x03, 0xbc);
    break;
case UC_GREEK_CAPITAL_LETTER_KAPPA:
    unicode_action_function(0x03, 0x9a);
    break;
case UC_SUBSCRIPT_EIGHT:
    unicode_action_function(0x20, 0x88);
    break;
case UC_GREEK_CAPITAL_LETTER_ALPHA:
    unicode_action_function(0x03, 0x91);
    break;
case UC_SUBSCRIPT_SEVEN:
    unicode_action_function(0x20, 0x87);
    break;
case UC_GREEK_CAPITAL_LETTER_BETA:
    unicode_action_function(0x03, 0x92);
    break;
case UC_GREEK_CAPITAL_LETTER_ETA:
    unicode_action_function(0x03, 0x97);
    break;
case UC_SUPERSCRIPT_EIGHT:
    unicode_action_function(0x20, 0x78);
    break;
case UC_SUPERSCRIPT_ZERO:
    unicode_action_function(0x20, 0x70);
    break;
case UC_NOT_AN_ELEMENT_OF:
    unicode_action_function(0x22, 0x09);
    break;
case UC_GREEK_SMALL_LETTER_UPSILON:
    unicode_action_function(0x03, 0xc5);
    break;
case UC_NOT_EQUAL_TO:
    unicode_action_function(0x22, 0x60);
    break;
case UC_GREEK_CAPITAL_LETTER_CHI:
    unicode_action_function(0x03, 0xa7);
    break;
case UC_FOR_ALL:
    unicode_action_function(0x22, 0x00);
    break;
case UC_GREEK_CAPITAL_LETTER_TAU:
    unicode_action_function(0x03, 0xa4);
    break;
case UC_VULGAR_FRACTION_ONE_QUARTER:
    unicode_action_function(0x00, 0xbc);
    break;
case UC_GREEK_SMALL_LETTER_CHI:
    unicode_action_function(0x03, 0xc7);
    break;
case UC_GREEK_CAPITAL_LETTER_THETA:
    unicode_action_function(0x03, 0x98);
    break;
case UC_GREEK_SMALL_LETTER_IOTA:
    unicode_action_function(0x03, 0xb9);
    break;
case UC_GREEK_CAPITAL_LETTER_LAMDA:
    unicode_action_function(0x03, 0x9b);
    break;
case UC_SUPERSCRIPT_LATIN_SMALL_LETTER_N:
    unicode_action_function(0x20, 0x7f);
    break;
case UC_GREEK_CAPITAL_LETTER_UPSILON:
    unicode_action_function(0x03, 0xa5);
    break;
case UC_GREEK_CAPITAL_LETTER_MU:
    unicode_action_function(0x03, 0x9c);
    break;
case UC_GREEK_CAPITAL_LETTER_EPSILON:
    unicode_action_function(0x03, 0x95);
    break;
case UC_GREEK_CAPITAL_LETTER_GAMMA:
    unicode_action_function(0x03, 0x93);
    break;
case UC_SUBSCRIPT_SIX:
    unicode_action_function(0x20, 0x86);
    break;
case UC_GREEK_CAPITAL_LETTER_DELTA:
    unicode_action_function(0x03, 0x94);
    break;
case UC_VULGAR_FRACTION_ONE_HALF:
    unicode_action_function(0x00, 0xbd);
    break;
        default:
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
        case L1:
            ergodox_right_led_1_on();
            break;
        case L2:
            ergodox_right_led_2_on();
            break;
        case L3:
            ergodox_right_led_3_on();
            break;
        case L4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case L5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        // case L6:
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        // case L7:
        //     ergodox_right_led_1_on();
        //     ergodox_right_led_2_on();
        //     ergodox_right_led_3_on();
        //     break;
        default:
            ergodox_board_led_off();
            break;
    }
};
