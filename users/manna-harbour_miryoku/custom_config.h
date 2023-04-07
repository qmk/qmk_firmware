// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// Caps Word configuration
#ifdef COMMAND_ENABLE
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL) //debug commands accessed by holding down both CTRLs: https://github.com/qmk/qmk_firmware/blob/master/docs/feature_command.md
#endif

#define BILATERAL_COMBINATIONS

// TODO: Retro Shift 
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

// TODO: Combined mod-tap on the lower row (ctrl+shift etc.)
#define MIRYOKU_LAYER_BASE \
KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,           \
LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              RSFT_T(KC_N),      RCTL_T(KC_E),      RALT_T(KC_I),      RGUI_T(KC_O),      \
LT(U_BUTTON,KC_Z), ALGR_T(KC_X),      KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           ALGR_T(KC_DOT),    LT(U_BUTTON,KC_SLSH),\
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_NUM,KC_ENT),  LT(U_SYM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_SYM_BREAK15 \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,           \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,           \
U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// getreuer https://getreuer.info/posts/keyboards/symbol-layer/index.html
#define MIRYOKU_LAYER_SYM \
KC_QUOT,           KC_LABK,           KC_RABK,           KC_DQUO,           KC_GRV,            KC_AMPR,           U_NA,              KC_LBRC,           KC_RBRC,           KC_PERC,           \
KC_EXLM,           KC_MINS,           KC_PLUS,           KC_EQL,            KC_HASH,           KC_PIPE,           U_NA,              KC_LPRN,           KC_RPRN,           KC_QUES,           \
KC_CIRC,           KC_SLSH,           KC_ASTR,           KC_BSLS,           U_NA,              KC_TILD,           KC_DLR,              KC_LCBR,           KC_RCBR,           KC_AT,             \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              U_NA,            KC_DOT,            U_NP,              U_NP

#define MIRYOKU_LAYER_NUM \
KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           KC_AA,             TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  TD(U_TD_U_TAP),    TD(U_TD_BOOT),     \
KC_SCLN,           KC_4,              KC_5,              KC_6,              KC_EQL,            KC_OE,             KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS,           KC_AE,             TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    KC_ALGR,           U_NA,              \
U_NP,              U_NP,              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_LAYER_NAV \
U_UND,             U_CUT,             U_CPY,             U_PST,             U_RDO,             U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,             \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           \
U_NA,              KC_ALGR,           TD(U_TD_U_NUM),    TD(U_TD_U_NAV),    U_NA,              KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP
