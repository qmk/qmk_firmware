/* Copyright 2022 Johannes Schneider (@JohSchneider) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layer_names {
    BASE, // default layer
    NPAD, // numberpad (blender)
    ARRO, // arrows and symbols
    FUNC, // F[1-10] and number key rows
    MOUS, // mouse
    GAME,
    LEDS
};

#define KC_ALDL RALT_T(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /**
       LEFT                                ╔═══════════╦══════════╦═══════════╗                 ╔═══════════╦═══════════╦═══════════╗                              RIGHT
                               ╔═══════════╣     E     ║     R    ║     T     ║     Top Row     ║     Y     ║     U     ║     I     ╠═══════════╗
       ╔═══════════╦═══════════╣     W     ╠═══════════╬══════════╬═══════════╣                 ╠═══════════╬═══════════╬═══════════╣     O     ╠═══════════╦═══════════╗
       ║           ║     Q     ╠═══════════╣     D     ║     F    ║     G     ║     Mid Row     ║     H     ║     J     ║     K     ╠═══════════╣     P     ║     [     ║
       ╠═══════════╬═══════════╣     S     ╠═══════════╬══════════╬═══════════╣                 ╠═══════════╬═══════════╬═══════════╣     L     ╠═══════════╬═══════════╣
       ║           ║     A     ╠═══════════╣     C     ║     V    ║     B     ║     Bot Row     ║     N     ║     M     ║     ,     ╠═══════════╣     ;     ║     '     ║
       ╠═══════════╬═══════════╣     X     ╠═══════════╩══════════╩═══════════╝                 ╚═══════════╩═══════════╩═══════════╣     .     ╠═══════════╬═══════════╣
       ║           ║     Z     ╠═══════════╝                                                                                        ╚═══════════╣     /     ║           ║
       ╚═══════════╩═══════════╝                                                                                                                ╚═══════════╩═══════════╝
                                                        ╔═════════╗                                         ╔═════════╗
                                           ╔═════════╗  ║4        ╠═════════╗                     ╔═════════╣3        ║  ╔═════════╗
                                           ║3        ║  ╚═════════╣5        ╠═════════╗ ╔═════════╣2        ╠═════════╝  ║4        ║  Thumb Cluster key-order
                                           ╠═════════╬═════════╗  ╚═════════╣6        ║ ║1        ╠═════════╝  ╔═════════╬═════════╣
                                           ║2        ║1        ║            ╚═════════╝ ╚═════════╝            ║6        ║5        ║
                                           ╚═════════╩═════════╝                                               ╚═════════╩═════════╝

        0           1           2           3           4           5                            0           1           2           3           4           5
       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+
       |  Layer 4  |     Q     |     W     |     E     |     R     |     T     |4   Top Row    0|     Y     |     U     |     I     |     O     |     P     |     [     |
       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+
       |  Layer 3  |     A     |     S     |     D     |     F     |     G     |5   Mid Row    1|     H     |     J     |     K     |     L     |     ;     |     '     |
       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+
       |  Layer 2  |     Z     |     X     |     C     |     V     |     B     |6   Bot Row    2|     N     |     M     |     ,     |     .     |     /     |           |
       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+

       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+
       +  Layer 1  |  Backsp   |   Delete  |  L Shift  |   L Ctrl  |   L Alt   |7 Thumb Clstr  3+  Layer 1  |  Backsp   |   Delete  |  Space    |   Enter   |   Tab     |
       +-----------+-----------+-----------+-----------+-----------+-----------+                +-----------+-----------+-----------+-----------+-----------+-----------+
                   |           |           |           |           |                                        |           |           |           |           |
                   |           |           |           |           |                                        |           |           |           |           |
    */
    [BASE] = LAYOUT( // Base
        //left                                                                                   //right
        KC_ESC     ,KC_Q       ,KC_W       ,KC_E       ,KC_R       ,KC_T,                        KC_Y       ,KC_U       ,KC_I       ,KC_O       ,KC_P       ,KC_MINUS,
        KC_TAB     ,KC_A       ,KC_S       ,KC_D       ,KC_F       ,KC_G,                        KC_H       ,KC_J       ,KC_K       ,KC_L       ,KC_SCLN    ,KC_QUOT,
        KC_LSFT    ,KC_Z       ,KC_X       ,KC_C       ,KC_V       ,KC_B,                        KC_N       ,KC_M       ,KC_COMM    ,KC_DOT     ,KC_SLSH    ,KC_EQUAL,
        TG(GAME)   ,MO(NPAD)   ,KC_BSPC    ,KC_LALT    ,KC_LCTL    ,KC_LSFT,                     KC_RSFT    ,KC_ENT     ,KC_SPC     ,KC_ALDL    ,MO(ARRO)   ,MO(FUNC)
        ),
    [NPAD] = LAYOUT(// numpad (blender)
        //left                                                                                   //right
        KC_TRNS    ,KC_KP_PLUS ,KC_KP_7    ,KC_KP_8    ,KC_KP_9    ,KC_KP_SLASH,                 KC_TRNS    ,KC_TRNS    ,KC_MPRV    ,KC_MPLY    ,KC_MNXT    ,KC_TRNS,
        KC_TRNS    ,KC_KP_MINUS,KC_KP_4    ,KC_KP_5    ,KC_KP_6    ,KC_KP_ASTERISK,              KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_KP_0    ,KC_KP_1    ,KC_KP_2    ,KC_KP_3    ,KC_KP_COMMA,                 KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_LOCK    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),
    [FUNC] = LAYOUT(// function and numbers
        //left                                                                                   //right
        KC_TRNS    ,KC_F1      ,KC_F2      ,KC_F3      ,KC_F4      ,KC_F5,                       KC_F6      ,KC_F7      ,KC_F8      ,KC_F9      ,KC_F10     ,KC_TRNS,
        KC_TRNS    ,KC_1       ,KC_2       ,KC_3       ,KC_4       ,KC_5,                        KC_6       ,KC_7       ,KC_8       ,KC_9       ,KC_0       ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),//       |           |           |           |           |
    [ARRO] = LAYOUT(// arrow and symbols   |           |           |
        //left                                                                                   //right
        KC_TRNS    ,KC_EXLM    ,KC_AT      ,KC_LCBR    ,KC_RCBR    ,KC_PIPE,                     KC_MPRV    ,KC_MPLY    ,KC_MNXT    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_HASH    ,KC_DLR     ,KC_LBRC    ,KC_RBRC    ,KC_GRV,                      KC_TRNS    ,KC_LEFT    ,KC_UP      ,KC_RIGHT   ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_PERC    ,KC_CIRC    ,KC_LPRN    ,KC_RPRN    ,KC_TILD,                     KC_TRNS    ,KC_TRNS    ,KC_DOWN    ,KC_TRNS    ,KC_BSLS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),//       |           |           |           |           |
    [MOUS] = LAYOUT(// Mouse   |           |           |           |
        //left                                                                                   //right
        KC_TRNS    ,KC_WH_U    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_WH_D    ,KC_MS_L    ,KC_MS_UP   ,KC_MS_R    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_MS_DOWN ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_LOCK    ,KC_LGUI    ,KC_TRNS    ,KC_MS_BTN1 ,KC_MS_BTN2 ,KC_BTN3,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),
    [LEDS] = LAYOUT( /* RGBLIGHT */
        //left                                                                                   //right
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,RGB_TOG    ,RGB_MOD    ,RGB_HUI    ,RGB_HUD    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,RGB_SAI    ,RGB_SAD    ,RGB_VAI    ,RGB_VAD    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                     KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS
        ),
    [GAME] = LAYOUT(//         |           |           |           |
        // gaming, with shifted WASD block
        //left                                                                                    //right
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                      KC_MPRV    ,KC_MPLY    ,KC_MNXT    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_A       ,KC_W       ,KC_D       ,KC_TRNS,                      KC_TRNS    ,KC_LEFT    ,KC_UP      ,KC_RIGHT   ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_Q       ,KC_S       ,KC_E       ,KC_TRNS,                      KC_TRNS    ,KC_TRNS    ,KC_DOWN    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,
        KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS    ,KC_TRNS,                      KC_Q       ,KC_E       ,KC_SPC     ,KC_TAB     ,KC_TRNS    ,KC_TRNS
        ) //       |           |           |           |           |
};
