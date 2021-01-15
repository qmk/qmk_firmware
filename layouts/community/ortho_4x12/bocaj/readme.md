# Overview

This is my Planck EZ layout, heavily based upon [my ergodox layout](../../ergodox/bocaj/).

I got this keyboard for two reasons:

1. QMK spoiled me and the Ergodox isn't incredibly portable (ok 3 reasons)
2. This can sit ontop of my janky Macbook Pro keyboard (disabled with Karabiner if the planck is connected) when I want to work from the couch.

## How to Build

Put simply:
`make planck/ez:bocaj`

On that note, I use a separate workspace when making changes to my layouts or userspace. In that repo, there is a tool that does this for me. See [JacobJerrell/qmk_layouts/tools/](https://github.com/JacobJerrell/qmk_layouts/tree/master/tools) until I get documentation finished (Write code first, define requirements second... right?).

## Layers

* WORKMAN/QWERTY: Default is workman, can be switched via the ADJUST layer. Idk why you would though.
* LOWER: Nums across the top, switches enter key to tab and tab key to delete. Symbols in the middle, remenascent of the ergodox
* RAISE: Symbols across the top, F-Keys on the 2nd row. Switches backspace to delete
* ADJUST: Computer Audio controls, RGB controls, Sound controls, macros, etc.
* MOD: Mouse controls under the left hand. Numpad under the right hand