<!--
 Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 
 This file is part of qmk_firmware.
 
 qmk_firmware is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 qmk_firmware is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
-->

# JJerrell's QMK Userspace

This userspace showcases my personal journey with QMK keyboards and aims to simplify additional development, reduce code duplication, and maintain a consistent experience across my current keyboards. My original userspace has been archived because I wanted to take the time to grasp _how_ what I was doing worked -- rather than copy/pasta and blind luck.

Some keyboard specific code is stored here because it's contextually relevant. It may be somewhat pedantic, but an effort has been made to wrap this code with preprocessor checks. i.e. `#if (defined(KEYBOARD_planck_ez))`.

## Daily Drivers

1. Ergodox EZ - My first mechanical love. Now the office keyboard (if we go back). After finding inferior travel cases for exorbitant amounts of money, I built a custom travel case out of a case designed for drones and maticulous work cutting guncase foam. Around $50 with plenty of foam left over for family LARPing weapons. I'll post a picture one of these days. It also has a spot for my wireless touchpad.
2. Planck EZ - The solution to not being able to sit at a desk 100% of the time and not being able to live without QMK for any amount of time. Karabiner-Elements disables the Macbook keyboard when this is plugged in and the planck sits ontop of it with a very short usb-c cable. Probably terrible for the built in keyboard but they screwed up this generation anyway.
3. Moonlander - Just when I thought it was over, the lovely people with ZSA did it again. This one stays at home on my desk.

## Features

- Keymap level customization
  - User methods implemented here will give the keymaps a chance to override functionality by optionally implementing relevant _keymap methods
- Layer Macros
  - WRAPPER defines in [wrapper.c] simplify consistent keymaps
- Leader key secrets
  - [jjerrell.c] sets up the functionality for this feature and calls into the leader_scan_secrets method.
  - TODO: add documentation for leader_scan_secrets implementation

## Issues

### Tap/hold keys and shifted keycodes

An immediate part of my love for QMK was it's ability to differentiate between holds and presses to a level where you can apply modifiers when a normal alpha code is held. This feature was the single-most health related improvement to adopting QMK, in my opinion.

Beloved as it may be it comes with some baggage; shifted keycodes will be applied as their unshifted counterparts. I've worked around this in the past but the solution this time is a close adoption of the symbol layer inspired by the Neo keyboard.

There is also a problem with relying on SFT_T() for all of your shifting needs because if you attempt to swap which fingers are holding it and don't release the first before pressing the second, shift won't register anymore. This could probably be fixed but it discourages typing in all caps because it becomes too tedious. However, most layers do have a dedicated shift key to counteract this when necessary.
