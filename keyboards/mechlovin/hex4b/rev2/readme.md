/*
Copyright 2021 Mechlovin' Studio

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
*/

# hex4b

![hex4b](https://i.imgur.com/lArfGgHh.jpeg)

A PCB for HEX.4B 75% keyboard.

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Hex.4B Rev.2 PCB, APM32F103CBT6
* Hardware Availability: [Hex Keyboard](https://hexkeyboards.com/)

Make example for this keyboard (after setting up your build environment):

    make mechlovin/hex4b/rev2:default

Flashing example for this keyboard:

    make mechlovin/hex4b/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Bootloader reset**: Hold down the key at (0,13) in the matrix (Backspace) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
* **Hardware reset**: Press reset button (located on the top side of the PCB)