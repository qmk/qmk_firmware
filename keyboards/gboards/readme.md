# gBoards Monorepo

Ever wanted to do some crazy stuff with combos or onboard steno? Here's a big repo for you to include into your 
keymaps. You may need to do some configuration on your part, for the documentation hit up [docs.gboards.ca](http://docs.gboards.ca/)

## Building

You can find all of my keyboards under the k/ folder. Make with 

`make gboards/k/gergoplex:default:flash` or similar

## Configuration
Dictionaries are layered ontop of each other at compile time, you specify these in dicts.def and combos.def respectively.
This system allows the easy integration of other users combos and a simple way to break out combos by functionality. 

If you have a cool dictionary, please submit a PR against the respective directory!

## Combos
This is a set of dicts that templates macros ontop of QMK. Use this for augmenting your current setup with 
multi-chords! You can browse the available combo lists in combos/


## Engine
This is the onboard chording engine for all sorts of fun shenanigans. Be aware that this currently is a bit of a QMK 
replacement focused on pure chording. Take a look at the configuration in keyboards/ginny for ideas, all these dicts
are stored over in dicts/

## Installation
You will need to add the following bits to your rules.mk, refer to keyboards/ginny for a working example
`VPATH               +=  keyboards/gboards/`

And if you're using the chording engine, this as well.
`SRC                 +=  g/engine.c `

For combos, add `#include "g/keymap_combos.h"` to keymap.c to compile your combos.def into your keymap

For the chording engine, add `#include "g/keymap_engine.h"` to keymap.c compile your dicts.def into your keymap. If you
don't have a config_engine.h file for your keyboard, you will need to create it. (Once again, look at keyboards/ginny/
for a example of how to do this.
