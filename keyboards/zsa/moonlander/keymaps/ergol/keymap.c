/*
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

#include QMK_KEYBOARD_H

#include <stdint.h>

#include "keycodes.h"
#include "version.h"

#ifdef FR_HOST
#    include "keymap_french.h"
// redefine the ascii_to_keycode so that
// the register_unicode works.
#    include "sendstring_french.h"
#else
#    include "send_string.h"
#endif

#include "unicode/unicode.h"

/*
** Implementation notes:
** Ergol breaks the usual association between keys, for instance that the
** shifted version of = is +. Thus defining a simple keymap is not enough and it
** requires more work.
**
** The approach taken in this keymap is to define the set of custom keycode
** Ergol uses, associate it to a (non optimized, space waste) structure and
** depending on whether we're on the dead key or the code layer we select a
** specific key code to send.
**
** The problem with this approach is that it makes impossible to use tap/TL/etc
** features which only works on the basic keycode set.
**
** The assumption are:
** - Base keycode is always "simple" and the shifted version is the same.
** - Dead key layer have different base and shifted keycode and might be unicode.
** - Code layer is the same as the Dead key one.
**
** Regarding the unicode, the simplest solution turned to use register_unicode
** (which expects a uint32_t) and a mask is used to differentiate whether it is
** a simple key code or an unicode sequence we want to send.
**
** The Dead key layer does not stay active even if the dead key is maintained
** pressed, it will wait for the next key and revert to the previous layer.
**
** The Dead key layer is empty and uses transparent to fallback on the base
** layer. It avoids defining custom keys by layer and seems simpler. If the keymap
** is too big, it would be worth spliting it in three.
**
**
*/

enum layers {
    ERGOL,
    ERGOL_1DK,
    ERGOL_CODE,
};

enum custom_keycodes {
    EKC_FIRST = SAFE_RANGE,
    EKC_Q     = SAFE_RANGE,
    EKC_C,
    EKC_O,
    EKC_P,
    EKC_W,

    EKC_J,
    EKC_M,
    EKC_D,
    EKC_DK,
    EKC_Y,

    EKC_A,
    EKC_S,
    EKC_E,
    EKC_N,
    EKC_F,

    EKC_L,
    EKC_R,
    EKC_T,
    EKC_I,
    EKC_U,

    EKC_Z,
    EKC_X,
    EKC_MNS,
    EKC_V,
    EKC_B,

    EKC_DOT,
    EKC_H,
    EKC_G,
    EKC_COMM,
    EKC_K,

    EKC_SPC,

    EKC_0,
    EKC_1,
    EKC_2,
    EKC_3,
    EKC_4,
    EKC_5,
    EKC_6,
    EKC_7,
    EKC_8,
    EKC_9,

    EKC_MAX
};

void keyboard_post_init_user(void) {
    /* debug_enable   = true; */
    /* debug_matrix   = true; */
    /* debug_keyboard = true; */
    // debug_mouse=true;
}

// https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
// https://github.com/qmk/qmk_firmware/blob/master/docs/features/unicode.md#basic-configuration-basic-configuration
//

#define IDX(KC) (KC - SAFE_RANGE)

typedef struct {
    uint16_t base;
    uint32_t s_base;

    uint32_t dkey;
    uint32_t s_dkey;

    uint32_t code;
    uint32_t s_code;
} ergol_key_t;

#define EGL(B, DK, SDK, C, SC)                                                            \
    (ergol_key_t) {                                                                       \
        .base = B, .s_base = KC_TRNS, .dkey = DK, .s_dkey = SDK, .code = C, .s_code = SC, \
    }

#define EGL_WITH_SBASE(B, SB, DK, SDK, C, SC)                                        \
    (ergol_key_t) {                                                                  \
        .base = B, .s_base = SB, .dkey = DK, .s_dkey = SDK, .code = C, .s_code = SC, \
    }

#define ________ \
    {            \
        {}       \
    }

static const uint32_t CP_MASK     = (UINT32_C(1) << 31);
static const uint32_t CP_VAL_MASK = (UINT32_C(1) << 31) - 1;
#define CP(x) (x | (UINT32_C(1) << 31)) /* in C, const is not a constant expression */

static inline bool is_cp(uint32_t cp) {
    return (cp & CP_MASK) == CP_MASK;
}

static inline uint32_t cp_val(uint32_t cp) {
    return (cp & CP_VAL_MASK);
}

