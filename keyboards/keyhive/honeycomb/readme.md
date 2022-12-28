Honeycomb Keyboard Firmware
======================

These configuration files use a completely different 'matrix scan' system than other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the macropad - it also receives rotary encoder information from the macropad. The matrix.c file contains the code to poll the external microcontroller for the key matrix, and the keymap.c file contains example code for encoder use. As long as the relevant functions in these files are not changed, all other QMK features are supported.

## Building

Run the following command in your terminal:

```
make keyhive/honeycomb:default
# or use this to automatically flash the controller
make keyhive/honeycomb:default:avrdude
```

Follow the QMK guide for this or ask in Discord.

### Other Keymaps

Because this is a totally custom macropad, it is recommended that you copy the `default/` folder, rename it as desired, and modify the `keymap.c` to your liking.
