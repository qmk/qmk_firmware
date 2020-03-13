KC60 (version 2.0) keyboard firmware
======================

## Quantum MK Firmware
For the full Quantum feature list, see [the parent readme.md](/readme.md).

## Building
Download or clone the whole firmware and navigate to the keyboards/kc60 folder. Once your dev env is setup, you'll be able to type `make` to generate your .hex - you can then use the Teensy Loader to program your .hex file.

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default
To build with the default keymap, simply run `make default`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` in the keymaps folder, and see keymap document (you can find in top readme.md) and existent keymap files.

To build the firmware binary hex file with a keymap just do `make` with a keymap like this:

```
$ make [default|jack|<name>]
```

Keymaps follow the format **__\<name\>.c__** and are stored in the `keymaps` folder.

## WS2812 Support

Build with WS2812 Support by running `make ws2812`.

## Warning
For those who want to use 2x1U instead of classic backspace you need to use K0D and K49 like this:
* K0D represents the key at the right of =.
* K49 represents the last key of the row (is wired at the right of the space key on the PCB)

In kc60.h I've put several definitions' examples of possible layouts proposed by online editor (http://123.57.250.164:9128/).
