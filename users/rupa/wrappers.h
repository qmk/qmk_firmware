/*
Copyright 2020 rupa <rupa@lrrr.us> @rupa

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

#pragma once
#include "rupa.h"

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define OS_RGUI OSM(MOD_RGUI)
#define OS_RALT OSM(MOD_RALT)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)

#define G_LWR   LT(_LOWER, KC_G)

#if defined(UNICODEMAP_ENABLE)
#    define CSHAPES XP(CCIR,CKEY)
#    define CUIDADO XP(CUI,HAS)
#    define NOPENAH XP(NOPE,STOP)
#    define MUSIC_A XP(M4,M8)
#    define MUSIC_B XP(M8B,M16)
#    define SMILE   XP(SMB,SMW)
#    define STARS   XP(STB,STW)
#    define YEPYEP  XP(CHEK,HUN)
#endif

/* _QWERTY
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │Es~│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│~ `│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │Del│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │RAISE │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │PgU│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │PgD│
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │Ctrl│Alt │Gui │        Space           │RAI│LOW│CAP│ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define ____65_QWERTY______________ROW1    QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV
#define ____65_QWERTY______________ROW2    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL
#define ____65_QWERTY______________ROW3    RAISE,   KC_A,    KC_S,    KC_D,    KC_F,    G_LWR,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP
#define ____65_QWERTY______________ROW4    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN
#define ____65_QWERTY______________ROW5    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    RAISE,   LOWER,   KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT

/* _RAISE
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │ ` │ ‽ │ ⸮ │   │ ¢ │   │   │   │★  │   │ ☻ │  ⃠ │CSH│  Del  │Hme│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │WAT│ ∃ │Rup│TAD│YUN│   │ ∈ │ ॐ │   │♩ ♪│♫ ♬│     │Ins│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │ ∀ │ ſ │ ⚂ │FRT│   │HUG│JOY│KSS│LOD│   │NO!│ ✓  💯  │End│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │ RShift │⚠ ☭│ ✖ │CAT│BOW│BUG│ № │MUS│DNC│ ⊢ │SHR│   McL│M↑ │McR│
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │RCtl│RAlt│RGui│          FLIP          │   │   │   │M← │M↓ │M→ │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define ____65_RAISE_______________ROW1    KC_GRV,  X(IBNG), X(IRNY), _______, X(CENT), _______, _______, _______, STARS,   _______, SMILE,   X(NEG),  CSHAPES, KC_DEL,  KC_HOME
#define ____65_RAISE_______________ROW2    _______, _______, WAT,     X(LEXI), RUPA,    TADA,    YUNO,    _______, X(LELM), X(OM),   _______, MUSIC_A, MUSIC_B, _______, KC_INS
#define ____65_RAISE_______________ROW3    _______, X(LALL), X(EFF),  DICE,    FART,    _______, HUGS,    JOY,     KISS,    LOD,     _______, NOPENAH,          YEPYEP,  KC_END
#define ____65_RAISE_______________ROW4    OS_RSFT,          CUIDADO, X(ECKS), CATS,    DOMO,    BUGS,    X(NUM),  MUSIC,   DANCE,   X(LPRO), SHRUG,   KC_BTN1, KC_MS_U, KC_BTN2
#define ____65_RAISE_______________ROW5    OS_RCTL, OS_RALT, OS_RGUI,                            FLIP,                      _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R

/* _LOWER
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │zzz│       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │u_f│u_i│u_m│u_n│usi│usn│u_s│   │   │PRT│   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │SLK│PAU│   │   │   │   │   │   │   │   │        │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │ZAL│   │CAP│VSN│   │NLK│   │   │   │   │      │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │   │ ← │ ↓ │ → │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define ____65_LOWER_______________ROW1    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ZZZZZ,   _______, _______
#define ____65_LOWER_______________ROW2    _______, U_FRACT, U_ITALI, U_MONOS, U_NORML, U_SANSI, U_SANSN, U_SCRPT, _______, _______, KC_PSCR, _______, _______, _______, _______
#define ____65_LOWER_______________ROW3    _______, _______, KC_SCRL, KC_PAUS, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______
#define ____65_LOWER_______________ROW4    _______,          ZALGO  , _______, KC_CAPS, VRSN,    _______, KC_NUM,  _______, _______, _______, _______, _______, _______, _______
#define ____65_LOWER_______________ROW5    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______

/* _ADJUST
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │r x│r m│rh+│rh-│rs+│rs-│rv+│rv-│ra+│ra-│   │   │RESET│   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │EEP RSET│   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │   │   │   │   │   │   │Mut│V- │V+ │   │U MODE│   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
 * │    │    │    │                        │   │   │   │   │   │   │
 * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
 */
#define ____65_ADJUST______________ROW1    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______
#define ____65_ADJUST______________ROW2    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______
#define ____65_ADJUST______________ROW3    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  _______
#define ____65_ADJUST______________ROW4    _______,          _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, UC_NEXT, _______, _______
#define ____65_ADJUST______________ROW5    _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______

#define ____65_ADJUST__________RGB_ROW2    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, _______, QK_BOOT, _______
#define ____65_ADJUST__________RGB_ROW3    _______, RGB_M_P, RGB_M_B, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,  _______

#define ____65_ADJUST___________BL_ROW2    _______, BL_TOGG, BL_BRTG, BL_STEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______

// clang-format on
