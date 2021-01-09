Copyright 2021 @filterpaper

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

Common user space code for a few custom keyboards. See https://docs.qmk.fm/#/feature_userspace?id=userspace-sharing-code-between-keymaps for more details.
## File list
* `config.h`	Self-explainatory QMK configuration options
* `rules.mk`	Makefile rules for common and keyboard-specific features
* `keyboard.c`	Common keyboard code and RGB specific functions
* `oled.c`		Corne split keyboard OLED code with bongo cat

## Compile commands
```
qmk compile -kb the_mark -km filterpaper
qmk compile -kb bm40hsrgb -km filterpaper
qmk compile -kb planck/rev6 -km filterpaper
qmk compile -kb crkbd/rev1/common -km filterpaper
qmk compile -kb kbdfans/kbd67/mkiirgb/v2 -km filterpaper
```

### Split keyboard
Corne is configured with EE_HANDS so the controller will check EEPROM values to know which side its on, and USB-C can be connected to either side.
These are the one time flash commands to write left and right side setting into the Elite-C EEPROM:
```
make crkbd/rev1/common:filterpaper:dfu-split-left
make crkbd/rev1/common:filterpaper:dfu-split-right
```
The same firmware can be flashed normally to both sides after this.