#ifdef FR_HOST
// clang-format off
const ergol_key_t ergol_key_maps[IDX(EKC_MAX)] = {
    [IDX(EKC_Q)] = EGL(FR_Q,       CP(0x00E2) /* â */, CP(0x00C2) /* Â */, CP(0x005E) /* ^ */,    CP(0x0302) /* ̂  Combining Circumflex Accent */),
    [IDX(EKC_C)] = EGL(FR_C,       FR_CCED /* ç */,    CP(0x00C7) /* Ç */, FR_LABK,    CP(0x2264) /* ≤ */),
    [IDX(EKC_O)] = EGL(FR_O,       CP(0x0153) /* œ */, CP(0x0152) /* Œ */, FR_RABK,    CP(0x2265) /* ≥ */),
    [IDX(EKC_P)] = EGL(FR_P,       CP(0x00F4) /* ô */, CP(0x00D4) /* Ô */, FR_DLR,     KC_TRNS), // XXX: Implement currencies
    [IDX(EKC_W)] = EGL(FR_W,       KC_TRNS,            KC_TRNS,            FR_PERC,    CP(0x2030) /* ‰ */),

    [IDX(EKC_J)] = EGL(FR_J,       KC_TRNS,            KC_TRNS,            FR_AT,      CP(0x030A) /* ̊  Combining Ring Above */),
    [IDX(EKC_M)] = EGL(FR_M,       CP(0x00B5) /* µ */, KC_TRNS,            FR_AMPR,    KC_TRNS),
    [IDX(EKC_D)] = EGL(FR_D,       FR_UNDS,            KC_TRNS,            FR_ASTR,    CP(0x00D7) /* × */),
    [IDX(EKC_DK)] = EGL_WITH_SBASE(KC_TRNS, KC_EXLM,   KC_TRNS,            CP(0x00A1) /* ¡ */,    FR_QUOT,   CP(0x0301) /* ´ Combining Acute Accent*/),
    [IDX(EKC_Y)] = EGL(FR_Y,       CP(0x00FB),         CP(0x00DB),         FR_GRV,     CP(0x0300) /* ̀  Combining Grave Accent */),

    [IDX(EKC_A)] = EGL(FR_A,       FR_AGRV,            CP(0x00C0),         FR_LCBR,    CP(0x0306) /* ̆  Combining Breve*/),
    [IDX(EKC_S)] = EGL(FR_S,       FR_EACU,            CP(0x00DB),         FR_LPRN,    KC_TRNS),
    [IDX(EKC_E)] = EGL(FR_E,       FR_EGRV,            CP(0x00C8),         FR_RPRN,    KC_TRNS),
    [IDX(EKC_N)] = EGL(FR_N,       CP(0x00EA) /* ê */, CP(0x00CA),         FR_RCBR,    CP(0x0307) /* ̇  Combining Dot Above*/),
    [IDX(EKC_F)] = EGL(FR_F,       CP(0x00F1) /* ñ */, CP(0x00D1),         FR_EQL,     CP(0x2260) /* ≠ */),

    [IDX(EKC_L)] = EGL(FR_L,       FR_LPRN,            KC_TRNS,            FR_BSLS,    CP(0x0338) /* ̸ Combining Long Solidus Overlay */),
    [IDX(EKC_R)] = EGL(FR_R,       FR_RPRN,            KC_TRNS,            FR_PLUS,    CP(0x2A72) /* ⩲ */),
    [IDX(EKC_T)] = EGL(FR_T,       CP(0x00EE) /* î */, CP(0x00CE) /* Î */, FR_MINS,    CP(0x0304) /* ̄  Combining Macron */),
    [IDX(EKC_I)] = EGL(FR_I,       CP(0x00EF) /* ï */, CP(0x00CF) /* Ï */, FR_SLSH,    CP(0x00F7) /* ÷ */),
    [IDX(EKC_U)] = EGL(FR_U,       CP(0x00F9) /* ù */, CP(0x00D9) /* Ù */, FR_DQUO,    CP(0x030B) /* ̋  Combining Double Acute Accent */),

    [IDX(EKC_Z)] = EGL(FR_Z,       CP(0x00E6) /* æ */, CP(0x00C6) /* Æ */, FR_TILD,    CP(0x0303) /* ̃  Combining Tilde*/),
    [IDX(EKC_X)] = EGL(FR_X,       KC_TRNS,            KC_TRNS,            FR_LBRC,    CP(0x0326) /* ̦  Combining Comma Below */),
    [IDX(EKC_MNS)] = EGL_WITH_SBASE(FR_MINS,  FR_QUES, KC_TRNS, KC_TRNS,   FR_RBRC,    CP(0x0328) /* ̨  Combining Ogonek */),
    [IDX(EKC_V)] = EGL(FR_V,       KC_TRNS,            KC_TRNS,            FR_UNDS,    CP(0x2013) /* – en dash */),
    [IDX(EKC_B)] = EGL(FR_B,       KC_TRNS,            KC_TRNS,            FR_HASH,     KC_TRNS),

    [IDX(EKC_DOT)] = EGL_WITH_SBASE(FR_DOT,   FR_COLN,  CP(0x2026) /* … */,KC_TRNS,    FR_PIPE,   CP(0x00A6) /* ¦ Broken bar */),
    [IDX(EKC_H)] = EGL(FR_H,       KC_TRNS,           KC_TRNS,             FR_EXLM,    CP(0x00AC) /* ¬ Not sign */),
    [IDX(EKC_G)] = EGL(FR_G,       KC_TRNS,           KC_TRNS,             FR_SCLN,    CP(0x0312) /*̒ Combining Turned Comma Above */),
    [IDX(EKC_COMM)] = EGL_WITH_SBASE(FR_COMM, FR_SCLN,CP(0x00B7) /* · */,  CP(0x2022) /* • */,   FR_COLN, KC_TRNS),
    [IDX(EKC_K)] = EGL(FR_K,       KC_TRNS,           KC_TRNS,           FR_QUES,   CP(0x0306) /* ̆  Combining Breve */),


    [IDX(EKC_1)] = EGL_WITH_SBASE(FR_1,       CP(0x20AC) /* € */, CP(0x201E) /* „ */, CP(0x201A) /* ‚ */,  CP(0x2081) /* ₁ */, CP(0x00B9) /* ¹ */),
    [IDX(EKC_2)] = EGL_WITH_SBASE(FR_2,       CP(0x00AB) /* « */, CP(0x201C) /* “ */, CP(0x2018) /* ‘ */,  CP(0x2082) /* ₂ */, CP(0x00B2) /* ² */),
    [IDX(EKC_3)] = EGL_WITH_SBASE(FR_3,       CP(0x00BB) /* » */, CP(0x201F) /* ” */, CP(0x2019) /* ’ */,  CP(0x2083) /* ₃ */, CP(0x00B3) /* ³ */),
    [IDX(EKC_4)] = EGL_WITH_SBASE(FR_4,       FR_DLR,             CP(0x00A2) /* ¢ */, KC_TRNS,             CP(0x2084) /* … */, CP(0x2074) /* … */),
    [IDX(EKC_5)] = EGL_WITH_SBASE(FR_5,       FR_PERC,            CP(0x2030) /* ‰ */, KC_TRNS,             CP(0x2085) /* … */, CP(0x2075) /* … */),
    [IDX(EKC_6)] = EGL_WITH_SBASE(FR_6,       CP(0x005E) /* ^ */, KC_TRNS,            KC_TRNS,             CP(0x2086) /* … */, CP(0x2076) /* … */),

    [IDX(EKC_7)] = EGL_WITH_SBASE(FR_7,       FR_AMPR,            KC_TRNS,            KC_TRNS,             CP(0x2087) /* … */, CP(0x2077) /* … */),
    [IDX(EKC_8)] = EGL_WITH_SBASE(FR_8,       FR_ASTR,            FR_SECT    /* § */, KC_TRNS,             CP(0x2088) /* … */, CP(0x2078) /* … */),
    [IDX(EKC_9)] = EGL_WITH_SBASE(FR_9,       FR_HASH,            CP(0x00B6) /* ¶ */, KC_TRNS,             CP(0x2089) /* … */, CP(0x2079) /* … */),
    [IDX(EKC_0)] = EGL_WITH_SBASE(FR_0,       FR_AT,              FR_DEG,             KC_TRNS,             CP(0x2080) /* … */, CP(0x2070) /* … */),

    [IDX(EKC_SPC)] = EGL_WITH_SBASE(KC_SPC,    CP(0x202F) /* no-break-space */,  CP(0x2019) /* ’ Right Single Quotation Mark, Apostrophe*/, KC_TRNS, KC_SPC, KC_TRNS),
};
// clang-format on
#else
// clang-format off
const ergol_key_t ergol_key_maps[IDX(EKC_MAX)] = {
    [IDX(EKC_Q)] = EGL(KC_Q,       CP(0x00E2) /* â */, CP(0x00C2) /* Â */, KC_CIRC,    CP(0x0302) /* ̂  Combining Circumflex Accent */),
    [IDX(EKC_C)] = EGL(KC_C,       CP(0x00E7) /* ç */, CP(0x00C7) /* Ç */, KC_LABK,    CP(0x2264) /* ≤ */),
    [IDX(EKC_O)] = EGL(KC_O,       CP(0x0153) /* œ */, CP(0x0152) /* Œ */, KC_RABK,    CP(0x2265) /* ≥ */),
    [IDX(EKC_P)] = EGL(KC_P,       CP(0x00F4) /* ô */, CP(0x00D4) /* Ô */, KC_DLR,     KC_TRNS), // XXX: Implement currencies
    [IDX(EKC_W)] = EGL(KC_W,       KC_TRNS,            KC_TRNS,            KC_PERC,    CP(0x2030) /* ‰ */),

    [IDX(EKC_J)] = EGL(KC_J,       KC_TRNS,            KC_TRNS,            KC_AT,      CP(0x030A) /* ̊  Combining Ring Above */),
    [IDX(EKC_M)] = EGL(KC_M,       CP(0x00B5) /* µ */, KC_TRNS,            KC_AMPR,    KC_TRNS),
    [IDX(EKC_D)] = EGL(KC_D,       KC_UNDS,            KC_TRNS,            KC_ASTR,    CP(0x00D7) /* × */),
    [IDX(EKC_DK)] = EGL_WITH_SBASE(KC_TRNS, KC_EXLM,   KC_TRNS,            CP(0x00A1) /* ¡ */,    KC_QUOT,   CP(0x0301) /* ´ Combining Acute Accent*/),
    [IDX(EKC_Y)] = EGL(KC_Y,       CP(0x00FB),         CP(0x00DB),         KC_GRV,     CP(0x0300) /* ̀  Combining Grave Accent */),

    [IDX(EKC_A)] = EGL(KC_A,       CP(0x00E0) /* à */, CP(0x00C0),         KC_LCBR,    CP(0x0306) /* ̆  Combining Breve*/),
    [IDX(EKC_S)] = EGL(KC_S,       CP(0x00E9) /* é */, CP(0x00DB),         KC_LPRN,    KC_TRNS),
    [IDX(EKC_E)] = EGL(KC_E,       CP(0x00E8) /* è */, CP(0x00C8),         KC_RPRN,    KC_TRNS),
    [IDX(EKC_N)] = EGL(KC_N,       CP(0x00EA) /* ê */, CP(0x00CA),         KC_RCBR,    CP(0x0307) /* ̇  Combining Dot Above*/),
    [IDX(EKC_F)] = EGL(KC_F,       CP(0x00F1) /* ñ */, CP(0x00D1),         KC_EQL,     CP(0x2260) /* ≠ */),

    [IDX(EKC_L)] = EGL(KC_L,       KC_LPRN,            KC_TRNS,            KC_BSLS,    CP(0x0338) /* ̸ Combining Long Solidus Overlay */),
    [IDX(EKC_R)] = EGL(KC_R,       KC_RPRN,            KC_TRNS,            KC_PLUS,    CP(0x2A72) /* ⩲ */),
    [IDX(EKC_T)] = EGL(KC_T,       CP(0x00EE) /* î */, CP(0x00CE) /* Î */, KC_MINS,    CP(0x0304) /* ̄  Combining Macron */),
    [IDX(EKC_I)] = EGL(KC_I,       CP(0x00EF) /* ï */, CP(0x00CF) /* Ï */, KC_SLSH,    CP(0x00F7) /* ÷ */),
    [IDX(EKC_U)] = EGL(KC_U,       CP(0x00F9) /* ù */, CP(0x00D9) /* Ù */, KC_DQUO,    CP(0x030B) /* ̋  Combining Double Acute Accent */),

    [IDX(EKC_Z)] = EGL(KC_Z,       CP(0x00E6) /* æ */, CP(0x00C6) /* Æ */, KC_TILD,    CP(0x0303) /* ̃  Combining Tilde*/),
    [IDX(EKC_X)] = EGL(KC_X,       KC_TRNS,            KC_TRNS,            KC_LBRC,    CP(0x0326) /* ̦  Combining Comma Below */),
    [IDX(EKC_MNS)] = EGL_WITH_SBASE(KC_MINS,  KC_QUES, KC_TRNS, KC_TRNS,   KC_RBRC,    CP(0x0328) /* ̨  Combining Ogonek */),
    [IDX(EKC_V)] = EGL(KC_V,       KC_TRNS,            KC_TRNS,            KC_UNDS,    CP(0x2013) /* – en dash */),
    [IDX(EKC_B)] = EGL(KC_B,       KC_TRNS,            KC_TRNS,            KC_HASH,     KC_TRNS),

    [IDX(EKC_DOT)] = EGL_WITH_SBASE(KC_DOT,   KC_COLN,  CP(0x2026) /* … */,KC_TRNS,    KC_PIPE,   CP(0x00A6) /* ¦ Broken bar */),
    [IDX(EKC_H)] = EGL(KC_H,       KC_TRNS,           KC_TRNS,             KC_EXLM,    CP(0x00AC) /* ¬ Not sign */),
    [IDX(EKC_G)] = EGL(KC_G,       KC_TRNS,           KC_TRNS,             KC_SCLN,    CP(0x0312) /*̒ Combining Turned Comma Above */),
    [IDX(EKC_COMM)] = EGL_WITH_SBASE(KC_COMM, KC_SCLN,CP(0x00B7) /* · */,  CP(0x2022) /* • */,   KC_COLN, KC_TRNS),
    [IDX(EKC_K)] = EGL(KC_K,       KC_TRNS,           KC_TRNS,           KC_QUES,   CP(0x0306) /* ̆  Combining Breve */),


    [IDX(EKC_1)] = EGL_WITH_SBASE(KC_1,       CP(0x20AC) /* € */, CP(0x201E) /* „ */, CP(0x201A) /* ‚ */,  CP(0x2081) /* ₁ */, CP(0x00B9) /* ¹ */),
    [IDX(EKC_2)] = EGL_WITH_SBASE(KC_2,       CP(0x00AB) /* « */, CP(0x201C) /* “ */, CP(0x2018) /* ‘ */,  CP(0x2082) /* ₂ */, CP(0x00B2) /* ² */),
    [IDX(EKC_3)] = EGL_WITH_SBASE(KC_3,       CP(0x00BB) /* » */, CP(0x201F) /* ” */, CP(0x2019) /* ’ */,  CP(0x2083) /* ₃ */, CP(0x00B3) /* ³ */),
    [IDX(EKC_4)] = EGL_WITH_SBASE(KC_4,       KC_DLR,             CP(0x00A2) /* ¢ */, KC_TRNS,             CP(0x2084) /* … */, CP(0x2074) /* … */),
    [IDX(EKC_5)] = EGL_WITH_SBASE(KC_5,       KC_PERC,            CP(0x2030) /* ‰ */, KC_TRNS,             CP(0x2085) /* … */, CP(0x2075) /* … */),
    [IDX(EKC_6)] = EGL_WITH_SBASE(KC_6,       KC_CIRC,            KC_TRNS,            KC_TRNS,             CP(0x2086) /* … */, CP(0x2076) /* … */),

    [IDX(EKC_7)] = EGL_WITH_SBASE(KC_7,       KC_AMPR,            KC_TRNS,            KC_TRNS,             CP(0x2087) /* … */, CP(0x2077) /* … */),
    [IDX(EKC_8)] = EGL_WITH_SBASE(KC_8,       KC_ASTR,            CP(0x00A7) /* § */, KC_TRNS,             CP(0x2088) /* … */, CP(0x2078) /* … */),
    [IDX(EKC_9)] = EGL_WITH_SBASE(KC_9,       KC_HASH,            CP(0x00B6) /* ¶ */, KC_TRNS,             CP(0x2089) /* … */, CP(0x2079) /* … */),
    [IDX(EKC_0)] = EGL_WITH_SBASE(KC_0,       KC_AT,              CP(0x00B0) /* ° */, KC_TRNS,             CP(0x2080) /* … */, CP(0x2070) /* … */),

    [IDX(EKC_SPC)] = EGL_WITH_SBASE(KC_SPC,    CP(0x202F) /* no-break-space */,  CP(0x2019) /* ’ Right Single Quotation Mark, Apostrophe*/, KC_TRNS, KC_SPC, KC_TRNS),
};
// clang-format on
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ERGOL] = LAYOUT(
        _______,  EKC_1 ,  EKC_2 ,  EKC_3 ,  EKC_4 ,  EKC_5 , _______,           _______,  EKC_6 ,  EKC_7,   EKC_8 ,  EKC_9 ,  EKC_0 , QK_BOOT,
        _______,  EKC_Q ,  EKC_C ,  EKC_O ,  EKC_P ,  EKC_W , KC_DEL ,           KC_BSPC,  EKC_J ,  EKC_M ,  EKC_D , EKC_DK ,  EKC_Y , _______,
        _______,  EKC_A ,  EKC_S ,  EKC_E ,  EKC_N ,  EKC_F , _______,           _______,  EKC_L ,  EKC_R ,  EKC_T ,  EKC_I ,  EKC_U , _______,
  KC_LEFT_SHIFT,  EKC_Z ,  EKC_X , EKC_MNS,  EKC_V ,  EKC_B ,                             EKC_DOT,  EKC_H ,  EKC_G ,EKC_COMM,  EKC_K , _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                           MO(ERGOL_CODE), _______, _______,     _______, KC_ENTER, EKC_SPC
    ),


    [ERGOL_1DK] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),


    [ERGOL_CODE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

};
// clang-format on

