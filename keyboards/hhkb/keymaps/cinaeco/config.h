#ifndef CONFIG_CINAECO_H
#define CONFIG_CINAECO_H

#include "../../config.h"

#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION
#define MANUFACTURER    QMK
#define PRODUCT         HHKB QMK cinaeco
#define DESCRIPTION     HHKB on QMK Firmware with cinaeco keymap

// Increase "Tap" detection window. Avoid missing 'q' or 'z' when typing slowly.
#undef TAPPING_TERM
#define TAPPING_TERM 230

// Uncomment to enable NKRO by default. May cause issues with KVM switches.
//#define FORCE_NKRO

#endif
