# ninjaPixel — Ferris Sweep keymap

A thin wrapper. All of the actual keymap (layers, configuration, shared code)
lives in the userspace at [`users/ninjaPixel-ferris/`](../../../../users/ninjaPixel-ferris/),
exactly like the Sofle keymap lives in `users/ninjaPixel/`.

This directory contains only:

| File        | Purpose                                                                 |
|-------------|-------------------------------------------------------------------------|
| `keymap.c`  | One line: `#include "ninjaPixel_ferris_keymap.h"` (the shared `keymaps`). |
| `rules.mk`  | Sets `USER_NAME := ninjaPixel-ferris` and enables Caps Word.             |

## Build

```sh
qmk compile -kb ferris/sweep -km ninjaPixel
# or
make ferris/sweep:ninjaPixel
```

## Flash

The Ferris Sweep uses Pro Micro controllers (Caterina bootloader), and each
half is flashed separately. Reset a half (double-tap its reset button, or
briefly bridge RST–GND) and then run the matching command:

```sh
# Left half (plug in / reset the LEFT half first):
make ferris/sweep:ninjaPixel:avrdude-split-left

# Right half (plug in / reset the RIGHT half first):
make ferris/sweep:ninjaPixel:avrdude-split-right
```

The `avrdude-split-left` / `avrdude-split-right` targets also write the
handedness flag for that half, so each side knows which is which.

You can also enter the bootloader without the reset button:

- **Bootmagic**: hold the top-outer key of a half while plugging it in.
- **Keycode**: press `QK_BOOT` (bottom-row corners of the **FN** layer).

See [`users/ninjaPixel-ferris/readme.md`](../../../../users/ninjaPixel-ferris/readme.md)
for the layer diagrams and customization notes.
