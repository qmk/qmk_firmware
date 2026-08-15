# Ferris Sweep — ninjaPixel keymap

A **Colemak** keymap for the Ferris Sweep.

## Hardware / converter

The stock `ferris/sweep` definition targets an **AVR Pro Micro** (ATmega32u4),
which builds a `.hex` and flashes over the `caterina` serial bootloader. Our
board is a generic **RP2040 Pro Micro** (USB-C) instead.

The switch is handled entirely by `keymap.json`:

```json
{
    "converter": "rp2040_ce"
}
```

`rp2040_ce` is the "Community Edition" Pro Micro RP2040 pinout that generic
RP2040 Pro Micro clones follow (and the same converter used by the Sofle Pro).
Do **not** use `promicro_rp2040` — it is deprecated and targets the specific
SparkFun board. (For the Sweep the two are electrically identical anyway: the
only pins that differ are RGB/VBUS pins this board doesn't use.)

QMK's converter system remaps the Pro Micro pin names from the board's
`keyboard.json` (the direct matrix pins and the `D2` split-serial pin) onto the
equivalent RP2040 GPIOs, and changes the build output from `.hex` to `.uf2`.

## Build

```bash
qmk compile -kb ferris/sweep -km ninjaPixel
```
## Flash

```bash
qmk flash -kb ferris/sweep -km ninjaPixel
```

When the CLI says it is looking for the device then put hit the `QK_BOOT` key (it's on the `LAYER_PICKER` layer, where the `B` key is).

## Generate keymap SVG

This uses [`keymap-drawer`](https://github.com/caksoylar/keymap-drawer), the same
tool the Sofle keymap uses (see `users/ninjaPixel/readme.md` for the one-time
install of `pipx` + `keymap-drawer`). Run from the repository root:

```bash
qmk c2json -kb ferris/sweep -km ninjaPixel --no-cpp \
    keyboards/ferris/sweep/keymaps/ninjaPixel/keymap.c \
  | keymap parse -c 10 -q - \
      -l Colemak "Layer Picker" Numbers "Fn Keys" Secondary \
  | sed 's/layout_name: LAYOUT}/layout_name: LAYOUT_split_3x5_2}/' \
  > keymap_vis.yaml \
  && keymap draw keymap_vis.yaml \
       > keyboards/ferris/sweep/keymaps/ninjaPixel/keymap.svg
```

The result is [`keymap.svg`](keymap.svg) in this directory.

### How this differs from the Sofle command

The Sofle's `keymap.c` is just `#include "ninjaPixel_keymap.h"`, so its command
passes that userspace header as the file to parse. Here the `LAYOUT()` calls live
directly in this keymap's own `keymap.c`, so we point `c2json` at `keymap.c`
instead. Three Sweep-specific details:

- **`--no-cpp` + explicit `keymap.c` path.** Letting `c2json` run the C
  preprocessor fails here, so we parse the file as raw text with `--no-cpp` (same
  as the Sofle). With `--no-cpp` you *must* pass the file path positionally —
  `-km ninjaPixel` alone is not enough for it to locate the file.
- **The `sed` layout rename.** `keymap.c` calls the layout `LAYOUT`, but the
  alias `keymap-drawer` knows for `ferris/sweep` is its canonical name,
  `LAYOUT_split_3x5_2`. The `sed` rewrites `layout_name:` so `keymap draw` can
  find the matching 3x5+2 split physical layout. Without it, `draw` errors with
  *"Could not find layout 'LAYOUT'"*.
- **`-c 10`** matches the 10 non-thumb columns (5 per half), and `-l ...` renames
  the five layers (otherwise they render as `L0`–`L4`).

### Caveat: unexpanded macros

As with the Sofle, `--no-cpp` means custom/compound keycodes are not expanded, so
keys like `OSL(_LAYER_PICKER)`, `LT(_SECONDARY, KC_SPC)` and `TO(_NUMBERS)` show
their raw macro text on the layer/thumb keys. This is cosmetic only. To prettify
them, hand-edit the labels in `keymap_vis.yaml` before the `keymap draw` step.


### notes

Unlike the AVR board, the RP2040 is flashed by copying a `.uf2` file onto a
mass-storage drive — `qmk flash` automates the copy.

If I'm unable to use the `QMK_BOOT` key for whatever reason, then I should be able to put each half into boot mode by following this:

> You'll need to bridge the boot to the pin to the right of it (the 3rd soldered one from the top) while plugging it in.
From there a file explorer window should open for you to drag and drop your firmware into.
> Source: Mechboards help email - 5 June 2026

Then run the flash command. 

If `qmk flash` doesn't auto-detect the drive, drag the generated
`ferris_sweep_ninjaPixel.uf2` onto the `RPI-RP2` volume manually.

