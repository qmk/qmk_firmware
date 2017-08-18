#include "satan.h"

#define KC_____ KC_TRNS
#define KC_FN MO(1) // Fn
#define KC_FNLK TG(1) // Fn lock
#define KC_HOME LCTL(KC_A) // Home, or ctrl-a
#define KC_END LCTL(KC_E) // End, or ctrl-e

// When using this split right shift layout, k3c and k3d are no longer reversed
// as in other layouts
#define COMPACT_KEYMAP_SPLIT_RSHIFT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k49,\
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, \
	k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d  \
) COMPACT_KEYMAP ( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k49,\
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3d, k3c, \
	k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d  \
)

// Mark I keyboard layout for GH60 Satan
// http://www.keyboard-layout-editor.com/#/gists/e1cde292bd2094cc3b763206d4d2cfb5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 0: qwerty
    COMPACT_KEYMAP_SPLIT_RSHIFT(
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, NO,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NO,  ENT ,
        LSFT,FN , Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,FN,
        LCTL,LALT,LGUI,          SPC,                     RGUI,RALT,RCTL,FNLK
    ),
    // 1: fn layer
    COMPACT_KEYMAP(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,____,
        ____,VOLU,____,____,____,____,____,HOME,UP  ,END ,PGUP,____,____,____,
        ____,VOLD,MRWD,MPLY,MFFD,____,____,LEFT,DOWN,RGHT,PGDN,____,____,____,
        ____,____,MUTE,____,____,____,____,____,____,____,SLEP,____,____,____,
        ____,____,____,          ____,                    ____,____,____,____
    )
};
