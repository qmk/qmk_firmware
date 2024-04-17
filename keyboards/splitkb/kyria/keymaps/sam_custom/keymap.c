/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H
#include "capsword.h"
#include "keymap.h"
#include "tapdance.h"
#include "transactions.h"
#include "rgb_matrix_user.h"
#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────────┬───┬───┬──────┬──────────────────┬─────┐                                                                 ┌─────┬─────────────┬────────────────────┬───┬───┬──────────────┐
//    │ TD(AUTOTAB) │ q │ w │  e   │        r         │  t  │                                                                 │  y  │      u      │         i          │ o │ p │      -       │
//    ├─────────────┼───┼───┼──────┼──────────────────┼─────┤                                                                 ├─────┼─────────────┼────────────────────┼───┼───┼──────────────┤
//    │   CTL_ESC   │ a │ s │  d   │        f         │  g  │                                                                 │  h  │      j      │         k          │ l │ ; │      '       │
//    ├─────────────┼───┼───┼──────┼──────────────────┼─────┼───────────────┬─────────────────┬─────────────────┬─────────────┼─────┼─────────────┼────────────────────┼───┼───┼──────────────┤
//    │    lsft     │ z │ x │  c   │        v         │  b  │  OSL(NUMPAD)  │    CLOSE_TAB    │   REOPEN_TAB    │ OSL(SYMBOL) │  n  │      m      │         ,          │ . │ / │ LT(SHIFT, =) │
//    └─────────────┴───┴───┼──────┼──────────────────┼─────┼───────────────┼─────────────────┼─────────────────┼─────────────┼─────┼─────────────┼────────────────────┼───┴───┴──────────────┘
//                          │ lgui │ TD(ALT_TAPDANCE) │ ent │ OSM(MOD_LSFT) │ TD(TMUX_SCROLL) │ TD(TMUX_SCROLL) │    bspc     │ spc │ OSL(WINDOW) │ TD(PLAYPAUSE_MUTE) │
//                          └──────┴──────────────────┴─────┴───────────────┴─────────────────┴─────────────────┴─────────────┴─────┴─────────────┴────────────────────┘
[_QWERTY] = LAYOUT(
  TD(AUTOTAB) , KC_Q , KC_W , KC_E    , KC_R             , KC_T   ,                                                                   KC_Y   , KC_U        , KC_I               , KC_O   , KC_P    , KC_MINUS           ,
  CTL_ESC     , KC_A , KC_S , KC_D    , KC_F             , KC_G   ,                                                                   KC_H   , KC_J        , KC_K               , KC_L   , KC_SCLN , KC_QUOTE           ,
  KC_LSFT     , KC_Z , KC_X , KC_C    , KC_V             , KC_B   , OSL(NUMPAD)   , CLOSE_TAB       , REOPEN_TAB      , OSL(SYMBOL) , KC_N   , KC_M        , KC_COMM            , KC_DOT , KC_SLSH , LT(SHIFT, KC_EQUAL),
                              KC_LGUI , TD(ALT_TAPDANCE) , KC_ENT , OSM(MOD_LSFT) , TD(TMUX_SCROLL) , TD(TMUX_SCROLL) , KC_BSPC     , KC_SPC , OSL(WINDOW) , TD(PLAYPAUSE_MUTE)
),

//    ┌─────┬─────┬─────┬────────────┬─────────────┬─────┐                           ┌─────┬───┬─────┬───┬───┬─────┐
//    │ tab │  1  │  2  │     3      │      4      │  5  │                           │  6  │ 7 │  8  │ 9 │ 0 │  -  │
//    ├─────┼─────┼─────┼────────────┼─────────────┼─────┤                           ├─────┼───┼─────┼───┼───┼─────┤
//    │     │     │     │            │             │     │                           │     │ 4 │  5  │ 6 │ * │  +  │
//    ├─────┼─────┼─────┼────────────┼─────────────┼─────┼───────┬─────┬──────┬──────┼─────┼───┼─────┼───┼───┼─────┤
//    │     │     │     │ LINUX_COPY │ LINUX_PASTE │     │ TO(0) │     │ pscr │      │  .  │ 1 │  2  │ 3 │ / │ ent │
//    └─────┴─────┴─────┼────────────┼─────────────┼─────┼───────┼─────┼──────┼──────┼─────┼───┼─────┼───┴───┴─────┘
//                      │            │             │ ent │       │     │      │ bspc │  0  │ . │     │
//                      └────────────┴─────────────┴─────┴───────┴─────┴──────┴──────┴─────┴───┴─────┘
[_NUMPAD] = LAYOUT(
  KC_TAB  , KC_1    , KC_2    , KC_3       , KC_4        , KC_5     ,                                         KC_6    , KC_7   , KC_8    , KC_9 , KC_0        , KC_MINUS,
  _______ , _______ , _______ , _______    , _______     , _______  ,                                         _______ , KC_4   , KC_5    , KC_6 , KC_ASTERISK , KC_PLUS ,
  _______ , _______ , _______ , LINUX_COPY , LINUX_PASTE , _______  , TO(0)   , _______ , KC_PSCR , _______ , KC_DOT  , KC_1   , KC_2    , KC_3 , KC_SLASH    , KC_ENTER,
                                _______    , _______     , KC_ENTER , _______ , _______ , _______ , KC_BSPC , KC_0    , KC_DOT , _______
),

//    ┌─────┬───┬───┬─────┬─────┬───┐                         ┌──────┬──────┬─────┬──────┬───┬─────┐
//    │  `  │ 0 │ { │  }  │  @  │ * │                         │  !   │  :   │  (  │  )   │ ; │     │
//    ├─────┼───┼───┼─────┼─────┼───┤                         ├──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ ^ │ = │  #  │  $  │ _ │                         │ left │ down │ up  │ rght │ ~ │     │
//    ├─────┼───┼───┼─────┼─────┼───┼─────┬─────┬─────┬───────┼──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ - │ < │  >  │  %  │ | │     │     │     │ TO(0) │  &   │  +   │  [  │  ]   │ / │     │
//    └─────┴───┴───┼─────┼─────┼───┼─────┼─────┼─────┼───────┼──────┼──────┼─────┼──────┴───┴─────┘
//                  │     │     │ \ │  :  │     │     │       │      │      │     │
//                  └─────┴─────┴───┴─────┴─────┴─────┴───────┴──────┴──────┴─────┘
[_SYMBOL] = LAYOUT(
  KC_GRV  , KC_0          , KC_LCBR  , KC_RCBR , KC_AT      , KC_ASTR       ,                                          KC_EXCLAIM , KC_COLON , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_SCLN  , _______,
  _______ , KC_CIRCUMFLEX , KC_EQUAL , KC_HASH , KC_DLR     , KC_UNDERSCORE ,                                          KC_LEFT    , KC_DOWN  , KC_UP         , KC_RIGHT       , KC_TILDE , _______,
  _______ , KC_MINUS      , KC_LT    , KC_GT   , KC_PERCENT , KC_PIPE       , _______  , _______ , _______ , TO(0)   , KC_AMPR    , KC_PLUS  , KC_LBRC       , KC_RBRC        , KC_SLSH  , _______,
                                       _______ , _______    , KC_BACKSLASH  , KC_COLON , _______ , _______ , _______ , _______    , _______  , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐                       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │ esc │  !  │  @  │  #  │  $  │  %  │                       │  ^  │  &  │  *  │  (  │  )  │  \  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤                       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │     │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┬─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                      │     │     │     │     │     │     │     │     │     │     │
//                      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_SHIFT] = LAYOUT(
  KC_ESC  , KC_EXCLAIM , KC_AT   , KC_HASH , KC_DLR  , KC_PERCENT ,                                         KC_CIRCUMFLEX , KC_AMPR , KC_ASTR , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_BACKSLASH,
  _______ , _______    , _______ , _______ , _______ , _______    ,                                         _______       , _______ , _______ , _______       , _______        , _______     ,
  _______ , _______    , _______ , _______ , _______ , _______    , _______ , _______ , _______ , _______ , _______       , _______ , _______ , _______       , _______        , _______     ,
                                   _______ , _______ , _______    , _______ , _______ , _______ , _______ , _______       , _______ , _______
),

