#include "ergodox_ez.h"
#include "action_layer.h"
#include "keymap_common.h"
#include "keymap_extras/keymap_german.h"

#define L0   0      // Layer 0
#define L1   1      // Layer 1
#define L2   2      // Layer 2
#define L3   3      // Layer 3
#define L4   4      // Layer 4
#define L5   5      // Layer 5
#define L6   6      // Layer 6
#define L7   7      // Layer 7
#define L8   8      // Layer 8
#define UMS 0
#define UC_UPWARDS_ARROW 1
#define UC_LEFTWARDS_ARROW 2
#define UC_DOWNWARDS_ARROW 3
#define UC_RIGHTWARDS_ARROW 4
#define UC_SUP_ONE 5
#define UC_SUP_TWO 6
#define UC_SUP_THREE 7
#define UC_SUP_FOUR 8
#define UC_SUP_FIVE 9
#define UC_FOR_ALL 10
#define UC_SUP_SIX 11
#define UC_SUP_SEVEN 12
#define UC_SUP_EIGHT 13
#define UC_SUP_NINE 14
#define UC_SUP_ZERO 15
#define UC_MULTIPLICATION_SIGN 16
#define UC_FR_ONE_HALF 17
#define UC_DIVISION_SIGN 18
#define UC_FR_ONE_QUARTER 19
#define UC_FR_ONE_FIFTH 20
#define UC_FR_ONE_SIXTH 21
#define UC_FR_ONE_EIGHTH 22
#define UC_PLUS_MINUS_SIGN 23
#define UC_EMPTY_SET 24
#define UC_INFINITY 25
#define UC_SUP_LATIN_SMALL_LETTER_N 26
#define UC_THERE_EXISTS 27
#define UC_ELEMENT_OF 28
#define UC_FR_ONE_THIRD 29
#define UC_NOT_EQUAL_TO 30
#define UC_FR_TWO_THIRDS 31
#define UC_FR_THREE_QUARTERS 32
#define UC_ASYMPTOTICALLY_EQUAL_TO 33
#define UC_THERE_DOES_NOT_EXIST 34
#define UC_NOT_AN_ELEMENT_OF 35
#define UC_SUB_ONE 36
#define UC_SUB_TWO 37
#define UC_SUB_THREE 38
#define UC_SUB_FOUR 39
#define UC_SUB_FIVE 40
#define UC_SUB_SIX 41
#define UC_SUB_SEVEN 42
#define UC_SUB_EIGHT 43
#define UC_SUB_NINE 44
#define UC_SUB_ZERO 45
#define UC_GR_LC_CHI 46
#define UC_GR_LC_PI 47
#define UC_GR_LC_PHI 48
#define UC_GR_LC_OMEGA 49
#define UC_GR_LC_GAMMA 50
#define UC_GR_LC_ETA 51
#define UC_GR_LC_XI 52
#define UC_GR_LC_KAPPA 53
#define UC_GR_LC_LAMDA 54
#define UC_GR_LC_ZETA 55
#define UC_GR_LC_UPSILON 56
#define UC_GR_LC_IOTA 57
#define UC_GR_LC_ALPHA 58
#define UC_GR_LC_EPSILON 59
#define UC_GR_LC_OMICRON 60
#define UC_GR_LC_SIGMA 61
#define UC_GR_LC_NU 62
#define UC_GR_LC_RHO 63
#define UC_GR_LC_TAU 64
#define UC_GR_LC_DELTA 65
#define UC_GR_LC_FINAL_SIGMA 66
#define UC_GR_LC_THETA 67
#define UC_GR_LC_BETA 68
#define UC_GR_LC_MU 69
#define UC_GR_LC_PSI 70
#define UC_GR_UC_CHI 71
#define UC_GR_UC_PI 72
#define UC_GR_UC_PHI 73
#define UC_GR_UC_OMEGA 74
#define UC_GR_UC_GAMMA 75
#define UC_GR_UC_ETA 76
#define UC_GR_UC_XI 77
#define UC_GR_UC_KAPPA 78
#define UC_GR_UC_LAMDA 79
#define UC_GR_UC_ZETA 80
#define UC_GR_UC_UPSILON 81
#define UC_GR_UC_IOTA 82
#define UC_GR_UC_ALPHA 83
#define UC_GR_UC_EPSILON 84
#define UC_GR_UC_OMICRON 85
#define UC_GR_UC_SIGMA 86
#define UC_GR_UC_NU 87
#define UC_GR_UC_RHO 88
#define UC_GR_UC_TAU 89
#define UC_GR_UC_DELTA 90
#define UC_GR_UC_THETA 91
#define UC_GR_UC_BETA 92
#define UC_GR_UC_MU 93
#define UC_GR_UC_PSI 94

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |MO(5)| 1  | 2  | 3  | 4  | 5  | ACUT |       ! GRV  | 6  | 7  | 8  | 9  | 0  |CIRC |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |MO(4)| X  | P  | F  | W  | G  | HOME |       !TG(2) | H  | J  | K  | L  | Q  |  Z  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |MO(1)| U  | I  | A  | E  | O  |------!       !------! S  | N  | R  | T  | D  | SS  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |MO(3)| UE | OE | AE | C  | V  | END  |       ! TAB  | B  | M  |COMM| DOT| UP |  Y  |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |LGUI|LALT|LCTL|                               !LALT|    |LEFT|DOWN|RGHT|
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               | INS  |TG(2) | !M(UMS)| DELT |
 *                        .------+------+------! !------+------+------.
 *                        !      !      | APP  | ! PGUP |      !      !
 *                        !      !      !------! !------!      !      !
 *                        | BSPC | LSFT | ESC  | ! PGDN |ENTER |SPACE |
 *                        '--------------------' '--------------------'
