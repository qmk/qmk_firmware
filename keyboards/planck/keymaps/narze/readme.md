# narze's layout

## Key features
- Qwerty + [Colemak](https://colemak.com) layouts, and you can type Qwerty on software-level Colemak as well. Very useful for gaming or when your friend wanna type something but don't use Colemak.
- [(S)uper (D)uper Mode](/users/narze/readme.md)
- Mouse keys with Z

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
