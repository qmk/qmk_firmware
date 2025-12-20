/*
Copyright 2025 JEEBIS <jeebis.iox@gmail.com>

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

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "keymap_japanese.h"

// レイヤー定義（enumの値を0から連番で確保する）
enum layer_names {
    _QWERTY = 0,
    _GEMINI,
    _NUMBER,
    _FUNCTION,
};

enum custom_keycodes {
    KC_DZ = SAFE_RANGE,  // 00キー
    TG_JIS,  // JISモード切替キー
};

typedef union {
    uint32_t raw;
    struct {
        bool is_jis_mode : 1; // JISモードフラグ
    };
} user_config_t;
user_config_t user_config;

// shift+2  " -> @
const key_override_t kor_at = ko_make_with_layers(MOD_MASK_SHIFT, KC_2, JP_AT, 1);
// shift+6  & -> ^
const key_override_t kor_circ = ko_make_with_layers(MOD_MASK_SHIFT, KC_6, JP_CIRC, 1);
// shift+7  ' -> &
const key_override_t kor_ampr = ko_make_with_layers(MOD_MASK_SHIFT, KC_7, JP_AMPR, 1);
// shift+8  ( -> *
const key_override_t kor_astr = ko_make_with_layers(MOD_MASK_SHIFT, KC_8, JP_ASTR, 1);
// shift+9  ) -> (
const key_override_t kor_lprn = ko_make_with_layers(MOD_MASK_SHIFT, KC_9, JP_LPRN, 1);
// shift+0    -> )
const key_override_t kor_rprn = ko_make_with_layers(MOD_MASK_SHIFT, KC_0, JP_RPRN, 1);
// shift+-  = -> _
const key_override_t kor_unds = ko_make_with_layers(MOD_MASK_SHIFT, KC_MINS, JP_UNDS, 1);
// =        ^ -> =
// shift+=  ~ -> +
const key_override_t kor_eql = ko_make_with_layers_and_negmods(0, JP_CIRC, JP_EQL, 1, MOD_MASK_SHIFT);
const key_override_t kor_plus = ko_make_with_layers(MOD_MASK_SHIFT, JP_CIRC, JP_PLUS, 1);
/* \        ] -> \ */
/* shift+\  } -> | */
const key_override_t kor_bsls = ko_make_with_layers_and_negmods(0, KC_BSLS, JP_BSLS, 1, MOD_MASK_SHIFT);
const key_override_t kor_pipe = ko_make_with_layers(MOD_MASK_SHIFT, KC_BSLS, JP_PIPE, 1);
// [        @ -> [
// shift+[  ` -> {
const key_override_t kor_lbrc = ko_make_with_layers_and_negmods(0, JP_AT, JP_LBRC, 1, MOD_MASK_SHIFT);
const key_override_t kor_lcbr = ko_make_with_layers(MOD_MASK_SHIFT, JP_AT, JP_LCBR, 1);
// ]        [ -> ]
// shift+]  { -> }
const key_override_t kor_rbrc = ko_make_with_layers_and_negmods(0, JP_LBRC, JP_RBRC, 1, MOD_MASK_SHIFT);
const key_override_t kor_rcbr = ko_make_with_layers(MOD_MASK_SHIFT, JP_LBRC, JP_RCBR, 1);
// shift+;  + -> :
const key_override_t kor_coln = ko_make_with_layers(MOD_MASK_SHIFT, KC_SCLN, JP_COLN, 1);
// '        : -> '
// shift+'  * -> "
const key_override_t kor_quot = ko_make_with_layers_and_negmods(0, KC_QUOT, JP_QUOT, 1, MOD_MASK_SHIFT);
const key_override_t kor_dquo = ko_make_with_layers(MOD_MASK_SHIFT, KC_QUOT, JP_DQUO, 1);
// `        全角半角 -> `
// shift+`  shift+全角半角 -> ~
const key_override_t kor_grv = ko_make_with_layers_and_negmods(0, JP_ZKHK, JP_GRV, 1, MOD_MASK_SHIFT);
const key_override_t kor_tild = ko_make_with_layers(MOD_MASK_SHIFT, JP_ZKHK, JP_TILD, 1);
// Caps     英数 -> Caps
const key_override_t kor_caps = ko_make_with_layers_and_negmods(0, JP_EISU, JP_CAPS, 1, MOD_MASK_SHIFT);