*/
[L0] = KEYMAP(
	MO(5),
	DE_1,	DE_2,	DE_3,	DE_4,	DE_5,	DE_ACUT,	MO(4),
	DE_X,	DE_P,	DE_F,	DE_W,	DE_G,	KC_HOME,	MO(1),
	DE_U,	DE_I,	DE_A,	DE_E,	DE_O,	MO(3),
	DE_UE,	DE_OE,	DE_AE,	DE_C,	DE_V,	KC_END,	KC_TRNS,
	KC_TRNS,	KC_LGUI,	KC_LALT,	KC_LCTL,	KC_INS,
	TG(2),	KC_APP,
	KC_BSPC,
	KC_LSFT,	KC_ESC,	DE_GRV,
	DE_6,	DE_7,	DE_8,	DE_9,	DE_0,	DE_CIRC,	TG(2),
	DE_H,	DE_J,	DE_K,	DE_L,	DE_Q,	DE_Z,	DE_S,
	DE_N,	DE_R,	DE_T,	DE_D,	DE_SS,	KC_TAB,
	DE_B,	DE_M,	DE_COMM,	DE_DOT,	KC_UP,	DE_Y,	KC_LALT,
	KC_TRNS,	KC_LEFT,	KC_DOWN,	KC_RGHT,	M(UMS),
	KC_DELT,	KC_PGUP,
	KC_PGDN,
	KC_ENTER,	KC_SPACE),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     |EXLM|DQOT|PARA|    |    |      |       !      |    |    |    |    |RING|     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     |ASTR|PIPE|SLSH|LCBR|RCBR|      |       !      |HASH|LESS|MORE|    |DQOT|     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |UNDS|MINS|AMPR|LBRC|RBRC|------!       !------!DLR |LPRN|RPRN|TILD|QUOT|QST  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |PLUS| EQL|    |    |      |       !      |BSLS|PERC|SCLN|COLN| ↑  |     |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    | ←  | ↓  | →  |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L1] = KEYMAP(
	KC_TRNS,
	DE_EXLM,	DE_DQOT,	DE_PARA,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	DE_ASTR,	DE_PIPE,	DE_SLSH,	DE_LCBR,	DE_RCBR,	KC_TRNS,	KC_TRNS,
	DE_UNDS,	DE_MINS,	DE_AMPR,	DE_LBRC,	DE_RBRC,	KC_TRNS,
	KC_TRNS,	DE_PLUS,	DE_EQL,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	DE_RING,	KC_TRNS,	KC_TRNS,
	DE_HASH,	DE_LESS,	DE_MORE,	KC_TRNS,	DE_DQOT,	KC_TRNS,	DE_DLR,
	DE_LPRN,	DE_RPRN,	DE_TILD,	DE_QUOT,	DE_QST,	KC_TRNS,
	DE_BSLS,	DE_PERC,	DE_SCLN,	DE_COLN,	M(UC_UPWARDS_ARROW),	KC_TRNS,	KC_TRNS,
	KC_TRNS,	M(UC_LEFTWARDS_ARROW),	M(UC_DOWNWARDS_ARROW),	M(UC_RIGHTWARDS_ARROW),	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     | F1 | F2 | F3 | F4 | F5 | F11  |       ! F12  | F6 | F7 | F8 | F9 |F10 |PEQL |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    | P7 | P8 | P9 |PAST|PSLS |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |------!       !------!    | P4 | P5 | P6 |PMNS|PMNS |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |      |       ! NLCK |    | P1 | P2 | P3 |PPLS|PPLS |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               ! P0 |PCMM|PDOT|PENT|PENT|
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L2] = KEYMAP(
	KC_TRNS,
	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5,	KC_F11,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_F12,
	KC_F6,	KC_F7,	KC_F8,	KC_F9,	KC_F10,	KC_PEQL,	KC_TRNS,
	KC_TRNS,	KC_P7,	KC_P8,	KC_P9,	KC_PAST,	KC_PSLS,	KC_TRNS,
	KC_P4,	KC_P5,	KC_P6,	KC_PMNS,	KC_PMNS,	KC_NLCK,
	KC_TRNS,	KC_P1,	KC_P2,	KC_P3,	KC_PPLS,	KC_PPLS,	KC_P0,
	KC_PCMM,	KC_PDOT,	KC_PENT,	KC_PENT,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     | ¹  | ²  | ³  | ⁴  | ⁵  |  ∀   |       !      | ⁶  | ⁷  | ⁸  | ⁹  |  ⁰ |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     | ×  | ½  | ÷  | ¼  |  ⅕ |      |       !      | ⅙  |    | ⅛  |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    | ±  | AT |EURO| ∅  |------!       !------! ∞  | ⁿ  | ∃  | ∈  |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     | ⅓  | ≠  | ⅔  | ¾  | ≃  |      |       !      |EXLM|    | ∄  | ∉  |    |     |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L3] = KEYMAP(
	KC_TRNS,
	M(UC_SUP_ONE),	M(UC_SUP_TWO),	M(UC_SUP_THREE),	M(UC_SUP_FOUR),	M(UC_SUP_FIVE),	M(UC_FOR_ALL),	KC_TRNS,
	M(UC_MULTIPLICATION_SIGN),	M(UC_FR_ONE_HALF),	M(UC_DIVISION_SIGN),	M(UC_FR_ONE_QUARTER),	M(UC_FR_ONE_FIFTH),	KC_TRNS,	KC_TRNS,
	KC_TRNS,	M(UC_PLUS_MINUS_SIGN),	DE_AT,	DE_EURO,	M(UC_EMPTY_SET),	KC_TRNS,
	M(UC_FR_ONE_THIRD),	M(UC_NOT_EQUAL_TO),	M(UC_FR_TWO_THIRDS),	M(UC_FR_THREE_QUARTERS),	M(UC_ASYMPTOTICALLY_EQUAL_TO),	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	M(UC_SUP_SIX),	M(UC_SUP_SEVEN),	M(UC_SUP_EIGHT),	M(UC_SUP_NINE),	M(UC_SUP_ZERO),	KC_TRNS,	KC_TRNS,
	M(UC_FR_ONE_SIXTH),	KC_TRNS,	M(UC_FR_ONE_EIGHTH),	KC_TRNS,	KC_TRNS,	KC_TRNS,	M(UC_INFINITY),
	M(UC_SUP_LATIN_SMALL_LETTER_N),	M(UC_THERE_EXISTS),	M(UC_ELEMENT_OF),	KC_TRNS,	KC_TRNS,	KC_TRNS,
	DE_EXLM,	KC_TRNS,	M(UC_THERE_DOES_NOT_EXIST),	M(UC_NOT_AN_ELEMENT_OF),	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     | ₁  | ₂  | ₃  | ₄  | ₅  |      |       !      | ₆  | ₇  | ₈  | ₉  | ₀  |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     | χ  | π  | φ  | ω  | γ  |      |       !      | η  | ξ  | κ  | λ  |    |  ζ  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     | υ  | ι  | α  | ε  | ο  |------!       !------! σ  | ν  | ρ  | τ  | δ  |  ς  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    | θ  |    |    |    |      |       !      | β  | μ  |    |    |    |  ψ  |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L4] = KEYMAP(
	KC_TRNS,
	M(UC_SUB_ONE),	M(UC_SUB_TWO),	M(UC_SUB_THREE),	M(UC_SUB_FOUR),	M(UC_SUB_FIVE),	KC_TRNS,	KC_TRNS,
	M(UC_GR_LC_CHI),	M(UC_GR_LC_PI),	M(UC_GR_LC_PHI),	M(UC_GR_LC_OMEGA),	M(UC_GR_LC_GAMMA),	KC_TRNS,	KC_TRNS,
	M(UC_GR_LC_UPSILON),	M(UC_GR_LC_IOTA),	M(UC_GR_LC_ALPHA),	M(UC_GR_LC_EPSILON),	M(UC_GR_LC_OMICRON),	KC_TRNS,
	KC_TRNS,	M(UC_GR_LC_THETA),	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	M(UC_SUB_SIX),	M(UC_SUB_SEVEN),	M(UC_SUB_EIGHT),	M(UC_SUB_NINE),	M(UC_SUB_ZERO),	KC_TRNS,	KC_TRNS,
	M(UC_GR_LC_ETA),	M(UC_GR_LC_XI),	M(UC_GR_LC_KAPPA),	M(UC_GR_LC_LAMDA),	KC_TRNS,	M(UC_GR_LC_ZETA),	M(UC_GR_LC_SIGMA),
	M(UC_GR_LC_NU),	M(UC_GR_LC_RHO),	M(UC_GR_LC_TAU),	M(UC_GR_LC_DELTA),	M(UC_GR_LC_FINAL_SIGMA),	KC_TRNS,
	M(UC_GR_LC_BETA),	M(UC_GR_LC_MU),	KC_TRNS,	KC_TRNS,	KC_TRNS,	M(UC_GR_LC_PSI),	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     | Χ  | Π  | Φ  | Ω  | Γ  |      |       !      | Η  | Ξ  | Κ  | Λ  |    |  Ζ  |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     | Υ  | Ι  | Α  | Ε  | Ο  |------!       !------! Σ  | Ν  | Ρ  | Τ  | Δ  |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    | Θ  |    |    |    |      |       !      | Β  | Μ  |    |    |    |  Ψ  |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L5] = KEYMAP(
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	M(UC_GR_UC_CHI),	M(UC_GR_UC_PI),	M(UC_GR_UC_PHI),	M(UC_GR_UC_OMEGA),	M(UC_GR_UC_GAMMA),	KC_TRNS,	KC_TRNS,
	M(UC_GR_UC_UPSILON),	M(UC_GR_UC_IOTA),	M(UC_GR_UC_ALPHA),	M(UC_GR_UC_EPSILON),	M(UC_GR_UC_OMICRON),	KC_TRNS,
	KC_TRNS,	M(UC_GR_UC_THETA),	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	M(UC_GR_UC_ETA),	M(UC_GR_UC_XI),	M(UC_GR_UC_KAPPA),	M(UC_GR_UC_LAMDA),	KC_TRNS,	M(UC_GR_UC_ZETA),	M(UC_GR_UC_SIGMA),
	M(UC_GR_UC_NU),	M(UC_GR_UC_RHO),	M(UC_GR_UC_TAU),	M(UC_GR_UC_DELTA),	KC_TRNS,	KC_TRNS,
	M(UC_GR_UC_BETA),	M(UC_GR_UC_MU),	KC_TRNS,	KC_TRNS,	KC_TRNS,	M(UC_GR_UC_PSI),	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |------!       !------!    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L6] = KEYMAP(
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |------!       !------!    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L7] = KEYMAP(
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
/*
 *    .-------------------------------------.       .-------------------------------------.
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----+----+-----------!       !------+----+----+----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |------!       !------!    |    |    |    |    |     |
 *    !-----+----+----+----x----x----!      !       !      !----x----x----+----+----+-----!
 *    |     |    |    |    |    |    |      |       !      |    |    |    |    |    |     |
 *    '-----+----+----+----+----+-----------'       '-----------+----+----+----+----+-----'
 *     |    |    |    |    |    |                               !    |    |    |    |    |
 *     '------------------------'.-------------. .-------------.'------------------------'
 *                               |      |      | !      |      |
 *                        .------+------+------! !------+------+------.
 *                        !      !      |      | !      |      !      !
 *                        !      !      !------! !------!      !      !
 *                        |      |      |      | !      |      |      |
 *                        '--------------------' '--------------------'
*/
[L8] = KEYMAP(
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,
	KC_TRNS,	KC_TRNS,
	KC_TRNS,
	KC_TRNS,	KC_TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
};

#define UC_MODE_WIN 0
#define UC_MODE_LINUX 1

static uint16_t unicode_mode = UC_MODE_WIN;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if (!record->event.pressed) {
		return MACRO_NONE;
	}
  	// MACRODOWN only works in this function
    switch(id) {
    	case UMS:
    		unicode_mode = (unicode_mode + 1) % 2;
    		break;
    	
    	default:
    		break;
    }
	if (unicode_mode == UC_MODE_WIN) {
		switch(id) {
			case UC_UPWARDS_ARROW:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_9), T(KP_1), U(LALT), END
	);
case UC_LEFTWARDS_ARROW:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_9), T(KP_0), U(LALT), END
	);
