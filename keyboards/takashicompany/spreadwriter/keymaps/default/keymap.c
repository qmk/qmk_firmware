#include QMK_KEYBOARD_H

enum custom_keycodes {
    SPREADWRITER = SAFE_RANGE,
    WEB,
    SPECIAL
};

// 必要な数のタップダンス状態のタイプを定義します
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    QUOT_LAYR, // カスタムタップダンスキー。他のタップダンスキーはこの列挙型に追加します
};

// タップダンスキーで使われる関数を宣言します

// 全てのタップダンスに関連する関数
td_state_t cur_dance(qk_tap_dance_state_t *state);

// 個別のタップダンスに関連する関数
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

uint8_t _MY_LAYER = 4;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC, LT(2, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_A, KC_S, LT(2, KC_D), KC_F, KC_G, SPREADWRITER, KC_H, KC_J, LT(2, KC_K), KC_L, KC_ENT, KC_ENT,
        KC_LSFT, SFT_T(KC_Z), GUI_T(KC_X), KC_C, KC_V, KC_B, MEH(KC_4), LSA(KC_5),  KC_N, KC_M, KC_COMM, CTL_T(KC_DOT), KC_BSPC, KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT, MO(5), MO(4), ALT_T(KC_LANG2), SFT_T(KC_TAB), TD(QUOT_LAYR), LT(6, KC_SPC), LT(1, KC_LANG1), KC_RALT, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
        KC_WH_U, KC_WH_D
    ),

    LAYOUT(
        KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
        KC_LCTL, CTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_TRNS, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_TRNS, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_T, KC_TRNS, RESET, KC_F11, KC_F12, KC_CAPS, KC_NO, KC_NO, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_JYEN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_NUHS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P0, KC_COMM, KC_DOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL), S(KC_JYEN), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_LBRC), S(KC_RBRC), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_SCLN), S(KC_QUOT), S(KC_NUHS), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P0, KC_COMM, KC_DOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_COMM), S(KC_DOT), S(KC_SLSH), S(KC_RO), KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), G(KC_JYEN), KC_TRNS,
        KC_LCTL, S(KC_EQL), S(KC_LBRC), S(KC_SLSH), S(KC_MINS), S(KC_RO), KC_TRNS, S(KC_SCLN), S(KC_QUOT), S(KC_RBRC), S(KC_NUHS), S(KC_JYEN), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

     LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

     LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPREADWRITER:
            if (record->event.pressed) {
                SEND_STRING("Spreadwriter");
                rgblight_toggle();
            }
            return false;

        case WEB:
            if (record->event.pressed) {
                SEND_STRING("https://github.com/takashicompany/spreadwriter");
            }
            return false;

        case SPECIAL:
            if (record->event.pressed) {
                add_mods(MOD_MASK_SHIFT);
                layer_on(4);
            } else {
                del_mods(MOD_MASK_SHIFT);
                layer_off(4);
            }

    }
    
    return true;
}

// 現在のタップダンスの状態を決定します
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    // if (state->count == 1) {
    //     if (!state->pressed) return TD_SINGLE_TAP;
    //     else return TD_SINGLE_HOLD;
    // } // else if (state->count == 2) return TD_DOUBLE_TAP;
    // else return TD_UNKNOWN;

    if (state->count == 1  && state->pressed) {
        return TD_SINGLE_HOLD;
    } // else if (state->count == 2) return TD_DOUBLE_TAP;
    return TD_SINGLE_TAP;
}

// この例のタップダンスキーに関連付けられた "tap" 構造体を初期化します
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// タップダンスキーの動作をコントロールする関数
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    //if (!state->interrupted) {

        ql_tap_state.state = cur_dance(state);
        switch (ql_tap_state.state) {
            case TD_SINGLE_TAP:
                // tap_code(KC_SPC);
                break;
            case TD_SINGLE_HOLD:
                register_code (KC_BSPC);
                unregister_code (KC_BSPC);
                layer_on(_MY_LAYER);
                break;
            case TD_DOUBLE_TAP:
                // レイヤーが既にセットされているか確認します
                if (layer_state_is(_MY_LAYER)) {
                    // レイヤーが既にセットされていたら、オフにします。
                    layer_off(_MY_LAYER);
                } else {
                    // レイヤーがセットされていなかったら、オンにします。
                    layer_on(_MY_LAYER);
                }
                break;
            default:
                break;
        }
    // }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // キーを押し続けていて今離したら、レイヤーをオフに切り替えます。
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_MY_LAYER);
    }
    ql_tap_state.state = TD_NONE;
}

void dance_each_tap (qk_tap_dance_state_t *state, void *user_data) {  // キーが押下される都度実行される
   switch (state->keycode) {
     case TD(QUOT_LAYR):
       if (state->count == 1) {
         register_code (KC_SPC);
         unregister_code (KC_SPC);
       }
       break;
   }
 }

// タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
    [QUOT_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(dance_each_tap, ql_finished, ql_reset, 100)
};