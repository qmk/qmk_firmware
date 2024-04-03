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
#include "keymap.h"
#include "tapdance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────┬───┬───┬──────────────────┬──────────────────┬─────┐                                                                 ┌─────┬───┬───┬───┬───┬──────────────┐
//    │   tab   │ q │ w │        e         │        r         │  t  │                                                                 │  y  │ u │ i │ o │ p │      -       │
//    ├─────────┼───┼───┼──────────────────┼──────────────────┼─────┤                                                                 ├─────┼───┼───┼───┼───┼──────────────┤
//    │ CTL_ESC │ a │ s │        d         │        f         │  g  │                                                                 │  h  │ j │ k │ l │ ; │      '       │
//    ├─────────┼───┼───┼──────────────────┼──────────────────┼─────┼───────────────┬─────────────────┬─────────────────┬─────────────┼─────┼───┼───┼───┼───┼──────────────┤
//    │  lsft   │ z │ x │        c         │        v         │  b  │  OSL(NUMPAD)  │    CLOSE_TAB    │   REOPEN_TAB    │ OSL(SYMBOL) │  n  │ m │ , │ . │ / │ LT(SHIFT, \) │
//    └─────────┴───┴───┼──────────────────┼──────────────────┼─────┼───────────────┼─────────────────┼─────────────────┼─────────────┼─────┼───┼───┼───┴───┴──────────────┘
//                      │ TD(WIN_TAPDANCE) │ TD(ALT_TAPDANCE) │ ent │ OSM(MOD_LSFT) │ TD(TMUX_SCROLL) │ TD(TMUX_SCROLL) │    bspc     │ spc │ [ │ ] │
//                      └──────────────────┴──────────────────┴─────┴───────────────┴─────────────────┴─────────────────┴─────────────┴─────┴───┴───┘
[_QWERTY] = LAYOUT(
  KC_TAB  , KC_Q , KC_W , KC_E             , KC_R             , KC_T   ,                                                                   KC_Y   , KC_U    , KC_I    , KC_O   , KC_P    , KC_MINUS               ,
  CTL_ESC , KC_A , KC_S , KC_D             , KC_F             , KC_G   ,                                                                   KC_H   , KC_J    , KC_K    , KC_L   , KC_SCLN , KC_QUOTE               ,
  KC_LSFT , KC_Z , KC_X , KC_C             , KC_V             , KC_B   , OSL(NUMPAD)   , CLOSE_TAB       , REOPEN_TAB      , OSL(SYMBOL) , KC_N   , KC_M    , KC_COMM , KC_DOT , KC_SLSH , LT(SHIFT, KC_BACKSLASH),
                          TD(WIN_TAPDANCE) , TD(ALT_TAPDANCE) , KC_ENT , OSM(MOD_LSFT) , TD(TMUX_SCROLL) , TD(TMUX_SCROLL) , KC_BSPC     , KC_SPC , KC_LBRC , KC_RBRC
),

//    ┌─────┬──────┬──────┬────────────┬─────────────┬────────┐                         ┌──────┬──────┬──────┬──────┬──────┬────────┐
//    │ tab │ kp_1 │ kp_2 │    kp_3    │    kp_4     │  kp_5  │                         │ kp_6 │ kp_7 │ kp_8 │ kp_9 │ kp_0 │  kp_-  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┤                         ├──────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │            │             │        │                         │      │ kp_4 │ kp_5 │ kp_6 │ kp_* │  kp_+  │
//    ├─────┼──────┼──────┼────────────┼─────────────┼────────┼─────┬─────┬──────┬──────┼──────┼──────┼──────┼──────┼──────┼────────┤
//    │     │      │      │ LINUX_COPY │ LINUX_PASTE │        │     │     │ pscr │      │      │ kp_1 │ kp_2 │ kp_3 │      │ kp_ent │
//    └─────┴──────┴──────┼────────────┼─────────────┼────────┼─────┼─────┼──────┼──────┼──────┼──────┼──────┼──────┴──────┴────────┘
//                        │            │             │ kp_ent │     │     │      │ bspc │ kp_0 │ kp_. │ kp_. │
//                        └────────────┴─────────────┴────────┴─────┴─────┴──────┴──────┴──────┴──────┴──────┘
[_NUMPAD] = LAYOUT(
  KC_TAB  , KC_KP_1 , KC_KP_2 , KC_KP_3    , KC_KP_4     , KC_KP_5     ,                                         KC_KP_6 , KC_KP_7   , KC_KP_8   , KC_KP_9 , KC_KP_0        , KC_KP_MINUS,
  _______ , _______ , _______ , _______    , _______     , _______     ,                                         _______ , KC_KP_4   , KC_KP_5   , KC_KP_6 , KC_KP_ASTERISK , KC_KP_PLUS ,
  _______ , _______ , _______ , LINUX_COPY , LINUX_PASTE , _______     , _______ , _______ , KC_PSCR , _______ , _______ , KC_KP_1   , KC_KP_2   , KC_KP_3 , _______        , KC_KP_ENTER,
                                _______    , _______     , KC_KP_ENTER , _______ , _______ , _______ , KC_BSPC , KC_KP_0 , KC_KP_DOT , KC_KP_DOT
),

