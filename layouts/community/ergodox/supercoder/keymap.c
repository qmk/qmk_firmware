/*
 * SuperCoder 2000 layout
 */

#include QMK_KEYBOARD_H

/* Layers */

#define SC2K    0 // default layer

/* The Keymap */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Keymap 0: Base Layer
   *
   * ,-----------------------------------------------------.           ,-----------------------------------------------------.
   * |         0 |   0  |   0  |   0  |   0  |   0  |   0  |           |  1   |   1  |   1  |   1  |   1  |  1   | 1         |
   * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
   * |         0 |   0  |   0  |   0  |   0  |   0  |   0  |           |  1   |   1  |   1  |   1  |   1  |  1   | 1         |
   * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
   * |         0 |   0  |   0  |   0  |   0  |   0  |------|           |------|   1  |   1  |   1  |   1  |  1   | 1         |
   * |-----------+------+------+------+------+------|   0  |           |  1   |------+------+------+------+------+-----------|
   * |         0 |   0  |   0  |   0  |   0  |   0  |      |           |      |   1  |   1  |   1  |   1  |  1   | 1         |
   * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
   *     |     0 |   0  |   0  |   0  |   0  |                                       |   1  |   1  |   1  |  1   | 1     |
   *     `-----------------------------------'                                       `-----------------------------------'
   *                                         ,-------------.           ,-------------.
   *                                         | DONE | DONE |           | DONE | DONE |
   *                                  ,------|------|------|           |------+------+------.
   *                                  |      |      | DONE |           | DONE |      |      |
   *                                  | DONE | DONE |------|           |------| DONE | DONE |
   *                                  |      |      | DONE |           | DONE |      |      |
   *                                  `--------------------'           `--------------------'
   */
[SC2K] = LAYOUT_ergodox(
 // left hand
 KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0
,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0
,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0
,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0
,KC_0    ,KC_0    ,KC_0    ,KC_0    ,KC_0

                                             ,KC_ENT  ,KC_ENT
                                                      ,KC_ENT
                                    ,KC_ENT  ,KC_ENT  ,KC_ENT

                                                                // right hand
                                                               ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1
                                                               ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1
                                                                        ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1
                                                               ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1
                                                                                 ,KC_1    ,KC_1    ,KC_1    ,KC_1    ,KC_1

                                                               ,KC_ENT  ,KC_ENT
                                                               ,KC_ENT
                                                               ,KC_ENT  ,KC_ENT   ,KC_ENT
                  ),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
}
