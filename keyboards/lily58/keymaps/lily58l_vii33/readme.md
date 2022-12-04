# Lily58L by vii33
<img src="https://images2.imgbox.com/00/5d/Xx4Zji9L_o.jpg" width="900" alt="Lily58l keyboard image">

Lily58l keyboard design by [BenRoe](https://github.com/qmk/qmk_firmware/tree/master/keyboards/lily58/keymaps/lily58l) with a heavily modified keymap for better ergonomics compared to the original.

> For further explanation and full keymap see [https://github.com/vii33/mecha-keyboard-lily58l](https://github.com/vii33/mecha-keyboard-lily58l).

## Changes
- Added [Luna](https://youtu.be/HgIQRazCAjo), the interactive keyboard dog.
- Re-did Lower and Upper Layer completely to be more sensible and reduce the number of cross-hand keystrokes, e.g. 
  - F-keys are now in the same place as number keys
  - All brackets are easily reachable with the right hand (developers)
  - Numpad resembles real numpad layout
- Added mod-taps for `Shift` <-> `Space`
- Added home [row modifiers](https://precondition.github.io/home-row-mods) for `Ctrl`, `Alt`, `Win`
- Changed encoder direction (clockwise should be **louder**/**scroll down** :) )
- Reduced LED brightness as default value is sometimes too much for the controller (imo)
- Optimized one-hand use with left hand on keyboard and right hand on mouse (Delete, Enter, Cut, Copy...)
- Added 'Game' Layer without special mod keys
- Included German special characters
- Added possibility to adjust RGB colors & brightness with encoders (turn walks through the color wheel)
- Added keys to start the predefined RGB animations (breathing, snake, ...)
- Refactored legacy LED #defines
- Reduced OLED refresh rate to improve matrix scan rate
- Included words-per-minute metric counter (used for Luna)
- more stuff...


## Original Board Description
A modified Lily58 pcb, with underglow, per key rgb light and rotary encoder support.
- SK6812 Mini-E per key led's (58x) for easy soldering
- 6x SK6812 Mini led's per side for underglow
- Support for 1 rotary encoder on each side

* Keyboard Maintainer: BenRoe [GitHub](https://github.com/BenRoe) / [Twitter](https://twitter.com/keycapsss)
* Hardware Supported: Pro Micro, or Elite-C
* Hardware Availability: [Keycapsss.com](https://keycapsss.com)

## Compiling

 Compiling example for this keyboard ([after setting up your build environment](https://docs.qmk.fm/#/getting_started_build_tools)):
 
    qmk compile -j 0 -kb lily58/light -km lily58l_vii33

Flashing example for this keyboard (left side):

    qmk flash -kb lily58/light -km lily58l_vii33 -bl dfu-split-left
    