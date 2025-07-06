# Rev 3

A 40% hotswap ortholinear RGB keyboard from KP Republic.

* **Revision 3: "FXTwink single pcb"**  
* Keyboard Maintainer: [ClownFish](https://github.com/clownfish-og)
* Hardware Supported: CSTC40 rev3
* STM32F402RCT6 MCU without separate LED driver and using `tinyuf2` bootloader. Integrated USB connection.
* Hardware Availability: kprepublic.com

Make example for this keyboard (after setting up your build environment):

    make kprepublic/cstc40/rev3:default
    
Flashing example for this keyboard:

    make kprepublic/cstc40/rev3:default:flash
    
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
