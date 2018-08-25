# 75_ansi

This is the standard 75% ANSI keyboard layout. 

One may argue that having 3 1u keys to the right of spacebar
is not desired as two 1.5u keys. However, most 75% boards that
come out have that as the standard. 

## Requirements

### 1. Layout defined

A keyboard's `.h` file needs to have `LAYOUT_75_ansi` defined

```c
#define LAYOUT_75_ansi( \
    K5A, K5B, K5C, K5D, K5E, K5F, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O,     K5Q, \
    K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M,      K4O, K4P, \
    K3A, K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M,      K3O, K3P, \
    K2A, K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L,           K2O, K2P, \
    K1A,      K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K,      K1M, K1N, K1O, K1P, \
    K0A, K0B, K0C,                               K0J, K0K, K0L, K0M, K0N, K0O, K0P  \
) { \
  { K5A, K5B, K5C, K5D,   K5E,   K5F,   K5G,   K5H,   K5I,   K5J,   K5K, K5L,   K5M, K5N,   K5O, KC_NO, K5Q }, \
  { K4A, K4B, K4C, K4D,   K4E,   K4F,   K4G,   K4H,   K4I,   K4J,   K4K, K4L,   K4M, KC_NO, K4O, K4P,   KC_NO    }, \
  { K3A, K3B, K3C, K3D,   K3E,   K3F,   K3G,   K3H,   K3I,   K3J,   K3K, K3L,   K3M, KC_NO, K3O, K3P,   KC_NO    }, \
  { K2A, K2B, K2C, K2D,   K2E,   K2F,   K2G,   K2H,   K2I,   K2J,   K2K, K2L,   KC_NO, KC_NO, K2O, K2P,   KC_NO    }, \
  { K1A, KC_NO, K1C, K1D,   K1E,   K1F,   K1G,   K1H,   K1I,   K1J,   K1K, KC_NO, K1M, K1N,   K1O, K1P,   KC_NO    }, \
  { K0A, K0B, K0C, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0J,   KC_NO, K0K, K0L,   K0M, K0N,   K0O, K0P,   KC_NO    }  \
}
)
```

This layout needs to match the layout defined in

        qmk_firmware/layouts/community/75_ansi/layout.json

### 2. Configuring rules.mk

`rules.mk` needs to have the following line:

        LAYOUTS = 75_ansi

### 3. Defining a keymap

A keymap must be defined at         

    qmk_firmware/layouts/community/75_ansi/yourfoldername/keymap.c   

This keymap must have a `LAYOUT_75_ansi` layout defined. 

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_75_ansi(\
        KC_ESC,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_PAUS, KC_DEL,
        KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,          KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                                  KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT)
    };
```

## Usage

To make generate a hex file, type

    make yourkeyboard:yourfoldername

This hex file will contain a keymap with layout `LAYOUT_75_ansi` derived from

    qmk_firmware/layouts/community/75_ansi/yourfoldername/keymap.c
