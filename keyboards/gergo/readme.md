# Gergo! By g Heavy Industries

Gergo uses the atmel-dfu loader, for flashing please install dfu-programmer for your system!

To build your firmware:
  - download/clone the QMK repository
  - cd to the QMK directory
  - run "make gergo:germ:dfu"
  - Fix any errors you made hacking on your keymap
  - press the reset button when prompted

## Settings
You may want to enable QMK_KEYS_PER_SCAN because the Gergo has a relatively
slow scan rate. Other options can be defined in keyboards/gergo/rules.mk