#define MT_SPC MT(MOD_LSFT, KC_SPC)  // タップでSpace、ホールドでShift
#define MT_ENT MT(MOD_LSFT, KC_ENT)  // タップでEnter、ホールドでShift
#define MT_ESC MT(MOD_LGUI, KC_ESC)  // タップでEscape、ホールドでGUI
#define MO_FUN MO(_FUNCTION)  // ホールドで_FUNCTIONレイヤー
#define MT_TGL LT(_NUMBER, KC_F24)  // タップで_GEMINIレイヤー切替、ホールドで_NUMBERレイヤー

static uint16_t default_layer = 0; // デフォルトレイヤー状態を保存する変数 (0:_QWERTY, 1: _GEMINI)

void eeconfig_init_user(void) {
    user_config.raw = 0; // 初期化時にJISモードを無効化
    user_config.is_jis_mode = false;
    eeconfig_update_user(user_config.raw);
    steno_set_mode(STENO_MODE_GEMINI);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

const key_override_t *key_overrides[] = {
    &kor_at,
    &kor_circ,
    &kor_ampr,
    &kor_astr,
    &kor_lprn,
    &kor_rprn,
    &kor_unds,
    &kor_eql,
    &kor_plus,
    &kor_bsls,
    &kor_pipe,
    &kor_lbrc,
    &kor_lcbr,
    &kor_rbrc,
    &kor_rcbr,
    &kor_coln,
    &kor_quot,
    &kor_dquo,
    &kor_grv,
    &kor_tild,
    &kor_caps,
    NULL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    os_variant_t os = detected_host_os();
    bool is_mac = (os == OS_MACOS || os == OS_IOS);
    
    // Mod-Tap shift に対応したシフト+数字キーの処理
    if (IS_LAYER_ON(_NUMBER) && record->event.pressed && (get_mods() & MOD_MASK_SHIFT)) {
        uint16_t shifted_code = KC_NO;
        switch (keycode) {
            case KC_2: shifted_code = JP_AT; break;       // Shift+2 -> @
            case KC_6: shifted_code = JP_CIRC; break;     // Shift+6 -> ^
            case KC_7: shifted_code = JP_AMPR; break;     // Shift+7 -> &
            case KC_8: shifted_code = JP_ASTR; break;     // Shift+8 -> *
            case KC_9: shifted_code = JP_LPRN; break;     // Shift+9 -> (
            case KC_0: shifted_code = JP_RPRN; break;     // Shift+0 -> )
            case KC_MINS: shifted_code = JP_UNDS; break;  // Shift+- -> _
            case KC_SCLN: shifted_code = JP_COLN; break;  // Shift+; -> :
            default: break;
        }
        if (shifted_code != KC_NO) {
            // 修飾キーを一度削除して、記号キーを送信
            uint8_t mods = get_mods();
            del_mods(MOD_MASK_SHIFT);
            tap_code16(shifted_code);
            add_mods(mods);
            return false;
        }
    }

    switch (keycode) {
        case MT_TGL:  // MT_TGLキー
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    // _QWERTY と _GEMINI の間でトグル切り替えを行う
                    if (default_layer == 0) {
                        set_single_persistent_default_layer(_GEMINI);
                        tap_code16(is_mac ? KC_LNG1 : KC_INT4); // Macなら「かな」キー、Windowsなら「変換」キーを送信
                        default_layer = 1;
                    } else {
                        set_single_persistent_default_layer(_QWERTY);
                        tap_code16(is_mac ? KC_LNG2 : KC_INT5); // Macなら「英数」キー、Windowsなら「無変換」キーを送信
                        default_layer = 0;
                    }
                }
                return false;
            }
            return true;
        case TG_JIS:
            if (record->event.pressed) {
                // 押された瞬間にJISモードをトグル
                user_config.is_jis_mode = !user_config.is_jis_mode;
                eeconfig_update_user(user_config.raw);
                // 状態に応じてキーオーバーライドをON/OFF
                if (user_config.is_jis_mode) {
                    tap_code16(QK_KEY_OVERRIDE_ON);
                } else {
                    tap_code16(QK_KEY_OVERRIDE_OFF);
                }
            }
            return false;
        case KC_DZ:
            if (record->event.pressed) {
                // 押された瞬間に0を2回送信
                SEND_STRING("00");
            }
            return true;
        case KC_LCTL:
            if (is_mac) {
                // Macの場合はCommandとして振る舞わせる
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                } else {
                    unregister_code(KC_LGUI);
                }
                return false;
            }
            return true;
        case KC_LGUI:
            if (is_mac) {
                // Macの場合はControlとして振る舞わせる
                if (record->event.pressed) {
                    register_code(KC_LCTL);
                } else {
                    unregister_code(KC_LCTL);
                }
                return false;
            }
            return true;
        case KC_INT4:
            if (is_mac) {
                // Macの場合は「英数」キーとして振る舞わせる
                if (record->event.pressed) {
                    register_code(KC_LNG2);
                } else {
                    unregister_code(KC_LNG2);
                }
                return false;
            }
            return true;
        case KC_INT5:
            if (is_mac) {
                // Macの場合は「かな」キーとして振る舞わせる
                if (record->event.pressed) {
                    register_code(KC_LNG1);
                } else {
                    unregister_code(KC_LNG1);
                }
                return false;
            }
            return true;
        default:
            break;
    }
    // Mod-Tapキーのホールド時にLCTL・LGUIが割り当てられている場合の処理
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX)) {
    // ホールド時の修飾キーが LCTL であるか確認
        if (QK_MOD_TAP_GET_MODS(keycode) == MOD_LCTL) {
            if (is_mac) {
                if (record->event.pressed) {
                    if (record->tap.count > 0) {
                        return true; // タップ時は通常のキーを送信
                    } else {
                        register_code(KC_LGUI); // Macなら Command を送信
                        return false;
                    }
                } else {
                    unregister_code(KC_LGUI);
                    return true; // 離した時のタップ処理は QMK 本体に任せる
                }
            }
        }
        // ホールド時の修飾キーが LGUI であるか確認
        else if (QK_MOD_TAP_GET_MODS(keycode) == MOD_LGUI) {
            if (is_mac) {
                if (record->event.pressed) {
                    if (record->tap.count > 0) {
                        return true; // タップ時は通常のキーを送信
                    } else {
                        register_code(KC_LCTL); // Macなら Control を送信
                        return false;
                    }
                } else {
                    unregister_code(KC_LCTL);
                    return true; // 離した時のタップ処理は QMK 本体に任せる
                }
            }
        }
    }
    return true;
}
// ..................................................................... Keymaps
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // QWERTY
    // ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
    // │  `  │  q  │  w  │  e  │  r ESC t  │             │  y DEL u  │  i  │  o  │  p  │  -  │
    // ├─────┼──a──┼──s──┼──d──┼──f──┼──g──┤             ├──h──┼──j──┼──k──┼──l──┼──;──┼──'──┤
    // │ ESC │  z  │  x  │  c  │  v TAB b  │             │  n BSP m  │  ,  │  .  │  /  │  \  │
    // └─────┴─────┴─────┴─────┴─────┴─────┘             └─────┴─────┴─────┴─────┴─────┴─────┘
    //                         ┌───────────┐             ┌───────────┐
    //                         │   SandS   │             │   EandS   │
    //                         ├─────┬─────┤   ┌─────┐   ├─────┬─────┤
    //                         │ ALT │ CTL │   │MT_TG│   │  [  =  ]  │
    //                         └─────┴─────┘   └─────┘   └─────┴─────┘
    [_QWERTY] = LAYOUT(
        KC_GRV, KC_Q, KC_W, KC_E, KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_MINS,
        KC_ESC, KC_Z, KC_X, KC_C, KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_BSLS,
                                  MT_SPC , MT_TGL,  MT_ENT,
                                  KC_LALT, KC_LCTL, KC_LBRC, KC_RBRC
    ),
    // GEMINI
    // ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
    // │  #  │  S  │  T  │  P  │  H  │  *  │             │  *  │  F  │  P  │  L  │  T  │  D  │
    // ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
    // │  #  │  S  │  K  │  W  │  R  │  *  │             │  *  │  R  │  B  │  G  │  S  │  Z  │
    // └─────┴─────┴─────┴─────┴─────┴─────┘             └─────┴─────┴─────┴─────┴─────┴─────┘
    //                         ┌───────────┐             ┌───────────┐
    //                         │     #     │             │     #     │
    //                         ├─────┬─────┤   ┌─────┐   ├─────┬─────┤
    //                         │  A  │  O  │   │MT_TG│   │  E  │  U  │
    //                         └─────┴─────┘   └─────┘   └─────┴─────┘
    [_GEMINI] = LAYOUT(
        STN_N1, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1, STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
        STN_N2, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2, STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                        STN_N3, MT_TGL,  STN_N4,
                                        STN_A,  STN_O,   STN_E,   STN_U
    ),
    // NUMBER
    // ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
    // │  `  │  -  │  1  │  2  │  3  │ 00  │             │ PGU │ HOM │  ↑  │ END │ CAP │ JIS │
    // ├─────┼──,──┼──4──┼──5──┼──6──┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
    // │ ESC │  .  │  7  │  8  │  9  │  0  │             │ PGD │  ←  │  ↓  │  →  │ GUI │MO_FN│
    // └─────┴─────┴─────┴─────┴─────┴─────┘             └─────┴─────┴─────┴─────┴─────┴─────┘
    //                         ┌───────────┐             ┌───────────┐
    //                         │   SandS   │             │   EandS   │
    //                         ├─────┬─────┤   ┌─────┐   ├─────┬─────┤
    //                         │ ALT │ CTL │   │MT_TG│   │INT5 │INT4 │
    //                         └─────┴─────┘   └─────┘   └─────┴─────┘
    [_NUMBER] = LAYOUT(
        KC_GRV, KC_MINS, KC_1, KC_2, KC_3,    KC_DZ,   KC_PGUP, KC_HOME, KC_UP,   KC_END,   KC_CAPS, TG_JIS,
        KC_ESC, KC_DOT,  KC_7, KC_8, KC_9,    KC_0,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_LGUI, MO_FUN,
                                     MT_SPC,  KC_TRNS, MT_ENT,
                                     KC_LALT, KC_LCTL, KC_INT5, KC_INT4
    ),
    // FUNCTION
    // ┌─────┬─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┬─────┐
    // │ F1  │ F2  │ F3  │ F4  │ F5  │ F11 │             │ BRU │ VL0 │ VL- │ VL+ │ PSC │ SLP │
    // ├─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┤
    // │ ESC │ F6  │ F7  │ F8  │ F9  │ F10 │             │ BRD │ |<< │ >|| │ >>| │ INS │MO_FN│
    // └─────┴─────┴─────┴─────┴─────┴─────┘             └─────┴─────┴─────┴─────┴─────┴─────┘
    //                         ┌───────────┐             ┌───────────┐
    //                         │   SandS   │             │   EandS   │
    //                         ├─────┬─────┤   ┌─────┐   ├─────┬─────┤
    //                         │ ALT │ CTL │   │MT_TG│   │ F12 │ F13 │
    //                         └─────┴─────┘   └─────┘   └─────┴─────┘
    [_FUNCTION] = LAYOUT(
        KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5,   KC_F11,  KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_PSCR, KC_SLEP,
        KC_ESC, KC_F6, KC_F7, KC_F8, KC_F9,   KC_F10,  KC_BRID, KC_MPRV, KC_MPLY, KC_MNXT, KC_LGUI, KC_TRNS,
                                     KC_TRNS, KC_TRNS, KC_TRNS,
                                     KC_TRNS, KC_TRNS, KC_F12,  KC_F13
    ),
};
// ..................................................................... Keymaps

