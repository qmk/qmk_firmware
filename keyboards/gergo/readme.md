# [Gergo! By g Heavy Industries](http://gboards.ca)

![Gergo image](https://4.bp.blogspot.com/-889nMXxgSM0/XCNxwnO5kUI/AAAAAAAA6mI/tZbWgZVCBW0dyZOCGJDkjN06DVax7j8XwCLcBGAs/s1600/48422820_967732713413298_485744639215665152_n.jpg)

Gergo uses the atmel-dfu loader, for flashing please install dfu-programmer for your system!

To build and flash your firmware:
  - download/clone the QMK repository
  - cd to the QMK directory
  - run "make gergo:germ"
  - Fix any errors you made hacking on your keymap
  - press the reset button when prompted

## Settings
You may want to enable QMK_KEYS_PER_SCAN because the Gergo has a relatively
slow scan rate. Other options can be defined in keyboards/gergo/rules.mk