case UC_DOWNWARDS_ARROW:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_9), T(KP_3), U(LALT), END
	);
case UC_RIGHTWARDS_ARROW:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_9), T(KP_2), U(LALT), END
	);
case UC_SUP_ONE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(KP_9), U(LALT), END
	);
case UC_SUP_TWO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(KP_2), U(LALT), END
	);
case UC_SUP_THREE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(KP_3), U(LALT), END
	);
case UC_SUP_FOUR:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_4), U(LALT), END
	);
case UC_SUP_FIVE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_5), U(LALT), END
	);
case UC_FOR_ALL:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_0), U(LALT), END
	);
case UC_SUP_SIX:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_6), U(LALT), END
	);
case UC_SUP_SEVEN:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_7), U(LALT), END
	);
case UC_SUP_EIGHT:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_8), U(LALT), END
	);
case UC_SUP_NINE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_9), U(LALT), END
	);
case UC_SUP_ZERO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(KP_0), U(LALT), END
	);
case UC_MULTIPLICATION_SIGN:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(D), T(KP_7), U(LALT), END
	);
case UC_FR_ONE_HALF:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(D), U(LALT), END
	);
case UC_DIVISION_SIGN:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(F), T(KP_7), U(LALT), END
	);
case UC_FR_ONE_QUARTER:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(C), U(LALT), END
	);
