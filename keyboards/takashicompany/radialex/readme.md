# Radialex

![Radialex](https://github.com/takashicompany/radialex/blob/master/images/qmk.jpg?raw=true)

40% larger keyboard.  
The radial key layout allows you to place your hand in a natural position and move your fingers the shortest distance to type.  
Your iconic keys and keycaps can be placed in the center of the keyboard.  
It is possible to make it shine with LED backlighting.  
The keyswitches can also be replaced with MX sockets.  

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Pro Micro
* Hardware Availability: https://github.com/takashicompany/radialex

Make example for this keyboard (after setting up your build environment):

    make takashicompany/radialex:default

Flashing example for this keyboard:

    make takashicompany/radialex:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
