Keyboard Firmware for https://retrogames.biz/thec64  TheC64 Mini 
Keyboard produced by Bleugh.biz
(this code is - modified from Atomic keyboard firmware)

I recommend https://msys.qmk.fm/ QMK MSYS , it's super easy.

Keyboard Maintainer: [Dean Woodyatt (https://github.com/bleughb/)]

The Keyboard Matrix is the same as the original Commodore 64, a 9x9 grid. I've also incorporated a header on the C64 Mini keyboard PCB to allow a genuine C64 keyboard to connect via USB to a PC or the Mini.

======================
DIY/Assembled  C64 Mini Keyboard Kit - Commodore 64 Keyboard - from [ BLEUGH ](www.bleugh.biz).

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/C64 Folder

### Default
To build with the default keymap, simply run qmk compile -kb c64 -km default

### Other Keymaps
The keymap is in the Keymaps folder. I'm still learning all about QMK - but feel free to tinker around, i'll help where I can. I'd recommend making a copy of the keymap file and calling it CUSTOMkemap or something similar, that way when you 'play' you have a fallback
A plan is to have dedicated keymaps for PC connection and C64 mini connection. Eventually maybe even to be able to toggle them with button presses

```
To build with the new keymap, simply run 'qmk compile -kb c64 -km CUSTOM(whateveryournameis)'
```
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.
