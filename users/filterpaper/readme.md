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

Personal user space to share code for a few custom keyboards. See https://docs.qmk.fm/#/feature_userspace?id=userspace-sharing-code-between-keymaps for details and [custom quantum funtions](../../docs/custom_quantum_functions.md) for customisation.
## File list
* `config.h`	QMK configuration options, see [configuring QMK](../../docs/config_options.md)
* `rules.mk`	Makefile rules for keyboard-specific features, includes keyboard.c
* `keyboard.c`	Common keyboard code, RGB and OLED function functions
* `mod-status.c`	Graphical layer and modifier status rendering module
* `bongo-cat.c`		Graphical tapping bongo cat rendering module, optimized for right OLED
* `bongo-cat-left.c`		Graphical tapping bongo cat rendering module, includes left-optimized cat
* `glcdfont.c`		Corne 8x6 font code with QMK Firmware Logo

## Compile commands
```
qmk compile -kb the_mark -km filterpaper
qmk compile -kb bm40hsrgb -km filterpaper
qmk compile -kb planck/rev6 -km filterpaper
qmk compile -kb crkbd/rev1/common -km filterpaper
```

### Split keyboard
Corne is configured with EE_HANDS, the controllers will check EEPROM values to know which side it's on and USB-C can be used on either.
These are the one time flash commands to write left and right side setting into the Elite-C EEPROM:
```
make crkbd/rev1/common:filterpaper:dfu-split-left
make crkbd/rev1/common:filterpaper:dfu-split-right
```
Following this, the same firmware binary can be flashed normally to both sides. See [split keyboard features](../../docs/feature_split_keyboard.md) for more details.

## Keymap layout

Individual keymap.c for each keyboard will have to be generated and saved within their respective keymaps directory. See 
the [json folder](json/) for details and list of exported QMK Configurator layouts.
