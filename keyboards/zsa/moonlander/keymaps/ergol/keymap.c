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
#include "keymap_french.h"
#include "unicode/unicode.h"

enum layers {
    ERGOL,
    ERGOL_1DK,
    ERGOL_2DK,
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

int current_layer = ERGOL;

typedef struct {
    uint16_t base;

    uint32_t dkey;
    uint32_t s_dkey;

    uint32_t code;
    uint32_t s_code;
} ergol_key_t;

#define EGL(B, DK, SDK, C, SC)                                         \
    (ergol_key_t) {                                                    \
        .base = B, .dkey = DK, .s_dkey = SDK, .code = C, .s_code = SC, \
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

// clang-format off
const ergol_key_t ergol_key_maps[IDX(EKC_MAX)] = {
    [IDX(EKC_Q)] = EGL(FR_Q,       CP(0x00E2) /* â */, CP(0x00C2) /* Â */, FR_CIRC,    KC_TRNS),
    [IDX(EKC_C)] = EGL(FR_C,       CP(0x00E7) /* ç */, CP(0x00C7) /* Ç */, KC_LT,      CP(0x2264) /* ≤ */),
    [IDX(EKC_O)] = EGL(FR_O,       CP(0x0153) /* œ */, CP(0x0152) /* Œ */, KC_GT,      CP(0x2265) /* ≥ */),
    [IDX(EKC_P)] = EGL(FR_P,       CP(0x00F4) /* ô */, CP(0x00D4) /* Ô */, KC_DLR,     CP(0x2264)),
    [IDX(EKC_W)] = EGL(FR_W,       KC_TRNS,            KC_TRNS,            KC_PERC,    CP(0x2030) /* ‰ */),


    [IDX(EKC_J)] = EGL(FR_J,       KC_TRNS,            KC_TRNS,            KC_AT,      KC_TRNS),
    [IDX(EKC_M)] = EGL(FR_M,       CP(0x00B5) /* µ */, KC_TRNS,            KC_AMPR,    KC_TRNS),
    [IDX(EKC_D)] = EGL(FR_D,       FR_UNDS,            KC_TRNS,            KC_ASTR,    CP(0x00D7) /* × */),
    [IDX(EKC_DK)] = EGL(KC_EXLM,   KC_TRNS,            KC_TRNS,            KC_QUOTE,   CP(0x00B4) /* ´ */),

};
// clang-format on

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [ERGOL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______,  EKC_Q ,  EKC_C ,  EKC_O ,  EKC_P ,  EKC_W , _______,           _______,  EKC_J ,  EKC_M ,  EKC_D , EKC_DK , _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        KC_LEFT_SHIFT, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, KC_ENTER, _______
    ),


    [ERGOL_1DK] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,            _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
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

static inline void tap_code16_with_unicode(uint32_t kc) {
    uint8_t temp_mod = get_mods();
    clear_mods();
    if (is_cp(kc)) {
        kc = cp_val(kc);
        register_unicode(kc);
    } else {
        tap_code16(kc);
    }
    set_mods(temp_mod);
}

static inline void tap_code16_mods(bool shifted, uint32_t kc) {
    tap_code16_with_unicode(shifted ? S(kc) : kc);
}

static inline void tap_code16_mods2(bool shifted, uint32_t kc, uint32_t skc) {
    if (shifted && kc != KC_TRNS) {
        tap_code16_with_unicode(skc);
    } else {
        tap_code16_with_unicode(kc);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;

        if (keycode == EKC_DK) {
            if (!shifted) {
                return true;
            }
        }

        if (keycode >= EKC_FIRST && keycode < EKC_MAX) {
            uint16_t    idx = IDX(keycode);
            ergol_key_t kc  = ergol_key_maps[idx];
            switch (current_layer) {
                default:
                case ERGOL:
                    // if key_code == EKC_DK we don't want the shift.
                    tap_code16_mods(shifted && keycode != EKC_DK, kc.base);
                    break;

                case ERGOL_1DK:
                    tap_code16_mods2(shifted, kc.dkey, kc.s_dkey);
                    break;

                case ERGOL_CODE:
                    tap_code16_mods2(shifted, kc.code, kc.s_code);
                    break;
            };
        }
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == EKC_DK) {
        bool shifted = (get_mods() & MOD_MASK_SHIFT) != 0;
        if (!shifted) {
            if (record->event.pressed) {
                switch (current_layer) {
                    case ERGOL:
                        set_oneshot_layer(ERGOL_1DK, ONESHOT_START);
                        break;
                    case ERGOL_1DK:
                        set_oneshot_layer(ERGOL_2DK, ONESHOT_START);
                        break;
                }
                unregister_code16(EKC_DK);
            }
        }
    } else {
        if (current_layer == ERGOL_1DK || current_layer == ERGOL_2DK) {
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    }
}

void oneshot_layer_changed_user(uint8_t layer) {
    current_layer = layer;
}
