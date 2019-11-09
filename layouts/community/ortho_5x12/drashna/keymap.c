#include "drashna.h"

// clang-format off
#define LAYOUT_ortho_5x12_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A,  \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
  ) \
  LAYOUT_ortho_5x12_wrapper( \
    KC_GRV,  K01,    K02,     K03,      K04,     K05,     K06,     K07,     K08,     K09,     K0A,     KC_BSPC, \
    KC_TAB,  K11,    K12,     K13,      K14,     K15,     K16,     K17,     K18,     K19,     K1A,     KC_BSPC, \
    KC_ESC,  ALT_T(K21), K22, K23,      K24,     K25,     K26,     K27,     K28,     K29,     K2A, RALT_T(KC_QUOT), \
    KC_MLSF, CTL_T(K31), K32, K33,      K34,     K35,     K36,     K37,     K38,     K39, RCTL_T(K3A), KC_ENT,  \
    KC_NO,   OS_LCTL, OS_LALT, OS_LGUI, SP_LWER, BK_LWER, DL_RAIS, ET_RAIS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
  )

#define LAYOUT_ortho_5x12_base_wrapper(...)       LAYOUT_ortho_5x12_base(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_5x12_base_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
  _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
  _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
  _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
),

[_COLEMAK] = LAYOUT_ortho_5x12_base_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
  _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
  _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
  _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
),

[_DVORAK] = LAYOUT_ortho_5x12_base_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
  _________________DVORAK_L1_________________, _________________DVORAK_R1_________________,
  _________________DVORAK_L2_________________, _________________DVORAK_R2_________________,
  _________________DVORAK_L3_________________, _________________DVORAK_R3_________________
),

[_WORKMAN] = LAYOUT_ortho_5x12_base_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,
  _________________WORKMAN_L1________________, _________________WORKMAN_R1________________,
  _________________WORKMAN_L2________________, _________________WORKMAN_R2________________,
  _________________WORKMAN_L3________________, _________________WORKMAN_R3________________
),

[_MODS] = LAYOUT_ortho_5x12_wrapper(
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  KC_LSFT, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_5x12_wrapper( \
  _______, ___________________BLANK___________________, ___________________BLANK___________________, _______,
  KC_TILD, _________________LOWER_L1__________________, _________________LOWER_R1__________________, KC_PIPE,
  KC_DEL,  _________________LOWER_L2__________________, _________________LOWER_R2__________________, _______,
  _______, _________________LOWER_L3__________________, _________________LOWER_R3__________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_5x12_wrapper( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_GRV,  _________________RAISE_L1__________________, _________________RAISE_R1__________________, _______,
  KC_DEL,  _________________RAISE_L2__________________, _________________RAISE_R2__________________, KC_BSLS,
  _______, _________________RAISE_L3__________________, _________________RAISE_R3__________________, _______,
  _______, _______, _______, _______, _______, _______, _______, _________________RAISE_R3__________________
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_5x12_wrapper( \
  KC_MAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RST,
  VRSN,    _________________ADJUST_L1_________________, _________________ADJUST_R1_________________, EEP_RST,
  _______, _________________ADJUST_L2_________________, _________________ADJUST_R2_________________, RGB_IDL,
  _______, _________________ADJUST_L3_________________, _________________ADJUST_R3_________________, TG_MODS,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};
// clang-format on
