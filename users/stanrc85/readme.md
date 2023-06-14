<!-- Copyright 2021 Stanrc85

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.-->

# Stanrc85's Standard Layout

Shared keymap between 60%, 65%, Alice layouts:
- 1upkeyboards60HSE
- Mark65
- Sneakbox Alice

## Keymap Notes
- Layer 0 is default QWERTY layout with additional custom features:
    - SpaceFN to function layer 2 on `Space`
    - `CTRL` when held and `ESC` when tapped on `CAPS LOCK`
    - Tap Dance on `Fn1` for `CTRL+ALT+DEL` and `WIN+L`
    - Tap Dance on `ESC` for `ESC` and  ` ` ` 

![Base QWERTY Layer](https://imgur.com/gvCkVUW.png)

- Layer 1 is default QWERTY with no custom features used mostly for gaming
    - Enabled by `Fn2+RCTL` from base layer

![Default ANSI Layer](https://imgur.com/2SAel0K.png)

- Layer 2 is Function layer:
    - F keys
    - Arrows
    - Volume and Media controls
    - AutoHotkey shortcuts based on [Speaker Control](https://github.com/stanrc85/Speaker-Control) script
        - AHK Mic is used to mute/unmute microphone
        - AHK Speaker switches audio output between headphones and speakers

![Function Layer](https://imgur.com/FUjG0pL.png)

- Layer 3 is RGB Underglow control and RESET
    - `Fn2+RCTL` used to toggle Default QWERTY layer on and off
    - `qmk compile` command on `Fn2+Enter`
    - `qmk flash` command on `Fn2+Shift+enter`

![RGB and RESET Layer](https://imgur.com/UPdhR12.png)



### Build
To build the firmware file associated with this keymap, simply run `make your_keyboard:stanrc85-ansi` or `make your_keyboard:stanrc85-alice`.
