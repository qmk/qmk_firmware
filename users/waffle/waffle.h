/* Copyright 2021 @waffle#0007
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

#pragma once
#include QMK_KEYBOARD_H
#include "wrappers.h"
#ifdef OLED_ENABLE
#include "oled.h"
#endif
#ifdef PIMORONI_TRACKBALL
#include "drivers/sensors/pimoroni_trackball.h"
void ball_increase_hue(void);
void cycle_white(void);
void decrease_color(void);
#endif

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum userspace_combos {
#ifdef OLED_ENABLE
    FLWR_RESET,
#endif
    RU_ENT,
    GH_QUOT,
    VM_QUES,
    CM_DQUO,
    TY_COLN,
    BN_UNDS,
    FJ_MINS,
    CV_SCLN,
    DF_BTN1,
    JK_BTN2,
    VB_WHD,
    NM_WHU,
    SD_MSD,
    KL_MSU,
    XC_CLICK
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum tapdance_types {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    TRIPLE_TAP,
    TRIPLE_HOLD
};

enum custom_tapdances {
    MSLGUI,
    OSLGUI,
    GCLIPST,
    QMK,
    DOCS,
};

uint8_t cur_dance(qk_tap_dance_state_t *state);
void msgui_finished(qk_tap_dance_state_t *state, void *user_data);
void msgui_reset(qk_tap_dance_state_t *state, void *user_data);
void gclipst_finished(qk_tap_dance_state_t *state, void *user_data);
void gclipst_reset(qk_tap_dance_state_t *state, void *user_data);
void oslgui_finished(qk_tap_dance_state_t *state, void *user_data);
void oslgui_reset(qk_tap_dance_state_t *state, void *user_data);
void dance_pep_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_qmk_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_doc_finished(qk_tap_dance_state_t *state, void *user_data);

enum userspace_custom_keycodes {
    CP_PSTE = SAFE_RANGE,
    ROFL,
#ifdef UNICODEMAP_ENABLE
    UNIT,
    UNIT2,
    TABLE1,
    TABLE2,
    LENNY,
    DANCE,
    SHRUG,
#endif
#ifdef PIMORONI_TRACKBALL
    BALL_HUI, //cycles hue
    BALL_WHT, //cycles white
    BALL_DEC, //decrease color
    BALL_SCR, //scroll
#endif
#ifdef RANDICT
    RWORD,
#endif
    ALT_TAB,
    MAKE
};

#ifdef UNICODEMAP_ENABLE
enum unicodemap_names {
    SIDE,
    UPAR,
    HAS,
    STAR,
    VIB
};
#endif

//---layers---
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define LWRSPC LT(_LOWER, KC_SPC)
#define RSEBSP LT(_RAISE, KC_BSPC)
//---general---
#define SFA SFT_T(KC_A)
#define SFCLN RSFT_T(KC_SCLN)
#define SFL SFT_T(KC_L)
#define SFEXM MT(MOD_LSFT, KC_F23)
#define SFPRN MT(MOD_RSFT, KC_F24)
#define ALTQ ALT_T(KC_Q)
#define ALTP ALT_T(KC_P)
#define ALT1 ALT_T(KC_1)
#define ALT0 ALT_T(KC_0)
#define CTLZ CTL_T(KC_Z)
#define CTLESC CTL_T(KC_ESC)
#define CTLSLH CTL_T(KC_SLSH)
#define CTLDOT CTL_T(KC_DOT)
#define CTLRGHT CTL_T(KC_RIGHT)
#define CLIPST C(S(KC_V))
#define LOCK G(KC_ESC)
//---tap dance---
#define DOCSTD TD(DOCS)
#define QMKTD TD(QMK)
#define MSLGTD TD(MSLGUI)
#define GCPTD TD(GCLIPST)
#define OSLGTD TD(OSLGUI)
//---unicode---
#define HAP X(SIDE)
#define ARWUP X(UPAR)
#define STARX X(STAR)
