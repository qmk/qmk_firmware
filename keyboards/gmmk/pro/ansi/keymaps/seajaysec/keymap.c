/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>, Chris Farrell
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
#include "seajaysec.h"

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [JK_ESC] = COMBO(jk_combo, KC_ESC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
    [LINUX] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,   TT_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // Subbing in a numpad here since Linux is the same layout
    [WINDOWS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, KC_TAB,  KC_P4,   KC_P5,   KC_P6,   KC_PDOT, _______, _______, _______,          KC_HOME,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_NO,   KC_PAST,          KC_PENT,          KC_END,
        _______,          KC_NO,   KC_DEL,  KC_INS,  KC_NO,   KC_NO,   KC_NO,   KC_P0,   KC_P0,   KC_PDOT, KC_PSLS,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [MACOS] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, RGB_VAD, RGB_VAI, RGB_HUD, RGB_HUI, RGB_MOD, RGB_RMOD,KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, _______,          KC_MPLY,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, KC_LALT, KC_LGUI,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [FUNCTIONS] = LAYOUT(
        _______, KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_LINX, KC_MAC,  KC_WIN,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_RST,          _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          KC_RGBH, KC_RGBS, KC_RGBV, KC_RGBE, KC_RGBP, KC_WRGB, _______, _______, _______, _______,          _______, _______, KC_HOME,
        _______, _______, _______,                            RGB_TOG,                            _______, _______, _______, _______, _______, _______
    ),
    // Not used at present
    [GIT] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,  G_DIFF, _______, _______, _______, _______, _______, _______,  G_PULL,   G_PUSH, _______, _______,         _______,
        _______,   G_ADD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, G_CHECK, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),
};

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

#define ______ {0, 0, 0}

const ledmap PROGMEM ledmaps[] = {
         //  LU = Left Underglow, RU = Right Underglow
         //  LU_1    ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)  RU_1
         //  LU_2    ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del       RU_2
         //  LU_3    Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp         RU_3
         //  LU_4    Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn         RU_4
         //  LU_5    Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End          RU_5
         //  LU_6    Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right        RU_6
    [LINUX] = RGB_MATRIX_LAYOUT_LEDMAP(
          PURPLE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    PURPLE,
          PURPLE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    PURPLE,
          PURPLE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    PURPLE,
          PURPLE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    PURPLE,
          PURPLE,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    PURPLE,
          PURPLE,    ______, PURPLE, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    PURPLE
    ),
    [WINDOWS] = RGB_MATRIX_LAYOUT_LEDMAP(
          GREEN,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    GREEN,
          GREEN,    ______, ______, ______, ______, ______, ______, ______,  GREEN,  GREEN,  GREEN, YELLOW, YELLOW, ______, ______,         ______,    GREEN,
          GREEN,    ______, PURPLE,   BLUE, PURPLE,   GOLD, ______,   GOLD,  GREEN,  GREEN, PURPLE, ______, ______, ______, ______,         PURPLE,    GREEN,
          GREEN,    ______,   BLUE,   BLUE,   BLUE,   GOLD, ______, ______,  GREEN,  GREEN, ______, ______, YELLOW,           TURQ,         PURPLE,    GREEN,
          GREEN,    ______,         ______,    RED,    RED, ______, ______,  GREEN,  GREEN, PURPLE, ______, YELLOW,         ______, ______, ______,    GREEN,
          GREEN,    ______,  GREEN, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    GREEN
    ),
    [MACOS] = RGB_MATRIX_LAYOUT_LEDMAP(
          GOLD,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    GOLD,
          GOLD,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    GOLD,
          GOLD,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    GOLD,
          GOLD,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    GOLD,
          GOLD,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    GOLD,
          GOLD,    ______, ______,   GOLD,                         ______,                         ______, ______, ______, ______, ______, ______,    GOLD
    ),

    [FUNCTIONS] = RGB_MATRIX_LAYOUT_LEDMAP(
          CYAN,     TURQ,   TURQ,   TURQ,   TURQ,   TURQ,   TURQ, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    CYAN,
          CYAN,   ______, PURPLE,  GREEN,   GOLD, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,           GOLD,    CYAN,
          CYAN,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,   TEAL,         ______,    CYAN,
          CYAN,     TURQ, ______, ______, ______, ______,   TURQ, ______, ______, ______, ______, ______, ______,         ______,         ______,    CYAN,
          CYAN,   ______,          GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN, ______, ______, ______, ______,         ______, ______,   GOLD,    CYAN,
          CYAN,   ______, ______,   CYAN,                         ______,                         ______, ______, ______, ______, ______, ______,    CYAN
    ),
};

#endif // RGB_MATRIX_LEDMAPS_ENABLED
// clang-format on
