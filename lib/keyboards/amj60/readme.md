AMJ60 keyboard firmware
======================
DIY/Assembled compact 60% keyboard.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/amj60
folder. Once your dev env is setup, you'll be able to type `make` to generate
your .hex - you can then use `make dfu` to program your PCB once you hit the
reset button. 

Depending on which keymap you would like to use, you will have to compile
slightly differently.

### Default
To build with the default keymap, simply run `make`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to
define your favorite layout yourself. To define your own keymap create file
named `<name>.c` in the keymaps folder, and see keymap document (you can find
in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with
`KEYMAP` option like:
``
$ make KEYMAP=[default|jack|<name>]
``
Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps`
folder.

## Variations
KEYMAP macros for the following layouts are available:

* default, for all the available, possible keys
* ANSI, for 60% ANSI keyboard
* ISO
* ISO w/ split right shift key
* HHKB

Remark: all but "ISO w/ split right shift key" are untested and were done to the best of my knowledge.

### Original tmk firmware
The original firmware that was used to port to qmk can be found [here](https://github.com/AMJKeyboard/AMJ60).

## Further information
Since information and documentation for this board are sparse, (at least for non-chinese speaking ppl) here is everything that could be found

* [geekhack discussion](https://geekhack.org/index.php?topic=53070.0)
* [chinese discussion](https://www.v2ex.com/t/161887)
* Board has [dedicated pinouts](https://i.imgur.com/D0sWhyh.jpg?1) for a bluetooth module
* has pins for external power [picture](https://i.imgur.com/00VrtIp.jpg?1).
* most information comes from [reddit](https://www.reddit.com/r/MechanicalKeyboards/comments/32oonr/gh60_pcb_for_your_custom_keyboard/)