case UC_FR_ONE_FIFTH:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_5), T(KP_5), U(LALT), END
	);
case UC_FR_ONE_SIXTH:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_5), T(KP_9), U(LALT), END
	);
case UC_FR_ONE_EIGHTH:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_5), T(B), U(LALT), END
	);
case UC_PLUS_MINUS_SIGN:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(KP_1), U(LALT), END
	);
case UC_EMPTY_SET:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_5), U(LALT), END
	);
case UC_INFINITY:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_1), T(E), U(LALT), END
	);
case UC_SUP_LATIN_SMALL_LETTER_N:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_7), T(F), U(LALT), END
	);
case UC_THERE_EXISTS:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_3), U(LALT), END
	);
case UC_ELEMENT_OF:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_8), U(LALT), END
	);
case UC_FR_ONE_THIRD:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_5), T(KP_3), U(LALT), END
	);
case UC_NOT_EQUAL_TO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_6), T(KP_0), U(LALT), END
	);
case UC_FR_TWO_THIRDS:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_1), T(KP_5), T(KP_4), U(LALT), END
	);
case UC_FR_THREE_QUARTERS:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_0), T(B), T(E), U(LALT), END
	);
case UC_ASYMPTOTICALLY_EQUAL_TO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_4), T(KP_3), U(LALT), END
	);
