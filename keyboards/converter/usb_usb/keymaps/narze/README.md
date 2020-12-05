# narze's layout for usb-usb converter

## Key features
- Qwerty + [Colemak](https://colemak.com) layouts, and you can type Qwerty on software-level Colemak as well. Very useful for gaming or when your friend wanna type something but don't use Colemak.
- [(S)uper (D)uper Mode](https://github.com/jasonrudolph/keyboard#super-duper-mode) inspired by [jasonrudolph](https://github.com/jasonrudolph), with [some extensions](https://gist.github.com/narze/861e2167784842d38771) such as backspace & forward delete.

## Build instructions
- `cd /path/to/qmk_firmware`
- Ensure latest libraries are loaded `make git-submodule`
- Build & flash : `make converter/usb_usb:narze:flash`
