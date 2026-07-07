// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _FN,
};

enum custom_keycodes {
    MY_FN = SAFE_RANGE, // Fnキー：ホールドでF1-F12レイヤー、タップ単体でWin+Space
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_F13,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRV,  KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT, KC_F14,           KC_SPC,           KC_ENT,           MY_FN,            KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * Fn層：数字段をFキーに割り当て
     * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┐
     * │ESC │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│  BSPC  │
     * ├────┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴────────┤
     * │                        (以下すべて透過)                       │
     * └────────────────────────────────────────────────────────────┘
     */
    [_FN] = LAYOUT(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    )
};

/* =========================================================================
 * F13 / F14：日本語キーボード運用でのIME切り替え
 *
 *   F13 単体タップ → Windows側で「IME-オフ」絶対指定として設定する
 *   F14 単体タップ → Windows側で「IME-オン」絶対指定として設定する
 *
 * F14長押し + J/K/I/U/Backspace：ウィンドウ/デスクトップ操作
 *   （F14を押してから一定時間(F14_TAP_TERM)経たないとコンボが発動しない。
 *    これは、F14を離した直後に他のキーを素早く打った際、ロールオーバーで
 *    誤ってコンボが発動してしまう問題を防ぐため）
 *
 * Fnキー：ホールドでF1-F12レイヤー、単体タップでWin+Space（US配列へ切替）
 * ========================================================================= */

#define F14_TAP_TERM 150 // これ未満のホールドはコンボとして扱わない(ms)

static bool     f14_is_held    = false; // F14キーが物理的に押されているか
static uint32_t f14_press_time = 0;     // F14を押した時刻
static bool     alttab_active  = false; // Alt+Tabモードに入っているか（Altをpress済みか）
static bool     f14_combo_used = false; // F14を押している間に何かコンボが発動したか

static bool     fn_is_held     = false; // Fnキーが物理的に押されているか
static bool     fn_combo_used  = false; // Fnを押している間に他のキーが使われたか

// F14を押してから十分な時間が経っているか（ロールオーバー誤爆防止）
static bool f14_combo_ready(void) {
    return f14_is_held && (timer_elapsed32(f14_press_time) >= F14_TAP_TERM);
}

// 現在の実際のShift状態を一時的に退避し、目的の文字を確実に送信してから復元する
static void tap_jis(uint16_t kc, bool want_shift) {
    uint8_t real_mods = get_mods();
    if (real_mods & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
    }
    if (want_shift) {
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(kc);
        unregister_mods(MOD_BIT(KC_LSFT));
    } else {
        tap_code(kc);
    }
    set_mods(real_mods); // 元のShift状態に戻す
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Fnを押している間に(Fn自体以外の)何かキーが押されたら「コンボ使用済み」とマークする
    if (fn_is_held && record->event.pressed && keycode != MY_FN) {
        fn_combo_used = true;
    }

    switch (keycode) {
        /* ---------- Fnキー：ホールドでF1-F12レイヤー、タップでWin+Space ---------- */
        case MY_FN:
            if (record->event.pressed) {
                fn_is_held = true;
                fn_combo_used = false;
                layer_on(_FN);
            } else {
                fn_is_held = false;
                layer_off(_FN);
                if (!fn_combo_used) {
                    tap_code16(LGUI(KC_SPC));
                }
            }
            return false;

        /* ---------- F13：確実にIME-オフ ---------- */
        case KC_F13:
            return true;

        /* ---------- F14長押しの起点 ---------- */
        case KC_F14:
            if (record->event.pressed) {
                f14_is_held = true;
                f14_press_time = timer_read32();
                f14_combo_used = false;
            } else {
                f14_is_held = false;
                if (alttab_active) {
                    unregister_code(KC_LALT);
                    alttab_active = false;
                } else if (!f14_combo_used) {
                    tap_code(KC_F14); // Windows側でIME-オンに割り当て
                }
            }
            return false;

        /* ---------- Alt+Tab ← 前へ（F14 + J） ---------- */
        case KC_J:
            if (f14_combo_ready()) {
                if (record->event.pressed) {
                    f14_combo_used = true;
                    if (!alttab_active) {
                        register_code(KC_LALT);
                        alttab_active = true;
                    }
                    tap_code16(LSFT(KC_TAB));
                }
                return false;
            }
            return true;

        /* ---------- Alt+Tab → 次へ（F14 + K） ---------- */
        case KC_K:
            if (f14_combo_ready()) {
                if (record->event.pressed) {
                    f14_combo_used = true;
                    if (!alttab_active) {
                        register_code(KC_LALT);
                        alttab_active = true;
                    }
                    tap_code(KC_TAB);
                }
                return false;
            }
            return true;

        /* ---------- 仮想デスクトップ 次へ（F14 + I） ---------- */
        case KC_I:
            if (f14_combo_ready()) {
                if (record->event.pressed) {
                    f14_combo_used = true;
                    tap_code16(LCTL(LGUI(KC_RIGHT)));
                }
                return false;
            }
            return true;

        /* ---------- 仮想デスクトップ 前へ（F14 + U） ---------- */
        case KC_U:
            if (f14_combo_ready()) {
                if (record->event.pressed) {
                    f14_combo_used = true;
                    tap_code16(LCTL(LGUI(KC_LEFT)));
                }
                return false;
            }
            return true;

        /* ---------- PrintScreen（F14 + Backspace） ---------- */
        case KC_BSPC:
            if (f14_combo_ready()) {
                if (record->event.pressed) {
                    f14_combo_used = true;
                    tap_code(KC_PSCR);
                }
                return false;
            }
            return true;

        /* ---------- F14 + 2 → "@" ---------- */
        case KC_2:
            if (f14_combo_ready()) {
                if (record->event.pressed) { f14_combo_used = true; tap_jis(KC_LBRC, false); }
                return false;
            }
            return true;

        /* ---------- F14 + 9 → "(" ---------- */
        case KC_9:
            if (f14_combo_ready()) {
                if (record->event.pressed) { f14_combo_used = true; tap_jis(KC_8, true); }
                return false;
            }
            return true;

        /* ---------- F14 + 0 → ")" ---------- */
        case KC_0:
            if (f14_combo_ready()) {
                if (record->event.pressed) { f14_combo_used = true; tap_jis(KC_9, true); }
                return false;
            }
            return true;

        /* ---------- F14 + "-" → "_" ---------- */
        case KC_MINS:
            if (f14_combo_ready()) {
                if (record->event.pressed) { f14_combo_used = true; tap_jis(KC_INT1, true); }
                return false;
            }
            return true;

        /* ---------- F14 + "\" → "\"（確実にバックスラッシュ） ---------- */
        case KC_BSLS:
            if (f14_combo_ready()) {
                if (record->event.pressed) { f14_combo_used = true; tap_jis(KC_INT1, false); }
                return false;
            }
            return true;

        /* ---------- F14 + Enter → F13（IME-オフ、即時発火） ---------- */
        case KC_ENT:
            if (f14_is_held) {
                if (record->event.pressed) { f14_combo_used = true; tap_code(KC_F13); }
                return false;
            }
            return true;

        default:
            return true;
    }
}