case UC_THERE_DOES_NOT_EXIST:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_4), U(LALT), END
	);
case UC_NOT_AN_ELEMENT_OF:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_2), T(KP_0), T(KP_9), U(LALT), END
	);
case UC_SUB_ONE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_1), U(LALT), END
	);
case UC_SUB_TWO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_2), U(LALT), END
	);
case UC_SUB_THREE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_3), U(LALT), END
	);
case UC_SUB_FOUR:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_4), U(LALT), END
	);
case UC_SUB_FIVE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_5), U(LALT), END
	);
case UC_SUB_SIX:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_6), U(LALT), END
	);
case UC_SUB_SEVEN:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_7), U(LALT), END
	);
case UC_SUB_EIGHT:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_8), U(LALT), END
	);
case UC_SUB_NINE:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_9), U(LALT), END
	);
case UC_SUB_ZERO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_2), T(KP_0), T(KP_8), T(KP_0), U(LALT), END
	);
case UC_GR_LC_CHI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_7), U(LALT), END
	);
case UC_GR_LC_PI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_0), U(LALT), END
	);
case UC_GR_LC_PHI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_6), U(LALT), END
	);
case UC_GR_LC_OMEGA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_9), U(LALT), END
	);
case UC_GR_LC_GAMMA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_3), U(LALT), END
	);
