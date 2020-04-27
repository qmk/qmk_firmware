#pragma once

#ifdef KEYBOARD_jian_handwired
  #include "handwired.h"
#endif

#ifdef KEYBOARD_jian_nsrev1
  #include "nsrev1.h"
#endif

#ifdef KEYBOARD_jian_rev2
#include "rev2.h"
#endif

#ifdef KEYBOARD_jian_rev1
  #include "rev1.h"
#endif

#define QWERTY_base  KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH


#define DVORAK_base  KC_GRV, KC_QUOT, KC_COMM, KC_DOT,KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_LBRC, KC_RBRC, \
                             KC_A,    KC_O,    KC_E,  KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH, \
                             KC_SCLN, KC_Q,    KC_J,  KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z
#define COLEMAK_base KC_GRV, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U,    KC_Y,   KC_SCLN, KC_LBRC, KC_RBRC, \
                             KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E,    KC_I,   KC_O,    KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define WORKMAN_base KC_GRV, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U,    KC_P,   KC_SCLN, KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_H, KC_T, KC_G, KC_Y, KC_N, KC_E,    KC_O,   KC_I,    KC_QUOT, \
                             KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH

#ifdef ALT_LAYOUTS_ENABLE

#include <keymap_dvorak.h>
#include <keymap_colemak.h>
#include <keymap_workman.h>

#define DVK2QWE_base DV_GRV, DV_Q, DV_W, DV_E, DV_R, DV_T, DV_Y, DV_U, DV_I,    DV_O,   DV_P,    DV_LBRC, DV_RBRC, \
                             DV_A, DV_S, DV_D, DV_F, DV_G, DV_H, DV_J, DV_K,    DV_L,   DV_SCLN, DV_QUOT, \
                             DV_Z, DV_X, DV_C, DV_V, DV_B, DV_N, DV_M, DV_COMM, DV_DOT, DV_SLSH
#define CMK2QWE_base KC_GRV, CM_Q, CM_W, CM_E, CM_R, CM_T, CM_Y, CM_U, CM_I,    CM_O,   CM_P,    KC_LBRC, KC_RBRC, \
                             CM_A, CM_S, CM_D, CM_F, CM_G, CM_H, CM_J, CM_K,    CM_L,   CM_SCLN, KC_QUOT, \
                             CM_Z, CM_X, CM_C, CM_V, CM_B, CM_N, CM_M, CM_COMM, CM_DOT, CM_SLSH
#define WMN2QWE_base KC_GRV, WK_Q, WK_W, WK_E, WK_R, WK_T, WK_Y, WK_U, WK_I,    WK_O,   WK_P,    KC_LBRC, KC_RBRC, \
                             WK_A, WK_S, WK_D, WK_F, WK_G, WK_H, WK_J, WK_K,    WK_L,   WK_SCLN, KC_QUOT, \
                             WK_Z, WK_X, WK_C, WK_V, WK_B, WK_N, WK_M, KC_COMM, KC_DOT, KC_SLSH
#define CMK2DVK_base KC_GRV, KC_QUOT, KC_COMM, KC_DOT,CM_P, CM_Y, CM_F, CM_G, CM_C, CM_R, CM_L, KC_LBRC, KC_RBRC, \
                             CM_A,    CM_O,    CM_E,  CM_U, CM_I, CM_D, CM_H, CM_T, CM_N, CM_S, CM_SLSH, \
                             CM_SCLN, CM_Q,    CM_J,  CM_K, CM_X, CM_B, CM_M, CM_W, CM_V, CM_Z
#define WMN2DVK_base KC_GRV, KC_QUOT, KC_COMM, KC_DOT,WK_P, WK_Y, WK_F, WK_G, WK_C, WK_R, WK_L, KC_LBRC, KC_RBRC, \
                             WK_A,    WK_O,    WK_E,  WK_U, WK_I, WK_D, WK_H, WK_T, WK_N, WK_S, KC_SLSH, \
                             WK_SCLN, WK_Q,    WK_J,  WK_K, WK_X, WK_B, WK_M, WK_W, WK_V, WK_Z
#define DVK2CMK_base DV_GRV, DV_Q, DV_W, DV_F, DV_P, DV_G, DV_J, DV_L, DV_U,    DV_Y,   DV_SCLN, DV_LBRC, DV_RBRC, \
                             DV_A, DV_R, DV_S, DV_T, DV_D, DV_H, DV_N, DV_E,    DV_I,   DV_O,    DV_QUOT, \
                             DV_Z, DV_X, DV_C, DV_V, DV_B, DV_K, DV_M, DV_COMM, DV_DOT, DV_SLSH
#define WMN2CMK_base KC_GRV, WK_Q, WK_W, WK_F, WK_P, WK_G, WK_J, WK_L, WK_U,    WK_Y,   WK_SCLN, KC_LBRC, KC_RBRC, \
                             WK_A, WK_R, WK_S, WK_T, WK_D, WK_H, WK_N, WK_E,    WK_I,   WK_O,    KC_QUOT, \
                             WK_Z, WK_X, WK_C, WK_V, WK_B, WK_K, WK_M, KC_COMM, KC_DOT, KC_SLSH
#define DVK2WMN_base DV_GRV, DV_Q, DV_D, DV_R, DV_W, DV_B, DV_J, DV_F, DV_U,    DV_P,   DV_SCLN, DV_LBRC, DV_RBRC, \
                             DV_A, DV_S, DV_H, DV_T, DV_G, DV_Y, DV_N, DV_E,    DV_O,   DV_I,    DV_QUOT, \
                             DV_Z, DV_X, DV_M, DV_C, DV_V, DV_K, DV_L, DV_COMM, DV_DOT, DV_SLSH
#define CMK2WMN_base KC_GRV, CM_Q, CM_D, CM_R, CM_W, CM_B, CM_J, CM_F, CM_U,    CM_P,   CM_SCLN, KC_LBRC, KC_RBRC, \
                             CM_A, CM_S, CM_H, CM_T, CM_G, CM_Y, CM_N, CM_E,    CM_O,   CM_I,    KC_QUOT, \
                             CM_Z, CM_X, CM_M, CM_C, CM_V, CM_K, CM_L, CM_COMM, CM_DOT, CM_SLSH

#endif // ALT_LAYOUTS_ENABLE
