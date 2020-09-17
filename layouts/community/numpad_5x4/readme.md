# numpad_5x4

This is the Number Pad 5x4 layout. 

## Requirements

### 1. Layout Defined

A keyboard's `.h` file needs to have `LAYOUT_numpad_5x4` defined

```c
#define LAYOUT_numpad_5x4( \
	k00, k01, k02, k03, \
	k10, k11, k12,      \
	k20, k21, k22, k23, \
	k30, k31, k32,      \
	     k41, k42, k43  \
) { \
	{ k00,   k01, k02, k03   }, \
	{ k10,   k11, k12, KC_NO }, \
	{ k20,   k21, k22, k23   }, \
	{ k30,   k31, k32, KC_NO }, \
	{ KC_NO, k41, k42, k43   }  \
}
```

![LAYOUT_numpad_5x4](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/soyuz/assets/layout-numpad-5x4-with-gmk-metropolis.png)

### 2. Configuring rules.mk

`rules.mk` needs to have the following line:

        LAYOUTS = numpad_5x4

### 3. Defining a Keymap

A keymap must be defined at         

    qmk_firmware/layouts/community/60_ansi_arrow/yourfoldername/keymap.c

This keymap must have a `LAYOUT_numpad_5x4` layout defined.

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x4(
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
                 KC_P0,   KC_PDOT, KC_PENT
    )
};
```

![Default Layer [0]](https://raw.githubusercontent.com/mrsendyyk/my_qmk/master/soyuz/assets/keymap-with-gmk-metropolis.png)
