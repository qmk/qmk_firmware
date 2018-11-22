# Maxipad

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme.md](/readme.md).

If you are using a pro micro then make sure to enable USE_PRO_MICRO in the makefile
Change the config.h pinout to match your mcu!!

Depending on which keymap you would like to use, you will have to compile slightly differently.

### Default

To build with the default keymap, simply run `make maxipad:default`.

### Other Keymaps
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `<name>.c` and see keymap document (you can find in top readme.md) and existent keymap files.