case UC_GR_LC_ETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_7), U(LALT), END
	);
case UC_GR_LC_XI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(E), U(LALT), END
	);
case UC_GR_LC_KAPPA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(A), U(LALT), END
	);
case UC_GR_LC_LAMDA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(B), U(LALT), END
	);
case UC_GR_LC_ZETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_6), U(LALT), END
	);
case UC_GR_LC_UPSILON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_5), U(LALT), END
	);
case UC_GR_LC_IOTA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_9), U(LALT), END
	);
case UC_GR_LC_ALPHA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_1), U(LALT), END
	);
case UC_GR_LC_EPSILON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_5), U(LALT), END
	);
case UC_GR_LC_OMICRON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(F), U(LALT), END
	);
case UC_GR_LC_SIGMA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_3), U(LALT), END
	);
case UC_GR_LC_NU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(D), U(LALT), END
	);
case UC_GR_LC_RHO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_1), U(LALT), END
	);
case UC_GR_LC_TAU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_4), U(LALT), END
	);
case UC_GR_LC_DELTA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_4), U(LALT), END
	);
case UC_GR_LC_FINAL_SIGMA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_2), U(LALT), END
	);
case UC_GR_LC_THETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_8), U(LALT), END
	);
case UC_GR_LC_BETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(KP_2), U(LALT), END
	);
case UC_GR_LC_MU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(B), T(C), U(LALT), END
	);
case UC_GR_LC_PSI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(C), T(KP_8), U(LALT), END
	);
case UC_GR_UC_CHI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_7), U(LALT), END
	);
case UC_GR_UC_PI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_0), U(LALT), END
	);
case UC_GR_UC_PHI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_6), U(LALT), END
	);
case UC_GR_UC_OMEGA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_9), U(LALT), END
	);
case UC_GR_UC_GAMMA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_3), U(LALT), END
	);
case UC_GR_UC_ETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_7), U(LALT), END
	);
case UC_GR_UC_XI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(E), U(LALT), END
	);
case UC_GR_UC_KAPPA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(A), U(LALT), END
	);
case UC_GR_UC_LAMDA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(B), U(LALT), END
	);
case UC_GR_UC_ZETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_6), U(LALT), END
	);
case UC_GR_UC_UPSILON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_5), U(LALT), END
	);
case UC_GR_UC_IOTA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_9), U(LALT), END
	);
case UC_GR_UC_ALPHA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_1), U(LALT), END
	);
case UC_GR_UC_EPSILON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_5), U(LALT), END
	);
case UC_GR_UC_OMICRON:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(F), U(LALT), END
	);
case UC_GR_UC_SIGMA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_3), U(LALT), END
	);
case UC_GR_UC_NU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(D), U(LALT), END
	);
case UC_GR_UC_RHO:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_1), U(LALT), END
	);
case UC_GR_UC_TAU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_4), U(LALT), END
	);
case UC_GR_UC_DELTA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_4), U(LALT), END
	);
case UC_GR_UC_THETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_8), U(LALT), END
	);
case UC_GR_UC_BETA:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(KP_2), U(LALT), END
	);
case UC_GR_UC_MU:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(KP_9), T(C), U(LALT), END
	);
case UC_GR_UC_PSI:
	return MACRODOWN(
		D(LALT), T(KP_PLUS), T(KP_0), T(KP_3), T(A), T(KP_8), U(LALT), END
	);
	    	default:
	    		break;
		}
	} else if (unicode_mode == UC_MODE_LINUX) {
		switch(id) {
			case UC_UPWARDS_ARROW:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_9), T(KP_1), T(KP_ENTER), END
	);
