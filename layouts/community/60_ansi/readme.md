# 60_ansi

This is the standard 60% ANSI keyboard layout. 

## Requirements

### 1. Layout defined

A keyboard's `.h` file needs to have `LAYOUT_60_ansi` defined

```c
#define LAYOUT_60_ansi( \
    K36, K37, K46, K47, K56, K57, K66, K67, K76, K77, K06, K07, K17,      K27, \
    K34, K35, K44, K45, K54, K55, K64, K65, K75, K05, K15, K16, K25, K24, \
    K32, K33, K43, K52, K53, K63, K73, K74, K03, K04, K13, K14, K23, \
    K31,      K42, K51, K61, K62, K71, K72, K01, K02, K11, K12, K21,  \
    K30, K40, K50,           K60,                     K70, K00, K10, K20  \
) { \
    { K00, K01,   K02,   K03, K04, K05, K06,   K07 }, \
    { K10, K11,   K12,   K13, K14, K15, K16,   K17 }, \
    { K20, K21,   KC_NO, K23, K24, K25, KC_NO, K27 }, \
    { K30, K31,   K32,   K33, K34, K35, K36,   K37 }, \
    { K40, KC_NO, K42,   K43, K44, K45, K46,   K47 }, \
    { K50, K51,   K52,   K53, K54, K55, K56,   K57 }, \
    { K60, K61,   K62,   K63, K64, K65, K66,   K67 }, \
    { K70, K71,   K72,   K73, K74, K75, K76,   K77 } \
}
)
```

This layout needs to match the layout defined in

        qmk_firmware/layouts/community/layout.json

### 2. Configuring rules.mk

`rules.mk` needs to have the following line:

        LAYOUTS = 60_ansi

### 3. Defining a keymap

A keymap must be defined at         

    qmk_firmware/layouts/community/60_ansi/yourfoldername/keymap.c   

This keymap must have a `LAYOUT_60_ansi` layout defined. 

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_60_ansi(
    QK_GESC, KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC, \
	KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS, \
    KC_LCTL, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,  \
    KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LALT, KC_LGUI,       KC_SPACE,             MO(1),   KC_RALT, KC_RGUI, KC_RCTL),
 };
```

## Usage

To make generate a hex file, type

    make yourkeyboard:yourfoldername

This hex file will contain a keymap with layout `LAYOUT_60_ansi` derived from

    qmk_firmware/layouts/community/60_ansi/yourfoldername/keymap.c
