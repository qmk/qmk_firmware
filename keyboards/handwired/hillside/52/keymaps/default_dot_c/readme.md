# Default Hillside 48 Layout (in .c format)

This layout is for those who prefer defining their layout in a keymap.c,
  instead of graphically with a keymap.json.
It is also a little simpler than the default layout as it puts the numbers along the top row
  and has only four layers.

With this layout it is easy to test that all the switches and the configuration works
  by using a keyboard tester app,
  such as the [QMK Configurator](https://config.qmk.fm/#/test).
To test the board, connect the two halves and connect the left to the computer.
All the keys should produce output, except the two layer keys,
The LEDs should glow a nice red.

If you want to connect the right half to the computer,
  uncomment the define MASTER_RIGHT line in config.h.
