<!-- 
     Copyright (C) 2020 Sendy YK <mr@sendyyk.com>.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program. If not, see <https://www.gnu.org/licenses/>.
-->

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

![LAYOUT_numpad_5x4](https://raw.githubusercontent.com/mrsendyyk/files/public/qmk/firmware/layouts/community/numpad_5x4/mrsendyyk/images/layout-numpad-5x4.png)

### 2. Configuring rules.mk

`rules.mk` needs to have the following line:

        LAYOUTS = numpad_5x4

### 3. Defining a Keymap

A keymap must be defined at         

    qmk_firmware/layouts/community/numpad_5x4/yourfoldername/keymap.c

This keymap must have a `LAYOUT_numpad_5x4` layout defined.

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_5x4(
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
                 KC_P0,   KC_PDOT, KC_PENT
    )
};
```

![_BASE](https://raw.githubusercontent.com/mrsendyyk/files/public/qmk/firmware/layouts/community/numpad_5x4/mrsendyyk/images/layout-numpad-5x4-keymap.png)

## Build The Firmware

Make example for keyboard (after setting up your build environment):

    make <keyboard_folder>:<keymap>

More information:
* [Setting Up Your QMK Environment](https://docs.qmk.fm/#/getting_started_build_tools)
* [More Detailed make Instructions](https://docs.qmk.fm/#/getting_started_make_guide)
* [The Complete Newbs Guide To QMK](https://docs.qmk.fm/#/newbs)
