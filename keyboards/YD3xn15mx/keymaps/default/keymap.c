// Copyright 2022 Thunderbird2086 (Thunderbird2086)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _ZOOM_M = 0,
  _ZOOM_W,
  //_MOUSE_,
  _RGB___,
  _ADJUST,
};

//  macOS       | Windows     |  Description
//  ------------+-------------+------------------------------------
//  SCMD(KC_A)  | LALT(KC_A)  |  Audio On/Off
//  SCMD(KC_D)  |             |  Switch to Dual Monitors
//  SCMD(KC_F)  | LALT(KC_F)  |  Enter/Exit Full Screen Mode
//  SCMD(KC_H)  | LALT(KC_H)  |  Show/Hide In-meeting Chat Panel
//  SCMD(KC_M)  |             |  Switch to Minimal Window
//  SCMD(KC_N)  | LALT(KC_N)  |  Switch Camera
//  SCMD(KC_S)  | LALT(KC_S)  |  Start/Stop Screen Sharing
//  SCMD(KC_T)  | LALT(KC_T)  |  Pause Screen Sharing
//  SCMD(KC_V)  | LALT(KC_V)  |  Video On/Off
//  SCMD(KC_W)  |             |  Switch to Speaker/Gallery View
//              | LALT(KC_F1) |  Switch to Speaker View
//              | LALT(KC_F2) |  Switch to Gallery View
//
//  LCMD(KC_L)  | LALT(KC_L)  |  Switch to Portrait/Landscape View
//  LCMD(KC_U)  | LALT(KC_U)  |  Show/Hide Participants Panel
//  LCMD(KC_W)  | LALT(KC_F4) |  Close Current Window

#define ZOOM_M DF(_ZOOM_M)
#define ZOOM_W DF(_ZOOM_W)
#define ______ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ZOOM_M] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                  SCMD(KC_V),                      SCMD(KC_A),
            KC_PGUP,    KC_PGDN,             KC_VOLD,    KC_VOLU,

   KC_ESC      , LCMD(KC_U)    , SCMD(KC_W)    , SCMD(KC_D)    , KC_ENT    ,
   TT(_ADJUST) , SCMD(KC_H)    , SCMD(KC_N)    , SCMD(KC_T)    , SCMD(KC_M),
   TT(_RGB___) , SCMD(KC_A)    , SCMD(KC_V)    , SCMD(KC_S)    , LCMD(KC_W)
   ),

  [_ZOOM_W] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                  LALT(KC_V),                      LALT(KC_A),
            KC_PGUP,    KC_PGDN,             KC_VOLD,    KC_VOLU,

   KC_ESC      , LALT(KC_U)    , LALT(KC_F1)   , LALT(KC_F2)   , KC_ENT       ,
   TT(_ADJUST) , LALT(KC_H)    , LALT(KC_N)    , LALT(KC_T)    , C(A(S(KC_H))),
   TT(_RGB___) , LALT(KC_A)    , LALT(KC_V)    , LALT(KC_S)    , LALT(KC_F4)
   ),

  [_RGB___] = LAYOUT(
                                    KC_MPLY,
                             KC_MPRV,    KC_MNXT,
                 KC_MSTP,                          KC_MUTE,
           KC_PGUP,    KC_PGDN,              KC_VOLD,    KC_VOLU,

   ______      , RGB_M_P       , RGB_M_B       , RGB_M_R       , RGB_MOD     ,
   TT(_ADJUST) , RGB_M_SW      , RGB_M_SN      , RGB_M_TW      , RGB_RMOD    ,
   MO(_RGB___) , RGB_M_X       , RGB_M_K       , RGB_M_G       , RGB_M_T    
  ),

  [_ADJUST] = LAYOUT(
                                    KC_MPLY,
                             KC_VOLD,    KC_VOLU,
                 KC_MSTP,                          KC_MUTE,
           KC_PGUP,    KC_PGDN,              KC_VOLD,    KC_VOLU,

   RESET       , ZOOM_W        , RGB_SAI       , RGB_VAI       , RGB_MOD     ,
   ______      , ZOOM_M        , RGB_SAD       , RGB_VAD       , RGB_RMOD    ,
   ______      , ______        , RGB_HUD       , RGB_HUI       , RGB_TOG
  ),
};


//layer_state_t layer_state_set_user(layer_state_t state) {
//  return update_tri_layer_state(state, _MOUSE_, _RGB___, _ADJUST);
//}