//    ┌─────────┬─────────┬─────────┬─────────┬────────────┬──────────────────┐                       ┌─────┬─────┬─────┬─────┬─────┬─────────────────┐
//    │ DB_TOGG │         │         │         │            │     RGB_TOG      │                       │     │     │     │     │     │ QK_CLEAR_EEPROM │
//    ├─────────┼─────────┼─────────┼─────────┼────────────┼──────────────────┤                       ├─────┼─────┼─────┼─────┼─────┼─────────────────┤
//    │         │ RGB_SPI │ RGB_HUI │ RGB_SAI │  RGB_VAI   │ RGB_MODE_FORWARD │                       │     │     │     │     │     │                 │
//    ├─────────┼─────────┼─────────┼─────────┼────────────┼──────────────────┼─────┬─────┬─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────────────────┤
//    │         │ RGB_SPD │ RGB_HUD │ RGB_SAD │  RGB_VAD   │ RGB_MODE_REVERSE │     │     │     │     │     │     │     │     │     │                 │
//    └─────────┴─────────┴─────────┼─────────┼────────────┼──────────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────────────────┘
//                                  │         │ TG(_MAGIC) │                  │     │     │     │     │     │     │     │
//                                  └─────────┴────────────┴──────────────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_MAGIC] = LAYOUT(
  DB_TOGG , _______ , _______ , _______ , _______    , RGB_TOG          ,                                         _______ , _______ , _______ , _______ , _______ , QK_CLEAR_EEPROM,
  _______ , RGB_SPI , RGB_HUI , RGB_SAI , RGB_VAI    , RGB_MODE_FORWARD ,                                         _______ , _______ , _______ , _______ , _______ , _______        ,
  _______ , RGB_SPD , RGB_HUD , RGB_SAD , RGB_VAD    , RGB_MODE_REVERSE , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______        ,
                                _______ , TG(_MAGIC) , _______          , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬──────────────────┬──────────────────┬──────────────────────┬──────────────────┐                       ┌────────────────────┬────────────────────┬─────────────────┬─────────────────┬──────────────────┬───────────────────┐
//    │     │     │ WMGMT_FULLSCREEN │                  │ WMGMT_NEXT_WALLPAPER │   WMGMT_TOP_33   │                       │  WMGMT_MONITOR_1   │  WMGMT_MONITOR_2   │ WMGMT_MONITOR_3 │ WMGMT_MONITOR_4 │  WMGMT_TOPLEFT   │  WMGMT_TOPRIGHT   │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┤                       ├────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_33   │ WMGMT_HCENTER_33 │    WMGMT_RIGHT_33    │ WMGMT_VCENTER_33 │                       │   WMGMT_LEFT_50    │   WMGMT_DOWN_50    │   WMGMT_UP_50   │ WMGMT_RIGHT_50  │ WMGMT_BOTTOMLEFT │ WMGMT_BOTTOMRIGHT │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┬─────┬─────┬─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_66   │   WMGMT_CENTER   │    WMGMT_RIGHT_66    │ WMGMT_BOTTOM_33  │     │     │     │     │ WMGMT_PREV_MONITOR │ WMGMT_NEXT_MONITOR │                 │                 │                  │    WMGMT_BASE     │
//    └─────┴─────┴──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┼─────┼─────┼─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┴──────────────────┴───────────────────┘
//                                   │   TG(_WINDOW)    │                      │                  │     │     │     │     │                    │                    │                 │
//                                   └──────────────────┴──────────────────────┴──────────────────┴─────┴─────┴─────┴─────┴────────────────────┴────────────────────┴─────────────────┘
[_WINDOW] = LAYOUT(
  _______ , _______ , WMGMT_FULLSCREEN , _______          , WMGMT_NEXT_WALLPAPER , WMGMT_TOP_33     ,                                         WMGMT_MONITOR_1    , WMGMT_MONITOR_2    , WMGMT_MONITOR_3 , WMGMT_MONITOR_4 , WMGMT_TOPLEFT    , WMGMT_TOPRIGHT   ,
  _______ , _______ , WMGMT_LEFT_33    , WMGMT_HCENTER_33 , WMGMT_RIGHT_33       , WMGMT_VCENTER_33 ,                                         WMGMT_LEFT_50      , WMGMT_DOWN_50      , WMGMT_UP_50     , WMGMT_RIGHT_50  , WMGMT_BOTTOMLEFT , WMGMT_BOTTOMRIGHT,
  _______ , _______ , WMGMT_LEFT_66    , WMGMT_CENTER     , WMGMT_RIGHT_66       , WMGMT_BOTTOM_33  , _______ , _______ , _______ , _______ , WMGMT_PREV_MONITOR , WMGMT_NEXT_MONITOR , _______         , _______         , _______          , WMGMT_BASE       ,
                                         TG(_WINDOW)      , _______              , _______          , _______ , _______ , _______ , _______ , _______            , _______            , _______
)
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return false;
}
#endif

