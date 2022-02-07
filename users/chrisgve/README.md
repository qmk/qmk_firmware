Copyright 2022 Christian C. Berclaz @chrisgve

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.


# Definitions and code for various keyboards

This snippet serves two main purposes

- It helps managing keyboard lighting (matrix or backlight) to indicate the state of certain layers or to indicate the state of Caps Lock
- It provide definitions necessary to build consistent layouts across different type of keyboards (Ortho, 45%, 60%, etc.) with a focus on the middle row and its neighbourghs

## Concept

### Overall layout

The base concept is to work around a HHKB format or a close derivative as below
|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
| --- |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
| Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bkspc |
| Ctrl |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |      Return    |
| Shift |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |      Shift    | Fn  |
| Ctrl | Alt | Gui |                     Space                         | Alt | Gui | Ctrl |

### Functionality

Generally the keyboard must remain functional whether used on MacOS, Linux, or Windows. However given the extensions implemented it is not just a matter of exchanging Alt and Gui, instead layouts are duplicated and additional functions are customized for each system where necessary. The default layout should be either set temporarily or permanently (EEPROM) at restart.

There is a mouse mode that can be temporary, eg while holding a key (A), or by switching to a mouse layer and then back to the default layer.

### Navigation and Vim

Navigation is toggled via pressing S and which toggle a layer for navigation (typically vim-like navigation), from layer S or from base layer pressing F toggles another navigation for further navigation (typically Home/PgDn/PgUp/End). Optionally the main navigation layer has alternative Home/End (convenient when using Excel) and main Vim copy/del/paste (Y/X/P) these are OS specific.

### Colors

For keyboard with RGB lighting, layers are tracked and color is set for
- the main navigation layer, "S-layer"
- the further navigation layer, "F-layer"
- the mouse layers
- the function/adjust layer
- caps lock on
- numpad mode (Generally used only for Ortho layouts)

## Color management based on layer or Key caps state

Colors are defined as follow
- `RGB_CAPS_R/G/B`  Color used for caps lock
- `RGB_NAV1_R/G/B`  Color used for the "S-layer"
- `RGB_NAV2_R/G/B`  Color used for the "F-layer"
- `RGB_MSE_R/G/B`   Color used for the mouse layers
- `RGB_ADJ_R/G/B`   Color used for the function/adjust layers
- `RGB_NUM_R/G/B`   Color used for numpad mode

## Reusable definitions and code

### Standard layouts

- `_QWERTY_MAC`: default layer for Mac
- `_MAC_NAV_1`: S-layer for Mac
- `_MAC_NAV_2`: F-layer for Mac
- `_QWERTY_LINUX`: default layer for Linux
- `_LINUX_NAV_1`: S-layer for Linux
- `_LINUX_NAV_2`: F-layer for Linux
- `_QWERTY_WIN`: default layer for Windows
- `_WIN_NAV_1`: S-layer for Windows
- `_WIN_NAV_2`: F-layer for Windows
- `_RAISE`: Raise layer for ortho
- `_LOWER`: Lower layer for ortho
- `_MOUSE`: Temporary mouse layer
- `_EX_MOUSE`: Exclusive mouse layer
- `_ADJUST_MAC`: Adjust/Function layer for Mac
- `_ADJUST_LINUX`: Adjust/Function layer for Linux
- `_ADJUST_WIN`: Adjust/Function layer for Windows

### Custom keycodes

- `DF_M_P`: Make the Mac layer the default persistent layer (EEPROM)
- `DF_L_P`: Make the Linux layer the default persistent layer
- `DF_W-P`: Make the Windows layer the default persistent layer
- `CU_BSPC`: Backspace key and Delete key when combined with Ctrl (L or R)
