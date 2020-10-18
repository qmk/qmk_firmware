# The Compose Key: Mnemonic shortcuts for your favorite strings

On many Linux systems, the Compose key lets you create shortcuts for interesting Unicode characters and strings. For example, to enter the Greek letter θ on a keyboard that doesn't support it, you might press `<COMPOSE> <g> <t> <h>`.

The Compose Key processor lets you do the same thing directly on your keyboard, so it'll work on your choice of OS.

# Setting up the Compose Key processor

1. Choose a key to use for your Compose Key. (Mod-Tap keys are not currently supported.) Assign it the keycode `COMPOSE`.
2. Include `COMPOSE_ENABLE = yes` in your `rules.mk`. To enable support for non-ANSI characters, include `UNICODE_ENABLE = yes` as well, and follow the [Unicode feature docs](feature_unicode.md) to set it up for your OS.
3. Define your compose sequences in a new file (e.g. `compose.conf`). For example:
    ```
# dongers
KC_S KC_H KC_R KC_U KC_G "¯\\_(ツ)_/¯"
KC_F KC_L KC_I KC_P "╯°□°)╯︵ ┻━┻"
KC_H KC_A KC_P KC_P KC_Y "ᕕ( ᐛ )ᕗ"
KC_Y KC_U KC_N KC_O "ლ(ಠ益ಠლ)"

# blackboard bold
KC_B KC_B KC_A "𝔸"
KC_B KC_B KC_B "𝔹"

# misc. symbols
KC_O KC_C "©"
KC_O KC_R "®"
KC_DOT KC_DOT "…" # ellipsis
```
    defines nine sequences, including e.g.: `COMPOSE-O-C` to type `©`, `COMPOSE-B-B-A` to type `𝔸`, and `COMPOSE-S-H-R-U-G` to type `¯\_(ツ)_/¯`.
4. Compile your sequences to C by running `bin/qmk compose path/to/your/compose.conf path/to/your/compose.h`.
5. Add `#include "compose.h"` to your `keymap.c`.
6. Recompile your firmware.

You can define as many sequences as you want, subject to firmware size restrictions. The author uses over a hundred sequences on a Gergo, so large configurations are definitely supported.