static inline void tap_press_or_release(bool pressed, bool shifted, ergol_key_t *key) {
    uint32_t keycode;
    bool     erase_shift;

    switch (get_highest_layer(layer_state)) {
#define SET_KC(kc, skc)              \
    if (shifted && skc != KC_TRNS) { \
        keycode     = skc;           \
        erase_shift = true;          \
    } else {                         \
        keycode     = kc;            \
        erase_shift = false;         \
    }
        default:
        case ERGOL:
            SET_KC(key->base, key->s_base);
            break;
        case ERGOL_1DK:
            SET_KC(key->dkey, key->s_dkey);
            break;
        case ERGOL_CODE:
            SET_KC(key->code, key->s_code);
            break;
#undef SET_KC
    }

    if (pressed && is_cp(keycode)) {
        uint8_t temp_mod = get_mods();
        clear_mods();
        keycode = cp_val(keycode);
        register_unicode(keycode);
        set_mods(temp_mod);
        return;
    }

    if (keycode == KC_TRNS) return;

    if (pressed) {
        // erase_shift is true if the ergol_keycode has a specific version of
        // the keycode to actually send when shift is also pressed.
        // For instance let say that the shifted version of `a` is `b` in
        // Ergo-l, the ergo keycode would contain: base: `a`, s_base: `b`, but
        // we would get `B` printed because shift is also sent.
        if (erase_shift) {
            del_mods(MOD_BIT(KC_LSFT));
        }

        register_code16(keycode);
        if (erase_shift) {
            add_mods(MOD_BIT(KC_LSFT));
        }
    } else {
        // We scan for the first active keycode on the current ergol keycode and
        // unregister it.
        // This is required because when we register from the dead key layer,
        // the layer is released before we receive the release event of the key.
        // It means that for instance when à was pressed, the unregister was on
        // the FR_A instead of FR_AGRV.
        if (is_key_pressed(keycode)) {
            unregister_code16(keycode);
            return;
        }
        if (!is_cp(key->dkey) && is_key_pressed(key->dkey)) {
            unregister_code16(key->dkey);
            return;
        }
        if (!is_cp(key->s_dkey) && is_key_pressed(key->s_dkey)) {
            unregister_code16(key->s_dkey);
            return;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;

    if (!IS_LAYER_ON(ERGOL_CODE)) {
        if (record->event.pressed) {
            if (keycode == EKC_DK) {
                if (!shifted) return true;
            }
        }
    }

    if (keycode >= EKC_FIRST && keycode < EKC_MAX) {
        uint16_t    idx = IDX(keycode);
        ergol_key_t kc  = ergol_key_maps[idx];
        tap_press_or_release(record->event.pressed, shifted, &kc);
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == EKC_DK) {
        bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;
        if (!shifted) {
            if (record->event.pressed) {
                switch (get_highest_layer(layer_state)) {
                    case ERGOL:
                        set_oneshot_layer(ERGOL_1DK, ONESHOT_START);
                        break;
                        /* case ERGOL_1DK: */
                        /*     set_oneshot_layer(ERGOL_2DK, ONESHOT_START); */
                        /*     break; */
                }
                unregister_code16(EKC_DK);
            }
        }
    } else {
        if (IS_LAYER_ON(ERGOL_1DK) /*|| IS_LAYER_ON(ERGOL_2DK) */) {
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    }
}
