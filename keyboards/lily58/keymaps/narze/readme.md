# narze's layout

## Key features

- Qwerty + [Colemak](https://colemak.com) layouts, and you can type Qwerty on software-level Colemak as well. Very useful for gaming or when your friend wanna type something but don't use Colemak.
- [(S)uper (D)uper Mode](/users/narze/readme.md)

## Build instructions

- `cd /path/to/qmk_firmware`
- Ensure latest libraries are loaded `make git-submodule`
- Flash to right hand side (Elite C) with `make lily58:narze:dfu` or `qmk flash -kb lily58 -km narze -b dfu`
- Flash to left hand side (Pro Micro) with `make lily58:narze:avrdude` or `qmk flash -kb lily58 -km narze -b avrdude`
