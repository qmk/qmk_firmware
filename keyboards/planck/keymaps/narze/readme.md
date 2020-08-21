# narze's layout

## Key features
- Qwerty + [Colemak](https://colemak.com) layouts, and you can type Qwerty on software-level Colemak as well. Very useful for gaming or when your friend wanna type something but don't use Colemak.
- [(S)uper (D)uper Mode](https://github.com/jasonrudolph/keyboard#super-duper-mode) inspired by [jasonrudolph](https://github.com/jasonrudolph), with [some extensions](https://gist.github.com/narze/861e2167784842d38771) such as backspace & forward delete.
- Mouse keys with Z

## (S)uper (D)uper Mode
Press `S+D` simultaneously and hold, then...
- `H/J/K/L` for Vim-like movement
- `I/O` to move between browser tabs (Not working on Windows yet)
- `A` for `Option (Alt)`
- `F/;` for `Backspace/Forward delete`
- `A` with `H/L` to move to previous/next word
- `A` with `G/;` to delete to previous/next word
- `G` for `Cmd` (Gui/Windows)
- Available for all layouts (but plover) using physical S & D keys position in qwerty
- `Spacebar` for `Shift` (it's easier when already holding A with your pinky)
- Disable with `Raise+Lower+M`
- You can edit or add more useful keys in SUPERDUPER layer
- It can be activated by holding `/` as well, but it's slower since `LT()` uses `TAPPING_TERM` of 200ms but `S+D` uses `COMBO_TERM` of only 20ms (Can be changed within config.h)

## Build instructions
- `cd /path/to/qmk_firmware`
- Ensure latest libraries are loaded `make git-submodule`
- Build with docker
  - Planck Rev. 4 : `util/docker_build.sh planck/rev4:narze`
  - Planck Light : `util/docker_build.sh planck/light:narze`
- Flash hex file
  - Using dfu-programmer `dfu-programmer atmega32u4 erase --force && dfu-programmer atmega32u4 flash .build/planck_rev4_narze.hex`
    - For Planck Light change the target microcontroller `dfu-programmer at90usb1286 erase --force && dfu-programmer at90usb1286 flash .build/planck_light_narze.hex`
  - Use [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
