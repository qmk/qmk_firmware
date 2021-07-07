# Userspace - Draevin

## Notable Files

- [draevin.h](draevin.h) - Standard layers, keys, and tap dance key and config for all my boards
- [draevin.c](draevin.c) - Colemak/QWERTY switch, KC_MAKE, and Shift/CAPS TD
- [wrappers](wrappers.h) - QWERTY, Colemak, F Row, Num Row, and `_FN` layer layout wrappers

## Keymap themes

Some general ideas shared between my maps

- Colemak and QWERTY layouts
  - In wrappers
  - All are Colemak default with `CM_QW` switch
- Nav and punctuation `_FN` layer
  - In wrappers
  - Right hand home arrows
  - Pinky `HOME`/`END` for ***speed***
  - Inner grouping symbols to decrease reach
- Split space
  - Left thumb `MO(_FN)` is standard, but on the wrong side in the Quefrency map (silly soldering error, but not bad enough to fix)
    - Quefrency is still *technically* split though, right? `*<:^)`
- Re-organized right mods
  - Personal preference on wanting easier right thumb `CTRL`
- Real `DEL` key
  - I can't seem to get away from it with layering, so all my maps have a delete key
    - Sinc/Quefrency have it in the +5 column on the right
    - DZ60 has it in the split backspace
- `KC_MAKE`

## Keymaps

- [DZ60](../../keyboards/dz60/keymaps/draevin/keymap.c)
- [Sinc 80](../../keyboards/keebio/sinc/keymaps/draevin/keymap.c)
- [Quefrency 65 w/ Macro](../../keyboards/keebio/quefrency/keymaps/draevin/keymap.c)
  - Horribly under-utilized macro block because I thought I needed more keys than I actually do (so sad)
  - Left side volume and paging rotary
