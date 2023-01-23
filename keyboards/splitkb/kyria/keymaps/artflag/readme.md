# Simple workman layout

## Features

- Workman layout
- semicolon and colon are flipped. Colon on tap, semicolon on double tap.

## Using the layout

1. Use https://config.qmk.fm/#/splitkb/kyria/rev2/LAYOUT to edit `workman-artflag.json`.

1. Convert to `keymap.c`:

   ```bash
   cd keyboards/splitkb/kyria/keymaps/ArtFlag
   qmk json2c workman-artflag.json > keymap.c
   cd ../../../../..
   ```

1. Git diff to bring back the code for tap dancing.
1. Compile and flash:

   ```bash
   qmk compile && qmk flash
   ```
   