# MelGeek Mach80

![Mach80](https://www.melgeek.com/collections/pcb-plate/products/melgeek-mach80-tkl87-hotswappable-rgb-pcba)

A hotswap 80% RGB Custom Mechanical keyboard.

* Keyboard Maintainer: [melgeek001365](https://github.com/melgeek001365)
* Hardware Supported: Mach80 rev1 20210819 
* Hardware Availability: [MelGeek](https://www.melgeek.com/)

Make example for this keyboard (after setting up your build environment):

    make melgeek/mach80/rev1:default
    
Enter the bootloader in 3 ways:  

**Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard * 
**Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead * 
**Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available *

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
