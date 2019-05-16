# qmk userspace for kuchosauronad0
Thanks to drashna and everyone else in the qmk_firmware/users/ directory :)

# Overview

## Keyboard Layout Templates
This borrows from @jola5's "Not quite neo" code. This allows me to maintain blocks of keymaps in the userspace, so that I can modify the userspace, and this is reflected in all of the keyboards that use it, at once.

This makes adding tap/hold mods, or other special keycodes or functions to all keyboards super easy, as it's done to all of them at once.

The caveat here is that the keymap needs a processor/wrapper, as it doesn't like the substitutions. However, this is as simple as just pushing it through a define. For instance:

`#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)`

Once that's been done and you've switched the keymaps to use the "wrapper", it will read the substitution blocks just fine.

Credit goes to @jola5 for first implementing this awesome idea.

## Custom Keycodes
Declared in `process_records.h` and `template.h` and defined in `process_record_user` in template.c 

## Tap Dances
Set `TAP_DANCE_ENABLE = yes` in rules.mk. See file tap_dances.{c,h}

## Leader Key
Set `LEADER_ENABLE = yes` in rules.mk.
TODO: document tmux / vim / os

## Unicode
TODO: Set `idk` in `idc`

## Diablo Layer
Currently not in use.

# Secret Macros
Set `NO_SECRETS = yes` in rules.mk.
