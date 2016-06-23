#ifndef KEYMAP_NORWEGIAN_H
#define KEYMAP_NORWEGIAN_H

#include "keymap_nordic.h"

// There are slight differrences in the keyboards in the nordic contries

// Norwegian redifinitions from the nordic keyset
#undef NO_ACUT
#define NO_ACUT	ALGR(NO_BSLS)  // ´
#undef NO_AE
#define NO_AE	KC_QUOT  // æ
#undef NO_BSLS
#define NO_BSLS KC_EQL  // '\'
#undef NO_CIRC
#define NO_CIRC LSFT(C_RBRC)  // ^
#undef NO_GRV
#define NO_GRV	LSFT(NO_BSLS)  //
#undef NO_OSLH
#define NO_OSLH	KC_SCLN  // ø
#undef NO_PIPE
#define NO_PIPE KC_GRV  // |

// Additional norwegian keys not defined in the nordic keyset
#define NO_AA	KC_LBRC  // å
#define NO_ASTR LSFT(KC_BSLS)  // *

// Norwegian unique MAC characters
#define NO_ACUT_MAC KC_EQL  // =
#define NO_APOS_MAC KC_NUBS  // '
#define NO_AT_MAC   KC_BSLS  // @
#define NO_BSLS_MAC ALGR(LSFT(KC_7)) // '\'
#define NO_DLR_MAC  LSFT(KC_4) // $
#define NO_GRV_MAC ALGR(NO_BSLS) // `
#define NO_GRTR_MAC LSFT(KC_GRV)  // >
#define NO_LCBR_MAC ALGR(LSFT(KC_8))  // }
#define NO_LESS_MAC KC_GRV  // >
#define NO_PIPE_MAC ALGR(KC_7)  // |
#define NO_RCBR_MAC ALGR(LSFT(KC_9))  // }

#endif
