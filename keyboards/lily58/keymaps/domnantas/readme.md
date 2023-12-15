# Domnantas layout for Lily58 Pro

## Features

- Optimised for lithuanian layout, but works on English too
- Backspace, Enter and Space are under thumbs, very little hand movement
- LShift swapped with LCtrl
- Numpad on Lower layer for left hand
- Navigation, media keys on Raise layer for right hand
- Status on the left OLED
- BONGOCAT on the right

## Instructions
Since status is always on the left and Bongocat on the right, the keymap has to be flashed with different commands:

```bash
# Right hand
qmk flash -kb lily58/rev1 -km domnantas -bl avrdude-split-left
# Left hand
qmk flash -kb lily58/rev1 -km domnantas -bl avrdude-split-right
```