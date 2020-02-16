#pragma once
#include "ninjonas.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum tapdance_types{
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum custom_tapdances{
  TD_ESC_CAPS = 0,
  TD_LBRC_BACK,
  TD_RBRC_FWD,
  TD_TAB_CTRLTAB,
  TD_GRV_CTRLGRV,
  TD_GUI_GUISPC,
  TD_W_CTRLW,
  TD_Q_GUIQ,
  TD_COPY_PASTE_NUMPAD,
  TD_Y_NUMPAD,
};

#define T_ESC  TD(TD_ESC_CAPS)    // Tap for ESC, double tap for CAPSLOCK
#define T_LBRC TD(TD_LBRC_BACK)   // Tap for [, double tap for back browser
#define T_RBRC TD(TD_RBRC_FWD)    // Tap for ], double tap for forward browser
#define T_TAB  TD(TD_TAB_CTRLTAB) // Tap for TAB, double tap for CTRL + TAB
#define T_GRV  TD(TD_GRV_CTRLGRV) // Tap for GRV, double tap for Cmd + GRV
#define T_GUI  TD(TD_GUI_GUISPC)  // Tap for Cmd, double tap for Cmd + Space
#define T_W    TD(TD_W_CTRLW)     // Tap for W, double tap for Cmd + W
#define T_Q    TD(TD_Q_GUIQ)      // Tap for Q, double tap for Cmd + Q
#define T_CPNU TD(TD_COPY_PASTE_NUMPAD)  // Tap for paste, hold for copy, double tap for NUMPAD
#define T_Y    TD(TD_Y_NUMPAD)     // Tap for Y, double tap for NUMPAD