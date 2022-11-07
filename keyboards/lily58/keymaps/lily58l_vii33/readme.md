# Lily58L by vii33
<img src="https://i.postimg.cc/3JsQJJV0/lily58l-logo-vii33.jpg" width="900">

Heavily modified keymap for better ergonomics compared to the original keymap by [BenRoe](https://github.com/BenRoe) from [Keycapsss.com](https://keycapsss.com).

For further explanation see [github.com/vii33](https://github.com/vii33/mecha-keyboard-lily58l).

## Changes
- Added [Luna](https://youtu.be/HgIQRazCAjo), the interactive dog, and Mario World screen.
- changed encoder direction (clockwise should be **louder**/**scroll down** :) )
- Re-did Lower and Upper Layer completely to be more sensible and reduce the number of cross-hand keystrokes, e.g. 
  - F-keys are now in the same place as number keys
  - Brackets are easily reachable with the right hand
  - Numpad resembles real numpad layout
- Added mod-taps for `Shift` <-> `Space`
- Added home [row modifiers](https://precondition.github.io/home-row-mods) for `Ctrl`, `Alt`, `Win`
- Optimized one-hand use with left hand on keyboard and right hand on mouse (Delete, Enter, Cut, Copy...)
- Added 'Game' Layer without special functions
- Included German special keys
- Added possibility to adjust RGB colors & brightness with encoders
- Added specific keys to start RGB animations
- Updated legacy LED animation `#defines`
- Reduced OLED refresh rate to improve matrix scan rate
- Included Words-per-minute metric counter (used for luna)
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
    