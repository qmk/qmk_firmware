# Rev 2

A 40% hotswap ortholinear RGB keyboard from KP Republic.

* **Revision 2: "single pcb"**  
* Keyboard Maintainer: [Var](https://github.com/itsvar8)
* Hardware Supported: CSTC40 rev2
* STM32F402RCT6 MCU with IS31FL3733 LED driver and using `stm32-dfu` bootloader. Integrated USB connection.
* Hardware Availability: kprepublic.com

Make example for this keyboard (after setting up your build environment):

    make kprepublic/cstc40/rev2:default

Flashing example for this keyboard:

    make kprepublic/cstc40/rev2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

The rev 2 uses pin `A10` in the key matrix, which apparently is a design flaw that may prevent the bootloader from entering the proper mode for DFU flashing - <https://docs.qmk.fm/#/platformdev_blackpill_f4x1?id=pins-to-be-avoided>. There is a simple workaround that works most of the time - press the pin key (generally the letter R) during the boot.
