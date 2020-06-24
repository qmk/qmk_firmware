#pragma once
#include "snowkuma.h"

// Tap Dance Declarations
enum { 
    TD_ANKASS = 0,
    TD_COPYCUT,
    TD_KRAKEN,
    TD_LBRC_BACK,
    TD_RBRC_FWD,
    TD_TILD,
    TD_TYPTEL,
    TD_ZOOM
};

#define T_ANKASS TD(TD_ANKASS)   // Tap for Anki, double tap for Assimil
#define T_CPYCUT TD(TD_COPYCUT)  // Tap to copy, double tap for cut
#define T_LBRC TD(TD_LBRC_BACK)  // Tap for [, double tap for back browser
#define T_RBRC TD(TD_RBRC_FWD)   // Tap for ], double tap for forward browser
#define T_KRAKEN TD(TD_KRAKEN)   // Tap to launch gitKraken, 3x to reset (works on planck but not on corne)
#define T_TILD TD(TD_TILD)       // Tap for ~, double tap for ~/
#define T_TYPTEL TD(TD_TYPTEL)   // Tap for TypeFu, double tap for Telegram
#define T_ZOOM TD(TD_ZOOM)       // Tap for audio mute, double tap for video