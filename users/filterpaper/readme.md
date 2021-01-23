Copyright (C) 2021 @filterpaper

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Summary

Personal user space to share code for a few custom keyboards. See [Sharing Code Between Keymaps](../../docs/feature_userspace.md) for details and [custom quantum funtions](../../docs/custom_quantum_functions.md) for customisation.

# Supported Keyboard

* [BM40 HS RGB](../../keyboards/bm40hsrgb)
* [Planck rev6](../../keyboards/planck)
* [Corne Keyboard (CRKBD)](../../keyboards/crkbd)
* [The Mark: 65](../../keyboards/boardsource/the_mark)

# File list

* `config.h`	QMK configuration options, see [configuring QMK](../../docs/config_options.md)
* `rules.mk`	Makefile rules for keyboard-specific features, includes keyboard.c
* `keyboard.c`	Main file with shared codes, RGB matrix and OLED functions, see [RGB matrix lighting](../../docs/feature_rgb_matrix.md)
* `mod-status.c`	Graphical layer and modifier status rendering module for primary controller
* `bongo-cat.c`		Graphical tapping bongo cat rendering module, optimized for right OLED
* `bongo-cat-left.c`		Graphical tapping bongo cat rendering module, optimized for both sides
* `glcdfont.c`		Corne 8x6 font code with QMK Firmware Logo
* `rgb_matrix_user.inc` Custom RGB matrix effect collected from Reddit, see [Custom RGB Matrix](../../docs/feature_rgb_matrix.md#custom-rgb-matrix-effects-idcustom-rgb-matrix-effects)

## Build commands
```
qmk compile -kb bm40hsrgb -km filterpaper
qmk compile -kb planck/rev6 -km filterpaper
qmk compile -kb crkbd/rev1/common -km filterpaper
qmk compile -kb boardsource/the_mark -km filterpaper
```

## Corne Split Setup
Corne is configured with EE_HANDS, the controllers will check EEPROM values to know which side it's on and USB-C can be used on either.
These are the one-time flash commands to write left and right side setting into the Elite-C EEPROM:
```
make crkbd/rev1/common:filterpaper:dfu-split-left
make crkbd/rev1/common:filterpaper:dfu-split-right
```
Following this, the same firmware binary can be flashed normally on both sides. See [split keyboard features](../../docs/feature_split_keyboard.md) for details.

# Keymap layout

Individual keymap.c for each keyboard will have to be created and saved within their respective keymaps directory. See 
the [json folder](json/) for details and list of exported QMK Configurator layouts.
