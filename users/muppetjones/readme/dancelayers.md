# Tap Dance Layers

This feature creates a key that changes the current layer via tap dance. By
default, this assumes that you have the following layers defined:

- `_ADJUST`
- `_LOWER`
- `_RAISE`
- `_MOUSE`

And sets up the following tap dance:

| Count | Action | Layer     |
| ----- | ------ | --------- |
| 1x    | hold   | `_ADJUST` |
| 1x    | tap    | `_MOUSE`  |
| 2x    | tap    | `_LOWER`  |
| 3x    | tap    | `_RAISE`  |
| 4x    | tap    | `_ADJUST` |

## Usage

> NOTE: If you use other tap-dance functions, you may require additonal setup.

1. Copy `features/dancelayers.{c,h}` into your keymap or userspace directory.
2. Add the following to your `rules.mk`

   ```
   TAP_DANCE_ENABLE = yes

   SRC += ./features/dancelayers.c
   ```

3. Add the following to your `keymap.c`:

   ```
   #ifdef TAP_DANCE_ENABLE
   #    include "features/dancelayers.h"
   #    define TD_LAYR TD(TD_LAYERS)
   #else
   #    define TD_LAYR XXXXXXX
   #endif
   ```

4. Add `TD_LYR` to your keymap.

## Functions and Enumerations

The following functions are available for use:

- `cur_dance`

The following tap dance enumerations are defined:

- `TD_1X_HOLD`
- `TD_1X_TAP`
- `TD_2X_TAP`
- `TD_3X_TAP`
- `TD_4X_TAP`

## Overriding the Defaults

If you want to define different layers to tap dance actions, you'll need to
define two additional functions in your `keymap.c`:

- `td_lyr_finished`
- `td_lyr_reset`

Both of these functions are necessary and require a certain pattern for each
layer. "Tap" actions are handled in `*_finished` while "hold" actions are
resolved in `*_finished` and `*_reset`.

See the implementation in `dancelayers.c` for an example.
