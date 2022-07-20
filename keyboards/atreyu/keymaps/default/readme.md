# Atreyu Keymap

The default keymap provided here is useful for testing and as a base
for your own mapping. It only includes basic layers and is missing many
keycodes. To build the default keymap:

make atreyu:default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
