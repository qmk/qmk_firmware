#pragma once

#undef MANUFACTURER
#undef PRODUCT
#define MANUFACTURER    "QMK"
#define PRODUCT         "HHKB QMK cinaeco"

// Increase "Tap" detection window. Avoid missing 'q' or 'z' when typing slowly.
#undef TAPPING_TERM
#define TAPPING_TERM 230
