/* 默认键位：与 CircuitPython 固件出厂默认保持一致（9 键版）
 *   键1 Esc / 键2 F1 / 键3 F2 / 键4 F3 / 键5 Tab
 *   键6 Ctrl+C / 键7 Ctrl+V / 键8 Enter / 键9 ↑
 *   （原键10 已拆掉，第二排由 4 键组成，整体右移半个键位）
 *
 * 灯光调节：按住键1（Esc 位）不动 -> 进入第 2 层，其余键变成灯效控制键。
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE = 0,
    _RGB,
};

/* 短按发 Esc，长按切到灯光控制层 */
#define RGB_LAYER_KEY LT(_RGB, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        RGB_LAYER_KEY, KC_F1, KC_F2, KC_F3, KC_TAB,
        LCTL(KC_C), LCTL(KC_V), KC_ENT, KC_UP),

    [_RGB] = LAYOUT(
        _______, RM_TOGGLE, RM_NEXT, RM_PREV, RM_SPDU,
        RM_SPDD, RM_VALU, RM_VALD, RM_HUEU),
};