void matrix_init_user(void) {
    rgb_matrix_init_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif

    switch (keycode) {
        // tap-hold macros
        // case TD(PLAYPAUSE_MUTE):
        case TD(AUTOTAB):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
        case MACRO_UP_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            break;
        case MACRO_BRACES_PAIR:
            if (record->event.pressed) {
                SEND_STRING("{}" SS_TAP(X_LEFT));
            }
            break;
        case MACRO_BRACKETS_PAIR:
            if (record->event.pressed) {
                SEND_STRING("[]" SS_TAP(X_LEFT));
            }
            break;
        case MACRO_PARENS_PAIR:
            if (record->event.pressed) {
                SEND_STRING("()" SS_TAP(X_LEFT));
            }
            break;
        case MACRO_LT_GT_PAIR:
            if (record->event.pressed) {
                SEND_STRING("<>" SS_TAP(X_LEFT));
            }
            break;
        case MACRO_HELM_FUNC:
            if (record->event.pressed) {
                    SEND_STRING("{{-  -}}" \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                    );
            }
            break;
        case MACRO_HELM_SINGLE_LINE_COMMENT:
            if (record->event.pressed) {
                    SEND_STRING("{{- /*  */ -}}" \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                    );
            }
            break;
        case MACRO_HELM_MULTI_LINE_COMMENT:
            if (record->event.pressed) {
                    SEND_STRING("{{/**/}}" \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_LEFT) \
                        SS_TAP(X_ENT) \
                        SS_TAP(X_ENT) \
                        SS_TAP(X_UP) \
                    );
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(RPC_CAPSWORD_SYNC, capsword_sync_handler);
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        bool needs_sync = false;
        static uint16_t last_sync = false;
        static bool last_state = false;

        if (memcmp(&is_capsword_enabled, &last_state, sizeof(last_state))) {
            needs_sync = true;
            memcpy(&last_state, &is_capsword_enabled, sizeof(last_state));
        }

        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        if (needs_sync) {
            if (transaction_rpc_send(RPC_CAPSWORD_SYNC, sizeof(is_capsword_enabled), &is_capsword_enabled)) {
                last_sync = timer_read32();
            }
        }
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// update the array size in tapdance.h when adding to or removing from this
tap_dance_action_t tap_dance_actions[] = {
    [TMUX_SCROLL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tmux_finished, tmux_reset),
    [WIN_TAPDANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_finished, win_reset),
    [ALT_TAPDANCE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
    [AUTOTAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_TAB, LALT(LCTL(KC_TAB))),
    [PLAYPAUSE_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, encoder_finished, encoder_reset),
    // [PLAYPAUSE_MUTE] = ACTION_TAP_DANCE_TAP_HOLD(KC_MUTE, KC_MEDIA_PLAY_PAUSE),
};

/* layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUMPAD, _SYMBOL, _WINDOW);
    state = update_tri_layer_state(state, _NUMPAD, _SHIFT, _MAGIC);
    return state;
}; */