// Combos
const uint16_t PROGMEM qwerty_combo1[] = {KC_Q, KC_Z, COMBO_END};
const uint16_t PROGMEM qwerty_combo2[] = {KC_W, KC_X, COMBO_END};
const uint16_t PROGMEM qwerty_combo3[] = {KC_E, KC_C, COMBO_END};
const uint16_t PROGMEM qwerty_combo4[] = {KC_R, KC_V, COMBO_END};
const uint16_t PROGMEM qwerty_combo5[] = {KC_T, KC_B, COMBO_END};
const uint16_t PROGMEM qwerty_combo6[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM qwerty_combo7[] = {KC_U, KC_M, COMBO_END};
const uint16_t PROGMEM qwerty_combo8[] = {KC_I, KC_COMM, COMBO_END};
const uint16_t PROGMEM qwerty_combo9[] = {KC_O, KC_DOT, COMBO_END};
const uint16_t PROGMEM qwerty_combo10[] = {KC_P, KC_SLSH, COMBO_END};
const uint16_t PROGMEM qwerty_combo11[] = {KC_MINS, KC_BSLS, COMBO_END};
const uint16_t PROGMEM qwerty_combo12[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM qwerty_func_combo1[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM qwerty_func_combo2[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM qwerty_func_combo3[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM qwerty_func_combo4[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM number_combo1[] = {KC_1, KC_7, COMBO_END};
const uint16_t PROGMEM number_combo2[] = {KC_2, KC_8, COMBO_END};
const uint16_t PROGMEM number_combo3[] = {KC_3, KC_9, COMBO_END};
const uint16_t PROGMEM number_combo4[] = {KC_DOT, KC_MINS, COMBO_END};
const uint16_t PROGMEM number_func_combo1[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM number_func_combo2[] = {KC_3, KC_DZ, COMBO_END};
const uint16_t PROGMEM number_func_combo3[] = {KC_PGDN, KC_LEFT, COMBO_END};
const uint16_t PROGMEM number_func_combo4[] = {KC_PGUP, KC_HOME, COMBO_END};


combo_t key_combos[] = {
    COMBO(qwerty_combo1, KC_A),
    COMBO(qwerty_combo2, KC_S),
    COMBO(qwerty_combo3, KC_D),
    COMBO(qwerty_combo4, KC_F),
    COMBO(qwerty_combo5, KC_G),
    COMBO(qwerty_combo6, KC_H),
    COMBO(qwerty_combo7, KC_J),
    COMBO(qwerty_combo8, KC_K),
    COMBO(qwerty_combo9, KC_L),
    COMBO(qwerty_combo10, KC_SCLN),
    COMBO(qwerty_combo11, KC_QUOT),
    COMBO(qwerty_combo12, KC_EQL),
    COMBO(qwerty_func_combo1, KC_TAB),
    COMBO(qwerty_func_combo2, KC_ESC),
    COMBO(qwerty_func_combo3, KC_BSPC),
    COMBO(qwerty_func_combo4, KC_DEL),
    COMBO(number_combo1, KC_4),
    COMBO(number_combo2, KC_5),
    COMBO(number_combo3, KC_6),
    COMBO(number_combo4, KC_COMMA),
    COMBO(number_func_combo1, KC_TAB),
    COMBO(number_func_combo2, KC_ESC),
    COMBO(number_func_combo3, KC_BSPC),
    COMBO(number_func_combo4, KC_DEL),
};