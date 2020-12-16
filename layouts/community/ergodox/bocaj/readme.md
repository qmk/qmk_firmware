# Overview

This is my personal Ergodox EZ configuration, and my daily driver.

Most of the code resides in my userspace and is heavily based upon [Drashna's work](https://github.com/qmk/qmk_firmware/tree/master/users/drashna)... although considerably slimmed down.

## How to build

Put simply:
`make ergodox_ez:bocaj`

On that note, I use a separate workspace when making changes to my layouts or userspace. In that repo, there is a tool that does this for me. See [JacobJerrell/qmk_layouts/tools/](https://github.com/JacobJerrell/qmk_layouts/tree/master/tools)

## Layers

* WORKMAN: No one uses this board but me and I've never had a reason to switch to QWERTY
* LOWER:
  * Left: Grave and navigation arrows
  * Right: Numpad
* RAISE:
  * Symbols across the top, F-Keys on the second row
* ADJUST
  * Audio control, make/reset/version macros
* MOD: mouse navigation

## Ergodox Specifics

I don't have the underglow or backlit versions so the 3 LEDs on the right board are used for layer indication if not on the base layer. If you're on the base layer, they're used for mod-key indicators.
