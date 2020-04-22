#pragma once
#include "snowkuma.h"

// enum custom_tapdances{
//   TD_ESC_CAPS = 0,
//   TD_TAB_CTRLTAB,
//   TD_GRV_CTRLGRV,
//   TD_GUI_GUISPC,
//   TD_W_CTRLW,
//   TD_Q_GUIQ,
// };

 // Tap Dance Declarations
enum {
	TD_COPYCUT = 0,
  TD_LBRC_BACK,
  TD_RBRC_FWD,
	TD_RESET,
	TD_TILD,
  TD_ZOOM
};

#define T_CPYCUT TD(TD_COPYCUT) // Tap to copy, double tap for cut
#define T_LBRC TD(TD_LBRC_BACK) // Tap for [, double tap for back browser
#define T_RBRC TD(TD_RBRC_FWD)  // Tap for ], double tap for forward browser
#define T_RESET TD(TD_RESET)    // Tap 3x to reset (works on planck but not Corne)
#define T_TILD TD(TD_TILD)      // Tap for ~, double tap for ~/
#define T_ZOOM TD(TD_ZOOM)      // Tap for audio mute, double tap for video