//    ┌─────┬───┬───┬─────┬─────┬───┐                       ┌──────┬──────┬─────┬──────┬───┬─────┐
//    │  `  │ ` │ { │  }  │  @  │ * │                       │  !   │  :   │  (  │  )   │ ; │     │
//    ├─────┼───┼───┼─────┼─────┼───┤                       ├──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ ^ │ = │  #  │  $  │ _ │                       │ left │ down │ up  │ rght │ ~ │     │
//    ├─────┼───┼───┼─────┼─────┼───┼─────┬─────┬─────┬─────┼──────┼──────┼─────┼──────┼───┼─────┤
//    │     │ - │ < │  >  │  |  │ & │     │     │     │     │  %   │  +   │  [  │  ]   │ / │     │
//    └─────┴───┴───┼─────┼─────┼───┼─────┼─────┼─────┼─────┼──────┼──────┼─────┼──────┴───┴─────┘
//                  │     │     │ \ │  :  │  %  │     │     │      │      │     │
//                  └─────┴─────┴───┴─────┴─────┴─────┴─────┴──────┴──────┴─────┘
[_SYMBOL] = LAYOUT(
  KC_GRV  , KC_GRV        , KC_LCBR  , KC_RCBR , KC_AT   , KC_ASTR       ,                                             KC_EXCLAIM , KC_COLON , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_SCLN  , _______,
  _______ , KC_CIRCUMFLEX , KC_EQUAL , KC_HASH , KC_DLR  , KC_UNDERSCORE ,                                             KC_LEFT    , KC_DOWN  , KC_UP         , KC_RIGHT       , KC_TILDE , _______,
  _______ , KC_MINUS      , KC_LT    , KC_GT   , KC_PIPE , KC_AMPR       , _______  , _______    , _______ , _______ , KC_PERCENT , KC_PLUS  , KC_LBRC       , KC_RBRC        , KC_SLSH  , _______,
                                       _______ , _______ , KC_BACKSLASH  , KC_COLON , KC_PERCENT , _______ , _______ , _______    , _______  , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┬─────┐                       ┌──────┬──────┬──────┬──────┬─────┬─────┐
//    │  `  │  !  │  @  │  #  │  $  │  %  │                       │  ^   │  &   │  *   │  (   │  )  │  \  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┤                       ├──────┼──────┼──────┼──────┼─────┼─────┤
//    │     │     │     │     │     │     │                       │      │      │      │      │     │     │
//    ├─────┼─────┼─────┼─────┼─────┼─────┼─────┬─────┬─────┬─────┼──────┼──────┼──────┼──────┼─────┼─────┤
//    │     │     │     │     │     │     │     │     │     │     │ mply │ mute │ vold │ volu │     │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┼──────┼──────┼──────┴─────┴─────┘
//                      │     │     │     │     │     │     │     │      │      │      │
//                      └─────┴─────┴─────┴─────┴─────┴─────┴─────┴──────┴──────┴──────┘
[_SHIFT] = LAYOUT(
  KC_GRV  , KC_EXCLAIM , KC_AT   , KC_HASH , KC_DLR  , KC_PERCENT ,                                         KC_CIRCUMFLEX       , KC_AMPR , KC_ASTR , KC_LEFT_PAREN , KC_RIGHT_PAREN , KC_BACKSLASH,
  _______ , _______    , _______ , _______ , _______ , _______    ,                                         _______             , _______ , _______ , _______       , _______        , _______     ,
  _______ , _______    , _______ , _______ , _______ , _______    , _______ , _______ , _______ , _______ , KC_MEDIA_PLAY_PAUSE , KC_MUTE , KC_VOLD , KC_VOLU       , _______        , _______     ,
                                   _______ , _______ , _______    , _______ , _______ , _______ , _______ , _______             , _______ , _______
),

//    ┌─────┬─────┬─────────┬─────────┬────────────┬──────────────────┐                       ┌─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │     │         │         │            │     RGB_TOG      │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼────────────┼──────────────────┤                       ├─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUI │ RGB_SAI │  RGB_VAI   │ RGB_MODE_FORWARD │                       │     │     │     │     │     │     │
//    ├─────┼─────┼─────────┼─────────┼────────────┼──────────────────┼─────┬─────┬─────┬─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │     │ RGB_HUD │ RGB_SAD │  RGB_VAD   │ RGB_MODE_REVERSE │     │     │     │     │     │     │     │     │     │     │
//    └─────┴─────┴─────────┼─────────┼────────────┼──────────────────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┴─────┴─────┘
//                          │         │ TG(_MAGIC) │                  │     │     │     │     │     │     │     │
//                          └─────────┴────────────┴──────────────────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
[_MAGIC] = LAYOUT(
  _______ , _______ , _______ , _______ , _______    , RGB_TOG          ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUI , RGB_SAI , RGB_VAI    , RGB_MODE_FORWARD ,                                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , RGB_HUD , RGB_SAD , RGB_VAD    , RGB_MODE_REVERSE , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
                                _______ , TG(_MAGIC) , _______          , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

//    ┌─────┬─────┬──────────────────┬──────────────────┬──────────────────────┬──────────────────┐                       ┌────────────────────┬────────────────────┬─────────────────┬─────────────────┬──────────────────┬───────────────────┐
//    │     │     │ WMGMT_FULLSCREEN │                  │ WMGMT_NEXT_WALLPAPER │   WMGMT_TOP_33   │                       │  WMGMT_MONITOR_1   │  WMGMT_MONITOR_2   │ WMGMT_MONITOR_3 │ WMGMT_MONITOR_4 │  WMGMT_TOPLEFT   │  WMGMT_TOPRIGHT   │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┤                       ├────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_33   │ WMGMT_HCENTER_33 │    WMGMT_RIGHT_33    │ WMGMT_VCENTER_33 │                       │   WMGMT_LEFT_50    │   WMGMT_DOWN_50    │   WMGMT_UP_50   │ WMGMT_RIGHT_50  │ WMGMT_BOTTOMLEFT │ WMGMT_BOTTOMRIGHT │
//    ├─────┼─────┼──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┬─────┬─────┬─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┼──────────────────┼───────────────────┤
//    │     │     │  WMGMT_LEFT_66   │   WMGMT_CENTER   │    WMGMT_RIGHT_66    │ WMGMT_BOTTOM_33  │     │     │     │     │ WMGMT_PREV_MONITOR │ WMGMT_NEXT_MONITOR │                 │                 │                  │                   │
//    └─────┴─────┴──────────────────┼──────────────────┼──────────────────────┼──────────────────┼─────┼─────┼─────┼─────┼────────────────────┼────────────────────┼─────────────────┼─────────────────┴──────────────────┴───────────────────┘
//                                   │   TG(_WINDOW)    │                      │                  │     │     │     │     │                    │                    │   WMGMT_BASE    │
//                                   └──────────────────┴──────────────────────┴──────────────────┴─────┴─────┴─────┴─────┴────────────────────┴────────────────────┴─────────────────┘
[_WINDOW] = LAYOUT(
  _______ , _______ , WMGMT_FULLSCREEN , _______          , WMGMT_NEXT_WALLPAPER , WMGMT_TOP_33     ,                                         WMGMT_MONITOR_1    , WMGMT_MONITOR_2    , WMGMT_MONITOR_3 , WMGMT_MONITOR_4 , WMGMT_TOPLEFT    , WMGMT_TOPRIGHT   ,
  _______ , _______ , WMGMT_LEFT_33    , WMGMT_HCENTER_33 , WMGMT_RIGHT_33       , WMGMT_VCENTER_33 ,                                         WMGMT_LEFT_50      , WMGMT_DOWN_50      , WMGMT_UP_50     , WMGMT_RIGHT_50  , WMGMT_BOTTOMLEFT , WMGMT_BOTTOMRIGHT,
  _______ , _______ , WMGMT_LEFT_66    , WMGMT_CENTER     , WMGMT_RIGHT_66       , WMGMT_BOTTOM_33  , _______ , _______ , _______ , _______ , WMGMT_PREV_MONITOR , WMGMT_NEXT_MONITOR , _______         , _______         , _______          , _______          ,
                                         TG(_WINDOW)      , _______              , _______          , _______ , _______ , _______ , _______ , _______            , _______            , WMGMT_BASE
)
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(AUTOTAB):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

/*
const uint16_t PROGMEM dot_slash[] = {KC_DOT, KC_SLASH, COMBO_END};
combo_t key_combos[] = {
    COMBO(dot_slash, UP_DIR)
};
 */

/* layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _NUMPAD, _SYMBOL, _WINDOW);
    state = update_tri_layer_state(state, _NUMPAD, _SHIFT, _MAGIC);
    return state;
}; */
