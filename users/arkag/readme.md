# Shot on Pixel 2 XL with Cheap Lamp at Work

![mmm, tasty](mechmini2.jpg)

# I don't know what I'm doing

Some links:
* [Layout File: Mech Mini 2](layout_mm2)
* [Userspace Header](arkag_h)
* [Userspace Main](arkag_c)

Here's a list of some things I have working with my currently [keyboard](mm2_home):

* Reactive (sort of) fading while typing, ported from [Velocikey](https://github.com/qmk/qmk_firmware/pull/3754).
* OS Switching, storing to EEPROM
* OS Specific Macros and Shortcuts(WIN+SHIFT+S for Windows and CMD+SHIFT+4 for MacOS)
* Flashing RGB LED on OS change
* Hex Unicode Macros dependent on OS(half works on Windows due to [WinCompose](https://github.com/SamHocevar/wincompose) not functioning properly just yet).
* "Sleep" function activates after 3 minutes (breathing).
* Markdown style macros for surround type __eve__ ~~ryw~~ *her* **eee** (apparently only certain places support underline and strikethrough ಠ__ಠ)

# License Stuff

Copyright 2018 arkag arkag@pm.me

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

[arkag_c]:    /users/arkag/arkag.c
[arkag_h]:    /users/arkag/arkag.h
[layout_mm2]: /keyboards/mechmini/v2/keymaps/arkag/keymap.c
[mm2_home]:   https://cartel.ltd/projects/mechmini2/
