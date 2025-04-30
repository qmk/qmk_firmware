
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


//       ┏━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┳━━━━━━━┓
//       ┃  ESC  ┃   1   ┃   2   ┃   3   ┃   4   ┃   5   ┃   6   ┃   7   ┃   8   ┃   9   ┃   0   ┃  -_   ┃  +=   ┃   `~  ┃
//       ┣━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┫
//       ┃  TAB  ┃   Q   ┃   W   ┃   E   ┃   R   ┃   T   ┃   Y   ┃   U   ┃   I   ┃   O   ┃   P   ┃  [{   ┃  ]}   ┃  '"   ┃
//       ┗━━━┳━━━┻━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━╋━━━━━━━┻━━┳━━━━┻━━━┳━━━┛
//           ┃  CAPSLOCK ┃   A   ┃   S   ┃   D   ┃   F   ┃   G   ┃   H   ┃   J   ┃   K   ┃   L   ┃   ENTER  ┃   ;:   ┃ 
//           ┗━━━┳━━━━━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━┳━━━┻━━━━━━━┻━┳━━━━━━━━┻━━━━┳━━━┛
//               ┃   SHIFT   ┃   Z   ┃   X   ┃   C   ┃   V   ┃   B   ┃   N   ┃   M   ┃   MOUSE1    ┃   MOUSE2    ┃
//               ┗━━━┳━━━━━━━┻┳━━━━━━┻━┳━━━━━┻━━┳━━━━┻━━━┳━━━┻━━━━┳━━┻━━━━━┳━┻━━━━━━┳┻━━━━━━━━━━━━━┻┳━━━━━━━━┳━━━┛
//                   ┃  CTRL  ┃  LGUI  ┃  LALT  ┃   ,<   ┃   .>   ┃   /?   ┃   \|   ┃      SPC      ┃  BACK  ┃
//                   ┗━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━┛
//                                     ┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓
//                                     ┃  MOUSE3 ┃    →    ┃    ↓    ┃    ←    ┃    ↑    ┃
//                                     ┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛


    [0] = LAYOUT(
        //     ESC        1        2        3        4        5        6        7        8        9        0        -        =        `
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_GRAVE,
        //     TAB        Q        W        E        R        T        Y        U        I        O        P        [        ]        '
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_QUOTE,
        //         CAPS        A        S        D        F        G        H        J        K        L        ;        ENTER
        KC_CAPS_LOCK, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_ENTER, KC_SEMICOLON,
        //             LSHIFT        Z        X        C        V        B        N        M        MOUSE1        MOUSE2
        KC_LEFT_SHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, QK_MOUSE_BUTTON_1, QK_MOUSE_BUTTON_2,
        //               LCTRL        LGUI        LALT        ,        .        /        \        SPC        BACKSPACE
        KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT, KC_COMMA, KC_DOT, KC_SCLN, KC_BSLS, KC_SPC, KC_BACKSPACE,
        //         MOUSE3             →        ↓        ←      ↑
        QK_MOUSE_BUTTON_3, KC_RIGHT, KC_DOWN, KC_LEFT, KC_UP)
    };

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Encoders: Left, Right, Big
    [0] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD)}
};
#endif