case UC_LEFTWARDS_ARROW:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_9), T(KP_0), T(KP_ENTER), END
	);
case UC_DOWNWARDS_ARROW:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_9), T(KP_3), T(KP_ENTER), END
	);
case UC_RIGHTWARDS_ARROW:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_9), T(KP_2), T(KP_ENTER), END
	);
case UC_SUP_ONE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(KP_9), T(KP_ENTER), END
	);
case UC_SUP_TWO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(KP_2), T(KP_ENTER), END
	);
case UC_SUP_THREE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(KP_3), T(KP_ENTER), END
	);
case UC_SUP_FOUR:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_4), T(KP_ENTER), END
	);
case UC_SUP_FIVE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_5), T(KP_ENTER), END
	);
case UC_FOR_ALL:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_0), T(KP_ENTER), END
	);
case UC_SUP_SIX:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_6), T(KP_ENTER), END
	);
case UC_SUP_SEVEN:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_7), T(KP_ENTER), END
	);
case UC_SUP_EIGHT:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_8), T(KP_ENTER), END
	);
case UC_SUP_NINE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_9), T(KP_ENTER), END
	);
case UC_SUP_ZERO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(KP_0), T(KP_ENTER), END
	);
case UC_MULTIPLICATION_SIGN:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(D), T(KP_7), T(KP_ENTER), END
	);
case UC_FR_ONE_HALF:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(D), T(KP_ENTER), END
	);
case UC_DIVISION_SIGN:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(F), T(KP_7), T(KP_ENTER), END
	);
case UC_FR_ONE_QUARTER:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(C), T(KP_ENTER), END
	);
case UC_FR_ONE_FIFTH:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_5), T(KP_5), T(KP_ENTER), END
	);
case UC_FR_ONE_SIXTH:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_5), T(KP_9), T(KP_ENTER), END
	);
case UC_FR_ONE_EIGHTH:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_5), T(B), T(KP_ENTER), END
	);
case UC_PLUS_MINUS_SIGN:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(KP_1), T(KP_ENTER), END
	);
case UC_EMPTY_SET:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_5), T(KP_ENTER), END
	);
case UC_INFINITY:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_1), T(E), T(KP_ENTER), END
	);
case UC_SUP_LATIN_SMALL_LETTER_N:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_7), T(F), T(KP_ENTER), END
	);
case UC_THERE_EXISTS:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_3), T(KP_ENTER), END
	);
case UC_ELEMENT_OF:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_8), T(KP_ENTER), END
	);
case UC_FR_ONE_THIRD:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_5), T(KP_3), T(KP_ENTER), END
	);
case UC_NOT_EQUAL_TO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_6), T(KP_0), T(KP_ENTER), END
	);
case UC_FR_TWO_THIRDS:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_1), T(KP_5), T(KP_4), T(KP_ENTER), END
	);
case UC_FR_THREE_QUARTERS:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_0), T(B), T(E), T(KP_ENTER), END
	);
case UC_ASYMPTOTICALLY_EQUAL_TO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_4), T(KP_3), T(KP_ENTER), END
	);
case UC_THERE_DOES_NOT_EXIST:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_4), T(KP_ENTER), END
	);
case UC_NOT_AN_ELEMENT_OF:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_2), T(KP_0), T(KP_9), T(KP_ENTER), END
	);
case UC_SUB_ONE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_1), T(KP_ENTER), END
	);
case UC_SUB_TWO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_2), T(KP_ENTER), END
	);
case UC_SUB_THREE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_3), T(KP_ENTER), END
	);
case UC_SUB_FOUR:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_4), T(KP_ENTER), END
	);
case UC_SUB_FIVE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_5), T(KP_ENTER), END
	);
case UC_SUB_SIX:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_6), T(KP_ENTER), END
	);
case UC_SUB_SEVEN:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_7), T(KP_ENTER), END
	);
case UC_SUB_EIGHT:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_8), T(KP_ENTER), END
	);
case UC_SUB_NINE:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_9), T(KP_ENTER), END
	);
case UC_SUB_ZERO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_2), T(KP_0), T(KP_8), T(KP_0), T(KP_ENTER), END
	);
case UC_GR_LC_CHI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_7), T(KP_ENTER), END
	);
