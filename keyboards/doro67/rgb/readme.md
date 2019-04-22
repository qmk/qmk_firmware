# Doro67 RGB PCB

65% custom keyboard made by 80ultraman/Alf/Backprop Studios with in switch RGB featuring the same switch matrix and layout as the regular PCB. 

Flashing the regular PCB firmware on this board will work, but will disable RGB lighting. 

Keyboard Maintainer: [MechMerlin](https://github.com/mechmerlin)  
Hardware Supported: Doro 67 RGB PCB  
Hardware Availability: [Geekhack GB](https://geekhack.org/index.php?topic=97265.0)

Make example for this keyboard (after setting up your build environment):

    make doro67/rgb:default

**RGB Note:** The WS2812 string of LEDs starts from the `K00` key connected to pin `B7`  and is connected from left to right, top to bottom, following the physical layout of the board.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
