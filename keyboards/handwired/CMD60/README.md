CMD60 keyboard firmware
======================

##CMD60

This layout has been designed to optimize use of the left-hand, and it focussed specifically on programmers who work
with text editors like SublimeText and Atom. It utilizes the power of Space_fn, and features a caps lock swap for Fn2
and enter key on tap. These features allow you to keep your right hand on the mouse more and should enable you to
achieve a higher level of productivity if you take the time to learn its function layers.

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/docs/README.md).

## Building

Download or clone the whole firmware and navigate to the keyboards/handwired/CMD60 folder.
Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use
the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make`.

### Other Keymaps

To build the firmware binary hex file with a keymap just do `make` with `keymap` option like:

```
$ make keymap=[default|jack|<name>]
```

Keymaps follow the format **__keymap.c__** and are stored in folders in the `keymaps` folder, eg `keymaps/my_keymap/`