case UC_GR_LC_PI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_0), T(KP_ENTER), END
	);
case UC_GR_LC_PHI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_6), T(KP_ENTER), END
	);
case UC_GR_LC_OMEGA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_9), T(KP_ENTER), END
	);
case UC_GR_LC_GAMMA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_3), T(KP_ENTER), END
	);
case UC_GR_LC_ETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_7), T(KP_ENTER), END
	);
case UC_GR_LC_XI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(E), T(KP_ENTER), END
	);
case UC_GR_LC_KAPPA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(A), T(KP_ENTER), END
	);
case UC_GR_LC_LAMDA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(B), T(KP_ENTER), END
	);
case UC_GR_LC_ZETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_6), T(KP_ENTER), END
	);
case UC_GR_LC_UPSILON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_5), T(KP_ENTER), END
	);
case UC_GR_LC_IOTA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_9), T(KP_ENTER), END
	);
case UC_GR_LC_ALPHA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_1), T(KP_ENTER), END
	);
case UC_GR_LC_EPSILON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_5), T(KP_ENTER), END
	);
case UC_GR_LC_OMICRON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(F), T(KP_ENTER), END
	);
case UC_GR_LC_SIGMA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_3), T(KP_ENTER), END
	);
case UC_GR_LC_NU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(D), T(KP_ENTER), END
	);
case UC_GR_LC_RHO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_1), T(KP_ENTER), END
	);
case UC_GR_LC_TAU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_4), T(KP_ENTER), END
	);
case UC_GR_LC_DELTA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_4), T(KP_ENTER), END
	);
case UC_GR_LC_FINAL_SIGMA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_2), T(KP_ENTER), END
	);
case UC_GR_LC_THETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_8), T(KP_ENTER), END
	);
case UC_GR_LC_BETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(KP_2), T(KP_ENTER), END
	);
case UC_GR_LC_MU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(B), T(C), T(KP_ENTER), END
	);
case UC_GR_LC_PSI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(C), T(KP_8), T(KP_ENTER), END
	);
case UC_GR_UC_CHI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_7), T(KP_ENTER), END
	);
case UC_GR_UC_PI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_0), T(KP_ENTER), END
	);
case UC_GR_UC_PHI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_6), T(KP_ENTER), END
	);
case UC_GR_UC_OMEGA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_9), T(KP_ENTER), END
	);
case UC_GR_UC_GAMMA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_3), T(KP_ENTER), END
	);
case UC_GR_UC_ETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_7), T(KP_ENTER), END
	);
case UC_GR_UC_XI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(E), T(KP_ENTER), END
	);
case UC_GR_UC_KAPPA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(A), T(KP_ENTER), END
	);
case UC_GR_UC_LAMDA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(B), T(KP_ENTER), END
	);
case UC_GR_UC_ZETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_6), T(KP_ENTER), END
	);
case UC_GR_UC_UPSILON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_5), T(KP_ENTER), END
	);
case UC_GR_UC_IOTA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_9), T(KP_ENTER), END
	);
case UC_GR_UC_ALPHA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_1), T(KP_ENTER), END
	);
case UC_GR_UC_EPSILON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_5), T(KP_ENTER), END
	);
case UC_GR_UC_OMICRON:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(F), T(KP_ENTER), END
	);
case UC_GR_UC_SIGMA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_3), T(KP_ENTER), END
	);
case UC_GR_UC_NU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(D), T(KP_ENTER), END
	);
case UC_GR_UC_RHO:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_1), T(KP_ENTER), END
	);
case UC_GR_UC_TAU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_4), T(KP_ENTER), END
	);
case UC_GR_UC_DELTA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_4), T(KP_ENTER), END
	);
case UC_GR_UC_THETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_8), T(KP_ENTER), END
	);
case UC_GR_UC_BETA:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(KP_2), T(KP_ENTER), END
	);
case UC_GR_UC_MU:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(KP_9), T(C), T(KP_ENTER), END
	);
case UC_GR_UC_PSI:
	return MACRODOWN(
		D(LCTRL), D(LSHIFT), T(U), U(LCTRL), U(LSHIFT), T(KP_0), T(KP_3), T(A), T(KP_8), T(KP_ENTER), END
	);
	    	default:
	    		break;
		}
	}
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void * matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void * matrix_scan_user(void) {
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
